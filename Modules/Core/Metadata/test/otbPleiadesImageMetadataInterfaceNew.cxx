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

#include "otbPleiadesImageMetadataInterface.h"

int otbPleiadesImageMetadataInterfaceNew(int itkNotUsed(argc), char * itkNotUsed(argv) [])
{
  otb::PleiadesImageMetadataInterface::Pointer object = otb::PleiadesImageMetadataInterface::New();

  std::cout << object << std::endl;

  return EXIT_SUCCESS;
}
