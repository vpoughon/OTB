/*=========================================================================

  Program:   ORFEO Toolbox
  Language:  C++


  Copyright (c) Centre National d'Etudes Spatiales. All rights reserved.
  See OTBCopyright.txt for details.


     This software is distributed WITHOUT ANY WARRANTY; without even
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
     PURPOSE.  See the above copyright notices for more information.

=========================================================================*/
#ifndef otbWrapperStringParameter_h
#define otbWrapperStringParameter_h

#include <string>
#include "otbWrapperParameter.h"

namespace otb
{
namespace Wrapper
{

/** \class StringParameter
 *  \brief This class represent a string parameter for the wrapper framework
 *
 * \ingroup OTBApplicationEngine
 */
class OTBApplicationEngine_EXPORT StringParameter
  : public Parameter
{
public:
  /** Standard class typedef */
  typedef StringParameter               Self;
  typedef Parameter                     Superclass;
  typedef itk::SmartPointer<Self>       Pointer;
  typedef itk::SmartPointer<const Self> ConstPointer;

  /** Defining ::New() static method */
  itkNewMacro(Self);

  /** RTTI support */
  itkTypeMacro(StringParameter, Parameter);

  /** Set the value */
  void SetValue( std::string value)
  {
    m_Value = value;
    SetActive(true);
  }

  /** Get the value */
  std::string GetValue() const
  {
    return m_Value;
  }

  bool HasValue() const ITK_OVERRIDE
  {
    return !m_Value.empty();
  }

  void ClearValue() ITK_OVERRIDE
  {
    m_Value = "";
  }

protected:
  /** Constructor */
  StringParameter()
  {}

  /** Destructor */
  ~StringParameter() ITK_OVERRIDE
  {}

  std::string  m_Value;

private:
  StringParameter(const StringParameter &); //purposely not implemented
  void operator =(const StringParameter&); //purposely not implemented

}; // End class Parameter

} // End namespace Wrapper
} // End namespace otb

#endif
