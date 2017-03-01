/*=========================================================================

  Program:   ORFEO Toolbox
  Language:  C++


  Copyright (c) Centre National d'Etudes Spatiales. All rights reserved.
  See OTBCopyright.txt for details.


  This software is distributed WITHOUT ANY WARRANTY; without even
  the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
  PURPOSE.  See the above copyright notices for more information.

=========================================================================*/



#include "otbScalarBufferToImageFileWriter.h"


int otbScalarBufferToImageFileWriterNew(int itkNotUsed(argc), char * itkNotUsed(argv) [])
{
  typedef otb::ScalarBufferToImageFileWriter<int, double> FilterType;
  FilterType::Pointer filter = FilterType::New();

  return EXIT_SUCCESS;
}
