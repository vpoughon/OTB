/*=========================================================================

  Program:   ORFEO Toolbox
  Language:  C++


  Copyright (c) Centre National d'Etudes Spatiales. All rights reserved.
  See OTBCopyright.txt for details.


     This software is distributed WITHOUT ANY WARRANTY; without even
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
     PURPOSE.  See the above copyright notices for more information.

=========================================================================*/
#ifndef otbWrapperQtWidgetSimpleProgressReport_h
#define otbWrapperQtWidgetSimpleProgressReport_h

#include <QtGui>
#ifndef Q_MOC_RUN  // See: https://bugreports.qt-project.org/browse/QTBUG-22829  //tag=QT4-boost-compatibility
#include "otbWrapperQtWidgetModel.h"
#include "itkProcessObject.h"
#include "itkQtProgressBar.h"
#endif //tag=QT4-boost-compatibility


namespace otb
{
namespace Wrapper
{

/** \class QtWidgetSimpleProgressReport
 * \brief Create a widget reporting the progress of the application
 *        process.
 *
 * \ingroup OTBQtWidget
 */
class OTBQtWidget_EXPORT QtWidgetSimpleProgressReport : public QWidget
{
  Q_OBJECT
public:
  QtWidgetSimpleProgressReport(QtWidgetModel * model);
  ~QtWidgetSimpleProgressReport() ITK_OVERRIDE;

  void SetApplication(Application::Pointer app);

  typedef itk::MemberCommand< QtWidgetSimpleProgressReport >  AddProcessCommandType;

  void ProcessEvent( itk::Object * caller, const itk::EventObject & event );

public slots:
  void Init();
  void ReportProcess();

  signals:
  void AddNewProcessToReport();

private:
  QtWidgetSimpleProgressReport(const QtWidgetSimpleProgressReport&); //purposely not implemented
  void operator=(const QtWidgetSimpleProgressReport&); //purposely not
                                                       //implemented

  Application::Pointer              m_Application;
  QtWidgetModel *                   m_Model;
  QVBoxLayout *                     m_Layout;

  AddProcessCommandType::Pointer    m_AddProcessCommand;
  itk::ProcessObject*               m_CurrentProcess;
  std::string                       m_CurrentDescription;

  itk::QtProgressBar * m_Bar;
  QLabel * m_Label;

};

}
}

#endif
