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

#if defined(_MSC_VER)
#pragma warning ( disable : 4786 )
#endif

#include "otbWrapperOutputImageParameter.h"
#include "otbImageFileReader.h"
#include "otbWrapperTypes.h"

int otbWrapperOutputImageParameterNew(int itkNotUsed(argc), char * itkNotUsed(argv)[])
{
  typedef otb::Wrapper::OutputImageParameter OutputImageParameterType;
  OutputImageParameterType::Pointer parameter = OutputImageParameterType::New();

  return EXIT_SUCCESS;
}


int otbWrapperOutputImageParameterTest1(int itkNotUsed(argc), char* argv[])
{
  typedef otb::Wrapper::OutputImageParameter OutputImageParameterType;
  OutputImageParameterType::Pointer param = OutputImageParameterType::New();

  typedef otb::ImageFileReader< otb::Wrapper::FloatVectorImageType > ReaderType;

  ReaderType::Pointer reader = ReaderType::New();

  reader->SetFileName( argv[1] );
  reader->UpdateOutputInformation();

  param->SetValue(reader->GetOutput());
  param->SetFileName( argv[2] );

  param->SetKey(argv[3]);
  param->SetDescription(argv[4]);

  // an explicit writer initialization is needed
  param->InitializeWriters();
  param->Write();

  return EXIT_SUCCESS;
}
