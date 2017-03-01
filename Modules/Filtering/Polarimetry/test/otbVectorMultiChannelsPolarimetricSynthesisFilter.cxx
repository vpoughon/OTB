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
#include "otbVectorImage.h"
#include "otbImageFileReader.h"
#include "otbImageFileWriter.h"
#include "otbMultiChannelsPolarimetricSynthesisFilter.h"

int otbVectorMultiChannelsPolarimetricSynthesisFilter(int itkNotUsed(argc), char * argv[])
{
  const char * inputFilename  = argv[1];
  const char * outputFilename = argv[2];

  double PsiI = strtod(argv[3], ITK_NULLPTR);
  double KhiI = strtod(argv[4], ITK_NULLPTR);
  double PsiR = strtod(argv[5], ITK_NULLPTR);
  double KhiR = strtod(argv[6], ITK_NULLPTR);

  typedef std::complex <double> InputPixelType;
  typedef double                OutputPixelType;
  const unsigned int Dimension = 2;
  typedef otb::VectorImage<InputPixelType,  Dimension>                                   InputImageType;
  typedef otb::Image<OutputPixelType, Dimension>                                         OutputImageType;
  typedef otb::ImageFileReader<InputImageType>                                           ReaderType;
  typedef otb::ImageFileWriter<OutputImageType>                                          WriterType;
  typedef otb::MultiChannelsPolarimetricSynthesisFilter<InputImageType, OutputImageType> FilterType;

  FilterType::Pointer polarimetricSynthesis = FilterType::New();

  polarimetricSynthesis->SetPsiI(PsiI);
  polarimetricSynthesis->SetKhiI(KhiI);
  polarimetricSynthesis->SetPsiR(PsiR);
  polarimetricSynthesis->SetKhiR(KhiR);
  polarimetricSynthesis->SetEmissionH(true);
  polarimetricSynthesis->SetEmissionV(true);

  ReaderType::Pointer reader = ReaderType::New();
  WriterType::Pointer writer = WriterType::New();

  reader->SetFileName(inputFilename);
  writer->SetFileName(outputFilename);

  polarimetricSynthesis->SetInput(reader->GetOutput());
  writer->SetInput(polarimetricSynthesis->GetOutput());

  writer->Update();

  return EXIT_SUCCESS;
}
