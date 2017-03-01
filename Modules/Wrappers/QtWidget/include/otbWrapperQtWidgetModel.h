/*=========================================================================

  Program:   ORFEO Toolbox
  Language:  C++


  Copyright (c) Centre National d'Etudes Spatiales. All rights reserved.
  See OTBCopyright.txt for details.


     This software is distributed WITHOUT ANY WARRANTY; without even
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
     PURPOSE.  See the above copyright notices for more information.

=========================================================================*/
#ifndef otbWrapperQtWidgetModel_h
#define otbWrapperQtWidgetModel_h

#include <QtGui>
#include <QTimer>
#ifndef Q_MOC_RUN  // See: https://bugreports.qt-project.org/browse/QTBUG-22829  //tag=QT4-boost-compatibility
#include "otbWrapperApplication.h"
#include "otbQtLogOutput.h"
#endif //tag=QT4-boost-compatibility

namespace otb
{

namespace Wrapper
{

class OTBQtWidget_EXPORT AppliThread : public QThread
{
 Q_OBJECT

 public:
  inline AppliThread(Application* app)
    {
      m_Application = app;
    }

  ~AppliThread() ITK_OVERRIDE;

  inline void Execute()
  {
    // Call the signal start to begin running the program
    start();
  }

signals:
  /**
   * \brief Signal emitted when the OTB-application has finished.
   *
   * \param status 0 The result status of the OTB-application.
   */
  void ApplicationExecutionDone( int status =0 );

  /**
   * \brief Signal emitted when an exception has been raised by an
   * otb::Application and is caught by this calling QThread.
   *
   * \param what The std::exception::what() which is forwarded to listeners.
   */
  void ExceptionRaised( QString what );

protected:
  void run() ITK_OVERRIDE;

private:
  AppliThread(const AppliThread&); //purposely not implemented
  void operator=(const AppliThread&); //purposely not implemented

  Application::Pointer m_Application;
};


/** \class QtWidgetModel
 * \brief
 *
 * \ingroup OTBQtWidget
 */
class OTBQtWidget_EXPORT QtWidgetModel : public QObject
{
  Q_OBJECT
public:
  QtWidgetModel(Application* app);

  ~QtWidgetModel() ITK_OVERRIDE;

  Application* GetApplication()
  {
    return m_Application;
  }

  QtLogOutput::Pointer GetLogOutput()
  {
    return m_LogOutput;
  }

  /** Logger warning message sender */
  void SendLogWARNING( const std::string & mes );
  /** Logger info message sender */
  void SendLogINFO( const std::string & mes );
  /** Logger debug message sender */
  void SendLogDEBUG( const std::string & mes );

  /** Used by inxml when forcing xml parse flag to update widget data via UpdateGui */
  void UpdateAllWidgets()
  {
    GetApplication()->ForceInXMLParseFlag();
    emit UpdateGui();
  }

signals:
  void SetApplicationReady(bool);

  void SetProgressReportBegin();

  /**
   * \brief Signal emitted when execution otb::Application has finished.
   *
   * \param status The result status of the otb::application (-1 when
   * an exception has occurred).
   */
  void SetProgressReportDone( int status =0 );

  /**
   * \brief Signal emitted when an exception has been raised by an
   * otb::Application and is caught by the calling QThread.
   *
   * \param what The std::exception::what() which is forwarded to listeners.
   */
  void ExceptionRaised( QString what );

  void UpdateGui();

protected slots:
  /**
   * \brief Slot called when execution is requested (e.g. by
   * otb::Wrapper::QtWidgetView).
   *
   * This slot is protected so it can only be called via Qt
   * signal/slot mechanism and not directly by extern caller.
   */
  void ExecuteAndWriteOutputSlot();

  /**
   * \brief Slots called every time one of the widget needs to be
   * updated (e.g. by specialized parameter widgets).
   *
   * This slot is protected so it can only be called via Qt
   * signal/slot mechanism and not directly by extern caller.
   */
  void NotifyUpdate();

private slots:
  /**
   * \brief
   *
   * \param status
   */
  void OnApplicationExecutionDone( int status );

  void TimerDone();

private:
  QtWidgetModel(const QtWidgetModel&); //purposely not implemented
  void operator=(const QtWidgetModel&); //purposely not implemented

  Application::Pointer m_Application;

  QtLogOutput::Pointer  m_LogOutput;

  bool m_IsRunning;

  QTimer *m_Timer;
};


}
}

#endif
