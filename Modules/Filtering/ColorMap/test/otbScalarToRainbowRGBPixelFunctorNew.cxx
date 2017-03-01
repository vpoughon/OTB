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




#include "otbImage.h"

#include "itkUnaryFunctorImageFilter.h"
#include "otbScalarToRainbowRGBPixelFunctor.h"

int otbScalarToRainbowRGBPixelFunctorNew(int itkNotUsed(argc), char * itkNotUsed(argv) [])
{

  typedef unsigned char               PixelType;
  typedef itk::RGBPixel<PixelType>    RGBPixelType;
  typedef otb::Image<PixelType, 2>    ImageType;
  typedef otb::Image<RGBPixelType, 2> RGBImageType;

  typedef otb::Functor::ScalarToRainbowRGBPixelFunctor<PixelType>
  ColorMapFunctorType;
  typedef itk::UnaryFunctorImageFilter<ImageType,
      RGBImageType, ColorMapFunctorType> ColorMapFilterType;
  ColorMapFilterType::Pointer colormapper = ColorMapFilterType::New();
  colormapper->GetFunctor().SetMaximum(150);
  colormapper->GetFunctor().SetMinimum(70);

  std::cout << colormapper << std::endl;

  return EXIT_SUCCESS;
}
