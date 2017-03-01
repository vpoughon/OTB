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

#include "otbNonMaxRemovalByDirectionFilter.h"
#include "otbImage.h"

int otbNonMaxRemovalByDirectionFilterNew(int itkNotUsed(argc), char * itkNotUsed(argv) [])
{
  const unsigned int Dimension = 2;
  typedef double                                                               PixelType;
  typedef otb::Image<PixelType, Dimension>                                     ImageType;
  typedef otb::NonMaxRemovalByDirectionFilter<ImageType, ImageType, ImageType> NonMaxRemovalByDirectionFilterType;

  // Instantiating object
  NonMaxRemovalByDirectionFilterType::Pointer filter = NonMaxRemovalByDirectionFilterType::New();

  std::cout << filter << std::endl;

  return EXIT_SUCCESS;
}
