/*=========================================================================

  Program:   ORFEO Toolbox
  Language:  C++


  Copyright (c) Centre National d'Etudes Spatiales. All rights reserved.
  See OTBCopyright.txt for details.


     This software is distributed WITHOUT ANY WARRANTY; without even
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
     PURPOSE.  See the above copyright notices for more information.

=========================================================================*/
#ifndef otbWrapperDirectoryParameter_h
#define otbWrapperDirectoryParameter_h

#include "otbWrapperStringParameter.h"
#include "otbMacro.h"

#include <string>

namespace otb
{
namespace Wrapper
{

/** \class DirectoryParameter
 *  \brief This class represent a string parameter for the wrapper framework
 *
 * \ingroup OTBApplicationEngine
 */
class OTBApplicationEngine_EXPORT DirectoryParameter
  : public Parameter
{
public:
  /** Standard class typedef */
  typedef DirectoryParameter            Self;
  typedef Parameter                     Superclass;
  typedef itk::SmartPointer<Self>       Pointer;
  typedef itk::SmartPointer<const Self> ConstPointer;

  /** Defining ::New() static method */
  itkNewMacro(Self);

  /** RTTI support */
  itkTypeMacro(DirectoryParameter, Parameter);

  bool HasValue() const ITK_OVERRIDE
  {
    return m_StringParam->HasValue();
  }

  // Set/Get Value
  otbSetObjectMemberMacro(StringParam, Value , std::string);
  otbGetObjectMemberMacro(StringParam, Value , std::string);

  // Clear Value
  void ClearValue() ITK_OVERRIDE
  {
    m_StringParam->ClearValue();
  }

  // Reimplement the SetActive method
  void SetActive(  const bool value ) ITK_OVERRIDE
  {
    Superclass::SetActive( value );
    m_StringParam->SetActive( value );
  }

  // GetActive method
  otbGetObjectMemberConstMacro(StringParam, Active, bool);

protected:
  /** Constructor */
  DirectoryParameter()
  {
    m_StringParam = StringParameter::New();
  }

  /** Destructor */
  ~DirectoryParameter() ITK_OVERRIDE
  {}

private:
  DirectoryParameter(const DirectoryParameter &); //purposely not implemented
  void operator =(const DirectoryParameter&); //purposely not
                                              //implemented

  StringParameter::Pointer   m_StringParam;

}; // End class Parameter

} // End namespace Wrapper
} // End namespace otb

#endif
