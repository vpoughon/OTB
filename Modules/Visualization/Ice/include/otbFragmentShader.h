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

#ifndef otb_FragmentShader_h
#define otb_FragmentShader_h

#include "OTBIceExport.h"

#include <itkObject.h>
#include <itkPoint.h>

namespace otb
{

class OTBIce_EXPORT FragmentShader
  : public itk::Object
{
public:
  typedef FragmentShader                                  Self;
  typedef itk::Object                                     Superclass;
  typedef itk::SmartPointer<Self>                         Pointer;
  typedef itk::SmartPointer<const Self>                   ConstPointer;

  typedef itk::Point<float,2>                             PointType;

  void LoadShader();

  virtual void SetupShader();

  void UnloadShader();

  itkSetMacro(UL,PointType);
  itkSetMacro(UR,PointType);
  itkSetMacro(LL,PointType);
  itkSetMacro(LR,PointType);
  itkGetConstReferenceMacro(UL,PointType);
  itkGetConstReferenceMacro(UR,PointType);
  itkGetConstReferenceMacro(LL,PointType);
  itkGetConstReferenceMacro(LR,PointType);

protected:
  FragmentShader();

  ~FragmentShader() ITK_OVERRIDE;

  void BuildShader();

  virtual std::string GetSource() const = 0;

  virtual std::string GetName() const = 0;

private:
  // prevent implementation
  FragmentShader(const Self&);
  void operator=(const Self&);

  PointType m_UL;
  PointType m_UR;
  PointType m_LL;
  PointType m_LR;

}; // End class FragmentShader

} // End namespace otb

#endif
