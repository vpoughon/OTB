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


#include "itkMacro.h"

#include "otbLineSpatialObjectList.h"
#include <list>

int otbLineSpatialObjectList(int itkNotUsed(argc), char * itkNotUsed(argv) [])
{
  typedef otb::LineSpatialObjectList                         LineSpatialObjectListType;
  typedef LineSpatialObjectListType::LineType                LineSpatialObjecType;
  typedef LineSpatialObjectListType::LineType::PointListType PointListType;
  typedef LineSpatialObjectListType::const_iterator          LineSpatialObjectListConstIterator;

  LineSpatialObjectListType::Pointer listLines = LineSpatialObjectListType::New();
  for (int i = 0; i < 10; ++i)
    {
    LineSpatialObjecType::Pointer lLine = LineSpatialObjecType::New();
    listLines->push_back(lLine);
    }

  LineSpatialObjectListConstIterator lIter;
  lIter = listLines->begin();
  while (lIter != listLines->end())
    {
    LineSpatialObjecType::Pointer lLine = (*lIter);
    PointListType                 lPoints = lLine->GetPoints();
    lIter++;
    }

  return EXIT_SUCCESS;
}
