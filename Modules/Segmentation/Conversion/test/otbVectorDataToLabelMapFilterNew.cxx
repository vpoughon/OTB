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


#include "otbMacro.h"

#include "otbVectorDataToLabelMapFilter.h"
#include "otbAttributesMapLabelObject.h"

int otbVectorDataToLabelMapFilterNew(int itkNotUsed(argc), char * itkNotUsed(argv)[])
{
  typedef unsigned short LabelType;
  const unsigned int Dimension = 2;
  typedef otb::VectorData<double, Dimension>                          VectorDataType;
  typedef otb::AttributesMapLabelObject<LabelType, Dimension, double> LabelObjectType;
  typedef itk::LabelMap<LabelObjectType>                              OutputLabelMapType;

  typedef otb::VectorDataToLabelMapFilter<VectorDataType, OutputLabelMapType> VectorDataToLabelMapFilterType;

  //Instantiation
  VectorDataToLabelMapFilterType::Pointer filter = VectorDataToLabelMapFilterType::New();

  std::cout << filter << std::endl;

  return EXIT_SUCCESS;
}
