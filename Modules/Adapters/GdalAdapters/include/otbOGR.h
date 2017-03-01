/*=========================================================================

  Program:   ORFEO Toolbox
  Language:  C++


  Copyright (c) Centre National d'Etudes Spatiales. All rights reserved.
  See OTBCopyright.txt for details.


     This software is distributed WITHOUT ANY WARRANTY; without even
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
     PURPOSE.  See the above copyright notices for more information.

=========================================================================*/
#ifndef otbOGR_h
#define otbOGR_h

namespace otb {
  /**\defgroup gGeometry Geometry
   * \ingroup Thematic
   * \brief Classes and functions aimed toward the manipulation of set of geometric objects.
   * This module mainly provides an encapsulation of <a
   * href="http://www.gdal.org/ogr/">OGR API</a>.
   * @{
   */
  namespace ogr { }
  //@}
} // namespace otb

#include "otbOGRDriversInit.h"
#include "otbOGRDataSourceWrapper.h"
// #include "otbOGRLayerWrapper.h" // implicit
// #include "otbOGRFeatureWrapper.h" // implicit
// #include "otbOGRFieldWrapper.h" // implicit
// #include "otbOGRGeometryWrapper.h" // implicit

/**\ingroup gGeometry
 * \file    otbOGR.h
 * \brief How to include all include files dedicated to OGR encapsulation in OTB...
 */


#endif // otbOGR_h
