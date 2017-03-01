/*=========================================================================

  Program:   ORFEO Toolbox
  Language:  C++


  Copyright (c) Centre National d'Etudes Spatiales. All rights reserved.
  See OTBCopyright.txt for details.


     This software is distributed WITHOUT ANY WARRANTY; without even
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
     PURPOSE.  See the above copyright notices for more information.

=========================================================================*/
#include "otbWrapperQtWidgetOutputVectorDataParameter.h"
#include "otbWrapperTypes.h"

#include <otbQtAdapters.h>

namespace otb
{
namespace Wrapper
{

QtWidgetOutputVectorDataParameter::QtWidgetOutputVectorDataParameter(OutputVectorDataParameter* param, QtWidgetModel* m)
: QtWidgetParameterBase(param, m),
  m_OutputVectorDataParam(param)
{
}

QtWidgetOutputVectorDataParameter::~QtWidgetOutputVectorDataParameter()
{
}

void QtWidgetOutputVectorDataParameter::DoUpdateGUI()
{
  //update lineedit
  QString text( m_OutputVectorDataParam->GetFileName() );
  if (text != m_Input->text())
    m_Input->setText(text);
}

void QtWidgetOutputVectorDataParameter::DoCreateWidget()
{
  m_HLayout = new QHBoxLayout;
  m_HLayout->setSpacing(0);
  m_HLayout->setContentsMargins(0, 0, 0, 0);

  m_Input = new QLineEdit;
  m_Input->setToolTip( m_OutputVectorDataParam->GetDescription() );
  connect( m_Input, SIGNAL(textChanged(const QString&)), this, SLOT(SetFileName(const QString&)) );
  connect( m_Input, SIGNAL(textChanged(const QString&)), GetModel(), SLOT(NotifyUpdate()) );
  m_HLayout->addWidget(m_Input);

  m_Button = new QPushButton;
  m_Button->setText("...");
  m_Button->setToolTip("Select output filename...");
  m_Button->setMaximumWidth(m_Button->width());
  connect( m_Button, SIGNAL(clicked()), this, SLOT(SelectFile()) );
  m_HLayout->addWidget(m_Button);

  this->setLayout(m_HLayout);
}


void
QtWidgetOutputVectorDataParameter
::SelectFile()
{
  assert( m_Input!=NULL );

  QString filename(
    GetSaveFileName(
      this,
      QString(),
      m_Input->text(),
      tr( "Vector data files (*)" ),
      NULL
    )
  );

  if( filename.isEmpty() )
    return;

  m_Input->setText( filename );
}


void QtWidgetOutputVectorDataParameter::SetFileName(const QString& value)
{
  // save value
  m_FileName = QFile::encodeName( value ).constData();

  m_OutputVectorDataParam->SetFileName(m_FileName);

  // notify of value change
  QString key( m_OutputVectorDataParam->GetKey() );
  emit ParameterChanged(key);
}


}
}
