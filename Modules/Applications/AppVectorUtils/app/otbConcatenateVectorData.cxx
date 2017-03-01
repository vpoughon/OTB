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

#include "otbWrapperApplication.h"
#include "otbWrapperApplicationFactory.h"

#include "otbConcatenateVectorDataFilter.h"

namespace otb
{
namespace Wrapper
{

class ConcatenateVectorData : public Application
{

public:
  /** Standard class typedefs. */
  typedef ConcatenateVectorData         Self;
  typedef Application                   Superclass;
  typedef itk::SmartPointer<Self>       Pointer;
  typedef itk::SmartPointer<const Self> ConstPointer;

  /** Standard macro */
  itkNewMacro(Self);

  itkTypeMacro(ConcatenateVectorData, otb::Application);

  /** VectorData Concatenate filter*/
  typedef otb::ConcatenateVectorDataFilter<VectorDataType>  ConcatenateFilterType;

private:
  void DoInit() ITK_OVERRIDE
  {
    SetName("ConcatenateVectorData");
    SetDescription("Concatenate VectorDatas");

    SetDocName("Concatenate");
    SetDocLongDescription("This application concatenates a list of VectorData to produce a unique VectorData as output."
                          "Note that the VectorDatas must be of the same type (Storing polygons only, lines only, or points only)");
    SetDocLimitations("None");
    SetDocAuthors("OTB-Team");
    SetDocSeeAlso(" ");

    AddDocTag(Tags::Vector);

    AddParameter(ParameterType_InputVectorDataList, "vd", "Input VectorDatas to concatenate");
    SetParameterDescription("vd", "VectorData files to be concatenated in an unique VectorData");

    AddParameter(ParameterType_OutputVectorData, "out", "Concatenated VectorData");
    SetParameterDescription("out", "Output conctenated VectorData");

    // Doc example parameter settings
    SetDocExampleParameterValue("vd", "ToulousePoints-examples.shp ToulouseRoad-examples.shp");
    SetDocExampleParameterValue("out", "ConcatenatedVectorData.shp");

  }


  void DoUpdateParameters() ITK_OVERRIDE
  {
    // Nothing to do here for the parameters : all are independent
  }

  void DoExecute() ITK_OVERRIDE
  {
    // Get the input VectorData list
    VectorDataListType* vectorDataList = GetParameterVectorDataList("vd");

    // Concatenate filter object
    m_ConcatenateFilter = ConcatenateFilterType::New();

    for (unsigned int idx = 0; idx < vectorDataList->Size(); idx++)
      {
      m_ConcatenateFilter->AddInput(vectorDataList->GetNthElement(idx));
      }

    // Set the output
    SetParameterOutputVectorData("out", m_ConcatenateFilter->GetOutput());
  }

  ConcatenateFilterType::Pointer m_ConcatenateFilter;
  };

}
}
OTB_APPLICATION_EXPORT(otb::Wrapper::ConcatenateVectorData)
