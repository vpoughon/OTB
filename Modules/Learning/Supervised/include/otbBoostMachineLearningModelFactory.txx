/*=========================================================================

  Program:   ORFEO Toolbox
  Language:  C++


  Copyright (c) Centre National d'Etudes Spatiales. All rights reserved.
  See OTBCopyright.txt for details.


     This software is distributed WITHOUT ANY WARRANTY; without even
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
     PURPOSE.  See the above copyright notices for more information.

=========================================================================*/
#ifndef otbBoostMachineLearningModelFactory_txx
#define otbBoostMachineLearningModelFactory_txx

#include "otbBoostMachineLearningModelFactory.h"

#include "itkCreateObjectFunction.h"
#include "otbBoostMachineLearningModel.h"
#include "itkVersion.h"

namespace otb
{

template <class TInputValue, class TOutputValue>
BoostMachineLearningModelFactory<TInputValue,TOutputValue>
::BoostMachineLearningModelFactory()
{

  std::string classOverride = std::string("otbMachineLearningModel");
  std::string subclass = std::string("otbBoostMachineLearningModel");

  this->RegisterOverride(classOverride.c_str(),
                         subclass.c_str(),
                         "Boost ML Model",
                         1,
                         itk::CreateObjectFunction<BoostMachineLearningModel<TInputValue,TOutputValue> >::New());
}

template <class TInputValue, class TOutputValue>
BoostMachineLearningModelFactory<TInputValue,TOutputValue>
::~BoostMachineLearningModelFactory()
{
}

template <class TInputValue, class TOutputValue>
const char*
BoostMachineLearningModelFactory<TInputValue,TOutputValue>
::GetITKSourceVersion(void) const
{
  return ITK_SOURCE_VERSION;
}

template <class TInputValue, class TOutputValue>
const char*
BoostMachineLearningModelFactory<TInputValue,TOutputValue>
::GetDescription() const
{
  return "Boost machine learning model factory";
}

} // end namespace otb

#endif
