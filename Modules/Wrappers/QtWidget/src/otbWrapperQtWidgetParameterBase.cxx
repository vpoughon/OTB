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

#include "otbWrapperQtWidgetParameterBase.h"

namespace otb
{
namespace Wrapper
{

QtWidgetParameterBase::QtWidgetParameterBase(Parameter * param, QtWidgetModel* m)
  : m_Model(m), m_Param(param)
{

}

QtWidgetParameterBase::~QtWidgetParameterBase()
{
}


void QtWidgetParameterBase::CreateWidget()
{
  this->DoCreateWidget();

  // connect the update signal to this widget
  connect( GetModel(), SIGNAL(UpdateGui()), this, SLOT(UpdateGUI() ) );
}

void QtWidgetParameterBase::UpdateGUI()
{
  // Update the GUI
  this->DoUpdateGUI();

  // Emit State of the Parameter to update this parameter checkbox
  if (!m_Param->GetMandatory())
    {
    bool state = m_Param->GetActive();
    emit ParameterActiveStatus(state);
   }
  else
    {
    // Activate the Mandatory param and the Mandatory subparam in an
    // activated Group
   if (m_Param->GetRoot()->GetActive())
     {
     emit ParameterActiveStatus(true);
     }
    }
}

void QtWidgetParameterBase::ParameterChanged(const QString& itkNotUsed(key))
{
  m_Param->SetUserValue(true);
}

QtWidgetModel* QtWidgetParameterBase::GetModel()
{
  return m_Model;
}

// Slot connected to the signal emitted the checkBox relative to
// current widget
void QtWidgetParameterBase::SetActivationState( bool value )
{
  //filter out EmptyParameter
  if(strcmp(m_Param->GetNameOfClass(), "EmptyParameter") == 0)
    {
    //only set user value if there is a change
    if(value != m_Param->GetActive())
      m_Param->SetUserValue(true);
    }

  this->setEnabled(value);
  m_Param->SetChecked(value);
  m_Param->SetActive(value);

}

// Slot connected to the signal emitted by the Reset Button
void QtWidgetParameterBase::Reset(  )
{
  m_Param->Reset();
  m_Param->SetUserValue(false);
  m_Param->SetAutomaticValue(false);
  this->UpdateGUI();
}

}

}
