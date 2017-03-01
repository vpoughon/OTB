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

#include "itkUnaryFunctorImageFilter.h"
#include "itkBinaryBallStructuringElement.h"
#include "otbMultiScaleConvexOrConcaveClassificationFilter.h"
#include "otbImage.h"
#include "itkMacro.h"

int otbMultiScaleConvexOrConcaveClassificationFilterNew(int itkNotUsed(argc), char * itkNotUsed(argv) [])
{
  const unsigned int Dimension = 2;
  typedef double         InputPixelType;
  typedef unsigned short LabeledPixelType;

  typedef otb::Image<InputPixelType, Dimension>  InputImageType;
  typedef otb::Image<LabeledPixelType, 2>        LabeledImageType;

  typedef otb::MultiScaleConvexOrConcaveClassificationFilter<InputImageType,
      LabeledImageType> MultiScaleClassificationFilterType;

  // Instantiation
  MultiScaleClassificationFilterType::Pointer filter = MultiScaleClassificationFilterType::New();

  std::cout << filter << std::endl;

  return EXIT_SUCCESS;
}
