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
#include "otbSOMMap.h"
#include "otbPeriodicSOM.h"
#include "itkRGBPixel.h"
#include "itkListSample.h"

int otbPeriodicSOMNew(int itkNotUsed(argc), char * itkNotUsed(argv) [])
{
  const unsigned int Dimension = 2;
  typedef float                                           ComponentType;
  typedef itk::VariableLengthVector<ComponentType>        PixelType;
  typedef itk::Statistics::EuclideanDistanceMetric<PixelType>   DistanceType;
  typedef otb::SOMMap<PixelType, DistanceType, Dimension> SOMMapType;
  //     typedef itk::Statistics::ImageToListAdaptor<SOMMapType> AdaptorType;
  typedef itk::Statistics::ListSample<PixelType>       ListSampleType;
  typedef otb::PeriodicSOM<ListSampleType, SOMMapType> SOMType;

  // Instantiation
  SOMType::Pointer som = SOMType::New();

  std::cout << som << std::endl;

  return EXIT_SUCCESS;
}
