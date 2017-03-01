/*=========================================================================

  Program:   ORFEO Toolbox
  Language:  C++


  Copyright (c) Centre National d'Etudes Spatiales. All rights reserved.
  See OTBCopyright.txt for details.


     This software is distributed WITHOUT ANY WARRANTY; without even
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
     PURPOSE.  See the above copyright notices for more information.

=========================================================================*/
#ifndef otbSharkRandomForestsMachineLearningModelFactory_txx
#define otbSharkRandomForestsMachineLearningModelFactory_txx


#include "otbSharkRandomForestsMachineLearningModelFactory.h"

#include "itkCreateObjectFunction.h"
#include "otbSharkRandomForestsMachineLearningModel.h"
#include "itkVersion.h"

namespace otb
{

template <class TInputValue, class TOutputValue>
SharkRandomForestsMachineLearningModelFactory<TInputValue,TOutputValue>
::SharkRandomForestsMachineLearningModelFactory()
{

  std::string classOverride = std::string("otbMachineLearningModel");
  std::string subclass = std::string("otbSharkRandomForestsMachineLearningModel");

  this->RegisterOverride(classOverride.c_str(),
                         subclass.c_str(),
                         "Shark RF ML Model",
                         1,
                         itk::CreateObjectFunction<SharkRandomForestsMachineLearningModel<TInputValue,TOutputValue> >::New());
}

template <class TInputValue, class TOutputValue>
SharkRandomForestsMachineLearningModelFactory<TInputValue,TOutputValue>
::~SharkRandomForestsMachineLearningModelFactory()
{
}

template <class TInputValue, class TOutputValue>
const char*
SharkRandomForestsMachineLearningModelFactory<TInputValue,TOutputValue>
::GetITKSourceVersion(void) const
{
  return ITK_SOURCE_VERSION;
}

template <class TInputValue, class TOutputValue>
const char*
SharkRandomForestsMachineLearningModelFactory<TInputValue,TOutputValue>
::GetDescription() const
{
  return "Shark Random Forest machine learning model factory";
}

} // end namespace otb

#endif
