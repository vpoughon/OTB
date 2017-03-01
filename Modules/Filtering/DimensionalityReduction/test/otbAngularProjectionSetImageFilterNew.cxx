/*=========================================================================

  Program:   ORFEO Toolbox
  Language:  C++


  Copyright (c) Centre National d'Etudes Spatiales. All rights reserved.
  See OTBCopyright.txt for details.


     This software is distributed WITHOUT ANY WARRANTY; without even
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
     PURPOSE.  See the above copyright notices for more information.

=========================================================================*/

#include "itkListSample.h"

#include "otbMath.h"
#include "otbImage.h"
#include "otbImageFileReader.h"
#include "otbImageFileWriter.h"
#include "otbCommandLineArgumentParser.h"

#include "otbAngularProjectionSetImageFilter.h"

int otbAngularProjectionSetImageFilterNew ( int itkNotUsed(argc), char * itkNotUsed(argv) [])
{
  const unsigned int Dimension = 2;
  const unsigned int SpaceDimension = 3;

  typedef float  PixelType;
  typedef double PrecisionType;
  typedef itk::FixedArray< PrecisionType, SpaceDimension > AngleType;
  typedef itk::Statistics::ListSample< AngleType >         AngleListType;
  typedef otb::Image< PixelType, Dimension >               ImageType;

  typedef otb::AngularProjectionSetImageFilter<
    ImageType, ImageType, AngleListType, PrecisionType > FilterType;

  FilterType::Pointer filter = FilterType::New();
  return EXIT_SUCCESS;
}
