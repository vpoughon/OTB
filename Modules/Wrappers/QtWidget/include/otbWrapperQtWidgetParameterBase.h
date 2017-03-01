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

#ifndef otbWrapperQtWidgetParameterBase_h
#define otbWrapperQtWidgetParameterBase_h

#include <QtGui>
#ifndef Q_MOC_RUN  // See: https://bugreports.qt-project.org/browse/QTBUG-22829  //tag=QT4-boost-compatibility
#include "otbWrapperParameter.h"
#include "otbWrapperQtWidgetModel.h"
#endif //tag=QT4-boost-compatibility
#include "OTBQtWidgetExport.h"

namespace otb
{
namespace Wrapper
{

/** \class QtWidgetParameterBase
 * \brief
 *
 * \ingroup OTBQtWidget
 */
class OTBQtWidget_EXPORT QtWidgetParameterBase : public QWidget
{
  Q_OBJECT
public:
  QtWidgetParameterBase(Parameter *, QtWidgetModel*);
  ~QtWidgetParameterBase() ITK_OVERRIDE;

  void CreateWidget();

public slots:
  void UpdateGUI();
  virtual void SetActivationState( bool value );
  void Reset();

protected slots:
  void ParameterChanged(const QString& key);

signals:
  void ParameterActiveStatus(bool value);

protected:
  QtWidgetModel* GetModel();


private:
  QtWidgetParameterBase(const QtWidgetParameterBase&); //purposely not implemented
  void operator=(const QtWidgetParameterBase&); //purposely not implemented

  virtual void DoUpdateGUI() = 0;

  virtual void DoCreateWidget() = 0;

  QtWidgetModel* m_Model;

  Parameter*      m_Param;
};


}
}

#endif
