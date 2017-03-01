/*=========================================================================

  Program:   ORFEO Toolbox
  Language:  C++


  Copyright (c) Centre National d'Etudes Spatiales. All rights reserved.
  See OTBCopyright.txt for details.


  This software is distributed WITHOUT ANY WARRANTY; without even
  the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
  PURPOSE.  See the above copyright notices for more information.

=========================================================================*/



#include "otbImageIOFactory.h"
#include "itkMacro.h"
#include <iostream>

int otbImageIOFactoryNew(int itkNotUsed(argc), char * itkNotUsed(argv) [])
{
  otb::ImageIOFactory *lImageIOFactory;
  lImageIOFactory = ITK_NULLPTR;
  return lImageIOFactory != ITK_NULLPTR; //to avoid unused variable warning
}
