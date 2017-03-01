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

#ifndef otbWrapperQtWidgetRAMParameter_h
#define otbWrapperQtWidgetRAMParameter_h

#include <QtGui>
#ifndef Q_MOC_RUN  // See: https://bugreports.qt-project.org/browse/QTBUG-22829  //tag=QT4-boost-compatibility
#include "otbWrapperRAMParameter.h"
#include "otbWrapperQtWidgetParameterBase.h"
#endif //tag=QT4-boost-compatibility


namespace otb
{
namespace Wrapper
{

/** \class QtWidgetRAMParameter
 * \brief
 *
 * \ingroup OTBQtWidget
 */
class OTBQtWidget_EXPORT QtWidgetRAMParameter : public QtWidgetParameterBase
{
  Q_OBJECT
public:
  QtWidgetRAMParameter(RAMParameter*, QtWidgetModel*);
  ~QtWidgetRAMParameter() ITK_OVERRIDE;

protected slots:
  void SetValue( int value );

private:
  QtWidgetRAMParameter(const QtWidgetRAMParameter&); //purposely not implemented
  void operator=(const QtWidgetRAMParameter&); //purposely not implemented

  void DoCreateWidget() ITK_OVERRIDE;

  void DoUpdateGUI() ITK_OVERRIDE;

  QHBoxLayout *         m_QHBoxLayout;
  QSpinBox *            m_QSpinBox;

  RAMParameter::Pointer m_RAMParam;
};


}
}

#endif
