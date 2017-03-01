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

#include "otbDrawPathFilter.h"
#include "otbImageFileWriter.h"
#include "otbImage.h"
#include "itkPolyLineParametricPath.h"

int otbDrawPathFilterNew(int itkNotUsed(argc), char * itkNotUsed(argv) [])
{
  const unsigned int Dimension = 2;
  typedef unsigned char                                       PixelType;
  typedef otb::Image<PixelType, Dimension>                    ImageType;
  typedef itk::PolyLineParametricPath<Dimension>              PathType;
  typedef otb::DrawPathFilter<ImageType, PathType, ImageType> DrawPathFilterType;

  DrawPathFilterType::Pointer filter = DrawPathFilterType::New();

  std::cout << filter << std::endl;

  return EXIT_SUCCESS;
}
