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

#ifndef otbWrapperQtWidgetComplexOutputImageParameter_h
#define otbWrapperQtWidgetComplexOutputImageParameter_h

#include <QtGui>
#ifndef Q_MOC_RUN  // See: https://bugreports.qt-project.org/browse/QTBUG-22829  //tag=QT4-boost-compatibility
#include "otbWrapperComplexOutputImageParameter.h"
#include "otbWrapperQtWidgetParameterBase.h"
#endif //tag=QT4-boost-compatibility


namespace otb
{
namespace Wrapper
{

/** \class QtWidgetComplexOutputImageParameter
 * \brief
 *
 * \ingroup OTBQtWidget
 */
class OTBQtWidget_EXPORT QtWidgetComplexOutputImageParameter : public QtWidgetParameterBase
{
  Q_OBJECT
public:
  QtWidgetComplexOutputImageParameter(ComplexOutputImageParameter*, QtWidgetModel*);
  ~QtWidgetComplexOutputImageParameter() ITK_OVERRIDE;

  /** Get the PixelType*/
  //itkGetMacro(PixelType, int);

protected slots:
  void SetFileName( const QString& value );
  void SelectFile();
  void SetPixelType(int pixelType);

private:
  QtWidgetComplexOutputImageParameter(const QtWidgetComplexOutputImageParameter&); //purposely not implemented
  void operator=(const QtWidgetComplexOutputImageParameter&); //purposely not implemented

  void DoCreateWidget() ITK_OVERRIDE;

  void DoUpdateGUI() ITK_OVERRIDE;

  std::string m_FileName;
  ComplexOutputImageParameter::Pointer m_OutputImageParam;

  QHBoxLayout * m_HLayout;
  QLineEdit*    m_Input;
  QPushButton * m_Button;
  QComboBox*    m_ComboBox;
  int           m_ComplexPixelType;

};


}
}

#endif
