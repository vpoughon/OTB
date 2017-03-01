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

#ifndef otbWrapperQtWidgetChoiceParameter_h
#define otbWrapperQtWidgetChoiceParameter_h

#include <QtGui>
#ifndef Q_MOC_RUN  // See: https://bugreports.qt-project.org/browse/QTBUG-22829  //tag=QT4-boost-compatibility
#include "otbWrapperChoiceParameter.h"
#include "otbWrapperQtWidgetParameterBase.h"
#endif //tag=QT4-boost-compatibility

namespace otb
{
namespace Wrapper
{

/** \class QtWidgetChoiceParameter
 * \brief
 *
 * \ingroup OTBQtWidget
 */
class OTBQtWidget_EXPORT QtWidgetChoiceParameter : public QtWidgetParameterBase
{
  Q_OBJECT
public:
  QtWidgetChoiceParameter(ChoiceParameter*, QtWidgetModel*);
  ~QtWidgetChoiceParameter() ITK_OVERRIDE;

protected slots:
  void SetValue( int value );

private:
  QtWidgetChoiceParameter(const QtWidgetChoiceParameter&); //purposely not implemented
  void operator=(const QtWidgetChoiceParameter&); //purposely not implemented

  void DoCreateWidget() ITK_OVERRIDE;

  void DoUpdateGUI() ITK_OVERRIDE;

  ChoiceParameter::Pointer m_ChoiceParam;

  QHBoxLayout*    m_MainHLayout;

  QComboBox*      m_ComboBox;
  QStackedWidget* m_StackWidget;

  QVBoxLayout*    m_VLayout;
  QGroupBox*      m_VLayoutGroup;

  typedef std::vector<QtWidgetParameterBase*> WidgetListType;
  typedef WidgetListType::iterator WidgetListIteratorType;
  WidgetListType m_WidgetList;
};

}
}

#endif
