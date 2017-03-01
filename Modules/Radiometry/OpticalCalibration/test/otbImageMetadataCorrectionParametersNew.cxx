/*=========================================================================

  Program:   ORFEO Toolbox
  Language:  C++


  Copyright (c) Centre National d'Etudes Spatiales. All rights reserved.
  See OTBCopyright.txt for details.


     This software is distributed WITHOUT ANY WARRANTY; without even
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
     PURPOSE.  See the above copyright notices for more information.

=========================================================================*/

#include "otbImageMetadataCorrectionParameters.h"

int otbImageMetadataCorrectionParametersNew(int itkNotUsed(argc), char * itkNotUsed(argv)[])
{
  typedef otb::ImageMetadataCorrectionParameters CorrectionParametersType;
  
  // Instantiating object
  CorrectionParametersType::Pointer objectAtmo = CorrectionParametersType::New();
  
  std::cout << objectAtmo << std::endl;
  
  return EXIT_SUCCESS;
}
