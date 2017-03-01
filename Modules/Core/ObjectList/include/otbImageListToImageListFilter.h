/*=========================================================================

  Program:   ORFEO Toolbox
  Language:  C++


  Copyright (c) Centre National d'Etudes Spatiales. All rights reserved.
  See OTBCopyright.txt for details.


     This software is distributed WITHOUT ANY WARRANTY; without even
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
     PURPOSE.  See the above copyright notices for more information.

=========================================================================*/
#ifndef otbImageListToImageListFilter_h
#define otbImageListToImageListFilter_h

#include "otbImageListSource.h"

namespace otb
{
/** \class ImageListToImageListFilter
 *  \brief Base class for all the filters taking an image list as input
 *  to produce an image list.
 * \ingroup Images
 * \ingroup Lists
 *
 * \ingroup OTBObjectList
 */
template <class TInputImage, class TOutputImage>
class ITK_EXPORT ImageListToImageListFilter
  : public ImageListSource<TOutputImage>
{
public:
  /** Standard typedefs */
  typedef ImageListToImageListFilter    Self;
  typedef ImageListSource<TOutputImage> Superclass;
  typedef itk::SmartPointer<Self>       Pointer;
  typedef itk::SmartPointer<const Self> ConstPointer;
  /** Type macro */
  itkNewMacro(Self);
  /** Creation through object factory macro */
  itkTypeMacro(ImageListToImageListFilter, ImageListSource);
  /** Template parameters typedefs */
  typedef          TInputImage                      InputImageType;
  typedef typename InputImageType::ConstPointer     InputImagePointer;
  typedef typename InputImageType::RegionType       InputImageRegionType;
  typedef typename InputImageType::PixelType        InputImagePixelType;
  typedef typename InputImageType::SizeType         SizeType;
  typedef typename InputImageType::ValueType        ValueType;
  typedef ImageList<InputImageType>                 InputImageListType;
  typedef typename InputImageListType::Pointer      InputImageListPointerType;
  typedef typename InputImageListType::ConstPointer InputImageListConstPointer;
  /** Derived typedefs */
  typedef typename Superclass::OutputImageType            OutputImageType;
  typedef typename Superclass::OutputImageListType        OutputImageListType;
  typedef typename Superclass::OutputImageListPointerType OutputImageListPointerType;
  typedef typename Superclass::OutputImagePointerType     OutputImagePointer;
  /** InputImage dimension constant */
  itkStaticConstMacro(InputImageDimension, unsigned int, TInputImage::ImageDimension);
  /** Overriding the SetInput() and GetInput() methods */
  using Superclass::SetInput;
  virtual void SetInput(const InputImageListType * imageList);
  virtual InputImageListType * GetInput(void);

protected:
  /** Constructor */
  ImageListToImageListFilter();
  /** Destructor */
  ~ImageListToImageListFilter() ITK_OVERRIDE {}
  /**PrintSelf method */
  void PrintSelf(std::ostream& os, itk::Indent indent) const ITK_OVERRIDE;

private:
  ImageListToImageListFilter(const Self &); //purposely not implemented
  void operator =(const Self&); //purposely not implemented
};
} // End namespace otb
#ifndef OTB_MANUAL_INSTANTIATION
#include "otbImageListToImageListFilter.txx"
#endif

#endif
