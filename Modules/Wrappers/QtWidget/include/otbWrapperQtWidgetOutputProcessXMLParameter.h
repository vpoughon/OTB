/*=========================================================================

  Program:   ORFEO Toolbox
  Language:  C++


  Copyright (c) Centre National d'Etudes Spatiales. All rights reserved.
  See OTBCopyright.txt for details.


     This software is distributed WITHOUT ANY WARRANTY; without even
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
     PURPOSE.  See the above copyright notices for more information.

=========================================================================*/
#ifndef otbWrapperQtWidgetOutputProcessXMLParameter_h
#define otbWrapperQtWidgetOutputProcessXMLParameter_h

#include <QtGui>
#ifndef Q_MOC_RUN  // See: https://bugreports.qt-project.org/browse/QTBUG-22829  //tag=QT4-boost-compatibility
#include "otbWrapperOutputProcessXMLParameter.h"
#include "otbWrapperQtWidgetParameterBase.h"
#endif //tag=QT4-boost-compatibility


namespace otb
{
namespace Wrapper
{

/** \class QtWidgetOutputProcessXMLParameter
 * \brief
 *
 * \ingroup OTBQtWidget
 */
class OTBQtWidget_EXPORT QtWidgetOutputProcessXMLParameter : public QtWidgetParameterBase
{
  Q_OBJECT
public:
  QtWidgetOutputProcessXMLParameter(OutputProcessXMLParameter*, QtWidgetModel*);
  ~QtWidgetOutputProcessXMLParameter() ITK_OVERRIDE;

  inline const QLineEdit* GetInput() const;
  inline QLineEdit* GetInput();

public slots:
  void SetFileName( const QString& value );

protected slots:
  void SelectFile();

private:
  QtWidgetOutputProcessXMLParameter(const QtWidgetOutputProcessXMLParameter&); //purposely not implemented
  void operator=(const QtWidgetOutputProcessXMLParameter&); //purposely not implemented

  void DoCreateWidget() ITK_OVERRIDE;

  void DoUpdateGUI() ITK_OVERRIDE;


  OutputProcessXMLParameter::Pointer m_XMLParam;

  QHBoxLayout * m_HLayout;
  QLineEdit*    m_Input;
  QPushButton * m_Button;
};


inline
const QLineEdit*
QtWidgetOutputProcessXMLParameter
::GetInput() const
{
  return m_Input;
}

inline
QLineEdit*
QtWidgetOutputProcessXMLParameter
::GetInput()
{
  return m_Input;
}

}
}

#endif
