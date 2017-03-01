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

#include "otbMapProjections.h"

int otbProjectionBaseNew(int itkNotUsed(argc), char * itkNotUsed(argv)[])
{
  otb::AlbersInverseProjection::Pointer      lAlbersProjection = otb::AlbersInverseProjection::New();
  otb::AzimEquDistForwardProjection::Pointer lAzimEquDistProjection = otb::AzimEquDistForwardProjection::New();

  return EXIT_SUCCESS;
}
