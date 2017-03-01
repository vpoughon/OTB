/*
 * Copyright (C) 1999-2011 Insight Software Consortium
 * Copyright (C) 2005-2016 Centre National d'Etudes Spatiales (CNES)
 *
 * This file is part of Orfeo Toolbox
 *
 *     https://www.orfeo-toolbox.org/
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef otbImageToLuminanceImageFilter_h
#define otbImageToLuminanceImageFilter_h

#include "otbUnaryImageFunctorWithVectorImageFilter.h"
#include "itkNumericTraits.h"
#include "otbMacro.h"
#include "otbOpticalImageMetadataInterfaceFactory.h"

#include <fstream>

namespace otb
{
namespace Functor
{
/**
   * \class ImageToLuminanceImageFunctor
   * \brief Add beta to the quotient Input over alpha.
   *
   * \sa ImageToLuminanceImageFilter
   * \ingroup Functor
   * \ingroup Radiometry
 *
 * \ingroup OTBOpticalCalibration
 */

template <class TInput, class TOutput>
class ImageToLuminanceImageFunctor
{
public:
  ImageToLuminanceImageFunctor() :
    m_Alpha(1.),
    m_Beta(0.)
  {}

  virtual ~ImageToLuminanceImageFunctor() {}

  void SetAlpha(double alpha)
  {
    m_Alpha = alpha;
  }
  void SetBeta(double beta)
  {
    m_Beta = beta;
  }
  double GetAlpha()
  {
    return m_Alpha;
  }
  double GetBeta()
  {
    return m_Beta;
  }

  inline TOutput operator ()(const TInput& inPixel) const
  {
    TOutput outPixel;
    double  temp;
    temp = static_cast<double>(inPixel) / m_Alpha + m_Beta;
    outPixel = static_cast<TOutput>(temp);
    return outPixel;
  }

private:
  double m_Alpha;
  double m_Beta;
};
}

/** \class ImageToLuminanceImageFilter
 *  \brief Convert a raw value into a luminance value
 *
 * Transform a classical image into the luminance image. For this it
 * uses the functor ImageToLuminanceImageFunctor calling for each component of each pixel.
 *
 *
 * For Spot image in the dimap format, the correction parameters are
 * retrieved automatically from the metadata
 *
 * \ingroup ImageToLuminanceImageFunctor
 * \ingroup Radiometry
 *
 * \example Radiometry/AtmosphericCorrectionSequencement.cxx
 *
 * \ingroup OTBOpticalCalibration
 */
template <class TInputImage, class TOutputImage>
class ITK_EXPORT ImageToLuminanceImageFilter :
  public UnaryImageFunctorWithVectorImageFilter<TInputImage,
      TOutputImage,
      typename Functor::ImageToLuminanceImageFunctor<typename
          TInputImage::
          InternalPixelType,
          typename
          TOutputImage::
          InternalPixelType> >
{
public:
  /**   Extract input and output images dimensions.*/
  itkStaticConstMacro(InputImageDimension, unsigned int, TInputImage::ImageDimension);
  itkStaticConstMacro(OutputImageDimension, unsigned int, TOutputImage::ImageDimension);

  /** "typedef" to simplify the variables definition and the declaration. */
  typedef TInputImage  InputImageType;
  typedef TOutputImage OutputImageType;
  typedef typename Functor::ImageToLuminanceImageFunctor<typename InputImageType::InternalPixelType,
      typename OutputImageType::InternalPixelType> FunctorType;

  /** "typedef" for standard classes. */
  typedef ImageToLuminanceImageFilter                                                          Self;
  typedef UnaryImageFunctorWithVectorImageFilter<InputImageType, OutputImageType, FunctorType> Superclass;
  typedef itk::SmartPointer<Self>                                                              Pointer;
  typedef itk::SmartPointer<const Self>                                                        ConstPointer;

  /** object factory method. */
  itkNewMacro(Self);

  /** return class name. */
  itkTypeMacro(ImageToLuminanceImageFilter, UnaryImageFunctorWithVectorImageFiltermageFilter);

  /** Supported images definition. */
  typedef typename InputImageType::PixelType          InputPixelType;
  typedef typename InputImageType::InternalPixelType  InputInternalPixelType;
  typedef typename InputImageType::RegionType         InputImageRegionType;
  typedef typename OutputImageType::PixelType         OutputPixelType;
  typedef typename OutputImageType::InternalPixelType OutputInternalPixelType;
  typedef typename OutputImageType::RegionType        OutputImageRegionType;

  typedef typename itk::VariableLengthVector<double> VectorType;

  /** Image size "typedef" definition. */
  typedef typename InputImageType::SizeType SizeType;

  /** Set the absolute calibration gains. */
  itkSetMacro(Alpha, VectorType);

  /** Give the absolute calibration gains. */
  itkGetConstReferenceMacro(Alpha, VectorType);

  /** Set the absolute calibration bias. */
  itkSetMacro(Beta, VectorType);
  /** Give the absolute calibration bias. */
  itkGetConstReferenceMacro(Beta, VectorType);

protected:
  /** Constructor */
  ImageToLuminanceImageFilter()
    {
    m_Alpha.SetSize(0);
    m_Beta.SetSize(0);
    };

  /** Destructor */
  ~ImageToLuminanceImageFilter() ITK_OVERRIDE {}

  /** Update the functor list and input parameters */
  void BeforeThreadedGenerateData(void) ITK_OVERRIDE
  {
    OpticalImageMetadataInterface::Pointer imageMetadataInterface = OpticalImageMetadataInterfaceFactory::CreateIMI(
      this->GetInput()->GetMetaDataDictionary());
    if (m_Alpha.GetSize() == 0)
      {
      m_Alpha = imageMetadataInterface->GetPhysicalGain();
      }

    if (m_Beta.GetSize() == 0)
      {
      m_Beta = imageMetadataInterface->GetPhysicalBias();
      }

    otbMsgDevMacro(<< "Dimension: ");
    otbMsgDevMacro(<< "m_Alpha.GetSize(): " << m_Alpha.GetSize());
    otbMsgDevMacro(<< "m_Beta.GetSize() : " << m_Beta.GetSize());
    otbMsgDevMacro(
      << "this->GetInput()->GetNumberOfComponentsPerPixel() : " << this->GetInput()->GetNumberOfComponentsPerPixel());

    if ((m_Alpha.GetSize() != this->GetInput()->GetNumberOfComponentsPerPixel())
        || (m_Beta.GetSize() != this->GetInput()->GetNumberOfComponentsPerPixel()))
      {
      itkExceptionMacro(<< "Alpha and Beta parameters should have the same size as the number of bands");
      }

    otbMsgDevMacro(<< "Using correction parameters: ");
    otbMsgDevMacro(<< "Alpha (gain): " << m_Alpha);
    otbMsgDevMacro(<< "Beta (bias):  " << m_Beta);

    this->GetFunctorVector().clear();
    for (unsigned int i = 0; i < this->GetInput()->GetNumberOfComponentsPerPixel(); ++i)
      {
      FunctorType functor;
      functor.SetAlpha(m_Alpha[i]);
      functor.SetBeta(m_Beta[i]);
      this->GetFunctorVector().push_back(functor);
      }
  }

private:
  /** Ponderation declaration*/
  VectorType m_Alpha;
  VectorType m_Beta;
};

} // end namespace otb

#endif
