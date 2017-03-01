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

#include "otbRAndNIRIndexImageFilter.h"
#include "otbImage.h"
#include "otbImage.h"

int otbRAndNIRVegetationIndexImageFilterNew(int itkNotUsed(argc), char * itkNotUsed(argv)[])
{
  const unsigned int Dimension = 2;
  typedef unsigned char                    PixelType;
  typedef otb::Image<PixelType, Dimension> InputRImageType;
  typedef otb::Image<PixelType, Dimension> InputNIRImageType;
  typedef otb::Image<PixelType, Dimension> OutputImageType;

  typedef otb::RAndNIRIndexImageFilter<InputRImageType, InputNIRImageType, OutputImageType> RAndNIRIndexImageFilterType;

  // Instantiating object
  RAndNIRIndexImageFilterType::Pointer filter = RAndNIRIndexImageFilterType::New();

  std::cout << filter << std::endl;

  return EXIT_SUCCESS;
}
