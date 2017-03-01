/*=========================================================================

  Program:   ORFEO Toolbox
  Language:  C++


  Copyright (c) Centre National d'Etudes Spatiales. All rights reserved.
  See OTBCopyright.txt for details.


  This software is distributed WITHOUT ANY WARRANTY; without even
  the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
  PURPOSE.  See the above copyright notices for more information.

=========================================================================*/



#include "otbImage.h"
#include "itkMacro.h"
#include <iostream>
#include "itkUnaryFunctorImageFilter.h"
#include "itkComplexToModulusImageFilter.h"
#include "itkStreamingImageFilter.h"
#include "otbImageFileReader.h"
#include "otbImageFileWriter.h"

int otbImageFileWriterStreamingONERAComplex(int itkNotUsed(argc), char* argv[])
{
  // Verify the number of parameters in the command line
  const char * inputFilename  = argv[1];
  const char * outputFilename = argv[2];

  typedef std::complex<float> PixelType;
  const unsigned int Dimension = 2;

  typedef otb::Image<PixelType,  Dimension> ImageType;

  typedef otb::ImageFileReader<ImageType>          ReaderType;
  typedef otb::ImageFileWriter<ImageType> WriterType;

  ReaderType::Pointer complexReader = ReaderType::New();
  WriterType::Pointer complexWriter = WriterType::New();

  complexReader->SetFileName(inputFilename);

  complexWriter->SetNumberOfDivisionsStrippedStreaming(100);
  complexWriter->SetFileName(outputFilename);
  complexWriter->SetInput(complexReader->GetOutput());

  complexWriter->Update();

  return EXIT_SUCCESS;
}
