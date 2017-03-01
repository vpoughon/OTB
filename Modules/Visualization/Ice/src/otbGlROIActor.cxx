/*=========================================================================

  Program:   ORFEO Toolbox
  Language:  C++


  Copyright (c) Centre National d'Etudes Spatiales. All rights reserved.
  See OTBCopyright.txt for details.


     This software is distributed WITHOUT ANY WARRANTY; without even
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
     PURPOSE.  See the above copyright notices for more information.

=========================================================================*/
#include "otbGlROIActor.h"
#include "otbViewSettings.h"
#ifdef _WIN32
#include <windows.h>
#endif
#include <GL/glew.h>


namespace otb
{

GlROIActor::GlROIActor()
  : m_UL(),
    m_LR(),
    m_Wkt(),
    m_Kwl(),
    m_Color(),
    m_Alpha(1.0),
    m_Fill(false),
    m_ViewportToImageTransform(),
    m_ImageToViewportTransform(),
    m_VpUL(),
    m_VpUR(),
    m_VpLL(),
    m_VpLR()
{
  m_UL.Fill( 0 );
  m_LR.Fill( 0 );

  m_Color.Fill(0);
  m_Color[0]=1.0;

  m_VpUL.Fill( 0 );
  m_VpUR.Fill( 0 );
  m_VpLL.Fill( 0 );
  m_VpLR.Fill( 0 );
}

GlROIActor::~GlROIActor()
{}


void
GlROIActor
::SetUL( const PointType & p )
{
  if( p!=m_UL )
    GeometryChangedOn();

  m_UL = p;
}


void
GlROIActor
::SetLR( const PointType & p )
{
  if( p!=m_LR )
    GeometryChangedOn();

  m_LR = p;
}


void GlROIActor::SetKwl(const ImageKeywordlistType & kwl)
{
  m_Kwl = kwl;
}

void GlROIActor::GetExtent(double & ulx, double & uly, double & lrx, double & lry) const
{
  //TODO: Fixme (should handle rotation as well)
  lrx = std::max(std::max(m_VpUL[0],m_VpUR[0]),std::max(m_VpLL[0],m_VpLR[0]));
  lry = std::max(std::max(m_VpUL[1],m_VpUR[1]),std::max(m_VpLL[1],m_VpLR[1]));
  ulx = std::min(std::min(m_VpUL[0],m_VpUR[0]),std::min(m_VpLL[0],m_VpLR[0]));
  uly = std::min(std::min(m_VpUL[1],m_VpUR[1]),std::min(m_VpLL[1],m_VpLR[1]));
}

void GlROIActor::ProcessViewSettings()
{
  // std::cout << std::hex << this << "::ProcessViewSettings()" << std::endl;

  UpdateTransforms();

  assert( GetSettings()!=NULL );

  if( GetGeometryChanged() ||
      GetSettings()->GetGeometryChanged() )
    {
    // std::cout << "otb::GlRoiActor@" << std::hex << this << " -> ROI" << std::endl;

    PointType ur;
    PointType ll;

    ur = m_UL;
    ur[ 0 ] = m_LR[ 0 ];

    ll = m_LR;
    ll[ 0 ] = m_UL[ 0 ];

    assert( !m_ImageToViewportTransform.IsNull() );
    assert( !m_ViewportToImageTransform.IsNull() );

    m_VpUL = m_ImageToViewportTransform->TransformPoint( m_UL );
    m_VpUR = m_ImageToViewportTransform->TransformPoint( ur );
    m_VpLL = m_ImageToViewportTransform->TransformPoint( ll );
    m_VpLR = m_ImageToViewportTransform->TransformPoint( m_LR );
    }
}

void GlROIActor::UpdateData()
{
  // Nothing to do here
}

void GlROIActor::Render()
{
  glColor3d(m_Color[0],m_Color[1],m_Color[2]);

  glBegin(GL_LINE_LOOP);
  glVertex2d(m_VpUL[0],m_VpUL[1]);
  glVertex2d(m_VpUR[0],m_VpUR[1]);
  glVertex2d(m_VpLR[0],m_VpLR[1]);
  glVertex2d(m_VpLL[0],m_VpLL[1]);
  glEnd();

  if(m_Fill)
    {
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA); 
    glColor4d(m_Color[0],m_Color[1],m_Color[2],m_Alpha);
    glBegin(GL_QUADS);
    glVertex2d(m_VpUL[0],m_VpUL[1]);
    glVertex2d(m_VpUR[0],m_VpUR[1]);
    glVertex2d(m_VpLR[0],m_VpLR[1]);
    glVertex2d(m_VpLL[0],m_VpLL[1]);
    glEnd();
    glDisable(GL_BLEND);
    }
}


void GlROIActor::UpdateTransforms()
{
  // std::cout << std::hex << this << "::UpdateTransforms()" << std::endl;

  // Retrieve settings
  ViewSettings::ConstPointer settings( this->GetSettings() );

  if( settings->GetUseProjection() )
    {
    if( settings->GetGeometryChanged() ||
	m_ImageToViewportTransform.IsNull() ||
	m_ViewportToImageTransform.IsNull() )
      {
      // std::cout
      // 	<< "otb::GlROIActor@" << std::hex << this
      // 	<< " Proj: ON" << std::endl;

      m_ImageToViewportTransform = RSTransformType::New();
      m_ViewportToImageTransform = RSTransformType::New();

      m_ViewportToImageTransform->SetInputProjectionRef( settings->GetWkt() );
      m_ViewportToImageTransform->SetInputKeywordList( settings->GetKeywordList() );
      m_ViewportToImageTransform->SetOutputProjectionRef( m_Wkt );
      m_ViewportToImageTransform->SetOutputKeywordList( m_Kwl );

      m_ImageToViewportTransform->SetInputProjectionRef( m_Wkt );
      m_ImageToViewportTransform->SetInputKeywordList( m_Kwl );
      m_ImageToViewportTransform->SetOutputProjectionRef( settings->GetWkt() );
      m_ImageToViewportTransform->SetOutputKeywordList( settings->GetKeywordList() );

      m_ViewportToImageTransform->InstantiateTransform();
      m_ImageToViewportTransform->InstantiateTransform();
      }
    }
  else
    {
    if( settings->GetGeometryChanged() ||
	m_ImageToViewportTransform.IsNull() ||
	m_ViewportToImageTransform.IsNull() )
      {
      // std::cout
      // 	<< "otb::GlROIActor@" << std::hex << this
      // 	<< " Proj: OFF" << std::endl;

      m_ImageToViewportTransform = RSTransformType::New();
      m_ViewportToImageTransform = RSTransformType::New();

      m_ImageToViewportTransform->InstantiateTransform();
      m_ViewportToImageTransform->InstantiateTransform();
      }
    }
}

}
