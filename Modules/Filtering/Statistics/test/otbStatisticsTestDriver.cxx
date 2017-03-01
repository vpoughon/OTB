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
  REGISTER_TEST(otbListSampleToHistogramListGeneratorNew);
  REGISTER_TEST(otbStreamingMinMaxImageFilter);
  REGISTER_TEST(otbStreamingMinMaxVectorImageFilterNew);
  REGISTER_TEST(otbVarianceImageFilterNew);
  REGISTER_TEST(otbStreamingStatisticsImageFilterNew);
  REGISTER_TEST(otbListSampleToVariableDimensionHistogramGeneratorNew);
  REGISTER_TEST(otbStreamingHistogramVectorImageFilterNew);
  REGISTER_TEST(otbStreamingHistogramVectorImageFilterTest);
  REGISTER_TEST(otbStreamingStatisticsVectorImageFilterNew);
  REGISTER_TEST(otbRealImageToComplexImageFilterTest);
  REGISTER_TEST(otbHistogramStatisticsFunction);
  REGISTER_TEST(otbGaussianAdditiveNoiseSampleListFilterNew);
  REGISTER_TEST(otbGaussianAdditiveNoiseSampleListFilter);
  REGISTER_TEST(otbNormalizeVectorImageFilterNewTest);
  REGISTER_TEST(otbNormalizeVectorImageFilterTest);
  REGISTER_TEST(otbVectorImageToMatrixNewTest);
  REGISTER_TEST(otbVectorImageToMatrixTest);
  REGISTER_TEST(otbListSampleToVariableDimensionHistogramGenerator);
  REGISTER_TEST(otbStreamingMinMaxImageFilterNew);
  REGISTER_TEST(otbShiftScaleSampleListFilterNew);
  REGISTER_TEST(otbShiftScaleSampleListFilter);
  REGISTER_TEST(otbVectorImageToIntensityImageFilter);
  REGISTER_TEST(otbVarianceImageFilter);
  REGISTER_TEST(otbConcatenateSampleListFilterNew);
  REGISTER_TEST(otbConcatenateSampleListFilter);
  REGISTER_TEST(otbLocalHistogramImageFunctionTest);
  REGISTER_TEST(otbVectorImageToIntensityImageFilterNew);
  REGISTER_TEST(otbProjectiveProjectionNew);
  REGISTER_TEST(otbProjectiveProjectionTestHighSNR);
  REGISTER_TEST(otbShiftScaleVectorImageFilterTest);
  REGISTER_TEST(otbContinuousMinimumMaximumImageCalculatorNew);
  REGISTER_TEST(otbStreamingCompareImageFilterNew);
  REGISTER_TEST(otbStreamingCompareImageFilter);
  REGISTER_TEST(otbStreamingStatisticsMapFromLabelImageFilterTest);
  REGISTER_TEST(otbLocalHistogramImageFunctionNew);
  REGISTER_TEST(otbRealAndImaginaryImageToComplexImageFilterTest);
  REGISTER_TEST(otbStreamingStatisticsImageFilter);
  REGISTER_TEST(otbListSampleToBalancedListSampleFilterNew);
  REGISTER_TEST(otbListSampleToBalancedListSampleFilter);
  REGISTER_TEST(otbStreamingStatisticsVectorImageFilter);
  REGISTER_TEST(otbStreamingMinMaxVectorImageFilter);
  REGISTER_TEST(otbListSampleGeneratorNew);
  REGISTER_TEST(otbListSampleGenerator);
  REGISTER_TEST(otbImaginaryImageToComplexImageFilterTest);
  REGISTER_TEST(otbListSampleToHistogramListGenerator);
  REGISTER_TEST(otbContinuousMinimumMaximumImageCalculatorTest);
  REGISTER_TEST(otbPeriodicSamplerTest);
  REGISTER_TEST(otbPatternSamplerTest);
  REGISTER_TEST(otbRandomSamplerTest);
}
