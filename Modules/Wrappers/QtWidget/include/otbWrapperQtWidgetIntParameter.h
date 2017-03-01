/*=========================================================================

  Program:   ORFEO Toolbox
  Language:  C++


  Copyright (c) Centre National d'Etudes Spatiales. All rights reserved.
  See OTBCopyright.txt for details.


     This software is distributed WITHOUT ANY WARRANTY; without even
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
     PURPOSE.  See the above copyright notices for more information.

=========================================================================*/
#ifndef otbWrapperQtWidgetIntParameter_h
#define otbWrapperQtWidgetIntParameter_h

#include <QtGui>
#ifndef Q_MOC_RUN  // See: https://bugreports.qt-project.org/browse/QTBUG-22829  //tag=QT4-boost-compatibility
#include "otbWrapperNumericalParameter.h"
#include "otbWrapperQtWidgetParameterBase.h"
#endif //tag=QT4-boost-compatibility


namespace otb
{
namespace Wrapper
{

/** \class QtWidgetIntParameter
 * \brief
 *
 * \ingroup OTBQtWidget
 */
class OTBQtWidget_EXPORT QtWidgetIntParameter : public QtWidgetParameterBase
{
  Q_OBJECT
public:
  QtWidgetIntParameter(IntParameter*, QtWidgetModel*);
  ~QtWidgetIntParameter() ITK_OVERRIDE;

protected slots:
  void SetValue( int value );

private:
  QtWidgetIntParameter(const QtWidgetIntParameter&); //purposely not implemented
  void operator=(const QtWidgetIntParameter&); //purposely not implemented

  void DoCreateWidget() ITK_OVERRIDE;

  void DoUpdateGUI() ITK_OVERRIDE;

  QHBoxLayout *         m_QHBoxLayout;
  QSpinBox *            m_QSpinBox;

  IntParameter::Pointer m_IntParam;
};


}
}

#endif
