/*=========================================================================

  Program:   ORFEO Toolbox
  Language:  C++


  Copyright (c) Centre National d'Etudes Spatiales. All rights reserved.
  See OTBCopyright.txt for details.


     This software is distributed WITHOUT ANY WARRANTY; without even
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
     PURPOSE.  See the above copyright notices for more information.

=========================================================================*/
#ifndef otbQtFileSelectionWidget_h
#define otbQtFileSelectionWidget_h

#include <QtGui>
#ifndef Q_MOC_RUN  // See: https://bugreports.qt-project.org/browse/QTBUG-22829  //tag=QT4-boost-compatibility
#include "otbWrapperInputImageListParameter.h"
#include "otbWrapperInputFilenameListParameter.h"
#include "otbWrapperQtWidgetParameterBase.h"
#endif //tag=QT4-boost-compatibility

#include "OTBQtWidgetExport.h"

namespace otb
{
namespace Wrapper
{

/** \class QtFileSelectionWidget
 * \brief
 *
 * \ingroup OTBQtWidget
 */
class OTBQtWidget_EXPORT QtFileSelectionWidget : public QWidget
{
  Q_OBJECT
public:
  enum IOMode
  {
    IO_MODE_INPUT = 0,
    IO_MODE_OUTPUT = 1,
  };

  QtFileSelectionWidget();
  ~QtFileSelectionWidget() ITK_OVERRIDE;

  bool IsChecked()
  {
    return m_Checkbox->isChecked();
  }

  void SetChecked( bool val )
  {
    return m_Checkbox->setChecked( val );
  }

  std::string GetFilename()
  {
    return QFile::encodeName( m_Input->text() ).constData();
  }

  void ClearFilename()
  {
    m_Input->clear();
  }

  QLineEdit* GetInput()
  {
    return m_Input;
  }

  void SetIOMode( IOMode );
  IOMode GetIOMode() const;

protected slots:
  void SelectFile();

private:
  QtFileSelectionWidget(const QtFileSelectionWidget&); //purposely not implemented
  void operator=(const QtFileSelectionWidget&); //purposely not implemented

  virtual void DoCreateWidget();

  virtual void DoUpdateGUI();


  QHBoxLayout * m_HLayout;
  QLineEdit * m_Input;
  QPushButton * m_Button;
  QCheckBox * m_Checkbox;
  IOMode m_IOMode;
};


}
}

#endif
