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

#include "otbRAndGAndNIRIndexImageFilter.h"
#include "otbImage.h"

int otbRAndGAndNIRVegetationIndexImageFilterNew(int itkNotUsed(argc), char * itkNotUsed(argv)[])
{
  const unsigned int Dimension = 2;
  typedef unsigned char                    PixelType;
  typedef otb::Image<PixelType, Dimension> InputRImageType;
  typedef otb::Image<PixelType, Dimension> InputGImageType;
  typedef otb::Image<PixelType, Dimension> InputNIRImageType;
  typedef otb::Image<PixelType, Dimension> OutputImageType;

  typedef otb::RAndGAndNIRIndexImageFilter<InputRImageType, InputGImageType, InputNIRImageType,
      OutputImageType> RAndGAndNIRIndexImageFilterType;

  // Instantiating object
  RAndGAndNIRIndexImageFilterType::Pointer filter = RAndGAndNIRIndexImageFilterType::New();

  std::cout << filter << std::endl;

  return EXIT_SUCCESS;
}
