/*=========================================================================

  Program:   ORFEO Toolbox
  Language:  C++


  Copyright (c) Centre National d'Etudes Spatiales. All rights reserved.
  See OTBCopyright.txt for details.


     This software is distributed WITHOUT ANY WARRANTY; without even
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
     PURPOSE.  See the above copyright notices for more information.

=========================================================================*/
#ifndef otbImageFunctionAdaptor_h
#define otbImageFunctionAdaptor_h

#include "itkImageFunction.h"

#include "otbVariableLengthVectorConverter.h"


#include <complex>

namespace otb
{
/**
 * \class ImageFunctionAdaptor
 * \brief Adapt the output of the internal image function to be a
 * itk::VariableLengthVector.
 *
 * This class is templated over the ImageFunction type and the
 * coordinate representation type.
 *
 *
 *
 * \ingroup ImageFunctions
 *
 * \ingroup OTBImageBase
 */

template< class TInternalImageFunctionType, class TOutputPrecision = double >
class ITK_EXPORT ImageFunctionAdaptor :
    public itk::ImageFunction< typename TInternalImageFunctionType::InputImageType,
                               itk::VariableLengthVector<TOutputPrecision>,
                               typename TInternalImageFunctionType::CoordRepType >
{
  public:
  // Standard class typedefs. //
  typedef ImageFunctionAdaptor                                          Self;
  typedef itk::ImageFunction< typename TInternalImageFunctionType::InputImageType,
                              itk::VariableLengthVector<TOutputPrecision>,
                              typename TInternalImageFunctionType::CoordRepType >
                                                                        Superclass;
  typedef itk::SmartPointer<Self>                                       Pointer;
  typedef itk::SmartPointer<const Self>                                 ConstPointer;

  // Run-time type information (and related methods). //
  itkTypeMacro(ImageFunctionAdaptor, ImageFunction);

  // Method for creation through the object factory. //
  itkNewMacro(Self);

  // InputImageType typedef support. //
  typedef typename TInternalImageFunctionType::InputImageType  InputImageType;
  typedef typename TInternalImageFunctionType::CoordRepType    CoordRepType;
  typedef typename Superclass::IndexType                       IndexType;
  typedef typename Superclass::ContinuousIndexType             ContinuousIndexType;
  typedef typename Superclass::PointType                       PointType;
  typedef typename Superclass::OutputType                      OutputType;
  typedef typename OutputType::ValueType                       OutputValueType;

  // InternalImageFunction related typedefs //
  typedef TInternalImageFunctionType                        InternalImageFunctionType;
  typedef typename InternalImageFunctionType::OutputType    InternalImageFunctionOutputType;

  // Converter related typedefs //
  typedef VariableLengthVectorConverter<InternalImageFunctionOutputType, TOutputPrecision> ConverterType;


  // Dimension of the underlying image. //
  itkStaticConstMacro(ImageDimension, unsigned int, InputImageType::ImageDimension);

  // Evalulate the function at specified index //
  OutputType EvaluateAtIndex(const IndexType& index) const ITK_OVERRIDE;

  // Evaluate the function at non-integer positions //
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

  // Accessors //
  itkGetConstMacro(InternalImageFunction, typename InternalImageFunctionType::Pointer);
  itkSetMacro(InternalImageFunction, typename InternalImageFunctionType::Pointer);

protected:
  ImageFunctionAdaptor();
  ~ImageFunctionAdaptor() ITK_OVERRIDE {}
  void PrintSelf(std::ostream& os, itk::Indent indent) const ITK_OVERRIDE;

private:
  ImageFunctionAdaptor(const Self &);  //purposely not implemented
  void operator =(const Self&);  //purposely not implemented

  // Internal Image Function //
  typename InternalImageFunctionType::Pointer    m_InternalImageFunction;
  // Converter //
  typename ConverterType::Pointer                m_Converter;
};

} // end namespace otb

#ifndef OTB_MANUAL_INSTANTIATION
#include "otbImageFunctionAdaptor.txx"
#endif

#endif
