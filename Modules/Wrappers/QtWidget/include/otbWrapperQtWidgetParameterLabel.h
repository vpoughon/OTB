/*=========================================================================

  Program:   ORFEO Toolbox
  Language:  C++


  Copyright (c) Centre National d'Etudes Spatiales. All rights reserved.
  See OTBCopyright.txt for details.


     This software is distributed WITHOUT ANY WARRANTY; without even
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
     PURPOSE.  See the above copyright notices for more information.

=========================================================================*/
#ifndef otbWrapperQtWidgetParameterLabel_h
#define otbWrapperQtWidgetParameterLabel_h

#include <QtGui>
#ifndef Q_MOC_RUN  // See: https://bugreports.qt-project.org/browse/QTBUG-22829  //tag=QT4-boost-compatibility
#include "otbWrapperParameter.h"
#endif //tag=QT4-boost-compatibility

#include "OTBQtWidgetExport.h"

namespace otb
{
namespace Wrapper
{

/** \class QtWidgetParameterLabel
 * \brief
 *
 * \ingroup OTBQtWidget
 */
class OTBQtWidget_EXPORT QtWidgetParameterLabel : public QWidget
{
  Q_OBJECT
public:
  QtWidgetParameterLabel(Parameter*);
  ~QtWidgetParameterLabel() ITK_OVERRIDE;

private:
  QtWidgetParameterLabel(const QtWidgetParameterLabel&); //purposely not implemented
  void operator=(const QtWidgetParameterLabel&); //purposely not implemented
};


}
}

#endif
