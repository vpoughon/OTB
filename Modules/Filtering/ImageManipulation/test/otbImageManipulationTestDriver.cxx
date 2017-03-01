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
  REGISTER_TEST(otbBinaryImageDensityFunctionNew);
  REGISTER_TEST(otbPrintableImageFilter);
  REGISTER_TEST(otbConcatenateScalarValueImageFilterNew);
  REGISTER_TEST(otbConcatenateScalarValueImageFilterTest);
  REGISTER_TEST(otbShiftScaleImageAdaptor);
  REGISTER_TEST(otbImageToVectorImageCastFilter);
  REGISTER_TEST(otbFunctionWithNeighborhoodToImageFilter);
  REGISTER_TEST(otbSqrtSpectralAngleImageFilter);
  REGISTER_TEST(otbUnaryFunctorNeighborhoodImageFilterNew);
  REGISTER_TEST(otbStreamingShrinkImageFilter);
  REGISTER_TEST(otbUnaryFunctorWithIndexImageFilterNew);
  REGISTER_TEST(otbUnaryFunctorImageFilterNew);
  REGISTER_TEST(otbUnaryImageFunctorWithVectorImageFilter);
  REGISTER_TEST(otbImageToVectorImageCastFilterNew);
  REGISTER_TEST(otbPrintableImageFilterWithMask);
  REGISTER_TEST(otbStreamingResampleImageFilter);
  REGISTER_TEST(otbUnaryFunctorNeighborhoodWithOffsetImageFilterNew);
  REGISTER_TEST(otbBoxAndWhiskerImageFilterNew);
  REGISTER_TEST(otbVectorImageToAmplitudeImageFilter);
  REGISTER_TEST(otbUnaryFunctorNeighborhoodWithOffsetImageFilter);
  REGISTER_TEST(otbStreamingResampleImageFilterCompareWithITK);
  REGISTER_TEST(otbRegionProjectionResampler);
  REGISTER_TEST(otbVectorImageTo3DScalarImageFilterNew);
  REGISTER_TEST(otbUnaryFunctorWithIndexImageFilter);
  REGISTER_TEST(otbMeanFunctorImageTest);
  REGISTER_TEST(otbBinaryImageToDensityImageFilterNew);
  REGISTER_TEST(otbVectorImageTo3DScalarImageFilter);
  REGISTER_TEST(otbTileImageFilterNew);
  REGISTER_TEST(otbTileImageFilter);
  REGISTER_TEST(otbMatrixImageFilterNew);
  REGISTER_TEST(otbMatrixImageFilterTest);
  REGISTER_TEST(otbMatrixTransposeMatrixImageFilter);
  REGISTER_TEST(otbPerBandVectorImageFilterNew);
  REGISTER_TEST(otbUnaryFunctorNeighborhoodImageFilter);
  REGISTER_TEST(otbStreamingResampleImageFilterNew);
  REGISTER_TEST(otbStreamingInnerProductVectorImageFilter);
  REGISTER_TEST(otbPhaseFunctorTest);
  REGISTER_TEST(otbShiftScaleVectorImageFilterNew);
  REGISTER_TEST(otbChangeLabelImageFilter);
  REGISTER_TEST(otbClampVectorImageFilterNew);
  REGISTER_TEST(otbClampVectorImageFilterTest);
  REGISTER_TEST(otbPrintableImageFilterNew);
  REGISTER_TEST(otbShiftScaleImageAdaptorNew);
  REGISTER_TEST(otbStreamingInnerProductVectorImageFilterNew);
  REGISTER_TEST(otbBoxAndWhiskerImageFilter);
  REGISTER_TEST(otbStreamingShrinkImageFilterNew);
  REGISTER_TEST(otbVectorRescaleIntensityImageFilter);
  REGISTER_TEST(otbLog10ThresholdedImageFilterTest);
  REGISTER_TEST(otbChangeLabelImageFilterNew);
  REGISTER_TEST(otbMatrixTransposeMatrixImageFilterNew);
  REGISTER_TEST(otbExtractROIResample);
  REGISTER_TEST(otbLocalGradientVectorImageFilterNewTest);
  REGISTER_TEST(otbLocalGradientVectorImageFilterTest);
  REGISTER_TEST(otbBinaryImageMinimalBoundingRegionCalculator);
  REGISTER_TEST(otbPerBandVectorImageFilterWithSobelFilter);
  REGISTER_TEST(otbBinaryImageDensityFunction);
  REGISTER_TEST(otbVectorImageToAmplitudeImageFilterNew);
  REGISTER_TEST(otbThresholdVectorImageFilterNew);
  REGISTER_TEST(otbThresholdVectorImageFilterTest);
  REGISTER_TEST(otbPerBandVectorImageFilterWithMeanFilter);
  REGISTER_TEST(otbConcatenateVectorImageFilterNew);
  REGISTER_TEST(otbAmplitudeFunctorTest);
  REGISTER_TEST(otbMultiplyByScalarImageFilterTest);
  REGISTER_TEST(otbClampImageFilterNew);
  REGISTER_TEST(otbClampImageFilterTest);
  REGISTER_TEST(otbConcatenateVectorImageFilter);
  REGISTER_TEST(otbBinaryImageMinimalBoundingRegionCalculatorNew);
  REGISTER_TEST(otbVectorRescaleIntensityImageFilterNew);
  REGISTER_TEST(otbSpectralAngleDistanceImageFilterNew);
  REGISTER_TEST(otbUnaryImageFunctorWithVectorImageFilterNew);
  REGISTER_TEST(otbBinaryImageToDensityImageFilter);
  REGISTER_TEST(otbSpectralAngleDistanceImageFilter);
  REGISTER_TEST(otbFunctionWithNeighborhoodToImageFilterNew);
  REGISTER_TEST(otbEuclideanDistanceMetricWithMissingValue);
  REGISTER_TEST(otbEuclideanDistanceMetricWithMissingValueNew);
  REGISTER_TEST(otbNRIBandImagesToOneNComplexBandsImage);
  REGISTER_TEST(otbOneRIBandImageToOneComplexBandImage);
  REGISTER_TEST(otbTwoNRIBandsImageToNComplexBandsImage);
  REGISTER_TEST(otbChangeNoDataValueFilter);
  REGISTER_TEST(otbImageToNoDataMaskFilter);
  REGISTER_TEST(otbChangeInformationImageFilter);
  REGISTER_TEST(otbGridResampleImageFilter);
  REGISTER_TEST(otbMaskedIteratorDecoratorNew);
  REGISTER_TEST(otbMaskedIteratorDecoratorNominal);
  REGISTER_TEST(otbMaskedIteratorDecoratorDegenerate);
  REGISTER_TEST(otbMaskedIteratorDecoratorExtended);
}
