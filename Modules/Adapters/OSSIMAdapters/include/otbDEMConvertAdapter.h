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


#ifndef otbDEMConvertAdapter_h
#define otbDEMConvertAdapter_h

#include "itkObject.h"
#include "itkObjectFactory.h"

#include "OTBOSSIMAdaptersExport.h"

namespace otb
{

class OTBOSSIMAdapters_EXPORT DEMConvertAdapter: public itk::Object
{
public:
  /** Standard class typedefs. */
  typedef DEMConvertAdapter             Self;
  typedef itk::Object                   Superclass;
  typedef itk::SmartPointer<Self>       Pointer;
  typedef itk::SmartPointer<const Self> ConstPointer;

  /** Method for creation through the object factory. */
  itkNewMacro(Self);

  /** Run-time type information (and related methods). */
  itkTypeMacro(EllipsoidAdapter, itk::Object);

  int Convert(std::string tempFilename, std::string output);

protected:
  DEMConvertAdapter();
  ~DEMConvertAdapter() ITK_OVERRIDE;

private:
  DEMConvertAdapter(const Self &); //purposely not implemented
  void operator =(const Self&); //purposely not implemented
};

} // namespace otb

#endif
