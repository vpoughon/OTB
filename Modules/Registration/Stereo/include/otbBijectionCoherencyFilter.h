/*=========================================================================

  Program:   ORFEO Toolbox
  Language:  C++


  Copyright (c) Centre National d'Etudes Spatiales. All rights reserved.
  See OTBCopyright.txt for details.


     This software is distributed WITHOUT ANY WARRANTY; without even
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
     PURPOSE.  See the above copyright notices for more information.

=========================================================================*/
#ifndef otbBijectionCoherencyFilter_h
#define otbBijectionCoherencyFilter_h

#include "itkImageToImageFilter.h"
#include "otbLineOfSightOptimizer.h"
#include "otbImage.h"

namespace otb
{

/** \class BijectionCoherencyFilter
 *  \brief Left-right coherency filter for disparity maps
 *
 *  This filter checks that left-to-right and right-to-left disparities (computed
 *  for a given stereo pair) are compatible, within a given tolerance radius.
 *  Disparities are expected to be given in index coordinates between a pair of
 *  epipolar images of equal size. 1D or 2D disparities may be supplied.
 *  Left-to-right disparities will be referred as direct, right-to-left as
 *  reverse.
 *  The output is a mask for coherent direct disparities.
 *
 *  \ingroup Streamed
 *  \ingroup Threaded
 *
 *
 * \ingroup OTBStereo
 */
template <class TDisparityImage, class TOutputImage = otb::Image<unsigned char> >
class ITK_EXPORT BijectionCoherencyFilter :
    public itk::ImageToImageFilter<TDisparityImage,TOutputImage>
{
public:
  /** Standard class typedef */
  typedef BijectionCoherencyFilter                            Self;
  typedef itk::ImageToImageFilter<TDisparityImage,
                                  TOutputImage>             Superclass;
  typedef itk::SmartPointer<Self>                           Pointer;
  typedef itk::SmartPointer<const Self>                     ConstPointer;

  /** Method for creation through the object factory. */
  itkNewMacro(Self);

  /** Run-time type information (and related methods). */
  itkTypeMacro(BijectionCoherencyFilter, ImageToImageFilter);

  /** Useful typedefs */
  typedef TDisparityImage  DispMapType;
  typedef TOutputImage     MaskType;

  typedef typename MaskType::RegionType      OutputRegionType;
  typedef typename DispMapType::RegionType   InputRegionType;
  typedef typename DispMapType::SizeType     SizeType;
  typedef typename DispMapType::IndexType    IndexType;

  /** Set the direct horizontal disparity map */
  void SetDirectHorizontalDisparityMapInput( const TDisparityImage * hmap );

  /** Set the direct vertical disparity map */
  void SetDirectVerticalDisparityMapInput( const TDisparityImage * vmap );

  /** Set the reverse horizontal disparity map */
  void SetReverseHorizontalDisparityMapInput( const TDisparityImage * hmap );

  /** Set the reverse vertical disparity map */
  void SetReverseVerticalDisparityMapInput( const TDisparityImage * vmap );

  /** Get the inputs */
  const TDisparityImage * GetDirectHorizontalDisparityMapInput() const;
  const TDisparityImage * GetDirectVerticalDisparityMapInput() const;
  const TDisparityImage * GetReverseHorizontalDisparityMapInput() const;
  const TDisparityImage * GetReverseVerticalDisparityMapInput() const;

  /** Set the tolerance radius */
  itkSetMacro(Tolerance,double);

  /** Get the tolerance radius */
  itkGetMacro(Tolerance,double);

  /** Set/Get macro for exploration area */
  itkSetMacro(MinHDisp,int);
  itkGetMacro(MinHDisp,int);

  itkSetMacro(MaxHDisp,int);
  itkGetMacro(MaxHDisp,int);

  itkSetMacro(MinVDisp,int);
  itkGetMacro(MinVDisp,int);

  itkSetMacro(MaxVDisp,int);
  itkGetMacro(MaxVDisp,int);

protected:
  /** Constructor */
  BijectionCoherencyFilter();

  /** Destructor */
  ~BijectionCoherencyFilter() ITK_OVERRIDE{};

  /** Generate output information */
  void GenerateOutputInformation() ITK_OVERRIDE;

  /** Generate input requested region */
  void GenerateInputRequestedRegion() ITK_OVERRIDE;

  /** Threaded generate data */
  void ThreadedGenerateData(const OutputRegionType & outputRegionForThread, itk::ThreadIdType threadId) ITK_OVERRIDE;

private:
  BijectionCoherencyFilter(const Self&); //purposely not implemented
  void operator=(const Self&); //purposely not implemented

  /** Tolerance radius (in pixels) */
  double m_Tolerance;

  /** Minimum horizontal input disparity  */
  int m_MinHDisp;

  /** Maximum horizontal input disparity */
  int m_MaxHDisp;

  /** Minimum vertical input disparity */
  int m_MinVDisp;

  /** Maximum vertical input disparity */
  int m_MaxVDisp;
};

} // end namespace otb

#ifndef OTB_MANUAL_INSTANTIATION
#include "otbBijectionCoherencyFilter.txx"
#endif

#endif
