/*=========================================================================

  Program:   ORFEO Toolbox
  Language:  C++


  Copyright (c) Centre National d'Etudes Spatiales. All rights reserved.
  See OTBCopyright.txt for details.


     This software is distributed WITHOUT ANY WARRANTY; without even
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
     PURPOSE.  See the above copyright notices for more information.

=========================================================================*/
#include "otbWrapperInputImageParameter.h"
#include "itksys/SystemTools.hxx"
#include "otbWrapperTypes.h"
#include "otbWrapperInputImageParameterMacros.h"
#include "otb_boost_string_header.h"

namespace otb
{
namespace Wrapper
{
otbGetImageMacro(DoubleImage);
otbGetImageMacro(DoubleVectorImage)
otbGenericCastImageMacro(DoubleImageType, SimpleCastImage, )
otbGenericCastImageMacro(DoubleVectorImageType, SimpleCastImage, Vector)
otbGenericCastImageMacro(DoubleImageType, CastVectorImageFromImage, Vector)
}
}
