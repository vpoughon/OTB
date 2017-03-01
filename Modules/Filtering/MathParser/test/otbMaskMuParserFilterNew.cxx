/*=========================================================================

  Program:   ORFEO Toolbox
  Language:  C++


  Copyright (c) Centre National d'Etudes Spatiales. All rights reserved.
  See OTBCopyright.txt for details.


  This software is distributed WITHOUT ANY WARRANTY; without even
  the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
  PURPOSE.  See the above copyright notices for more information.

=========================================================================*/

#include "otbVectorImage.h"
#include "otbImage.h"
#include "otbMaskMuParserFilter.h"

int otbMaskMuParserFilterNew( int itkNotUsed(argc), char * itkNotUsed(argv) [])
{

  typedef float InputPixelType;
  const unsigned int     Dimension = 2;

  typedef otb::VectorImage<InputPixelType,  Dimension>      InputVectorImageType;
  typedef otb::Image<unsigned int, Dimension>                OutputImageType;
  typedef otb::MaskMuParserFilter<InputVectorImageType, OutputImageType>  FilterType;


   FilterType::Pointer   filter       = FilterType::New();

   return EXIT_SUCCESS;
}
