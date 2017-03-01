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


#ifndef mvdQuicklookViewManipulator_h
#define mvdQuicklookViewManipulator_h

//
// Configuration include.
//// Included at first position before any other ones.
#include "ConfigureMonteverdi.h"


/*****************************************************************************/
/* INCLUDE SECTION                                                           */

//
// Qt includes (sorted by alphabetic order)
//// Must be included before system/custom includes.
#include <QtGui>

//
// System includes (sorted by alphabetic order)

//
// ITK includes (sorted by alphabetic order)

//
// OTB includes (sorted by alphabetic order)
#include "OTBMonteverdiGUIExport.h"
//
// Monteverdi includes (sorted by alphabetic order)
#include "mvdImageViewManipulator.h"


/*****************************************************************************/
/* PRE-DECLARATION SECTION                                                   */

//
// External classes pre-declaration.
namespace
{
}

namespace mvd
{
//
// Internal classes pre-declaration.


/*****************************************************************************/
/* CLASS DEFINITION SECTION                                                  */

/**
 * \class QuicklookViewManipulator
 *
 * \ingroup OTBMonteverdiGUI
 *
 *  \brief TODO.
 */
class OTBMonteverdiGUI_EXPORT QuicklookViewManipulator :
    public ImageViewManipulator
{

  /*-[ QOBJECT SECTION ]-----------------------------------------------------*/

  Q_OBJECT;

  /*-[ PUBLIC SECTION ]------------------------------------------------------*/

//
// Public methods.
public:

  /** \brief Constructor. */
#if USE_VIEW_SETTINGS_SIDE_EFFECT
  QuicklookViewManipulator( const otb::ViewSettings::Pointer& viewSettings,
                            QObject* p =NULL );
#else // USE_VIEW_SETTINGS_SIDE_EFFECT
  QuicklookViewManipulator( QObject* p =NULL );
#endif // USE_VIEW_SETTINGS_SIDE_EFFECT

  /** \brief Destructor. */
  ~QuicklookViewManipulator() ITK_OVERRIDE;

  //
  // ImageViewManipulator overloads.

  ZoomType GetFixedZoomType() const ITK_OVERRIDE;

  
    void
    SetupRenderingContext(
      AbstractImageViewRenderer::RenderingContext * const ) const ITK_OVERRIDE;


  void MousePressEvent( QMouseEvent* event ) ITK_OVERRIDE;

  void MouseMoveEvent( QMouseEvent* event ) ITK_OVERRIDE;

  // virtual void MousePressEvent( QMouseEvent* event );

  // virtual void MouseReleaseEvent( QMouseEvent* event );

  void MouseDoubleClickEvent( QMouseEvent * ) ITK_OVERRIDE {};

  void WheelEvent( QWheelEvent* event) ITK_OVERRIDE;

  void ResizeEvent( QResizeEvent * event ) ITK_OVERRIDE;

  void KeyPressEvent( QKeyEvent* event ) ITK_OVERRIDE;

  void KeyReleaseEvent( QKeyEvent* event ) ITK_OVERRIDE;

  /*-[ PUBLIC SLOTS SECTION ]-----------------------------------------------**/

//
// Public SLOTS.
public slots:

  /*-[ SIGNALS SECTION ]-----------------------------------------------------*/

//
// Signals.
signals:

  /*-[ PROTECTED SECTION ]---------------------------------------------------*/

//
// Protected methods.
protected:

//
// Protected attributes.
protected:

  /*-[ PRIVATE SECTION ]-----------------------------------------------------*/

//
// Private types.
private:

//
// Private methods.
private:

//
// Private attributes.
private:
  /**
   */
  PointType m_RoiOrigin;
  /**
   */
  SpacingType m_RoiSpacing;
  /**
   */
  SizeType m_RoiSize;

  /*-[ PRIVATE SLOTS SECTION ]-----------------------------------------------*/

//
// Slots.
private slots:
  /**
   */
  void OnRoiChanged( const PointType& origin,
                     const SizeType& size,
                     const SpacingType& spacing,
                     const PointType& center );
};

} // end namespace 'mvd'

/*****************************************************************************/
/* INLINE SECTION                                                            */

namespace mvd
{
} // end namespace 'mvd'

#endif // mvdQuicklookViewManipulator_h
