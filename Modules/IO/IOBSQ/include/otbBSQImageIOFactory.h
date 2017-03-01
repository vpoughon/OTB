/*=========================================================================

  Program:   ORFEO Toolbox
  Language:  C++


  Copyright (c) Centre National d'Etudes Spatiales. All rights reserved.
  See OTBCopyright.txt for details.


     This software is distributed WITHOUT ANY WARRANTY; without even
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
     PURPOSE.  See the above copyright notices for more information.

=========================================================================*/
#ifndef otbBSQImageIOFactory_h
#define otbBSQImageIOFactory_h

#include "itkObjectFactoryBase.h"

namespace otb
{
/** \class BSQImageIOFactory
 * \brief Creation d'un instance d'un objet BSQImageIO utilisant les object factory.
 *
 * \ingroup OTBIOBSQ
 */
class ITK_EXPORT BSQImageIOFactory : public itk::ObjectFactoryBase
{
public:
  /** Standard class typedefs. */
  typedef BSQImageIOFactory             Self;
  typedef itk::ObjectFactoryBase        Superclass;
  typedef itk::SmartPointer<Self>       Pointer;
  typedef itk::SmartPointer<const Self> ConstPointer;

  /** Class methods used to interface with the registered factories. */
  const char* GetITKSourceVersion(void) const ITK_OVERRIDE;
  const char* GetDescription(void) const ITK_OVERRIDE;

  /** Method for class instantiation. */
  itkFactorylessNewMacro(Self);
  static BSQImageIOFactory * FactoryNew() { return new BSQImageIOFactory; }

  /** Run-time type information (and related methods). */
  itkTypeMacro(BSQImageIOFactory, itk::ObjectFactoryBase);

  /** Register one factory of this type  */
  static void RegisterOneFactory(void)
  {
    BSQImageIOFactory::Pointer BSQFactory = BSQImageIOFactory::New();
    itk::ObjectFactoryBase::RegisterFactoryInternal(BSQFactory);
  }

protected:
  BSQImageIOFactory();
  ~BSQImageIOFactory() ITK_OVERRIDE;

private:
  BSQImageIOFactory(const Self &); //purposely not implemented
  void operator =(const Self&); //purposely not implemented

};

} // end namespace otb

#endif
