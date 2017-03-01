/*=========================================================================

  Program:   ORFEO Toolbox
  Language:  C++


  Copyright (c) Centre National d'Etudes Spatiales. All rights reserved.
  See OTBCopyright.txt for details.


     This software is distributed WITHOUT ANY WARRANTY; without even
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
     PURPOSE.  See the above copyright notices for more information.

=========================================================================*/
#include "otbWrapperQtWidgetDirectoryParameter.h"

#include <otbQtAdapters.h>

namespace otb
{
namespace Wrapper
{

QtWidgetDirectoryParameter::QtWidgetDirectoryParameter(DirectoryParameter* param, QtWidgetModel* m)
: QtWidgetParameterBase(param, m),
  m_DirectoryParam(param)
{
}

QtWidgetDirectoryParameter::~QtWidgetDirectoryParameter()
{
}

void QtWidgetDirectoryParameter::DoUpdateGUI()
{
  // Update the lineEdit
  QString text(
    QFile::decodeName(
      m_DirectoryParam->GetValue().c_str()
    )
  );

  m_Input->setText(text);
}

void QtWidgetDirectoryParameter::DoCreateWidget()
{
  // Set up input text edit
  m_HLayout = new QHBoxLayout;
  m_HLayout->setSpacing(0);
  m_HLayout->setContentsMargins(0, 0, 0, 0);
  m_Input = new QLineEdit;
  m_Input->setToolTip( m_DirectoryParam->GetDescription() );
  connect( m_Input, SIGNAL(textChanged(const QString&)), this, SLOT(SetFileName(const QString&)) );
  connect( m_Input, SIGNAL(textChanged(const QString&)), GetModel(), SLOT(NotifyUpdate()) );

  m_HLayout->addWidget(m_Input);

  // Set up input text edit
  m_Button = new QPushButton;
  m_Button->setText("...");
  m_Button->setToolTip("Select d Directory...");
  m_Button->setMaximumWidth(m_Button->width());
  connect( m_Button, SIGNAL(clicked()), this, SLOT(SelectFile()) );
  m_HLayout->addWidget(m_Button);

  this->setLayout(m_HLayout);
}


void
QtWidgetDirectoryParameter
::SelectFile()
{
  assert( m_Input!=NULL );

  QString dir(
    GetExistingDirectory(
      this,
      QString(),
      m_Input->text()
    )
  );

  if( dir.isEmpty() )
    return;

  m_Input->setText( dir );
}


void QtWidgetDirectoryParameter::SetFileName(const QString& value)
{
  // save value
  m_DirectoryParam->SetValue(
    QFile::encodeName( value ).constData()
  );

  // notify of value change
  QString key( m_DirectoryParam->GetKey() );
  emit ParameterChanged(key);
}

}
}
