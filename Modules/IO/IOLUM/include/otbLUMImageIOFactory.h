/*=========================================================================

  Program:   ORFEO Toolbox
  Language:  C++


  Copyright (c) Centre National d'Etudes Spatiales. All rights reserved.
  See OTBCopyright.txt for details.


     This software is distributed WITHOUT ANY WARRANTY; without even
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
     PURPOSE.  See the above copyright notices for more information.

=========================================================================*/
#ifndef otbLUMImageIOFactory_h
#define otbLUMImageIOFactory_h

#include "itkObjectFactoryBase.h"

namespace otb
{
/** \class LUMImageIOFactory
 * \brief Creation d'un instance d'un objet LUMImageIO utilisant les object factory.
 *
 * \ingroup OTBIOLUM
 */
class ITK_EXPORT LUMImageIOFactory : public itk::ObjectFactoryBase
{
public:
  /** Standard class typedefs. */
  typedef LUMImageIOFactory             Self;
  typedef itk::ObjectFactoryBase        Superclass;
  typedef itk::SmartPointer<Self>       Pointer;
  typedef itk::SmartPointer<const Self> ConstPointer;

  /** Class methods used to interface with the registered factories. */
  const char* GetITKSourceVersion(void) const ITK_OVERRIDE;
  const char* GetDescription(void) const ITK_OVERRIDE;

  /** Method for class instantiation. */
  itkFactorylessNewMacro(Self);
  static LUMImageIOFactory * FactoryNew() { return new LUMImageIOFactory; }

  /** Run-time type information (and related methods). */
  itkTypeMacro(LUMImageIOFactory, itk::ObjectFactoryBase);

  /** Register one factory of this type  */
  static void RegisterOneFactory(void)
  {
    LUMImageIOFactory::Pointer LUMFactory = LUMImageIOFactory::New();
    itk::ObjectFactoryBase::RegisterFactory(LUMFactory);
  }

protected:
  LUMImageIOFactory();
  ~LUMImageIOFactory() ITK_OVERRIDE;

private:
  LUMImageIOFactory(const Self &); //purposely not implemented
  void operator =(const Self&); //purposely not implemented

};

} // end namespace otb

#endif
