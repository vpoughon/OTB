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

#include "otbWrapperQtWidgetParameterFactory.h"

#include "otbWrapperParameter.h"
#include "otbWrapperQtWidgetModel.h"

#include "otbWrapperQtWidgetParameterBase.h"

#include "otbWrapperQtWidgetEmptyParameter.h"
#include "otbWrapperQtWidgetIntParameter.h"
#include "otbWrapperQtWidgetFloatParameter.h"
#include "otbWrapperQtWidgetStringParameter.h"
#include "otbWrapperQtWidgetStringListParameter.h"
#include "otbWrapperQtWidgetChoiceParameter.h"
#include "otbWrapperQtWidgetListViewParameter.h"
#include "otbWrapperQtWidgetInputImageParameter.h"
#include "otbWrapperQtWidgetComplexInputImageParameter.h"
#include "otbWrapperQtWidgetComplexOutputImageParameter.h"
#include "otbWrapperQtWidgetInputImageListParameter.h"
#include "otbWrapperQtWidgetOutputImageParameter.h"
#include "otbWrapperQtWidgetOutputVectorDataParameter.h"
#include "otbWrapperQtWidgetInputFilenameParameter.h"
#include "otbWrapperQtWidgetInputFilenameListParameter.h"
#include "otbWrapperQtWidgetOutputFilenameParameter.h"
#include "otbWrapperQtWidgetDirectoryParameter.h"
#include "otbWrapperQtWidgetParameterGroup.h"
#include "otbWrapperQtWidgetInputVectorDataListParameter.h"
#include "otbWrapperQtWidgetInputVectorDataParameter.h"
#include "otbWrapperQtWidgetRAMParameter.h"
#include "otbWrapperQtWidgetOutputProcessXMLParameter.h"
#include "otbWrapperQtWidgetInputProcessXMLParameter.h"

namespace otb
{
namespace Wrapper
{

template <class TParameterType, class TQtWidget>
class QtWidgetParameterGenericFactory
{
public:

  static bool CanCreate( Parameter* param )
  {
    return dynamic_cast<TParameterType *>(param) != ITK_NULLPTR;
  }

  static QtWidgetParameterBase* Create( Parameter* param, QtWidgetModel* model )
  {
    QtWidgetParameterBase* widget = ITK_NULLPTR;
    TParameterType* specificParam = dynamic_cast<TParameterType *>(param);

    if (specificParam)
      {
      widget = new TQtWidget(specificParam, model);
      }
    return widget;
  }
};

QtWidgetParameterFactory::QtWidgetParameterFactory()
{
}

QtWidgetParameterFactory::~QtWidgetParameterFactory()
{
}

QtWidgetParameterBase*
QtWidgetParameterFactory::CreateQtWidget( Parameter* param, QtWidgetModel* model )
{
  QtWidgetParameterBase* widget = ITK_NULLPTR;

#define CREATEWIDGET( ParameterType, WidgetType ) \
  else if ( QtWidgetParameterGenericFactory<ParameterType,  WidgetType>::CanCreate(param) ) \
    { \
    widget = QtWidgetParameterGenericFactory<ParameterType,  WidgetType>::Create(param, model); \
    }

  if (0) {}
  CREATEWIDGET(EmptyParameter,          QtWidgetEmptyParameter)
  CREATEWIDGET(IntParameter,            QtWidgetIntParameter)
  CREATEWIDGET(FloatParameter,          QtWidgetFloatParameter)
  CREATEWIDGET(InputFilenameParameter,       QtWidgetInputFilenameParameter)
  CREATEWIDGET(OutputFilenameParameter,       QtWidgetOutputFilenameParameter)
  CREATEWIDGET(DirectoryParameter,      QtWidgetDirectoryParameter)
  CREATEWIDGET(StringParameter,         QtWidgetStringParameter)
  CREATEWIDGET(StringListParameter,     QtWidgetStringListParameter)
  CREATEWIDGET(ChoiceParameter,         QtWidgetChoiceParameter)
  CREATEWIDGET(ListViewParameter,       QtWidgetListViewParameter)
  CREATEWIDGET(InputImageParameter,     QtWidgetInputImageParameter)
  CREATEWIDGET(ComplexInputImageParameter,     QtWidgetComplexInputImageParameter)
  CREATEWIDGET(ComplexOutputImageParameter,     QtWidgetComplexOutputImageParameter)
  CREATEWIDGET(InputImageListParameter, QtWidgetInputImageListParameter)
  CREATEWIDGET(InputFilenameListParameter, QtWidgetInputFilenameListParameter)
  CREATEWIDGET(InputVectorDataListParameter, QtWidgetInputVectorDataListParameter)
  CREATEWIDGET(InputVectorDataParameter, QtWidgetInputVectorDataParameter)
  CREATEWIDGET(OutputImageParameter,    QtWidgetOutputImageParameter)
  CREATEWIDGET(OutputVectorDataParameter, QtWidgetOutputVectorDataParameter)
  CREATEWIDGET(EmptyParameter,          QtWidgetEmptyParameter)
  CREATEWIDGET(ParameterGroup,          QtWidgetParameterGroup)
  CREATEWIDGET(RAMParameter,            QtWidgetRAMParameter)
  CREATEWIDGET(OutputProcessXMLParameter,        QtWidgetOutputProcessXMLParameter)
  CREATEWIDGET(InputProcessXMLParameter,        QtWidgetInputProcessXMLParameter)
#undef CREATEWIDGET

  if (widget)
    {
    widget->CreateWidget();
    widget->UpdateGUI();
    }

  return widget;


}


}
}
