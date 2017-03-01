/*
 * Copyright (C) 2005-2016 Centre National d'Etudes Spatiales (CNES)
 *
 * This file is part of Orfeo Toolbox
 *
 *     https://www.orfeo-toolbox.org/
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef otbLibSVMMachineLearningModel_h
#define otbLibSVMMachineLearningModel_h

#include "itkLightObject.h"
#include "itkFixedArray.h"
#include "otbMachineLearningModel.h"

// SVM estimator
#include "otbSVMSampleListModelEstimator.h"
// Validation
#include "otbSVMClassifier.h"

namespace otb
{
template <class TInputValue, class TTargetValue>
class ITK_EXPORT LibSVMMachineLearningModel
  : public MachineLearningModel <TInputValue, TTargetValue>
{
public:
  /** Standard class typedefs. */
  typedef LibSVMMachineLearningModel           Self;
  typedef MachineLearningModel<TInputValue, TTargetValue> Superclass;
  typedef itk::SmartPointer<Self>                         Pointer;
  typedef itk::SmartPointer<const Self>                   ConstPointer;

  typedef typename Superclass::InputValueType             InputValueType;
  typedef typename Superclass::InputSampleType            InputSampleType;
  typedef typename Superclass::InputListSampleType        InputListSampleType;
  typedef typename Superclass::TargetValueType            TargetValueType;
  typedef typename Superclass::TargetSampleType           TargetSampleType;
  typedef typename Superclass::TargetListSampleType       TargetListSampleType;
  typedef typename Superclass::ConfidenceValueType        ConfidenceValueType;

  // LibSVM related typedefs
  typedef otb::Functor::VariableLengthVectorToMeasurementVectorFunctor<InputSampleType> MeasurementVectorFunctorType;
  typedef otb::SVMSampleListModelEstimator<InputListSampleType, TargetListSampleType, MeasurementVectorFunctorType>
      SVMEstimatorType;

  typedef otb::SVMClassifier<InputSampleType, TargetValueType> ClassifierType;

  /** Run-time type information (and related methods). */
  itkNewMacro(Self);
  itkTypeMacro(SVMMachineLearningModel, MachineLearningModel);

  /** Train the machine learning model */
  void Train() ITK_OVERRIDE;

  /** Save the model to file */
  void Save(const std::string &filename, const std::string & name="") ITK_OVERRIDE;

  /** Load the model from file */
  void Load(const std::string & filename, const std::string & name="") ITK_OVERRIDE;

  /**\name Classification model file compatibility tests */
  //@{
  /** Is the input model file readable and compatible with the corresponding classifier ? */
  bool CanReadFile(const std::string &) ITK_OVERRIDE;

  /** Is the input model file writable and compatible with the corresponding classifier ? */
  bool CanWriteFile(const std::string &) ITK_OVERRIDE;
  //@}

  //Setters/Getters to SVM model
  otbGetObjectMemberMacro(SVMestimator, SVMType, int);
  otbSetObjectMemberMacro(SVMestimator, SVMType, int);

  otbGetObjectMemberMacro(SVMestimator, KernelType, int);
  otbSetObjectMemberMacro(SVMestimator, KernelType, int);

  otbGetObjectMemberMacro(SVMestimator, C, double);
  otbSetObjectMemberMacro(SVMestimator, C, double);

  // TODO : we should harmonize this parameter name : ParameterOptimization -> ParametersOptimization
  bool GetParameterOptimization()
    {
    return this->m_SVMestimator->GetParametersOptimization();
    }
  void SetParameterOptimization(bool value)
    {
    this->m_SVMestimator->SetParametersOptimization(value);
    this->Modified();
    }

  otbGetObjectMemberMacro(SVMestimator, DoProbabilityEstimates, bool);
  void SetDoProbabilityEstimates(bool value)
    {
    this->m_SVMestimator->DoProbabilityEstimates(value);
    }

  otbGetObjectMemberMacro(SVMestimator, Epsilon, double);
  otbSetObjectMemberMacro(SVMestimator, Epsilon, double);

  otbGetObjectMemberMacro(SVMestimator, P, double);
  otbSetObjectMemberMacro(SVMestimator, P, double);

  otbGetObjectMemberMacro(SVMestimator, Nu, double);
  otbSetObjectMemberMacro(SVMestimator, Nu, double);

protected:
  /** Constructor */
  LibSVMMachineLearningModel();

  /** Destructor */
  ~LibSVMMachineLearningModel() ITK_OVERRIDE;

  /** Predict values using the model */
  TargetSampleType DoPredict(const InputSampleType& input, ConfidenceValueType *quality=ITK_NULLPTR) const ITK_OVERRIDE;

  /** PrintSelf method */
  void PrintSelf(std::ostream& os, itk::Indent indent) const ITK_OVERRIDE;

private:
  LibSVMMachineLearningModel(const Self &); //purposely not implemented
  void operator =(const Self&); //purposely not implemented

  typename SVMEstimatorType::Pointer m_SVMestimator;
};
} // end namespace otb

#ifndef OTB_MANUAL_INSTANTIATION
#include "otbLibSVMMachineLearningModel.txx"
#endif

#endif
