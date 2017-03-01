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

#include "otbTestMain.h"

void RegisterTests()
{
  REGISTER_TEST(otbConfusionMatrixCalculatorNew);
  REGISTER_TEST(otbConfusionMatrixCalculatorSetListSamples);
  REGISTER_TEST(otbConfusionMatrixCalculatorWrongSize);
  REGISTER_TEST(otbConfusionMatrixCalculatorCompute);
  REGISTER_TEST(otbConfusionMatrixCalculatorComputeWithBaseline);
  REGISTER_TEST(otbConfusionMatrixMeasurementsNew);
  REGISTER_TEST(otbConfusionMatrixMeasurementsTest);
  REGISTER_TEST(otbConfusionMatrixConcatenateTest);
  
  #ifdef OTB_USE_LIBSVM
  REGISTER_TEST(otbLibSVMMachineLearningModelCanRead);
  #endif
  
  #ifdef OTB_USE_OPENCV
  REGISTER_TEST(otbSVMMachineLearningModelCanRead);
  REGISTER_TEST(otbRandomForestsMachineLearningModelCanRead);
  REGISTER_TEST(otbBoostMachineLearningModelCanRead);
  REGISTER_TEST(otbNeuralNetworkMachineLearningModelCanRead);
  REGISTER_TEST(otbNormalBayesMachineLearningModelCanRead);
  REGISTER_TEST(otbDecisionTreeMachineLearningModelCanRead);
  REGISTER_TEST(otbGradientBoostedTreeMachineLearningModelCanRead);
  REGISTER_TEST(otbKNNMachineLearningModelCanRead);
  #endif
  
  #ifdef OTB_USE_LIBSVM
  REGISTER_TEST(otbLibSVMMachineLearningModelNew);
  REGISTER_TEST(otbLibSVMMachineLearningModel);
  REGISTER_TEST(otbLibSVMRegressionTests);
  #endif
  
  #ifdef OTB_USE_OPENCV
  REGISTER_TEST(otbSVMMachineLearningModelNew);
  REGISTER_TEST(otbSVMMachineLearningModel);
  REGISTER_TEST(otbSVMMachineLearningRegressionModel);
  REGISTER_TEST(otbKNearestNeighborsMachineLearningModelNew);
  REGISTER_TEST(otbKNearestNeighborsMachineLearningModel);
  REGISTER_TEST(otbRandomForestsMachineLearningModelNew);
  REGISTER_TEST(otbRandomForestsMachineLearningModel);
  REGISTER_TEST(otbBoostMachineLearningModelNew);
  REGISTER_TEST(otbBoostMachineLearningModel);
  REGISTER_TEST(otbANNMachineLearningModelNew);
  REGISTER_TEST(otbANNMachineLearningModel);
  REGISTER_TEST(otbNormalBayesMachineLearningModelNew);
  REGISTER_TEST(otbNormalBayesMachineLearningModel);
  REGISTER_TEST(otbDecisionTreeMachineLearningModelNew);
  REGISTER_TEST(otbDecisionTreeMachineLearningModel);
  REGISTER_TEST(otbGradientBoostedTreeMachineLearningModelNew);
  REGISTER_TEST(otbGradientBoostedTreeMachineLearningModel);
  REGISTER_TEST(otbNeuralNetworkRegressionTests);
  REGISTER_TEST(otbSVMRegressionTests);
  REGISTER_TEST(otbDecisionTreeRegressionTests);
  REGISTER_TEST(otbGradientBoostedTreeRegressionTests);
  REGISTER_TEST(otbKNearestNeighborsRegressionTests);
  REGISTER_TEST(otbRandomForestsRegressionTests);
#endif  

#ifdef OTB_USE_SHARK
  REGISTER_TEST(otbSharkRFMachineLearningModelNew);
  REGISTER_TEST(otbSharkRFMachineLearningModel);
  REGISTER_TEST(otbSharkRFMachineLearningModelCanRead);
  REGISTER_TEST(otbSharkImageClassificationFilter);
#endif
  
  REGISTER_TEST(otbImageClassificationFilterNew);
  REGISTER_TEST(otbImageClassificationFilter);
}
