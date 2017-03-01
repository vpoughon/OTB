/*=========================================================================

  Program:   ORFEO Toolbox
  Language:  C++


  Copyright (c) Centre National d'Etudes Spatiales. All rights reserved.
  See OTBCopyright.txt for details.


     This software is distributed WITHOUT ANY WARRANTY; without even
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
     PURPOSE.  See the above copyright notices for more information.

=========================================================================*/
#include "otbGlActor.h"

namespace otb
{
GlActor::GlActor()
  : m_Settings(ViewSettings::New()),
    m_Name("Actor"),
    m_Visible(true),
    m_GeometryChanged( false ),
    m_Overlay( false )
{}

GlActor::~GlActor()
{}

} // End namespace 'otb'.
