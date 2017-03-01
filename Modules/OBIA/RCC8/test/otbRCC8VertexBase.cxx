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

#include "otbRCC8VertexBase.h"
#include "otbPolygon.h"
#include "otbMacro.h"

int otbRCC8VertexBase(int itkNotUsed(argc), char* argv[])
{
  typedef otb::Polygon<> PathType;
  unsigned int imageLevel = atoi(argv[1]);
  bool         imageType = atoi(argv[2]);
  typedef otb::RCC8VertexBase<PathType>     RCC8VertexType;
  typedef RCC8VertexType::AttributesMapType AttributesMapType;
  // Instantiation
  RCC8VertexType::Pointer vertex1 = RCC8VertexType::New();

  PathType::Pointer path = PathType::New();
  path->Initialize();

  PathType::ContinuousIndexType p1, p2, p3;

  p1[0] = 0;
  p1[1] = 0;

  p2[0] = 10;
  p2[1] = 10;

  p3[0] = -5;
  p3[1] = 2;

  path->AddVertex(p1);
  path->AddVertex(p2);
  path->AddVertex(p3);

  // Getters / setters tests
  vertex1->SetSegmentationLevel(imageLevel);
  vertex1->SetSegmentationType(imageType);
  vertex1->SetPath(path);

  otbControlConditionTestMacro(vertex1->GetSegmentationLevel() != imageLevel,
                               "Test failed: vertex1->GetSegmentationLevel()!=imageLevel");
  otbControlConditionTestMacro(vertex1->GetSegmentationType() != imageType,
                               "Test failed: vertex1->GetSegmentationType()!=imageType");

  otbControlConditionTestMacro(vertex1->GetPath()->GetVertexList()->GetElement(0) != p1,
                               "Test failed:vertex1->GetPath()->GetVertexList()->GetElement(0)!=p1");
  otbControlConditionTestMacro(vertex1->GetPath()->GetVertexList()->GetElement(1) != p2,
                               "Test failed:vertex1->GetPath()->GetVertexList()->GetElement(1)!=p2");
  otbControlConditionTestMacro(vertex1->GetPath()->GetVertexList()->GetElement(2) != p3,
                               "Test failed:vertex1->GetPath()->GetVertexList()->GetElement(2)!=p3");

  // attributes vector set test
  AttributesMapType attr1 = vertex1->GetAttributesMap();
  otbControlConditionTestMacro(attr1["SegmentationLevel"].compare(std::string(argv[1])) != 0,
                               "Test failed: vertex1->GetAttributesMap()[\"SegmentationLevel\"]!=std::string(argv[1])");
  otbControlConditionTestMacro(atoi(attr1["SegmentationType"].c_str()) != static_cast<int>(imageType),
                               "Test failed:atoi(attr1[\"SegmentationType\"].c_str())!=imageType ");

  otbControlConditionTestMacro(atof(attr1["P0x"].c_str()) != p1[0],
                               "Test failed: atof(attr1[\"P0x\"].c_str())!=p1[0]");
  otbControlConditionTestMacro(atof(attr1["P0y"].c_str()) != p1[1],
                               "Test failed: atof(attr1[\"P0y\"].c_str())!=p1[1]");
  otbControlConditionTestMacro(atof(attr1["P1x"].c_str()) != p2[0],
                               "Test failed: atof(attr1[\"P1x\"].c_str())!=p2[0]");
  otbControlConditionTestMacro(atof(attr1["P1y"].c_str()) != p2[1],
                               "Test failed: atof(attr1[\"P1y\"].c_str())!=p2[1]");
  otbControlConditionTestMacro(atof(attr1["P2x"].c_str()) != p3[0],
                               "Test failed: atof(attr1[\"P2x\"].c_str())!=p3[0]");
  otbControlConditionTestMacro(atof(attr1["P2y"].c_str()) != p3[1],
                               "Test failed: atof( attr1[\"P2y\"].c_str())!=p3[1]");

  // attributes vector get test
  RCC8VertexType::Pointer vertex2 = RCC8VertexType::New();
  vertex2->SetAttributesMap(attr1);
  otbControlConditionTestMacro(vertex1->GetSegmentationLevel() != vertex2->GetSegmentationLevel(),
                               "Test failed: vertex1->GetSegmentationLevel()!=vertex2->GetSegmentationLevel()");
  otbControlConditionTestMacro(vertex1->GetSegmentationType() != vertex2->GetSegmentationType(),
                               "Test failed: vertex1->GetSegmentationType()!=vertex2->GetSegmentationType()");

  otbControlConditionTestMacro(vertex2->GetPath()->GetVertexList()->GetElement(0) != p1,
                               "Test failed:vertex2->GetPath()->GetVertexList()->GetElement(0)!=p1");
  otbControlConditionTestMacro(vertex2->GetPath()->GetVertexList()->GetElement(1) != p2,
                               "Test failed:vertex2->GetPath()->GetVertexList()->GetElement(1)!=p2");
  otbControlConditionTestMacro(vertex2->GetPath()->GetVertexList()->GetElement(2) != p3,
                               "Test failed:vertex2->GetPath()->GetVertexList()->GetElement(2)!=p3");

  return EXIT_SUCCESS;
}
