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
#include "otbSOM.h"
#include "otbSOMActivationBuilder.h"
#include "itkListSample.h"
#include "otbImage.h"

int otbSOMActivationBuilderNew(int itkNotUsed(argc), char * itkNotUsed(argv) [])
{
  const unsigned int Dimension = 2;
  typedef float                                         ComponentType;
  typedef unsigned char                                 OutputPixelType;
  typedef itk::VariableLengthVector<ComponentType>      PixelType;
  typedef itk::Statistics::EuclideanDistanceMetric<PixelType> DistanceType;

  typedef otb::SOMMap<PixelType, DistanceType, Dimension>                     MapType;

  typedef itk::Statistics::ListSample<PixelType>                              ListSampleType;
  typedef otb::Image<OutputPixelType, Dimension>                              OutputImageType;
  typedef otb::SOMActivationBuilder<ListSampleType, MapType, OutputImageType> SOMActivationBuilderType;

  // Instantiation
  SOMActivationBuilderType::Pointer somAct = SOMActivationBuilderType::New();

  std::cout << somAct << std::endl;

  return EXIT_SUCCESS;
}
