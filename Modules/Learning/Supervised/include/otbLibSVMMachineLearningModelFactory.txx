/*=========================================================================

  Program:   ORFEO Toolbox
  Language:  C++


  Copyright (c) Centre National d'Etudes Spatiales. All rights reserved.
  See OTBCopyright.txt for details.


     This software is distributed WITHOUT ANY WARRANTY; without even
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
     PURPOSE.  See the above copyright notices for more information.

=========================================================================*/
#ifndef otbLibSVMMachineLearningModelFactory_txx
#define otbLibSVMMachineLearningModelFactory_txx

#include "otbLibSVMMachineLearningModelFactory.h"

#include "itkCreateObjectFunction.h"
#include "otbLibSVMMachineLearningModel.h"
#include "itkVersion.h"

namespace otb
{

template <class TInputValue, class TOutputValue>
LibSVMMachineLearningModelFactory<TInputValue,TOutputValue>
::LibSVMMachineLearningModelFactory()
{

  std::string classOverride = std::string("otbMachineLearningModel");
  std::string subclass = std::string("otbLibSVMMachineLearningModel");

  this->RegisterOverride(classOverride.c_str(),
                         subclass.c_str(),
                         "LibSVM ML Model",
                         1,
                         itk::CreateObjectFunction<LibSVMMachineLearningModel<TInputValue,TOutputValue> >::New());
}

template <class TInputValue, class TOutputValue>
LibSVMMachineLearningModelFactory<TInputValue,TOutputValue>
::~LibSVMMachineLearningModelFactory()
{
}

template <class TInputValue, class TOutputValue>
const char*
LibSVMMachineLearningModelFactory<TInputValue,TOutputValue>
::GetITKSourceVersion(void) const
{
  return ITK_SOURCE_VERSION;
}

template <class TInputValue, class TOutputValue>
const char*
LibSVMMachineLearningModelFactory<TInputValue,TOutputValue>
::GetDescription() const
{
  return "LibSVM machine learning model factory";
}

} // end namespace otb

#endif
