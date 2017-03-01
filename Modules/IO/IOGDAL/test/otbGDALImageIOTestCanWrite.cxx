/*=========================================================================

  Program:   ORFEO Toolbox
  Language:  C++


  Copyright (c) Centre National d'Etudes Spatiales. All rights reserved.
  See OTBCopyright.txt for details.


  This software is distributed WITHOUT ANY WARRANTY; without even
  the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
  PURPOSE.  See the above copyright notices for more information.

=========================================================================*/



#include "otbGDALImageIO.h"
#include "itkMacro.h"
#include <iostream>

int otbGDALImageIOTestCanWrite(int itkNotUsed(argc), char* argv[])
{
  otb::GDALImageIO::Pointer lGDALImageIO = otb::GDALImageIO::New();
  bool                      lCanWrite = lGDALImageIO->CanWriteFile(argv[1]);
  if (lCanWrite == false)
    {
    std::cerr << "Erreur otb::GDALImageIO : impossible d'ecrire l'image " << argv[1] << "." << std::endl;
    return EXIT_FAILURE;
    }

  return EXIT_SUCCESS;
}
