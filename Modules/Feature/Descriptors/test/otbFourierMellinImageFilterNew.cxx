/*=========================================================================

  Program:   ORFEO Toolbox
  Language:  C++


  Copyright (c) Centre National d'Etudes Spatiales. All rights reserved.
  See OTBCopyright.txt for details.


  This software is distributed WITHOUT ANY WARRANTY; without even
  the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
  PURPOSE.  See the above copyright notices for more information.

=========================================================================*/



#include "otbForwardFourierMellinTransformImageFilter.h"

int otbFourierMellinImageFilterNew(int itkNotUsed(argc), char* itkNotUsed(argv) [])
{

  typedef double PixelType;
  const unsigned int Dimension = 2;

  typedef otb::Image<PixelType, Dimension> InputImageType;

  typedef itk::LinearInterpolateImageFunction<InputImageType, double> InterpolatorType;
  typedef otb::ForwardFourierMellinTransformImageFilter<PixelType,
      InterpolatorType, Dimension>       FourierMellinTransformType;

  FourierMellinTransformType::Pointer filter = FourierMellinTransformType::New();

  std::cout << filter << std::endl;

  return EXIT_SUCCESS;
}
