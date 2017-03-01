/*=========================================================================

  Program:   ORFEO Toolbox
  Language:  C++


  Copyright (c) Centre National d'Etudes Spatiales. All rights reserved.
  See OTBCopyright.txt for details.


     This software is distributed WITHOUT ANY WARRANTY; without even
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
     PURPOSE.  See the above copyright notices for more information.

=========================================================================*/
#ifndef otbWrapperQtWidgetProgressReport_h
#define otbWrapperQtWidgetProgressReport_h

#include <QtGui>
#ifndef Q_MOC_RUN  // See: https://bugreports.qt-project.org/browse/QTBUG-22829  //tag=QT4-boost-compatibility
#include "otbWrapperQtWidgetModel.h"
#include "itkQtProgressBar.h"
#include "itkProcessObject.h"
#endif //tag=QT4-boost-compatibility


namespace otb
{
namespace Wrapper
{

/** \class QtWidgetProgressReport
 * \brief Create a widget reporting the progress of the application
 *        process.
 *
 * \ingroup OTBQtWidget
 */
class OTBQtWidget_EXPORT QtWidgetProgressReport : public QWidget
{
  Q_OBJECT
public:
  QtWidgetProgressReport(QtWidgetModel * model);
  ~QtWidgetProgressReport() ITK_OVERRIDE;

  void SetApplication(Application::Pointer app);

  typedef itk::MemberCommand< QtWidgetProgressReport >  AddProcessCommandType;

  void ProcessEvent( itk::Object * caller, const itk::EventObject & event );

  std::string GetCurrentDescription()
  {
    return m_CurrentDescription;
  }

/*
  itk::ProcessObject* GetCurrentProcess()
  {
    return m_CurrentProcess;
  }

  QtWidgetModel * GetModel()
  {
    m_Model;
  }

  QVBoxLayout * GetLayout()
  {
    return m_Layout;
  }
*/
public slots:
  void RemoveLayout();
  /*virtual */void ReportProcess();

  signals:
  void AddNewProcessToReport();

private:
  QtWidgetProgressReport(const QtWidgetProgressReport&); //purposely not implemented
  void operator=(const QtWidgetProgressReport&); //purposely not implemented

  Application::Pointer              m_Application;
  QtWidgetModel *                   m_Model;
  QVBoxLayout *                     m_Layout;

  AddProcessCommandType::Pointer    m_AddProcessCommand;
  itk::ProcessObject*               m_CurrentProcess;
  std::string                       m_CurrentDescription;
};

}
}

#endif
