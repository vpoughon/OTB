/*=========================================================================

  Program:   ORFEO Toolbox
  Language:  C++


  Copyright (c) Centre National d'Etudes Spatiales. All rights reserved.
  See OTBCopyright.txt for details.


  This software is distributed WITHOUT ANY WARRANTY; without even
  the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
  PURPOSE.  See the above copyright notices for more information.

=========================================================================*/


#include "otbAttributesMapLabelObject.h"
#include "itkLabelMap.h"
#include "otbShapeAttributesLabelMapFilter.h"

int otbShapeAttributesLabelMapFilterNew(int itkNotUsed(argc), char * itkNotUsed(argv)[])
{
  typedef otb::AttributesMapLabelObject<unsigned short, 2, double> LabelObjectType;
  typedef itk::LabelMap<LabelObjectType>                         LabelMapType;
  typedef otb::ShapeAttributesLabelMapFilter<LabelMapType>       LabelMapFilterType;

  // instantiation
  LabelMapFilterType::Pointer filter = LabelMapFilterType::New();

  std::cout << filter << std::endl;

  return EXIT_SUCCESS;
}
