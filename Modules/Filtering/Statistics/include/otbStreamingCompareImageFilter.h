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
#ifndef otbStreamingCompareImageFilter_h
#define otbStreamingCompareImageFilter_h

#include "otbPersistentImageFilter.h"
#include "itkNumericTraits.h"
#include "itkArray.h"
#include "itkSimpleDataObjectDecorator.h"
#include "otbPersistentFilterStreamingDecorator.h"

namespace otb
{

/** \class PersistentCompareImageFilter
 * \brief Compute mean squared error,  mean absolute error and PSNR of two imagee using the output requested region.
 *
 *  This filter persists its temporary data. It means that if you Update it n times on n different
 * requested regions, the output estimators will be the estimators of the whole set of n regions.
 *
 * To reset the temporary data, one should call the Reset() function.
 *
 * To get the estimators once the regions have been processed via the pipeline, use the Synthetize() method.
 *
 * \sa PersistentImageFilter
 * \ingroup Streamed
 * \ingroup Multithreaded
 *
 * \ingroup OTBStatistics
 */
template<class TInputImage>
class ITK_EXPORT PersistentCompareImageFilter :
  public PersistentImageFilter<TInputImage, TInputImage>
{
public:
  /** Standard Self typedef */
  typedef PersistentCompareImageFilter                    Self;
  typedef PersistentImageFilter<TInputImage, TInputImage> Superclass;
  typedef itk::SmartPointer<Self>                         Pointer;
  typedef itk::SmartPointer<const Self>                   ConstPointer;

  /** Method for creation through the object factory. */
  itkNewMacro(Self);

  /** Runtime information support. */
  itkTypeMacro(PersistentCompareImageFilter, PersistentImageFilter);

  /** Image related typedefs. */
  typedef TInputImage                   ImageType;
  typedef typename TInputImage::Pointer InputImagePointer;

  typedef typename TInputImage::RegionType RegionType;
  typedef typename TInputImage::SizeType   SizeType;
  typedef typename TInputImage::IndexType  IndexType;
  typedef typename TInputImage::PixelType  PixelType;
  typedef itk::ProcessObject::DataObjectPointerArraySizeType DataObjectPointerArraySizeType;

  itkStaticConstMacro(InputImageDimension, unsigned int,
                      TInputImage::ImageDimension);

  /** Image related typedefs. */
  itkStaticConstMacro(ImageDimension, unsigned int,
                      TInputImage::ImageDimension);

  /** Type to use for computations. */
  typedef typename itk::NumericTraits<PixelType>::RealType RealType;

  /** Smart Pointer type to a DataObject. */
  typedef typename itk::DataObject::Pointer DataObjectPointer;

  /** Type of DataObjects used for scalar outputs */
  typedef itk::SimpleDataObjectDecorator<RealType>  RealObjectType;
  typedef itk::SimpleDataObjectDecorator<PixelType> PixelObjectType;

  /** Get the inputs */
  const TInputImage * GetInput1();
  const TInputImage * GetInput2();

  /** Connect one the first operands. */
  void SetInput1(const TInputImage *image);

  /** Connect one the second operands. */
  void SetInput2(const TInputImage *image);

  /** Return the computed PSNR. */
  RealType GetPSNR() const
  {
    return this->GetPSNROutput()->Get();
  }
  RealObjectType* GetPSNROutput();
  const RealObjectType* GetPSNROutput() const;

  /** Return the computed MSE. */
  RealType GetMSE() const
  {
    return this->GetMSEOutput()->Get();
  }
  RealObjectType* GetMSEOutput();
  const RealObjectType* GetMSEOutput() const;

  /** Return the computed MAE. */
  RealType GetMAE() const
  {
    return this->GetMAEOutput()->Get();
  }
  RealObjectType* GetMAEOutput();
  const RealObjectType* GetMAEOutput() const;
  
  /** Return the Number of Pixel which are different. */
  RealType GetDiffCount() const
  {
    return this->GetDiffCountOutput()->Get();
  }
  RealObjectType* GetDiffCountOutput();
  const RealObjectType* GetDiffCountOutput() const;

  itkGetMacro(PhysicalSpaceCheck,bool);
  itkSetMacro(PhysicalSpaceCheck,bool);

  /** Make a DataObject of the correct type to be used as the specified
   * output. */
  DataObjectPointer MakeOutput(DataObjectPointerArraySizeType idx) ITK_OVERRIDE;
  using Superclass::MakeOutput;

  /** Pass the input through unmodified. Do this by Grafting in the
   *  AllocateOutputs method.
   */
  void AllocateOutputs() ITK_OVERRIDE;
  void GenerateOutputInformation() ITK_OVERRIDE;
  void Synthetize(void) ITK_OVERRIDE;
  void Reset(void) ITK_OVERRIDE;

protected:
  PersistentCompareImageFilter();
  ~PersistentCompareImageFilter() ITK_OVERRIDE {}
  void PrintSelf(std::ostream& os, itk::Indent indent) const ITK_OVERRIDE;

  /** Multi-thread version GenerateData. */
  void  ThreadedGenerateData(const RegionType&
                             outputRegionForThread,
                             itk::ThreadIdType threadId) ITK_OVERRIDE;

  /** Allows skipping the verification of physical space between
   *  the two input images (see flag m_PhysicalSpaceCheck)
   */
  void VerifyInputInformation() ITK_OVERRIDE;

private:
  PersistentCompareImageFilter(const Self &); //purposely not implemented
  void operator =(const Self&); //purposely not implemented

  itk::Array<RealType>  m_SquareOfDifferences;
  itk::Array<RealType>  m_AbsoluteValueOfDifferences;
  itk::Array<PixelType> m_ThreadMinRef;
  itk::Array<PixelType> m_ThreadMaxRef;
  itk::Array<long>      m_Count;
  itk::Array<long>      m_DiffCount;
  bool                  m_PhysicalSpaceCheck;
}; // end of class PersistentCompareImageFilter

/*===========================================================================*/

/** \class StreamingCompareImageFilter
 * \brief This class streams the whole input image through the PersistentCompareImageFilter.
 *
 * This way, it allows computing estimator on two images. It calls the
 * Reset() method of the PersistentCompareImageFilter before streaming the image and the
 * Synthetize() method of the PersistentCompareImageFilter after having streamed the image
 * to compute the estimators. The accessor on the results are wrapping the accessors of the
 * internal PersistentCompareImageFilter.
 *
 * This filter can be used as:
 * \code
 * typedef otb::StreamingCompareImageFilter<ImageType> CompareType;
 * CompareType::Pointer estimators = CompareType::New();
 * estimators->SetInput(reader->GetOutput());
 * estimators->Update();
 * std::cout << estimators-> GetMSE() << std::endl;
 * std::cout << estimators-> GetPSNR() << std::endl;
 * \endcode
 *
 * \sa PersistentCompareImageFilter
 * \sa PersistentImageFilter
 * \sa PersistentFilterStreamingDecorator
 * \sa StreamingImageVirtualWriter
 * \ingroup Streamed
 * \ingroup Multithreaded
 *
 * \ingroup OTBStatistics
 */

template<class TInputImage>
class ITK_EXPORT StreamingCompareImageFilter :
  public PersistentFilterStreamingDecorator<PersistentCompareImageFilter<TInputImage> >
{
public:
  /** Standard Self typedef */
  typedef StreamingCompareImageFilter Self;
  typedef PersistentFilterStreamingDecorator
  <PersistentCompareImageFilter<TInputImage> > Superclass;
  typedef itk::SmartPointer<Self>       Pointer;
  typedef itk::SmartPointer<const Self> ConstPointer;

  /** Type macro */
  itkNewMacro(Self);

  /** Creation through object factory macro */
  itkTypeMacro(StreamingCompareImageFilter, PersistentFilterStreamingDecorator);

  typedef typename Superclass::FilterType       CompareFilterType;
  typedef typename CompareFilterType::PixelType PixelType;
  typedef typename CompareFilterType::RealType  RealType;
  typedef TInputImage                           InputImageType;

  /** Type of DataObjects used for scalar outputs */
  typedef itk::SimpleDataObjectDecorator<RealType>  RealObjectType;
  typedef itk::SimpleDataObjectDecorator<PixelType> PixelObjectType;

  /** Connect one the first operands. */
  void SetInput1(InputImageType * input)
  {
    this->GetFilter()->SetInput1(input);
  }

  /** Connect one the second operands. */
  void SetInput2(InputImageType * input)
  {
    this->GetFilter()->SetInput2(input);
  }

  /** Return the computed PSNR. */
  RealType GetPSNR() const
  {
    return this->GetFilter()->GetPSNROutput()->Get();
  }
  RealObjectType* GetPSNROutput()
  {
    return this->GetFilter()->GetPSNROutput();
  }
  const RealObjectType* GetPSNROutput() const
  {
    return this->GetFilter()->GetPSNROutput();
  }

  /** Return the computed MSE. */
  RealType GetMSE() const
  {
    return this->GetMSEOutput()->Get();
  }
  RealObjectType* GetMSEOutput()
  {
    return this->GetFilter()->GetMSEOutput();
  }
  const RealObjectType* GetMSEOutput() const
  {
    return this->GetFilter()->GetMSEOutput();
  }

  /** Return the computed MAE. */
  RealType GetMAE() const
  {
    return this->GetFilter()->GetMAEOutput()->Get();
  }
  RealObjectType* GetMAEOutput()
  {
    return this->GetFilter()->GetMAEOutput();
  }
  const RealObjectType* GetMAEOutput() const
  {
    return this->GetFilter()->GetMAEOutput();
  }
  
  /** Return the Number of Pixel different. */
  RealType GetDiffCount() const
  {
    return this->GetFilter()->GetDiffCountOutput()->Get();
  }
  RealObjectType* GetDiffCountOutput()
  {
    return this->GetFilter()->GetDiffCountOutput();
  }
  const RealObjectType* GetDiffCountOutput() const
  {
    return this->GetFilter()->GetDiffCountOutput();
  }

  /** Set the PhysicalSpaceCheck flag */
  void SetPhysicalSpaceCheck(bool flag)
  {
    this->GetFilter()->SetPhysicalSpaceCheck(flag);
  }

  /** Get the PhysicalSpaceCheck flag */
  bool GetPhysicalSpaceCheck()
  {
    return this->GetFilter()->GetPhysicalSpaceCheck();
  }

protected:
  /** Constructor */
  StreamingCompareImageFilter() {};
  /** Destructor */
  ~StreamingCompareImageFilter() ITK_OVERRIDE {}

private:
  StreamingCompareImageFilter(const Self &); //purposely not implemented
  void operator =(const Self&); //purposely not implemented
};

} // end namespace otb

#ifndef OTB_MANUAL_INSTANTIATION
#include "otbStreamingCompareImageFilter.txx"
#endif

#endif
