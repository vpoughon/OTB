/*
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

#ifndef otbStreamingShrinkImageFilter_h
#define otbStreamingShrinkImageFilter_h


#include "otbPersistentImageFilter.h"
#include "otbPersistentFilterStreamingDecorator.h"

#include "otbStreamingManager.h"
#include "otbMacro.h"

namespace otb
{

class ITK_EXPORT StreamingShrinkImageRegionSplitter : public itk::ImageRegionSplitter<2>
{
public:
  /** Standard class typedefs. */
  typedef StreamingShrinkImageRegionSplitter        Self;
  typedef itk::ImageRegionSplitter<2>               Superclass;
  typedef itk::SmartPointer<Self>                   Pointer;
  typedef itk::SmartPointer<const Self>             ConstPointer;

  /** Method for creation through the object factory. */
  itkNewMacro(Self);

  /** Run-time type information (and related methods). */
  itkTypeMacro(StreamingShrinkImageRegionSplitter, itk::Object);

  /** Dimension of the image available at compile time. */
  itkStaticConstMacro(ImageDimension, unsigned int, 2);

  /** Dimension of the image available at run time. */
  static unsigned int GetImageDimension()
  {
    return ImageDimension;
  }

  /** Index typedef support. An index is used to access pixel values. */
  typedef itk::Index<ImageDimension>         IndexType;
  typedef IndexType::IndexValueType IndexValueType;

  /** Size typedef support. A size is used to define region bounds. */
  typedef itk::Size<ImageDimension>        SizeType;
  typedef SizeType::SizeValueType SizeValueType;

  /** Region typedef support.   */
  typedef itk::ImageRegion<ImageDimension> RegionType;

  /** How many pieces can the specified region be split? A given region
   *  cannot always be divided into the requested number of pieces.  For
   *  instance, if the numberOfPieces exceeds the number of pixels along
   *  a certain dimensions, then some splits will not be possible.
   */
  unsigned int GetNumberOfSplits(const RegionType& region,
                                         unsigned int requestedNumber) ITK_OVERRIDE;

  /** Get a region definition that represents the ith piece a specified region.
   * The "numberOfPieces" specified should be less than or equal to what
   * GetNumberOfSplits() returns. */
  RegionType GetSplit(unsigned int i, unsigned int numberOfPieces,
                              const RegionType& region) ITK_OVERRIDE;

  itkGetMacro(TileSizeAlignment, unsigned int);

  itkGetMacro(TileDimension, unsigned int);

  itkSetMacro(ShrinkFactor, unsigned int);
  itkGetMacro(ShrinkFactor, unsigned int);

protected:
  StreamingShrinkImageRegionSplitter() : m_SplitsPerDimension(0U), m_TileDimension(0), m_TileSizeAlignment(0), m_ShrinkFactor(10) {}
  ~StreamingShrinkImageRegionSplitter() ITK_OVERRIDE {}
  void PrintSelf(std::ostream& os, itk::Indent indent) const ITK_OVERRIDE;

private:
  StreamingShrinkImageRegionSplitter(const StreamingShrinkImageRegionSplitter &); //purposely not implemented
  void operator =(const StreamingShrinkImageRegionSplitter&); //purposely not implemented

  itk::FixedArray<unsigned int, ImageDimension> m_SplitsPerDimension;
  unsigned int m_TileDimension;
  unsigned int m_TileSizeAlignment;
  unsigned int m_ShrinkFactor;
};


template <class TInputImage>
class ITK_EXPORT StreamingShrinkStreamingManager : public StreamingManager<TInputImage>
{
public:
  /** Standard class typedefs. */
  typedef StreamingShrinkStreamingManager Self;
  typedef StreamingManager<TInputImage>   Superclass;
  typedef itk::SmartPointer<Self>         Pointer;
  typedef itk::SmartPointer<const Self>   ConstPointer;

  /** Method for creation through the object factory. */
  itkNewMacro(Self);

  /** Runtime information support. */
  itkTypeMacro(StreamingShrinkStreamingManager, StreamingManager);

  typedef TInputImage                            ImageType;
  typedef typename ImageType::Pointer            ImagePointerType;
  typedef typename ImageType::RegionType         RegionType;
  typedef typename RegionType::IndexType         IndexType;
  typedef typename RegionType::SizeType          SizeType;
  typedef typename ImageType::InternalPixelType  PixelType;

  itkStaticConstMacro(InputImageDimension, unsigned int, TInputImage::ImageDimension);

  /** Actually computes the stream divisions, according to the specified streaming mode,
   * eventually using the input parameter to estimate memory consumption */
  void PrepareStreaming(itk::DataObject * input, const RegionType &region) ITK_OVERRIDE;

  void SetShrinkFactor(unsigned int val)
  {
    m_ShrinkFactor = val;
  }

  unsigned int GetShrinkFactor() const
  {
    return m_ShrinkFactor;
  }

protected:
  StreamingShrinkStreamingManager();
  ~StreamingShrinkStreamingManager() ITK_OVERRIDE;

private:
  StreamingShrinkStreamingManager(const StreamingShrinkStreamingManager &); //purposely not implemented
  void operator =(const StreamingShrinkStreamingManager&); //purposely not implemented

  unsigned int m_ShrinkFactor;
};


/** \class PersistentShrinkImageFilter
 * \brief
 *
 * \sa PersistentImageFilter
 * \ingroup Streamed
 * \ingroup Multithreaded
 *
 *
 * \ingroup OTBImageManipulation
 */
template<class TInputImage, class TOutputImage = TInputImage>
class ITK_EXPORT PersistentShrinkImageFilter :
  public PersistentImageFilter<TInputImage, TOutputImage>
{
public:
  /** Standard Self typedef */
  typedef PersistentShrinkImageFilter                      Self;
  typedef PersistentImageFilter<TInputImage, TOutputImage> Superclass;
  typedef itk::SmartPointer<Self>                          Pointer;
  typedef itk::SmartPointer<const Self>                    ConstPointer;

  /** Method for creation through the object factory. */
  itkNewMacro(Self);

  /** Runtime information support. */
  itkTypeMacro(PersistentShrinkImageFilter, PersistentImageFilter);

  /** Image related typedefs. */
  typedef TInputImage                             InputImageType;
  typedef typename TInputImage::Pointer           InputImagePointer;
  typedef typename TInputImage::RegionType        RegionType;
  typedef typename TInputImage::SizeType          SizeType;
  typedef typename TInputImage::IndexType         IndexType;
  typedef typename TInputImage::PixelType         PixelType;

  /** Image related typedefs. */
  typedef TOutputImage                             OutputImageType;
  typedef typename TOutputImage::Pointer           OutputImagePointer;

  itkStaticConstMacro(InputImageDimension, unsigned int, TInputImage::ImageDimension);

  /** Smart Pointer type to a DataObject. */
  typedef typename itk::DataObject::Pointer DataObjectPointer;

  OutputImageType * GetShrunkOutput()
  {
    return m_ShrunkOutput;
  }

  /** THIS METHOD IS DEPRECATED AND SHOULD NOT BE USED. */
  OutputImageType * GetShrinkedOutput()
  {
    otbWarningMacro(<< "GetShrinkedOutput has been deprecated.  Please use GetShrunkOutput instead");
    return GetShrunkOutput();
  }
  
  void Synthetize(void) ITK_OVERRIDE;

  void Reset(void) ITK_OVERRIDE;

  itkSetMacro(ShrinkFactor, unsigned int);
  itkGetMacro(ShrinkFactor, unsigned int);

protected:
  PersistentShrinkImageFilter();

  ~PersistentShrinkImageFilter() ITK_OVERRIDE;

  void PrintSelf(std::ostream& os, itk::Indent indent) const ITK_OVERRIDE;

  void  BeforeThreadedGenerateData() ITK_OVERRIDE;

  /** Multi-thread version GenerateData. */
  void  ThreadedGenerateData(const RegionType& outputRegionForThread, itk::ThreadIdType threadId) ITK_OVERRIDE;

  void  AfterThreadedGenerateData() ITK_OVERRIDE;

  /** Pass the input through unmodified. Do this by Grafting in the
   *  AllocateOutputs method.
   */
  void AllocateOutputs() ITK_OVERRIDE;

  void GenerateOutputInformation() ITK_OVERRIDE;


private:
  PersistentShrinkImageFilter(const Self &); //purposely not implemented
  void operator =(const Self&); //purposely not implemented

  /* the output shrunk image */
  OutputImagePointer m_ShrunkOutput;

  /** The shrink factor */
  unsigned int m_ShrinkFactor;

  /** The offset to get the cell center */
  IndexType m_Offset;
}; // end of class PersistentStatisticsVectorImageFilter


/** \class StreamingShrinkImageFilter
 * \brief Generates a quicklook of the input image
 *
 * This filter computes a subsampled version of the input image with streaming capabilities
 *
 * The subsampling ration is set with SetShrinkFactor
 *
 * \sa PersistentImageFilter
 * \ingroup Streamed
 * \ingroup Multithreaded
 *
 *
 * \ingroup OTBImageManipulation
 */
template<class TInputImage, class TOutputImage = TInputImage>
class ITK_EXPORT StreamingShrinkImageFilter :
  public PersistentFilterStreamingDecorator< PersistentShrinkImageFilter<TInputImage, TOutputImage> >
{
public:
  /** Standard Self typedef */
  typedef StreamingShrinkImageFilter                Self;
  typedef PersistentFilterStreamingDecorator
    <PersistentShrinkImageFilter<TInputImage, TOutputImage> >  Superclass;
  typedef itk::SmartPointer<Self>                   Pointer;
  typedef itk::SmartPointer<const Self>             ConstPointer;

  /** Type macro */
  itkNewMacro(Self);

  /** Creation through object factory macro */
  itkTypeMacro(StreamingShrinkImageFilter, PersistentFilterStreamingDecorator);

  typedef TInputImage                                 InputImageType;
  typedef TOutputImage                                OutputImageType;
  typedef typename Superclass::FilterType             PersistentFilterType;

  typedef StreamingShrinkStreamingManager<InputImageType>       StreamingShrinkStreamingManagerType;
  typedef typename StreamingShrinkStreamingManagerType::Pointer StreamingShrinkStreamingManagerPointerType;

  using Superclass::SetInput;
  void SetInput(InputImageType * input)
  {
    this->GetFilter()->SetInput(input);
  }

  const InputImageType * GetInput()
  {
    return this->GetFilter()->GetInput();
  }

  OutputImageType * GetOutput()
  {
    return this->GetFilter()->GetShrunkOutput();
  }

  otbSetObjectMemberMacro(Filter, ShrinkFactor, unsigned int);
  otbGetObjectMemberMacro(Filter, ShrinkFactor, unsigned int);

  void Update(void) ITK_OVERRIDE
  {
    m_StreamingManager->SetShrinkFactor( this->GetFilter()->GetShrinkFactor() );
    Superclass::Update();
  }

protected:
  /** Constructor */
  StreamingShrinkImageFilter()
  {
    // Use a specific StreamingManager implementation
    m_StreamingManager = StreamingShrinkStreamingManagerType::New();
    this->GetStreamer()->SetStreamingManager( m_StreamingManager );
  }

  /** Destructor */
  ~StreamingShrinkImageFilter() ITK_OVERRIDE {}

private:
  StreamingShrinkImageFilter(const Self &); //purposely not implemented
  void operator =(const Self&); //purposely not implemented

  StreamingShrinkStreamingManagerPointerType m_StreamingManager;
};

} // End namespace otb

#ifndef OTB_MANUAL_INSTANTIATION
#include "otbStreamingShrinkImageFilter.txx"
#endif

#endif
