/*
 * Copyright (C) 2005-2016 Centre National d'Etudes Spatiales (CNES)
 *
 * This file is part of Orfeo Toolbox
 *
 *     https://www.orfeo-toolbox.org/
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include "itkMacro.h"

#include "itkUnaryFunctorImageFilter.h"
#include "otbImage.h"
#include "otbVectorImage.h"
#include "otbImageFileReader.h"
#include "otbImageFileWriter.h"
#include "otbBuiltUpIndicesFunctor.h"

int otbNDBIMultiChannelTM4AndTM5IndexImageFilter(int itkNotUsed(argc), char * argv[])
{
  const unsigned int Dimension = 2;
  typedef otb::VectorImage<double, Dimension>   InputImageType;
  typedef otb::Image<double, Dimension>         OutputImageType;
  typedef otb::ImageFileReader<InputImageType>  ReaderType;
  typedef otb::ImageFileWriter<OutputImageType> WriterType;
  typedef otb::Functor::NDBI <InputImageType::InternalPixelType,
      InputImageType::InternalPixelType,
      OutputImageType::PixelType> FunctorType;

  typedef itk::UnaryFunctorImageFilter<InputImageType, OutputImageType, FunctorType>
  UnaryFunctorImageFilterType;

  // Instantiating object
  UnaryFunctorImageFilterType::Pointer filter = UnaryFunctorImageFilterType::New();
  ReaderType::Pointer                  reader = ReaderType::New();
  WriterType::Pointer                  writer = WriterType::New();

  const char * inputFilename  = argv[1];
  const char * outputFilename = argv[2];

  unsigned int tm4Channel(::atoi(argv[3]));
  unsigned int tm5Channel(::atoi(argv[4]));

  reader->SetFileName(inputFilename);
  writer->SetFileName(outputFilename);
  filter->GetFunctor().SetIndex1(tm4Channel);
  filter->GetFunctor().SetIndex2(tm5Channel);
  //filter->GetFunctor().SetTM5Index(tm5Channel);
  //filter->GetFunctor().SetTM4Index(tm4Channel);
  filter->SetInput(reader->GetOutput());

  writer->SetInput(filter->GetOutput());
  writer->Update();

  return EXIT_SUCCESS;
}
