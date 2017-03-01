/*=========================================================================

  Program:   ORFEO Toolbox
  Language:  C++


  Copyright (c) Centre National d'Etudes Spatiales. All rights reserved.
  See OTBCopyright.txt for details.


     This software is distributed WITHOUT ANY WARRANTY; without even
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
     PURPOSE.  See the above copyright notices for more information.

=========================================================================*/
#ifndef otbRadiometricMomentsImageFunction_h
#define otbRadiometricMomentsImageFunction_h

#include "itkImageFunction.h"
#include "otbRadiometricMomentsFunctor.h"
#include "itkConstNeighborhoodIterator.h"
#include "itkFixedArray.h"

namespace otb
{

/**
 * \class RadiometricMomentsImageFunction
 * \brief Calculate the radiometric moments.
 *
 * Calculate the radiometric moments over a specified neighborhood
 *
 * This class is templated over the input image type and the
 * coordinate representation type (e.g. float or double).
 *
 * \ingroup ImageFunctions
 *
 * \ingroup OTBMoments
 */


template <class TInputImage, class TCoordRep = double >
class ITK_EXPORT RadiometricMomentsImageFunction :
  public itk::ImageFunction< TInputImage,
    itk::FixedArray<
    typename itk::NumericTraits<typename TInputImage::PixelType>::RealType,
    4 >,
    TCoordRep >
{
public:
  /** Standard class typedefs. */
  typedef RadiometricMomentsImageFunction                                 Self;
  typedef itk::ImageFunction< TInputImage,
                   itk::FixedArray<
                   typename itk::NumericTraits<
                   typename TInputImage::PixelType>::RealType,
                   4 >,
                   TCoordRep >                                            Superclass;
  typedef itk::SmartPointer<Self>                                         Pointer;
  typedef itk::SmartPointer<const Self>                                   ConstPointer;

  /** Run-time type information (and related methods). */
  itkTypeMacro(RadiometricMomentsImageFunction, ImageFunction);

  /** Method for creation through the object factory. */
  itkNewMacro(Self);

  /** InputImageType typedef support. */
  typedef TInputImage                              InputImageType;
  typedef typename Superclass::IndexType           IndexType;
  typedef typename Superclass::ContinuousIndexType ContinuousIndexType;
  typedef typename Superclass::PointType           PointType;

  typedef typename Superclass::OutputType          OutputType;
  typedef typename OutputType::ValueType           ScalarRealType;

  typedef TCoordRep                                CoordRepType;

  typedef Functor::RadiometricMomentsFunctor< itk::ConstNeighborhoodIterator<InputImageType>, ScalarRealType>
                                                   FunctorType;

  /** Dimension of the underlying image. */
  itkStaticConstMacro(ImageDimension, unsigned int,
                      InputImageType::ImageDimension);

  /** Evalulate the function at specified index */
  OutputType EvaluateAtIndex(const IndexType& index) const ITK_OVERRIDE;

  /** Evaluate the function at non-integer positions */
  OutputType Evaluate(const PointType& point) const ITK_OVERRIDE
  {
    IndexType index;
    this->ConvertPointToNearestIndex(point, index);
    return this->EvaluateAtIndex(index);
  }
  OutputType EvaluateAtContinuousIndex(
    const ContinuousIndexType& cindex) const ITK_OVERRIDE
  {
    IndexType index;
    this->ConvertContinuousIndexToNearestIndex(cindex, index);
    return this->EvaluateAtIndex(index);
  }

  /** Get/Set the radius of the neighborhood over which the
   *  statistics are evaluated
   */
  itkSetMacro( NeighborhoodRadius, unsigned int );
  itkGetConstReferenceMacro( NeighborhoodRadius, unsigned int );

protected:
  RadiometricMomentsImageFunction();
  ~RadiometricMomentsImageFunction() ITK_OVERRIDE {}
  void PrintSelf(std::ostream& os, itk::Indent indent) const ITK_OVERRIDE;

private:
  RadiometricMomentsImageFunction(const Self &);  //purposely not implemented
  void operator =(const Self&);  //purposely not implemented

  unsigned int m_NeighborhoodRadius;
  FunctorType m_Functor;
};

} // namespace otb

#ifndef OTB_MANUAL_INSTANTIATION
#include "otbRadiometricMomentsImageFunction.txx"
#endif

#endif
