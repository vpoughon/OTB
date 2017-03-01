/*=========================================================================

  Program:   ORFEO Toolbox
  Language:  C++


  Copyright (c) Centre National d'Etudes Spatiales. All rights reserved.
  See OTBCopyright.txt for details.


  This software is distributed WITHOUT ANY WARRANTY; without even
  the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
  PURPOSE.  See the above copyright notices for more information.

=========================================================================*/

#include "otbMacro.h"


#include "otbSpatialisationFilter.h"
#include "otbAttributesMapLabelObject.h"

int otbSpatialisationTestNew(int itkNotUsed(argc), char * itkNotUsed(argv)[])
{
  typedef unsigned short LabelType;
  const unsigned int Dimension = 2;
  typedef otb::AttributesMapLabelObject<LabelType, Dimension, std::string>    LabelObjectType;
  typedef itk::LabelMap<LabelObjectType>                                      LabelMapType;
  typedef otb::SpatialisationFilter<LabelMapType>                             FilterType;

  FilterType::Pointer filter = FilterType::New();

  return EXIT_SUCCESS;
}
