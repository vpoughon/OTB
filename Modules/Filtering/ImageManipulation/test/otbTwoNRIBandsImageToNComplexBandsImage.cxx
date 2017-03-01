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

#include "otbTwoNRIBandsImageToNComplexBandsImage.h"

#include "otbImage.h"
#include "otbVectorImage.h"
#include "otbImageFileReader.h"
#include "otbImageFileWriter.h"

int otbTwoNRIBandsImageToNComplexBandsImage(int itkNotUsed(argc), char * argv[])
{

  typedef double PixelType;
  typedef otb::VectorImage<PixelType,  2> InputImageType;
    
  typedef std::complex<double> OutputPixelType;
  typedef otb::VectorImage<OutputPixelType, 2> OutputImageType;
 
 
  typedef otb::TwoNRIBandsImageToNComplexBandsImage<InputImageType, OutputImageType> FilterType;
  typedef otb::ImageFileReader<InputImageType> ReaderType;
  typedef otb::ImageFileWriter<OutputImageType> WriterType;

  ReaderType::Pointer reader = ReaderType::New();
  FilterType::Pointer filter = FilterType::New();
  WriterType::Pointer writer = WriterType::New();
  
  
  reader->SetFileName(argv[1]);
  writer->SetFileName(argv[2]);

  filter->SetInput(0,reader->GetOutput());
  writer->SetInput(filter->GetOutput());
  writer->Update();



  return EXIT_SUCCESS;
}
