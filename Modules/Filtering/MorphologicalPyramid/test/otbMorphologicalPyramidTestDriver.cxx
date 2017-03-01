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
  REGISTER_TEST(otbMorphologicalPyramidSegmentationFilterNew);
  REGISTER_TEST(otbMorphologicalPyramidAnalysisFilter);
  REGISTER_TEST(otbMorphologicalPyramidSegmenter);
  REGISTER_TEST(otbMorphologicalPyramidSegmenterNew);
  REGISTER_TEST(otbMorphologicalPyramidSynthesisFilter);
  REGISTER_TEST(otbMorphologicalPyramidMRToMSConverter);
  REGISTER_TEST(otbMorphologicalPyramidSynthesisFilterNew);
  REGISTER_TEST(otbMorphologicalPyramidMRToMSConverterNew);
  REGISTER_TEST(otbMorphologicalPyramidResampler);
  REGISTER_TEST(otbMorphologicalPyramidAnalysisFilterNew);
  REGISTER_TEST(otbMorphologicalPyramidResamplerNew);
  REGISTER_TEST(otbMorphologicalPyramidSegmentationFilter);
}
