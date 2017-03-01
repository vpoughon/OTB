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

#ifndef otbWrapperQtWidgetListViewParameter_h
#define otbWrapperQtWidgetListViewParameter_h

#include <QtGui>
#ifndef Q_MOC_RUN  // See: https://bugreports.qt-project.org/browse/QTBUG-22829  //tag=QT4-boost-compatibility
#include "otbWrapperListViewParameter.h"
#include "otbWrapperQtWidgetParameterBase.h"
#endif //tag=QT4-boost-compatibility

namespace otb
{
namespace Wrapper
{

/** \class QtWidgetListViewParameter
 * \brief
 *
 * \ingroup OTBQtWidget
 */
class OTBQtWidget_EXPORT QtWidgetListViewParameter : public QtWidgetParameterBase
{
  Q_OBJECT
public:
  QtWidgetListViewParameter(ListViewParameter*, QtWidgetModel*);
  ~QtWidgetListViewParameter() ITK_OVERRIDE;

  std::vector<int>  GetSelectedItems()
  {
    return m_SelectedItems;
  }

protected slots:
  void SelectedItems();

private:
  QtWidgetListViewParameter(const QtWidgetListViewParameter&); //purposely not implemented
  void operator=(const QtWidgetListViewParameter&); //purposely not implemented

  void DoCreateWidget() ITK_OVERRIDE;

  void DoUpdateGUI() ITK_OVERRIDE;

  ListViewParameter::Pointer m_ListViewParam;

  QListWidget*               m_ListView;

  QHBoxLayout*               m_VLayout;

  std::vector<int>           m_SelectedItems;

  int                        m_LineHeight;
};

}
}

#endif
