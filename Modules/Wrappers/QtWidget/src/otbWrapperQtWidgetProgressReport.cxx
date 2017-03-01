/*=========================================================================

  Program:   ORFEO Toolbox
  Language:  C++


  Copyright (c) Centre National d'Etudes Spatiales. All rights reserved.
  See OTBCopyright.txt for details.


     This software is distributed WITHOUT ANY WARRANTY; without even
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
     PURPOSE.  See the above copyright notices for more information.

=========================================================================*/

#include "otbWrapperQtWidgetProgressReport.h"
#include "otbWrapperOutputImageParameter.h"
#include "itksys/SystemTools.hxx"

#include "otbWrapperAddProcessToWatchEvent.h"

namespace otb
{
namespace Wrapper
{

QtWidgetProgressReport::QtWidgetProgressReport(QtWidgetModel * model)
  : m_CurrentProcess()
{
  m_Model = model;
  connect(model, SIGNAL(SetProgressReportBegin()), this, SLOT(show()) );
  connect(model, SIGNAL(SetProgressReportDone()), this, SLOT(close()) );
  connect(model, SIGNAL(SetProgressReportDone()), this, SLOT(RemoveLayout()) );
  connect(this, SIGNAL(AddNewProcessToReport()), this, SLOT(ReportProcess()) );

  m_Layout = new QVBoxLayout;
  this->setLayout(m_Layout);

  m_AddProcessCommand = AddProcessCommandType::New();
  m_AddProcessCommand->SetCallbackFunction( this, &QtWidgetProgressReport::ProcessEvent );

  this->show();
}

QtWidgetProgressReport::~QtWidgetProgressReport()
{
  delete m_Layout;
}

void QtWidgetProgressReport::SetApplication(Application::Pointer app)
{
  m_Application = app;
  m_Application->AddObserver( AddProcessToWatchEvent(), m_AddProcessCommand.GetPointer() );
}

void
QtWidgetProgressReport::ProcessEvent( itk::Object * itkNotUsed(caller),
                                      const itk::EventObject & ev )
{
  if( typeid( otb::Wrapper::AddProcessToWatchEvent ) == typeid( ev ) )
    {
    const AddProcessToWatchEvent* eventToWatch = dynamic_cast< const  AddProcessToWatchEvent*> ( &ev );

    if(eventToWatch)
      {
      m_CurrentProcess = eventToWatch->GetProcess();
      m_CurrentDescription =  eventToWatch->GetProcessDescription();
      emit AddNewProcessToReport();
      }
    }
}

void QtWidgetProgressReport::ReportProcess ( )
{
  // Build the widget containing the QtProgressBar for the current
  // process

  // Create a itk::QtProgressBar, observing the event ProgressEvent
  itk::QtProgressBar * bar =  new itk::QtProgressBar(this);
  connect( bar, SIGNAL(SetValueChanged(int)), bar, SLOT(setValue(int)) );
  connect( m_Model, SIGNAL(SetProgressReportDone()), bar, SLOT(reset()) );
  bar->Observe(m_CurrentProcess);

  // label
  QLabel *label = new QLabel(QString(m_CurrentDescription.c_str()));

  // Build the layout and store the pointers
  m_Layout->addWidget(label);
  m_Layout->addWidget(bar);
}

void QtWidgetProgressReport::RemoveLayout()
{
  // Remove the children of the layout (progress bar widgets)
  QLayoutItem *child;
  while ((child = this->layout()->takeAt(0)) != ITK_NULLPTR)
    {
    delete child->widget();
    delete child;
    }
}

}
}
