/*=========================================================================

  Program:   ORFEO Toolbox
  Language:  C++


  Copyright (c) Centre National d'Etudes Spatiales. All rights reserved.
  See OTBCopyright.txt for details.


     This software is distributed WITHOUT ANY WARRANTY; without even
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
     PURPOSE.  See the above copyright notices for more information.

=========================================================================*/


#include <iostream>

#include "otbGenericRSTransform.h"

int otbGenericRSTransformNew(int itkNotUsed(argc), char * itkNotUsed(argv)[])
{

  typedef otb::GenericRSTransform<> TransformType;
  TransformType::Pointer transform = TransformType::New();

  std::cout << transform << std::endl;

  return EXIT_SUCCESS;
}
