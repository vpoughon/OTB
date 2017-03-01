/*=========================================================================

  Program:   ORFEO Toolbox
  Language:  C++


  Copyright (c) Centre National d'Etudes Spatiales. All rights reserved.
  See OTBCopyright.txt for details.


     This software is distributed WITHOUT ANY WARRANTY; without even
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
     PURPOSE.  See the above copyright notices for more information.

=========================================================================*/
#include "otbWrapperQtWidgetParameterLabel.h"

namespace otb
{
namespace Wrapper
{

QtWidgetParameterLabel::QtWidgetParameterLabel(Parameter* param)
{
  // Set up label
  QLabel *label = new QLabel;

  label->setText(param->GetName());
  label->setToolTip(param->GetKey());

  QVBoxLayout *labelLayout = new QVBoxLayout;
  labelLayout->setSpacing(0);
  labelLayout->setContentsMargins(0, 0, 0, 0);
  labelLayout->addWidget(label, 0);

  this->setLayout(labelLayout);
}

QtWidgetParameterLabel::~QtWidgetParameterLabel()
{
}

}
}
