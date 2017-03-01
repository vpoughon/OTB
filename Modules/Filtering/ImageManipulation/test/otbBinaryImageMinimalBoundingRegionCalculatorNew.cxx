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
#include "otbImage.h"
#include "otbBinaryImageMinimalBoundingRegionCalculator.h"

int otbBinaryImageMinimalBoundingRegionCalculatorNew(int itkNotUsed(argc), char * itkNotUsed(argv) [])
{
  const unsigned int Dimension = 2;

  typedef unsigned char                    PixelType;
  typedef otb::Image<PixelType, Dimension> ImageType;
  typedef otb::BinaryImageMinimalBoundingRegionCalculator<ImageType>
  BoundingRegionCalculatorType;

  //Instantiation
  BoundingRegionCalculatorType::Pointer brct = BoundingRegionCalculatorType::New();

  std::cout << brct << std::endl;

  return EXIT_SUCCESS;
}
