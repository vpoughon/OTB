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


#include "otbGeometricSarSensorModelAdapter.h"

#include "otbMacro.h"
#include "otbImageKeywordlist.h"

#if defined(__GNUC__) || defined(__clang__)
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-parameter"
#pragma GCC diagnostic ignored "-Woverloaded-virtual"
#pragma GCC diagnostic ignored "-Wshadow"
#include "ossim/ossimGeometricSarSensorModel.h"
#include "ossim/projection/ossimProjection.h"
#include "ossim/ossimPluginProjectionFactory.h"
#include "ossim/otb/JSDDateTime.h"
#pragma GCC diagnostic pop
#else
#include "ossim/ossimGeometricSarSensorModel.h"
#include "ossim/projection/ossimProjection.h"
#include "ossim/ossimPluginProjectionFactory.h"
#include "ossim/otb/JSDDateTime.h"
#endif


namespace otb {

GeometricSarSensorModelAdapter::GeometricSarSensorModelAdapter():
  m_SensorModel(ITK_NULLPTR)
{
}

GeometricSarSensorModelAdapter::~GeometricSarSensorModelAdapter()
{
  if (m_SensorModel != ITK_NULLPTR)
    {
    delete m_SensorModel;
    m_SensorModel = ITK_NULLPTR;
    }
}


void GeometricSarSensorModelAdapter::CreateSensorModel(const ImageKeywordlist& image_kwl)
{
  ossimKeywordlist geom;

  image_kwl.convertToOSSIMKeywordlist(geom);
  otbMsgDevMacro(<< "CreateSensorModel()");
  otbMsgDevMacro(<< "* type: " << geom.find("type"));

  ossimProjection* sensor =  ossimplugins::ossimPluginProjectionFactory::instance()->createProjection(geom);

  m_SensorModel = dynamic_cast<ossimplugins::ossimGeometricSarSensorModel*>(sensor);
  if (!m_SensorModel)
  {
    otbMsgDevMacro(<< "CreateSensorModel() failed");
  }
}

ossimplugins::JSDDateTime GeometricSarSensorModelAdapter::getTime(double line)
{
  return m_SensorModel->getTime(line);
}

void GeometricSarSensorModelAdapter::GetPlatformPositionAtLine(
    double line, std::vector<double>& position, std::vector<double>& speed)
{
       m_SensorModel->getPlatformPositionAtLine(line, position, speed);
}

} // namespace otb
