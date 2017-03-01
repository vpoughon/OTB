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

#include "otbImage.h"
#include "otbVectorImage.h"
#include "otbImageFileReader.h"
#include "otbImageFileWriter.h"
#include "otbReciprocalHAlphaImageFilter.h"
#include "itkMeanImageFilter.h"
#include "otbPerBandVectorImageFilter.h"
#include "otbSinclairReciprocalImageFilter.h"
#include "otbSinclairToReciprocalCoherencyMatrixFunctor.h"


int otbReciprocalHAlphaImageFilter(int itkNotUsed(argc), char * argv[])
{
  const char * inputFilenameHH = argv[1];
  const char * inputFilenameHV = argv[2];
  const char * inputFilenameVV = argv[3];
  int size = atoi(argv[4]);
  const char * outputFilename = argv[5];


  typedef std::complex<double>  ComplexPixelType;
  const unsigned int Dimension = 2;


  typedef otb::Image<ComplexPixelType, Dimension>  	   ComplexImageType;
  typedef otb::VectorImage<ComplexPixelType, Dimension>  ComplexVectorImageType;
  typedef otb::VectorImage<double, Dimension>          RealVectorImageType;



  typedef otb::ImageFileReader<ComplexImageType>  ReaderType;
  typedef otb::ImageFileWriter<RealVectorImageType> WriterType;
  
  
  typedef otb::SinclairReciprocalImageFilter<ComplexImageType, ComplexImageType, ComplexImageType, ComplexVectorImageType, 
  otb::Functor::SinclairToReciprocalCovarianceMatrixFunctor<ComplexImageType::PixelType,
                                    ComplexImageType::PixelType,
                                    ComplexImageType::PixelType,
                                    ComplexVectorImageType::PixelType> > SinclairToCovFilterType;
  
  
  typedef itk::MeanImageFilter<ComplexImageType, ComplexImageType>         MeanFilterType;
  typedef otb::PerBandVectorImageFilter<ComplexVectorImageType, ComplexVectorImageType, MeanFilterType> PerBandMeanFilterType;
  
  
  typedef otb::ReciprocalHAlphaImageFilter<ComplexVectorImageType, RealVectorImageType> HAlphaFilterType;
  
  

  ReaderType::Pointer readerHH = ReaderType::New();
  ReaderType::Pointer readerHV = ReaderType::New();
  ReaderType::Pointer readerVV = ReaderType::New();
  
  WriterType::Pointer writer = WriterType::New();

  SinclairToCovFilterType::Pointer sinclairtocov = SinclairToCovFilterType::New();
  PerBandMeanFilterType::Pointer perBand = PerBandMeanFilterType::New();
  HAlphaFilterType::Pointer haafilter = HAlphaFilterType::New();
        
  
  MeanFilterType::InputSizeType radius;
  radius.Fill( size );
  perBand->GetFilter()->SetRadius(radius);
 
 
  readerHH->SetFileName(inputFilenameHH);
  readerHV->SetFileName(inputFilenameHV);
  readerVV->SetFileName(inputFilenameVV);
  
  sinclairtocov->SetInputHH(readerHH->GetOutput());
  sinclairtocov->SetInputHV_VH(readerHV->GetOutput());
  sinclairtocov->SetInputVV(readerVV->GetOutput());
 
  perBand->SetInput(sinclairtocov->GetOutput());
  
  haafilter->SetInput(perBand->GetOutput());

  writer->SetFileName(outputFilename);
  writer->SetInput(haafilter->GetOutput());
  writer->Update();

  return EXIT_SUCCESS;
}
