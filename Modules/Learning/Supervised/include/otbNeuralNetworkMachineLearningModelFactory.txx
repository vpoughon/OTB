/*=========================================================================

  Program:   ORFEO Toolbox
  Language:  C++


  Copyright (c) Centre National d'Etudes Spatiales. All rights reserved.
  See OTBCopyright.txt for details.


     This software is distributed WITHOUT ANY WARRANTY; without even
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
     PURPOSE.  See the above copyright notices for more information.

=========================================================================*/
#ifndef otbNeuralNetworkMachineLearningModelFactory_txx
#define otbNeuralNetworkMachineLearningModelFactory_txx

#include "otbNeuralNetworkMachineLearningModelFactory.h"

#include "itkCreateObjectFunction.h"
#include "otbNeuralNetworkMachineLearningModel.h"
#include "itkVersion.h"

namespace otb
{

template <class TInputValue, class TOutputValue>
NeuralNetworkMachineLearningModelFactory<TInputValue,TOutputValue>
::NeuralNetworkMachineLearningModelFactory()
{

  std::string classOverride = std::string("otbMachineLearningModel");
  std::string subclass = std::string("otbNeuralNetworkMachineLearningModel");

  this->RegisterOverride(classOverride.c_str(),
                         subclass.c_str(),
                         "Artificial Neural Network ML Model",
                         1,
                         itk::CreateObjectFunction<NeuralNetworkMachineLearningModel<TInputValue,TOutputValue> >::New());
}

template <class TInputValue, class TOutputValue>
NeuralNetworkMachineLearningModelFactory<TInputValue,TOutputValue>
::~NeuralNetworkMachineLearningModelFactory()
{
}

template <class TInputValue, class TOutputValue>
const char*
NeuralNetworkMachineLearningModelFactory<TInputValue,TOutputValue>
::GetITKSourceVersion(void) const
{
  return ITK_SOURCE_VERSION;
}

template <class TInputValue, class TOutputValue>
const char*
NeuralNetworkMachineLearningModelFactory<TInputValue,TOutputValue>
::GetDescription() const
{
  return "Artificial Neural Network machine learning model factory";
}

} // end namespace otb

#endif
