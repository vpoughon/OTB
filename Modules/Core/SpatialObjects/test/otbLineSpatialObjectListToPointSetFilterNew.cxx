/*=========================================================================

  Program:   ORFEO Toolbox
  Language:  C++


  Copyright (c) Centre National d'Etudes Spatiales. All rights reserved.
  See OTBCopyright.txt for details.


  This software is distributed WITHOUT ANY WARRANTY; without even
  the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
  PURPOSE.  See the above copyright notices for more information.

=========================================================================*/



#include "itkPointSet.h"
#include <iostream>

#include "otbLineSpatialObjectListToPointSetFilter.h"

int otbLineSpatialObjectListToPointSetFilterNew(int itkNotUsed(argc), char * itkNotUsed(argv) [])
{
  typedef float                         InputPixelType;
  typedef otb::LineSpatialObjectList    LinesListType;
  typedef itk::PointSet<InputPixelType> PointSetType;

  typedef otb::LineSpatialObjectListToPointSetFilter<LinesListType,
      PointSetType>   FilterType;

  FilterType::Pointer filter = FilterType::New();

  std::cout << filter << std::endl;

  return EXIT_SUCCESS;
}
