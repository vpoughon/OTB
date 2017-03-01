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
#include "otbFillGapsFilter.h"

int otbFillGapsFilterNew(int itkNotUsed(argc), char * itkNotUsed(argv) [])
{
  typedef otb::FillGapsFilter FillGapsFilterType;
  FillGapsFilterType::Pointer filter = FillGapsFilterType::New();

  std::cout << filter << std::endl;

  return EXIT_SUCCESS;
}
