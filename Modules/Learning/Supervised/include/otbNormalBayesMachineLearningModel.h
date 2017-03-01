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

#ifndef otbNormalBayesMachineLearningModel_h
#define otbNormalBayesMachineLearningModel_h

#include "otbRequiresOpenCVCheck.h"

#include "itkLightObject.h"
#include "itkFixedArray.h"
#include "otbMachineLearningModel.h"


class CvNormalBayesClassifier;

namespace otb
{
template <class TInputValue, class TTargetValue>
class ITK_EXPORT NormalBayesMachineLearningModel
  : public MachineLearningModel <TInputValue, TTargetValue>
{
public:
  /** Standard class typedefs. */
  typedef NormalBayesMachineLearningModel           Self;
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

  /** Run-time type information (and related methods). */
  itkNewMacro(Self);
  itkTypeMacro(NormalBayesMachineLearningModel, MachineLearningModel);

  /** Train the machine learning model */
  void Train() ITK_OVERRIDE;

  /** Save the model to file */
  void Save(const std::string & filename, const std::string & name="") ITK_OVERRIDE;

  /** Load the model from file */
  void Load(const std::string & filename, const std::string & name="") ITK_OVERRIDE;

  /**\name Classification model file compatibility tests */
  //@{
  /** Is the input model file readable and compatible with the corresponding classifier ? */
  bool CanReadFile(const std::string &) ITK_OVERRIDE;

  /** Is the input model file writable and compatible with the corresponding classifier ? */
  bool CanWriteFile(const std::string &) ITK_OVERRIDE;
  //@}

protected:
  /** Constructor */
  NormalBayesMachineLearningModel();

  /** Destructor */
  ~NormalBayesMachineLearningModel() ITK_OVERRIDE;

  /** Predict values using the model */
  TargetSampleType DoPredict(const InputSampleType& input, ConfidenceValueType *quality=ITK_NULLPTR) const ITK_OVERRIDE;

  
  /** PrintSelf method */
  void PrintSelf(std::ostream& os, itk::Indent indent) const ITK_OVERRIDE;

private:
  NormalBayesMachineLearningModel(const Self &); //purposely not implemented
  void operator =(const Self&); //purposely not implemented

  CvNormalBayesClassifier * m_NormalBayesModel;
};
} // end namespace otb

#ifndef OTB_MANUAL_INSTANTIATION
#include "otbNormalBayesMachineLearningModel.txx"
#endif

#endif
