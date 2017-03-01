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

#ifndef otbTrainBoost_txx
#define otbTrainBoost_txx
#include "otbLearningApplicationBase.h"

namespace otb
{
namespace Wrapper
{

  template <class TInputValue, class TOutputValue>
  void
  LearningApplicationBase<TInputValue,TOutputValue>
  ::InitBoostParams()
  {
    AddChoice("classifier.boost", "Boost classifier");
    SetParameterDescription("classifier.boost", "This group of parameters allows setting Boost classifier parameters. "
        "See complete documentation here \\url{http://docs.opencv.org/modules/ml/doc/boosting.html}.");
    //BoostType
    AddParameter(ParameterType_Choice, "classifier.boost.t", "Boost Type");
    AddChoice("classifier.boost.t.discrete", "Discrete AdaBoost");
    AddChoice("classifier.boost.t.real", "Real AdaBoost (technique using confidence-rated predictions "
                                                "and working well with categorical data)");
    AddChoice("classifier.boost.t.logit", "LogitBoost (technique producing good regression fits)");
    AddChoice("classifier.boost.t.gentle", "Gentle AdaBoost (technique setting less weight on outlier data points "
                                               "and, for that reason, being often good with regression data)");
    SetParameterString("classifier.boost.t", "real", false);
    SetParameterDescription("classifier.boost.t", "Type of Boosting algorithm.");
    //Do not expose SplitCriteria
    //WeakCount
    AddParameter(ParameterType_Int, "classifier.boost.w", "Weak count");
    SetParameterInt("classifier.boost.w",100, false);
    SetParameterDescription("classifier.boost.w","The number of weak classifiers.");
    //WeightTrimRate
    AddParameter(ParameterType_Float, "classifier.boost.r", "Weight Trim Rate");
    SetParameterFloat("classifier.boost.r",0.95, false);
    SetParameterDescription("classifier.boost.r","A threshold between 0 and 1 used to save computational time. "
                            "Samples with summary weight <= (1 - weight_trim_rate) do not participate in the next iteration of training. "
                            "Set this parameter to 0 to turn off this functionality.");
    //MaxDepth : Not sure that this parameter has to be exposed.
    AddParameter(ParameterType_Int, "classifier.boost.m", "Maximum depth of the tree");
    SetParameterInt("classifier.boost.m",1, false);
    SetParameterDescription("classifier.boost.m","Maximum depth of the tree.");
  }

  template <class TInputValue, class TOutputValue>
  void
  LearningApplicationBase<TInputValue,TOutputValue>
  ::TrainBoost(typename ListSampleType::Pointer trainingListSample,
               typename TargetListSampleType::Pointer trainingLabeledListSample,
               std::string modelPath)
  {
    typename BoostType::Pointer boostClassifier = BoostType::New();
    boostClassifier->SetRegressionMode(this->m_RegressionFlag);
    boostClassifier->SetInputListSample(trainingListSample);
    boostClassifier->SetTargetListSample(trainingLabeledListSample);
    boostClassifier->SetBoostType(GetParameterInt("classifier.boost.t"));
    boostClassifier->SetWeakCount(GetParameterInt("classifier.boost.w"));
    boostClassifier->SetWeightTrimRate(GetParameterFloat("classifier.boost.r"));
    boostClassifier->SetMaxDepth(GetParameterInt("classifier.boost.m"));

    boostClassifier->Train();
    boostClassifier->Save(modelPath);
  }

} //end namespace wrapper
} //end namespace otb

#endif
