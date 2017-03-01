/*=========================================================================

  Program:   ORFEO Toolbox
  Language:  C++


  Copyright (c) Centre National d'Etudes Spatiales. All rights reserved.
  See OTBCopyright.txt for details.


  This software is distributed WITHOUT ANY WARRANTY; without even
  the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
  PURPOSE.  See the above copyright notices for more information.

=========================================================================*/



#include "itkMacro.h"
#include <iostream>

#include "otbImage.h"
#include "otbImageFileReader.h"
#include "otbImageFileWriter.h"
#include "otbAsymmetricFusionOfLineDetectorImageFilter.h"

int otbAsymmetricFusionOfLineDetector(int itkNotUsed(argc), char * argv[])
{
  const char * inputFilename  = argv[1];
  const char * outputFilename = argv[2];

  // Width of the linear feature = 2*WidthLine+1
  unsigned int WidthLine((unsigned int) ::atoi(argv[3]));
  // Length of the linear feature = 2*LengthLine+1
  unsigned int LengthLine((unsigned int) ::atoi(argv[4]));

  typedef unsigned char InputPixelType;
  typedef double        OutputPixelType;
  const unsigned int Dimension = 2;

  typedef otb::Image<InputPixelType,  Dimension> InputImageType;
  typedef otb::Image<OutputPixelType, Dimension> OutputImageType;
  typedef otb::Image<OutputPixelType, Dimension> OutputImageDirectionType;

  typedef otb::ImageFileReader<InputImageType>  ReaderType;
  typedef otb::ImageFileWriter<OutputImageType> WriterType;

  typedef itk::LinearInterpolateImageFunction<InputImageType, double> InterpolatorType;

  typedef otb::AsymmetricFusionOfLineDetectorImageFilter<InputImageType, OutputImageType, OutputImageDirectionType,
      InterpolatorType> FilterType;

  FilterType::Pointer FilterAssSymSum = FilterType::New();

  FilterAssSymSum->SetWidthLine(WidthLine);
  FilterAssSymSum->SetLengthLine(LengthLine);

  ReaderType::Pointer reader = ReaderType::New();
  WriterType::Pointer writer = WriterType::New();

  reader->SetFileName(inputFilename);
  writer->SetFileName(outputFilename);

  FilterAssSymSum->SetInput(reader->GetOutput());
  writer->SetInput(FilterAssSymSum->GetOutput());

  writer->Update();

  return EXIT_SUCCESS;
}
