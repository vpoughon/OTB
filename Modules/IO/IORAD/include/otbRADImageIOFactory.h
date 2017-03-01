/*=========================================================================

  Program:   ORFEO Toolbox
  Language:  C++


  Copyright (c) Centre National d'Etudes Spatiales. All rights reserved.
  See OTBCopyright.txt for details.


     This software is distributed WITHOUT ANY WARRANTY; without even
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
     PURPOSE.  See the above copyright notices for more information.

=========================================================================*/
#ifndef otbRADImageIOFactory_h
#define otbRADImageIOFactory_h

#include "itkObjectFactoryBase.h"

namespace otb
{
/** \class RADImageIOFactory
 * \brief Creation d'un instance d'un objet RADImageIO utilisant les object factory.
 *
 * \ingroup OTBIORAD
 */
class ITK_EXPORT RADImageIOFactory : public itk::ObjectFactoryBase
{
public:
  /** Standard class typedefs. */
  typedef RADImageIOFactory             Self;
  typedef itk::ObjectFactoryBase        Superclass;
  typedef itk::SmartPointer<Self>       Pointer;
  typedef itk::SmartPointer<const Self> ConstPointer;

  /** Class methods used to interface with the registered factories. */
  const char* GetITKSourceVersion(void) const ITK_OVERRIDE;
  const char* GetDescription(void) const ITK_OVERRIDE;

  /** Method for class instantiation. */
  itkFactorylessNewMacro(Self);
  static RADImageIOFactory * FactoryNew() { return new RADImageIOFactory; }

  /** Run-time type information (and related methods). */
  itkTypeMacro(RADImageIOFactory, itk::ObjectFactoryBase);

  /** Register one factory of this type  */
  static void RegisterOneFactory(void)
  {
    RADImageIOFactory::Pointer RADFactory = RADImageIOFactory::New();
    itk::ObjectFactoryBase::RegisterFactory(RADFactory);
  }

protected:
  RADImageIOFactory();
  ~RADImageIOFactory() ITK_OVERRIDE;

private:
  RADImageIOFactory(const Self &); //purposely not implemented
  void operator =(const Self&); //purposely not implemented

};

} // end namespace otb

#endif
