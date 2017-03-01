/*=========================================================================

  Program:   ORFEO Toolbox
  Language:  C++


  Copyright (c) Centre National d'Etudes Spatiales. All rights reserved.
  See OTBCopyright.txt for details.


     This software is distributed WITHOUT ANY WARRANTY; without even
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
     PURPOSE.  See the above copyright notices for more information.

=========================================================================*/
#ifndef otbVectorImageTo3DScalarImageFilter_h
#define otbVectorImageTo3DScalarImageFilter_h

#include "itkImageToImageFilter.h"

namespace otb
{
/** \class VectorImageTo3DScalarImageFilter
 *  \brief This filter convert a 2 Dimension VectorImage to a 3 Dimension scalar image.
 *
 *  The third dimension of the output image is the index of the band in the vector image.
 *
 *  No Dimension checking is done by the filter so it is up to the user to template the input
 * and output image dimension correctly.
 *
 * Casting is done through standard casting operators.
 *
 * \ingroup Streamed
 * \ingroup Threaded
 *
 * \ingroup OTBImageManipulation
 */
template <class TInputImage, class TOutputImage>
class ITK_EXPORT VectorImageTo3DScalarImageFilter
  : public itk::ImageToImageFilter<TInputImage, TOutputImage>
{
public:
  /** Standard typedefs */
  typedef VectorImageTo3DScalarImageFilter                   Self;
  typedef itk::ImageToImageFilter<TInputImage, TOutputImage> Superclass;
  typedef itk::SmartPointer<Self>                            Pointer;
  typedef itk::SmartPointer<const Self>                      ConstPointer;

  /** Type macro */
  itkNewMacro(Self);

  /** Creation through object factory macro */
  itkTypeMacro(VectorImageTo3DScalarImageFilter, ImageToImageFilter);

  /** Template parameters typedefs */
  typedef TInputImage                           InputImageType;
  typedef typename InputImageType::ConstPointer InputImageConstPointerType;
  typedef typename InputImageType::RegionType   InputImageRegionType;
  typedef typename InputImageType::SizeType     InputImageSizeType;
  typedef typename InputImageType::IndexType    InputImageIndexType;
  typedef typename InputImageType::PixelType    InputPixelType;
  typedef TOutputImage                          OutputImageType;
  typedef typename OutputImageType::Pointer     OutputImagePointerType;
  typedef typename OutputImageType::RegionType  OutputImageRegionType;
  typedef typename OutputImageType::IndexType   OutputImageIndexType;
  typedef typename OutputImageType::SizeType    OutputImageSizeType;
  typedef typename OutputImageType::PixelType   OutputPixelType;

protected:

  /** Generate output information */
  void GenerateOutputInformation(void) ITK_OVERRIDE;

  /** Generate input requested region */
  void GenerateInputRequestedRegion(void) ITK_OVERRIDE;

  /** Threaded Generate data */
  void ThreadedGenerateData(const OutputImageRegionType& outputRegionForThread,
                            itk::ThreadIdType threadId) ITK_OVERRIDE;

  /** Constructor */
  VectorImageTo3DScalarImageFilter();
  /** Destructor */
  ~VectorImageTo3DScalarImageFilter() ITK_OVERRIDE {}
  /**PrintSelf method */
  void PrintSelf(std::ostream& os, itk::Indent indent) const ITK_OVERRIDE;

private:
  VectorImageTo3DScalarImageFilter(const Self &); //purposely not implemented
  void operator =(const Self&); //purposely not implemented
};
} // End namespace otb
#ifndef OTB_MANUAL_INSTANTIATION
#include "otbVectorImageTo3DScalarImageFilter.txx"
#endif

#endif
