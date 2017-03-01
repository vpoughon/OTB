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

#ifndef otbWrapperInputVectorDataParameter_h
#define otbWrapperInputVectorDataParameter_h

#include "otbVectorDataFileReader.h"
#include "otbWrapperParameter.h"

namespace otb
{
namespace Wrapper
{
/** \class InputVectorDataParameter
 *  \brief This class represents a InputVectorData parameter
 *
 * \ingroup OTBApplicationEngine
 */

class OTBApplicationEngine_EXPORT InputVectorDataParameter : public Parameter
{
public:
  /** Standard class typedef */
  typedef InputVectorDataParameter      Self;
  typedef Parameter                     Superclass;
  typedef itk::SmartPointer<Self>       Pointer;
  typedef itk::SmartPointer<const Self> ConstPointer;

  /** Defining ::New() static method */
  itkNewMacro(Self);

  /** RTTI support */
  itkTypeMacro(InputVectorDataParameter, Parameter);

  typedef double CoordinatePrecisionType;
  typedef double ValuePrecisionType;
  typedef otb::VectorData<CoordinatePrecisionType, 2, ValuePrecisionType>  VectorDataType;

  /** Set value from filename */
  bool SetFromFileName(const std::string& filename);
  itkGetConstMacro(FileName, std::string);

  VectorDataType* GetVectorData();

  void SetVectorData(VectorDataType* vectorData);

  bool HasValue() const ITK_OVERRIDE;

  void ClearValue() ITK_OVERRIDE;

protected:
  /** Constructor */
  InputVectorDataParameter();

  /** Destructor */
  ~InputVectorDataParameter() ITK_OVERRIDE;

  typedef otb::VectorDataFileReader<VectorDataType> VectorDataFileReaderType;
  VectorDataType::Pointer m_VectorData;
  VectorDataFileReaderType::Pointer m_Reader;

  std::string m_FileName;

private:
  InputVectorDataParameter(const Parameter &); //purposely not implemented
  void operator =(const Parameter&); //purposely not implemented

};

} // End namespace Wrapper
} // End namespace otb

#endif
