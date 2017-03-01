/*=========================================================================

  Program:   ORFEO Toolbox
  Language:  C++


  Copyright (c) Centre National d'Etudes Spatiales. All rights reserved.
  See OTBCopyright.txt for details.


     This software is distributed WITHOUT ANY WARRANTY; without even
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
     PURPOSE.  See the above copyright notices for more information.

=========================================================================*/
#ifndef otbInverseSensorModel_h
#define otbInverseSensorModel_h

#include "otbSensorModelBase.h"

#include "itkMacro.h"
#include "itkObject.h"

namespace otb
{

/** \class InverseSensorModel
 *
 * \brief Class for inverse sensor models
 *
 * Based on ossimProjectionFactoryRegistry and ossimProjection methods.
 * It takes as input a world point and computes the index position of the
 * corresponding point in the input image.
 * (lon, lat, h) -> (i, j).
 * Notice that the elevation h is optional.
 *
 * \ingroup Transform
 * \ingroup Projection
 *
 * \ingroup OTBTransform
 */
template <class TScalarType,
    unsigned int NInputDimensions = 2,
    unsigned int NOutputDimensions = 2>
class ITK_EXPORT InverseSensorModel : public SensorModelBase<TScalarType,
      NInputDimensions,
      NOutputDimensions>
{

public:
  /** Standard class typedefs. */
  typedef InverseSensorModel Self;
  typedef SensorModelBase<TScalarType,
      NInputDimensions,
      NOutputDimensions>         Superclass;
  typedef itk::SmartPointer<Self>       Pointer;
  typedef itk::SmartPointer<const Self> ConstPointer;

  typedef typename Superclass::InputPointType  InputPointType;
  typedef typename Superclass::OutputPointType OutputPointType;

  /** Method for creation through the object factory. */
  itkNewMacro(Self);

  /** Run-time type information (and related methods). */
  itkTypeMacro(InverseSensorModel, SensorModelBase);

  itkStaticConstMacro(InputSpaceDimension,  unsigned int, NInputDimensions);
  itkStaticConstMacro(OutputSpaceDimension, unsigned int, NOutputDimensions);

  // Transform of geographic point in image sensor index
  OutputPointType TransformPoint(const InputPointType& point) const ITK_OVERRIDE;
  // Transform of geographic point in image sensor index -- Backward Compatibility
  //  OutputPointType TransformPoint(const InputPointType &point, double height) const;

protected:
  InverseSensorModel();
  ~InverseSensorModel() ITK_OVERRIDE;

  /** PrintSelf method */
  void PrintSelf(std::ostream& os, itk::Indent indent) const ITK_OVERRIDE;

private:

  InverseSensorModel(const Self &); //purposely not implemented
  void operator =(const Self&);     //purposely not implemented

};

} // namespace otb

#ifndef OTB_MANUAL_INSTANTIATION
#include "otbInverseSensorModel.txx"
#endif

#endif
