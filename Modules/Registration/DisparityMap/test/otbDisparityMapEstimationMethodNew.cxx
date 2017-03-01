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

#include "otbDisparityMapEstimationMethod.h"
#include "otbImage.h"
#include "itkTranslationTransform.h"

int otbDisparityMapEstimationMethodNew(int itkNotUsed(argc), char * itkNotUsed(argv) [])
{
  const unsigned int Dimension = 2;
  typedef unsigned char                                                         PixelType;
  typedef otb::Image<PixelType, Dimension>                                      ImageType;
  typedef itk::TranslationTransform<double, Dimension>                          TransformType;
  typedef TransformType::ParametersType                                         ParametersType;
  typedef itk::PointSet<ParametersType, Dimension>                              PointSetType;
  typedef otb::DisparityMapEstimationMethod<ImageType, ImageType, PointSetType> DMEstimationType;

  // Instantiation
  DMEstimationType::Pointer dmestimator = DMEstimationType::New();

  std::cout << dmestimator << std::endl;

  return EXIT_SUCCESS;
}
