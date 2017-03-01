/*=========================================================================

  Program:   ORFEO Toolbox
  Language:  C++


  Copyright (c) Centre National d'Etudes Spatiales. All rights reserved.
  See OTBCopyright.txt for details.

     This software is distributed WITHOUT ANY WARRANTY; without even
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
     PURPOSE.  See the above copyright notices for more information.

=========================================================================*/
#ifndef otbClampImageFilter_h
#define otbClampImageFilter_h

#include "itkImageToImageFilter.h"

namespace otb
{

/** \class ClampImageFilter
 * \brief Set image values to a user-specified value if they are below,
 * above, or between simple threshold values.
 *
 * ClampImageFilter  clamp image values to be between an upper
 * and lower value. Values lower than m_Lower values are set to lower,
 * and values greater than upper threshold are set to upper threshold
 * value.
 *
 * By default lower and upper thresholds are set to the maximum and
 * minimum bounds of the image pixel type.
 *
 * The pixels must support the operators >= and <=.
 *
 * \ingroup IntensityImageFilters Multithreaded
 *
 * \ingroup OTBImageManipulation
 */
  template <class TInputImage, class TOutputImage=TInputImage>
  class ITK_EXPORT ClampImageFilter : public itk::ImageToImageFilter<TInputImage, TOutputImage>
{
public:
  /** Standard class typedefs. */
  typedef ClampImageFilter               Self;
  typedef itk::ImageToImageFilter<TInputImage, TOutputImage>  Superclass;
  typedef itk::SmartPointer<Self>                 Pointer;
  typedef itk::SmartPointer<const Self>           ConstPointer;

  /** Method for creation through the object factory. */
  itkNewMacro(Self);

  /** Run-time type information (and related methods). */
  itkTypeMacro(ClampImageFilter, itk::ImageToImageFilter);


  /** Some additional typedefs.  */
  typedef TInputImage                                  InputImageType;
  typedef typename InputImageType::ConstPointer        InputImagePointer;
  typedef typename InputImageType::RegionType          InputImageRegionType;
  typedef typename InputImageType::PixelType           InputImagePixelType;

  /** Some additional typedefs.  */
  typedef TOutputImage                                 OutputImageType;
  typedef typename OutputImageType::Pointer            OutputImagePointer;
  typedef typename OutputImageType::RegionType         OutputImageRegionType;
  typedef typename OutputImageType::PixelType          OutputImagePixelType;


  /** The values greater than or equal to the value are set to OutsideValue. */
  void ClampAbove(const OutputImagePixelType &thresh);

  /** The values less than or equal to the value are set to OutsideValue. */
  void ClampBelow(const OutputImagePixelType &thresh);

  /** The values outside the range are set to OutsideValue. */
  void ClampOutside(const OutputImagePixelType &lower, const OutputImagePixelType &upper);

  /** Set/Get methods to set the lower threshold */
  void SetLower(OutputImagePixelType val)
  {
    m_Lower = val;
    m_DLower = static_cast<double>(val);
    this->Modified();
  }
  itkGetConstMacro(Lower, OutputImagePixelType);

  /** Set/Get methods to set the upper threshold */
  void SetUpper(OutputImagePixelType val)
  {
    m_Upper = val;
    m_DUpper = static_cast<double>(val);
    this->Modified();
  }
  itkGetConstMacro(Upper, OutputImagePixelType);


protected:
  ClampImageFilter();
  ~ClampImageFilter() ITK_OVERRIDE {};
  void PrintSelf(std::ostream& os, itk::Indent indent) const ITK_OVERRIDE;

  /** ClampImageFilter can be implemented as a multithreaded filter.
   * Therefore, this implementation provides a ThreadedGenerateData() routine
   * which is called for each processing thread. The output image data is
   * allocated automatically by the superclass prior to calling
   * ThreadedGenerateData().  ThreadedGenerateData can only write to the
   * portion of the output image specified by the parameter
   * "outputRegionForThread"
   *
   * \sa ImageToImageFilter::ThreadedGenerateData(),
   *     ImageToImageFilter::GenerateData()  */
  void ThreadedGenerateData(const OutputImageRegionType& outputRegionForThread,
                            itk::ThreadIdType threadId ) ITK_OVERRIDE;

  void GenerateOutputInformation(void) ITK_OVERRIDE
  {
    Superclass::GenerateOutputInformation();

    this->GetOutput()->SetNumberOfComponentsPerPixel( this->GetInput()->GetNumberOfComponentsPerPixel() );
  }

private:
  ClampImageFilter(const Self&); //purposely not implemented
  void operator=(const Self&); //purposely not implemented

  double m_DLower;
  double m_DUpper;

  OutputImagePixelType m_Lower;
  OutputImagePixelType m_Upper;
};


} // end namespace otb

#ifndef OTB_MANUAL_INSTANTIATION
#include "otbClampImageFilter.txx"
#endif

#endif
