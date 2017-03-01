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

#include "otbLuminanceToImageImageFilter.h"
#include "otbVectorImage.h"

int otbLuminanceToImageImageFilterNew(int itkNotUsed(argc), char * itkNotUsed(argv)[])
{
  const unsigned int Dimension = 2;
  typedef double                                 PixelType;
  typedef otb::VectorImage<PixelType, Dimension> InputImageType;

  typedef otb::LuminanceToImageImageFilter<InputImageType, InputImageType> LuminanceToImageImageFilterType;

  // Instantiating object
  LuminanceToImageImageFilterType::Pointer filter = LuminanceToImageImageFilterType::New();

  std::cout << filter << std::endl;

  return EXIT_SUCCESS;
}
