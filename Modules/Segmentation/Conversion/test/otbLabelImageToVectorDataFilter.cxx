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



#include "otbLabelImageToVectorDataFilter.h"
#include "otbImage.h"
#include "otbImageFileReader.h"
#include "otbVectorDataFileWriter.h"

int otbLabelImageToVectorDataFilter(int argc, char * argv[])
{
  if (argc != 3)
    {
    std::cerr << "Usage: " << argv[0];
    std::cerr << " inputLabelImageFile outputVectorfile(shp)" << std::endl;
    return EXIT_FAILURE;
    }
  const char * infname = argv[1];
  const char * outfname = argv[2];


  const unsigned int Dimension = 2;
  typedef unsigned short LabelType;
  typedef otb::Image<LabelType, Dimension> InputLabelImageType;

  typedef otb::LabelImageToVectorDataFilter<InputLabelImageType>   FilterType;
  typedef otb::ImageFileReader<InputLabelImageType>                LabelImageReaderType;
  typedef FilterType::VectorDataType                               VectorDataType;
  typedef otb::VectorDataFileWriter<VectorDataType>                WriterType;

  FilterType::Pointer filter = FilterType::New();
  LabelImageReaderType::Pointer reader = LabelImageReaderType::New();
  WriterType::Pointer  writer = WriterType::New();

  reader->SetFileName(infname);

  filter->SetInput(reader->GetOutput());
  filter->SetUse8Connected(false);

  writer->SetFileName(outfname);
  writer->SetInput(filter->GetOutput());
  writer->Update();

  return EXIT_SUCCESS;
}
