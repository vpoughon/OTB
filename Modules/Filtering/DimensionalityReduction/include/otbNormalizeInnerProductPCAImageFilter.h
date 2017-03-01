/*=========================================================================

  Program:   ORFEO Toolbox
  Language:  C++


  Copyright (c) Centre National d'Etudes Spatiales. All rights reserved.
  See OTBCopyright.txt for details.

  Some parts of this code are derived from ITK. See ITKCopyright.txt
  for details.


     This software is distributed WITHOUT ANY WARRANTY; without even
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
     PURPOSE.  See the above copyright notices for more information.

=========================================================================*/
#ifndef otbNormalizeInnerProductPCAImageFilter_h
#define otbNormalizeInnerProductPCAImageFilter_h

#include "itkInPlaceImageFilter.h"
#include "otbStreamingStatisticsVectorImageFilter.h"

namespace otb
{
/** \class NormalizeInnerProductPCAImageFilter
 *  \brief  The aim of the class is to normalise vector images using a vector coefficient values.
 *
 * \ingroup VectorImage
 *
 * \ingroup OTBDimensionalityReduction
 */
template <class TInputImage, class TOutputImage>
class ITK_EXPORT NormalizeInnerProductPCAImageFilter : public itk::InPlaceImageFilter<TInputImage, TOutputImage>

{
public:
  /** Standard class typedefs. */
  typedef NormalizeInnerProductPCAImageFilter                Self;
  typedef itk::InPlaceImageFilter<TInputImage, TOutputImage> Superclass;
  typedef itk::SmartPointer<Self>                            Pointer;
  typedef itk::SmartPointer<const Self>                      ConstPointer;

  /** Method for creation through the object factory. */
  itkNewMacro(Self);

  /** return class name. */
  itkTypeMacro(NormalizeInnerProductPCAImageFilter, itk::InPlaceImageFilter);

  /**   Extract input and output images dimensions.*/
  itkStaticConstMacro(InputImageDimension, unsigned int, TInputImage::ImageDimension);
  itkStaticConstMacro(OutputImageDimension, unsigned int, TOutputImage::ImageDimension);

  /** "typedef" to simplify the variables definition and the declaration. */
  typedef TInputImage  InputImageType;
  typedef TOutputImage OutputImageType;

  /** Supported images definition. */
  typedef typename InputImageType::PixelType          InputPixelType;
  typedef typename InputImageType::InternalPixelType  InputInternalPixelType;
  typedef typename InputImageType::RegionType         InputImageRegionType;
  typedef typename OutputImageType::PixelType         OutputPixelType;
  typedef typename OutputImageType::InternalPixelType OutputInternalPixelType;
  typedef typename OutputImageType::RegionType        OutputImageRegionType;

  /** Image size "typedef" definition. */
  typedef typename InputImageType::SizeType SizeType;

  /** Typedef for statistic computing. */
  typedef StreamingStatisticsVectorImageFilter<InputImageType>             StreamingStatisticsVectorImageFilterType;
  typedef typename StreamingStatisticsVectorImageFilterType::Pointer       StreamingStatisticsVectorImageFilterPointer;
  typedef typename StreamingStatisticsVectorImageFilterType::RealType      RealType;
  typedef typename StreamingStatisticsVectorImageFilterType::RealPixelType RealPixelType;
  typedef typename StreamingStatisticsVectorImageFilterType::MatrixType    MatrixType;

  itkSetMacro(UseUnbiasedEstimator, bool);
  itkGetMacro(UseUnbiasedEstimator, bool);

protected:
  NormalizeInnerProductPCAImageFilter();
  ~NormalizeInnerProductPCAImageFilter() ITK_OVERRIDE {}

  /** NormalizeInnerProductPCAImageFilter can produce an image which is a different
   * resolution than its input image.  As such, NormalizeInnerProductPCAImageFilter
   * needs to provide an implementation for
   * GenerateOutputInformation() in order to inform the pipeline
   * execution model.  The original documentation of this method is
   * below.
   *
   * \sa ProcessObject::GenerateOutputInformaton()  */
  void GenerateOutputInformation() ITK_OVERRIDE;

  /** NormalizeInnerProductPCAImageFilter can be implemented as a multithreaded filter.
   * Therefore, this implementation provides a ThreadedGenerateData() routine
   * which is called for each processing thread. The output image data is
   * allocated automatically by the superclass prior to calling
   * ThreadedGenerateData().  ThreadedGenerateData can only write to the
   * portion of the output image specified by the parameter
   * "outputRegionForThread"
   *
   * \sa ImageToImageFilter::ThreadedGenerateData(),
   *     ImageToImageFilter::GenerateData()  */
  void ThreadedGenerateData(const OutputImageRegionType& outputRegionForThread, itk::ThreadIdType threadId) ITK_OVERRIDE;

  /** BeforeThreadedGenerateData method */
  void BeforeThreadedGenerateData() ITK_OVERRIDE;

  void PrintSelf(std::ostream& os, itk::Indent indent) const ITK_OVERRIDE;

private:

  /** Contains normalization coefficient input image */
  RealPixelType m_CoefNorm;

  /* use an unbiased estimator to compute the covariance */
  bool m_UseUnbiasedEstimator;
};

} // end namespace otb

#ifndef OTB_MANUAL_INSTANTIATION
#include "otbNormalizeInnerProductPCAImageFilter.txx"
#endif

#endif
