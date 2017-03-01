/*=========================================================================

  Program:   ORFEO Toolbox
  Language:  C++


  Copyright (c) Centre National d'Etudes Spatiales. All rights reserved.
  See OTBCopyright.txt for details.


     This software is distributed WITHOUT ANY WARRANTY; without even
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
     PURPOSE.  See the above copyright notices for more information.

=========================================================================*/
#ifndef otbMSTARImageIOFactory_h
#define otbMSTARImageIOFactory_h

#include "itkObjectFactoryBase.h"

namespace otb
{
/** \class MSTARImageIOFactory
 * \brief Creation d'un instance d'un objet MSTARImageIO utilisant les object factory.
 *
 * \ingroup OTBIOMSTAR
 */
class ITK_EXPORT MSTARImageIOFactory : public itk::ObjectFactoryBase
{
public:
  /** Standard class typedefs. */
  typedef MSTARImageIOFactory           Self;
  typedef itk::ObjectFactoryBase        Superclass;
  typedef itk::SmartPointer<Self>       Pointer;
  typedef itk::SmartPointer<const Self> ConstPointer;

  /** Class methods used to interface with the registered factories. */
  const char* GetITKSourceVersion(void) const ITK_OVERRIDE;
  const char* GetDescription(void) const ITK_OVERRIDE;

  /** Method for class instantiation. */
  itkFactorylessNewMacro(Self);
  static MSTARImageIOFactory * FactoryNew() { return new MSTARImageIOFactory; }

  /** Run-time type information (and related methods). */
  itkTypeMacro(MSTARImageIOFactory, itk::ObjectFactoryBase);

  /** Register one factory of this type  */
  static void RegisterOneFactory(void)
  {
    MSTARImageIOFactory::Pointer MSTARFactory = MSTARImageIOFactory::New();
    itk::ObjectFactoryBase::RegisterFactory(MSTARFactory);
  }

protected:
  MSTARImageIOFactory();
  ~MSTARImageIOFactory() ITK_OVERRIDE;

private:
  MSTARImageIOFactory(const Self &); //purposely not implemented
  void operator =(const Self&); //purposely not implemented

};

} // end namespace otb

#endif
