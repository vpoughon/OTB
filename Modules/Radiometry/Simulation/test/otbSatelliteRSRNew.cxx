/*=========================================================================

  Program:   ORFEO Toolbox
  Language:  C++


  Copyright (c) Centre National d'Etudes Spatiales. All rights reserved.
  See OTBCopyright.txt for details.


  This software is distributed WITHOUT ANY WARRANTY; without even
  the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
  PURPOSE.  See the above copyright notices for more information.

=========================================================================*/

#include "otbMacro.h"

#include "otbSatelliteRSR.h"

int otbSatelliteRSRNew(int itkNotUsed(argc), char * itkNotUsed(argv)[])
{
  typedef otb::SatelliteRSR< double, double>  ResponseType;
  typedef ResponseType::Pointer  ResponsePointerType;


  //Instantiation
  ResponsePointerType  myResponse=ResponseType::New();

  return EXIT_SUCCESS;
}
