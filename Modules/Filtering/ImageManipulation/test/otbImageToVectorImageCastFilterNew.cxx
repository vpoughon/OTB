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

#include "itkMacro.h"
#include "otbImageToVectorImageCastFilter.h"
#include "otbVectorImage.h"
#include "otbImage.h"

int otbImageToVectorImageCastFilterNew(int itkNotUsed(argc), char * itkNotUsed(argv) [])
{
  typedef double PixelType;
  const unsigned int Dimension = 2;

  typedef otb::Image<PixelType, Dimension>       ImageType;
  typedef otb::VectorImage<PixelType, Dimension> VectorImageType;

  typedef otb::ImageToVectorImageCastFilter<ImageType, VectorImageType> VectorImageCastFilterType;

  // Instantiation
  VectorImageCastFilterType::Pointer caster = VectorImageCastFilterType::New();

  std::cout << caster << std::endl;

  return EXIT_SUCCESS;
}
