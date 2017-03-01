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

#include "otbReflectanceToLuminanceImageFilter.h"
#include "otbImageFileReader.h"
#include "otbImageFileWriter.h"

int otbReflectanceToLuminanceImageFilter(int argc, char * argv[])
{
  const char * inputFileName  = argv[1];
  const char * outputFileName = argv[2];
  const double angle = static_cast<double>(atof(argv[3]));
  double       flux = 0.;
  int          day = 1;
  int          month = 1;

  if (argc == 9)
    {
    flux = static_cast<double>(atof(argv[8]));
    }
  else
    {
    day = atoi(argv[8]);
    month = atoi(argv[9]);
    }

  const unsigned int Dimension = 2;
  typedef double                                                                  PixelType;
  typedef otb::VectorImage<PixelType, Dimension>                                  InputImageType;
  typedef otb::VectorImage<PixelType, Dimension>                                  OutputImageType;
  typedef otb::ImageFileReader<InputImageType>                                    ReaderType;
  typedef otb::ImageFileWriter<OutputImageType>                                   WriterType;
  typedef otb::ReflectanceToLuminanceImageFilter<InputImageType, OutputImageType> ReflectanceToLuminanceImageFilterType;
  typedef ReflectanceToLuminanceImageFilterType::VectorType                       VectorType;

  ReaderType::Pointer reader  = ReaderType::New();
  WriterType::Pointer writer = WriterType::New();
  reader->SetFileName(inputFileName);
  writer->SetFileName(outputFileName);
  reader->UpdateOutputInformation();

  unsigned int nbOfComponent = reader->GetOutput()->GetNumberOfComponentsPerPixel();
  // WARNING : 1 ELEMENT FOR EACH PIXEL IMAGE COMPONENT
  VectorType solarIllumination(nbOfComponent);
  solarIllumination.Fill(0);
  solarIllumination[0] = static_cast<double>(atof(argv[4]));
  solarIllumination[1] = static_cast<double>(atof(argv[5]));
  solarIllumination[2] = static_cast<double>(atof(argv[6]));
  solarIllumination[3] = static_cast<double>(atof(argv[7]));

  // Instantiating object
  ReflectanceToLuminanceImageFilterType::Pointer filter = ReflectanceToLuminanceImageFilterType::New();

  filter->SetZenithalSolarAngle(angle);
  filter->SetSolarIllumination(solarIllumination);
  filter->SetUseClamp(false);
  if (argc == 9)
    {
    filter->SetFluxNormalizationCoefficient(flux);
    }
  else
    {
    filter->SetDay(day);
    filter->SetMonth(month);
    }

  filter->SetInput(reader->GetOutput());
  writer->SetInput(filter->GetOutput());
  writer->Update();

  return EXIT_SUCCESS;
}
