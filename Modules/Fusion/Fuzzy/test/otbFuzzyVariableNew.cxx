/*=========================================================================

  Program:   ORFEO Toolbox
  Language:  C++


  Copyright (c) Centre National d'Etudes Spatiales. All rights reserved.
  See OTBCopyright.txt for details.


  This software is distributed WITHOUT ANY WARRANTY; without even
  the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
  PURPOSE.  See the above copyright notices for more information.

=========================================================================*/


#include "otbFuzzyVariable.h"

int otbFuzzyVariableNew(int itkNotUsed(argc), char * itkNotUsed(argv)[])
{
  typedef float PrecisionType;
  typedef unsigned short LabelType;
  typedef otb::FuzzyVariable<LabelType, PrecisionType> FuzzyVarType;

  FuzzyVarType::Pointer fv = FuzzyVarType::New();

  return EXIT_SUCCESS;
}
