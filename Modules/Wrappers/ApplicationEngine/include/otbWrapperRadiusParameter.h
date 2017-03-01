/*=========================================================================

  Program:   ORFEO Toolbox
  Language:  C++


  Copyright (c) Centre National d'Etudes Spatiales. All rights reserved.
  See OTBCopyright.txt for details.


     This software is distributed WITHOUT ANY WARRANTY; without even
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
     PURPOSE.  See the above copyright notices for more information.

=========================================================================*/
#ifndef otbWrapperRadiusParameter_h
#define otbWrapperRadiusParameter_h

#include "otbWrapperNumericalParameter.h"

namespace otb
{
namespace Wrapper
{

/** \class StringParameter
 *  \brief This class represent a radius parameter for the wrapper framework
 *
 * \ingroup OTBApplicationEngine
 */
class OTBApplicationEngine_EXPORT RadiusParameter
  : public IntParameter
{
public:
  /** Standard class typedef */
  typedef RadiusParameter               Self;
  typedef Parameter                     Superclass;
  typedef itk::SmartPointer<Self>       Pointer;
  typedef itk::SmartPointer<const Self> ConstPointer;

  /** Defining ::New() static method */
  itkNewMacro(Self);

  /** RTTI support */
  itkTypeMacro(RadiusParameter, Parameter);

  bool HasValue() const ITK_OVERRIDE
  {
    return true;
  }

protected:
  /** Constructor */
  RadiusParameter()
  {
    this->SetName("Radius");
    this->SetKey("r");
    this->SetDescription("Radius in pixels");
  }

  /** Destructor */
  ~RadiusParameter() ITK_OVERRIDE
  {}

private:
  RadiusParameter(const RadiusParameter &); //purposely not implemented
  void operator =(const RadiusParameter&); //purposely not implemented

};

} // End namespace Wrapper
} // End namespace otb

#endif
