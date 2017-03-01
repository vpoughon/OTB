/*=========================================================================

  Program:   ORFEO Toolbox
  Language:  C++


  Copyright (c) Centre National d'Etudes Spatiales. All rights reserved.
  See OTBCopyright.txt for details.


  This software is distributed WITHOUT ANY WARRANTY; without even
  the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
  PURPOSE.  See the above copyright notices for more information.

=========================================================================*/


#include "otbAttributesMapLabelObjectWithClassLabel.h"

int otbAttributesMapLabelObjectWithClassLabelNew(int itkNotUsed(argc), char * itkNotUsed(argv)[])
{
  typedef otb::AttributesMapLabelObjectWithClassLabel<unsigned short, 2, double, unsigned short> LabelObjectType;

  // instantiation
  LabelObjectType::Pointer object = LabelObjectType::New();

  std::cout << object << std::endl;

  return EXIT_SUCCESS;
}
