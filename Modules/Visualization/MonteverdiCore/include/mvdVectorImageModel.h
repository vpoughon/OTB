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


#ifndef mvdVectorImageModel_h
#define mvdVectorImageModel_h

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

//
// System includes (sorted by alphabetic order)

//
// ITK includes (sorted by alphabetic order)
#ifndef Q_MOC_RUN  // See: https://bugreports.qt-project.org/browse/QTBUG-22829  //tag=QT4-boost-compatibility
#include "itkExtractImageFilter.h"
#endif //tag=QT4-boost-compatibility

//
// OTB includes (sorted by alphabetic order)
#ifndef Q_MOC_RUN  // See: https://bugreports.qt-project.org/browse/QTBUG-22829  //tag=QT4-boost-compatibility
#include "otbGenericRSTransform.h"
#endif //tag=QT4-boost-compatibility

//
// Monteverdi includes (sorted by alphabetic order)
#ifndef Q_MOC_RUN  // See: https://bugreports.qt-project.org/browse/QTBUG-22829  //tag=QT4-boost-compatibility
#include "mvdAbstractImageModel.h"
#include "mvdFilenameInterface.h"
#include "mvdVectorImageSettings.h"
#include "mvdTypes.h"
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
class DatasetModel;


/*****************************************************************************/
/* CLASS DEFINITION SECTION                                                  */

/** \class VectorImageModel
 *
 * \ingroup OTBMonteverdiCore
 *
 */
class OTBMonteverdiCore_EXPORT VectorImageModel :
    public AbstractImageModel,
    public FilenameInterface
{

  /*-[ QOBJECT SECTION ]-----------------------------------------------------*/

  Q_OBJECT;

  /*-[ PUBLIC SECTION ]------------------------------------------------------*/

//
// Public types.
public:
  /**
   * In-memory storage type of source image (from file).
   */
  typedef DefaultImageType SourceImageType;

//
// Public methods.
public:

  /**
   */
  static const unsigned int DEFAULT_LOD_SIZE;

  /** Constructor */
  VectorImageModel( QObject* p =NULL );

  /** Destructor */
  ~VectorImageModel() ITK_OVERRIDE;

  /** */
  static void EnsureValidImage( const QString& filename );

  /** */
  // TODO: Move into template wrapper base-class.
  SourceImageType::ConstPointer ToImage() const;

  /** */
  // TODO: Move into template wrapper base-class.
  const SourceImageType::Pointer& ToImage();

  /**
   */
  inline const VectorImageSettings & GetSettings() const;

  /** */
  inline VectorImageSettings & GetSettings();

  /** */
  inline void SetSettings( const VectorImageSettings & settings );

  /** */
  inline const otb::GenericRSTransform<> * GetGenericRSTransform() const;

  /**
   * Width and height are added to compute the best level of detail to
   * load from the image if multi-resolution image.
   */
  void SetFilename( const QString& filename, int width, int height );

  /**
   * Following the zoom factor, get the best level of detail
   */
  CountType ComputeBestLod( double ZoomFactor ) const;

  /**
   * Following the zoom factor, get the best level of detail
   */
  CountType ComputeBestLod( int width, int height ) const;

  //
  // AbstractImageModel methods.

  /**
   * Get the number of available LOD.
   */
  CountType GetNbLod() const ITK_OVERRIDE;

  /**
   * Get a smart-pointer to the current LOD image-base.
   */
  ImageBaseType::ConstPointer ToImageBase() const ITK_OVERRIDE;

  /**
   * Get a smart-pointer to the current LOD image-base.
   */
  ImageBaseType::Pointer ToImageBase() ITK_OVERRIDE;

  /**
   * Get the placename from the center pixel
   */
  std::string GetCenterPixelPlaceName();

  //
  // AbstractModel methods.

  bool IsModified() const ITK_OVERRIDE;

  void ClearModified() ITK_OVERRIDE;

  // get image size in byte
  std::streamoff GetImageSizeInBytes()
  {
    return m_ImageFileReader->GetImageIO()->GetImageSizeInBytes();
  }

  /*-[ PUBLIC SLOTS SECTION ]------------------------------------------------*/

//
// Public slots.
public slots:
  /**
   */
  void OnPhysicalCursorPositionChanged( const QPoint &,
                                        const PointType &,
                                        const PointType &,
                                        const DefaultImageType::PixelType & );

  /*-[ SIGNALS SECTION ]-----------------------------------------------------*/

//
// Signals.
signals:
  /**
   */
  void SettingsUpdated( AbstractImageModel* imageModel =NULL );

  /**
   */
  void PropertiesUpdated( AbstractImageModel* imageModel =NULL );

  /**   */
  void ViewportRegionChanged(double, double);

  /** */
  void CurrentIndexUpdated( const IndexType&, bool isInside );
  void CurrentIndexUpdated(const QString&);
  void CurrentPhysicalUpdated(const QStringList&);
  void CurrentGeographicUpdated(const QStringList&);
  void CurrentRadioUpdated(const QString&);
  void CurrentPixelValueUpdated(const VectorImageType::PixelType &,
                                const QStringList& );

  /*-[ PROTECTED SECTION ]---------------------------------------------------*/

//
// Protected methods.
protected:

  //
  // AbstractModel methods.

  void virtual_BuildModel( void* context =NULL ) ITK_OVERRIDE;

  //
  // AbstractImageModel methods.

  void InitializeColorSetupSettings();

  void InitializeColorDynamicsSettings();

//
// Protected attributes.
protected:

  /** */
  SourceImageType::Pointer m_Image;

  /*-[ PRIVATE SECTION ]-----------------------------------------------------*/

//
// Private types.
private:

//
// Private methods.
private:

  /**
    * Helper method to get the best closest Jpeg2K level of detail.
    */
  static
    unsigned int
    Closest( double invZoomfactor,
             unsigned int lodCount );

  /**
    * helper to setup the lod image using a width/height or a zoom factor
    */
  void SetupCurrentLodImage(int w, int h);

  /**
   */
  void ApplySettings();

  /**
   */
  void BuildGdalOverviews();

  //
  // AbstractLayerModel methods.

  std::string virtual_GetWkt() const ITK_OVERRIDE;
  bool virtual_HasKwl() const ITK_OVERRIDE;
  void virtual_ToWgs84( const PointType &,
				PointType &,
				double & alt ) const ITK_OVERRIDE;

  //
  // AbstractImageModel methods.

  void virtual_SetCurrentLod( CountType lod ) ITK_OVERRIDE;

  void virtual_RefreshHistogram() ITK_OVERRIDE;

//
// Private attributes.
private:
  // Default image reader
  DefaultImageFileReaderType::Pointer m_ImageFileReader;

  /**
   * User-configurable settings of image-model.
   */
  VectorImageSettings m_Settings;

  /** List of all Level of detail (Resolution) available from the file */
  CountType m_LodCount;

  //  Generic RS Transform to get lat/long coordinates
  otb::GenericRSTransform<>::Pointer m_ToWgs84;

  /*-[ PRIVATE SLOTS SECTION ]-----------------------------------------------*/

//
// Slots.
private slots:
  /** */
  void OnModelUpdated();
};

} // end namespace 'mvd'.

/*****************************************************************************/
/* INLINE SECTION                                                            */

//
// Monteverdi includes (sorted by alphabetic order)


namespace mvd
{

/*****************************************************************************/
inline
VectorImageModel::SourceImageType::ConstPointer
VectorImageModel
::ToImage() const
{
  // TODO: Fix unsafe weak-pointer dereferencing.
  return otb::ConstCast< VectorImageModel::SourceImageType >( m_Image );
}

/*****************************************************************************/
inline
const VectorImageModel::SourceImageType::Pointer&
VectorImageModel
::ToImage()
{
  return m_Image;
}

/*****************************************************************************/
inline
void
VectorImageModel
::SetSettings( const VectorImageSettings & settings )
{
  m_Settings = settings;
}

/*****************************************************************************/
inline
const VectorImageSettings &
VectorImageModel
::GetSettings() const
{
  return m_Settings;
}

/*****************************************************************************/
inline
VectorImageSettings &
VectorImageModel
::GetSettings()
{
  return m_Settings;
}

/*****************************************************************************/
inline
const otb::GenericRSTransform<> *
VectorImageModel
::GetGenericRSTransform() const
{
  return m_ToWgs84;
}

/*****************************************************************************/

} // end namespace 'mvd'

#endif // mvdVectorImageModel_h
