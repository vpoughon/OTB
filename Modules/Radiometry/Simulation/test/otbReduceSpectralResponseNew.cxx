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

#include "otbSatelliteRSR.h"
#include "otbReduceSpectralResponse.h"

int otbReduceSpectralResponseNew(int itkNotUsed(argc), char * itkNotUsed(argv)[])
{
  typedef otb::SpectralResponse< double, double>  ResponseType;
  //typedef ResponseType::Pointer  ResponsePointerType;

  typedef otb::SatelliteRSR< double, double>  SatRSRType;
  //typedef SatRSRType::Pointer  SatRSRPointerType;

  typedef otb::ReduceSpectralResponse < ResponseType, SatRSRType>  ReduceResponseType;
  typedef ReduceResponseType::Pointer  ReduceResponseTypePointerType;
  //Instantiation
  ReduceResponseTypePointerType  myResponse=ReduceResponseType::New();

  return EXIT_SUCCESS;
}
