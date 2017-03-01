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

#ifndef mvdAbstractLayerModel_h
#define mvdAbstractLayerModel_h


//
// Configuration include.
//// Included at first position before any other ones.
#ifndef Q_MOC_RUN  // See: https://bugreports.qt-project.org/browse/QTBUG-22829  //tag=QT4-boost-compatibility
#include "ConfigureMonteverdi.h"
#endif //tag=QT4-boost-compatibility

#include "OTBMonteverdiCoreExport.h"

/*****************************************************************************/
/* INCLUDE SECTION                                                           */

//
// Qt includes (sorted by alphabetic order)
//// Must be included before system/custom includes.
#include <QtCore>

//
// System includes (sorted by alphabetic order)

//
// ITK includes (sorted by alphabetic order)

//
// OTB includes (sorted by alphabetic order)

//
// Monteverdi includes (sorted by alphabetic order)
#ifndef Q_MOC_RUN  // See: https://bugreports.qt-project.org/browse/QTBUG-22829  //tag=QT4-boost-compatibility
#include "mvdAbstractModel.h"
#include "mvdTypes.h"
#include "mvdVisibleInterface.h"
#endif //tag=QT4-boost-compatibility

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


//
// Global types.

/**
 */
enum SpatialReferenceType
{
  SRT_UNKNOWN =0,
  SRT_CARTO,
  SRT_GEO,
  SRT_SENSOR,
};

//
// Global functions.

/**
 */
OTBMonteverdiCore_EXPORT SpatialReferenceType GetSpatialReferenceType( const std::string & filename );

/**
 */
OTBMonteverdiCore_EXPORT SpatialReferenceType GetSpatialReferenceType( const std::string & wkt, bool hasKwl );

/*****************************************************************************/
/* CLASS DEFINITION SECTION                                                  */

/**
 * \class AbstractLayerModel
 *
 * \ingroup OTBMonteverdiCore
 *
 * \brief WIP.
 */
class OTBMonteverdiCore_EXPORT AbstractLayerModel :
    public AbstractModel,
    public VisibleInterface
{

  /*-[ QOBJECT SECTION ]-----------------------------------------------------*/

  Q_OBJECT;

  /*-[ PUBLIC SECTION ]------------------------------------------------------*/

//
// Public methods.
public:

  /** \brief Destructor. */
  ~AbstractLayerModel() ITK_OVERRIDE;

  /**
   */
  SpatialReferenceType GetSpatialReferenceType() const;

  /**
   */
  std::string GetWkt() const;

  /**
   */
  std::string GetAuthorityCode( bool ) const;

  /**
   */
  void ToWgs84( const PointType &, PointType & wgs84, double & alt ) const;

  /*-[ PUBLIC SLOTS SECTION ]------------------------------------------------*/

//
// Public SLOTS.
public slots:

  /*-[ SIGNALS SECTION ]-----------------------------------------------------*/

//
// Signals.
signals:
  /**
   */
  void VisibilityChanged( bool =true );
  void VisibilityChanged( AbstractLayerModel *, bool );

  /*-[ PROTECTED SECTION ]---------------------------------------------------*/

//
// Protected methods.
protected:

  /** \brief Constructor. */
  AbstractLayerModel( QObject* p =NULL );

  /**
   */
  bool HasKwl() const;

//
// Protected attributes.
protected:

  /*-[ PRIVATE SECTION ]-----------------------------------------------------*/

//
// Private methods.
private:

  /**
   */
  virtual std::string virtual_GetWkt() const =0;

  /**
   */
  virtual bool virtual_HasKwl() const;

  /**
   */
  virtual void virtual_ToWgs84( const PointType &, PointType & wgs84, double & alt ) const =0;

  //
  // VisibleInterface overloads.
  void virtual_SignalVisibilityChanged( bool ) ITK_OVERRIDE;

//
// Private attributes.
private:

  /*-[ PRIVATE SLOTS SECTION ]-----------------------------------------------*/

//
// Slots.
private slots:
};

} // end namespace 'mvd'.

/*****************************************************************************/
/* INLINE SECTION                                                            */

//
// Qt includes (sorted by alphabetic order)
//// Must be included before system/custom includes.

//
// System includes (sorted by alphabetic order)

//
// ITK includes (sorted by alphabetic order)

//
// OTB includes (sorted by alphabetic order)

//
// Monteverdi includes (sorted by alphabetic order)

namespace mvd
{
} // end namespace 'mvd'

#endif // mvdAbstractLayerModel_h
