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

#ifndef otbWrapperProxyParameter_h
#define otbWrapperProxyParameter_h

#include "itkObject.h"
#include "otbWrapperParameter.h"
#include <utility>

namespace otb
{
namespace Wrapper
{
/**
 * \class ProxyParameter
 *
 * \brief Parameter class acting as a proxy to a different parameter
 *
 * The target parameter of this proxy is defined as a pair of a group parameter
 * containing the target and the targets key. It allows to define proxies on
 * parameters that may be themselves replaced by a proxy
 *
 * \ingroup OTBApplicationEngine
 */
class ProxyParameter : public Parameter
{
public:
  typedef ProxyParameter                       Self;
  typedef Parameter                            Superclass;
  typedef itk::SmartPointer<Self>              Pointer;
  typedef itk::SmartPointer<const Self>        ConstPointer;

  itkNewMacro(Self);

  itkTypeMacro(ProxyParameter, Parameter);

  typedef std::pair<Parameter::Pointer, std::string> ProxyTargetType;

  /** Set the target parameter of the proxy
   *  \param target pair of a group parameter containing the target and its key
   */
  void SetTarget(const ProxyTargetType& target)
    {
    m_Target = target;
    }

  /** Get the target parameter of the proxy
   *  First part is the group parameter containing the target
   *  Second part is the key of the target */
  const ProxyTargetType & GetTarget(void)
    {
    return m_Target;
    }

protected:
  ProxyParameter() {}
  ~ProxyParameter() ITK_OVERRIDE {}

private:
  ProxyParameter(const Self &); //purposely not implemented
  void operator =(const Self&); //purposely not implemented

  ProxyTargetType m_Target;
};

}
}

//#ifndef OTB_MANUAL_INSTANTIATION
//#include "otbWrapperProxyParameter.txx"
//#endif

#endif
