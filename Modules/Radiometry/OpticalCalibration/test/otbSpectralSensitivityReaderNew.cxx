/*=========================================================================

  Program:   ORFEO Toolbox
  Language:  C++


  Copyright (c) Centre National d'Etudes Spatiales. All rights reserved.
  See OTBCopyright.txt for details.


     This software is distributed WITHOUT ANY WARRANTY; without even
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
     PURPOSE.  See the above copyright notices for more information.

=========================================================================*/

#include "otbSpectralSensitivityReader.h"

using namespace otb;

int otbSpectralSensitivityReaderNew(int itkNotUsed(argc), char * itkNotUsed(argv) [])
{

  SpectralSensitivityReader::Pointer spectSen = SpectralSensitivityReader::New();

  std::cout << spectSen << std::endl;

  return EXIT_SUCCESS;
}
