/*=========================================================================

  Program:   ORFEO Toolbox
  Language:  C++


  Copyright (c) Centre National d'Etudes Spatiales. All rights reserved.
  See OTBCopyright.txt for details.


     This software is distributed WITHOUT ANY WARRANTY; without even
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
     PURPOSE.  See the above copyright notices for more information.

=========================================================================*/
#ifndef otbImageListToSingleImageFilter_h
#define otbImageListToSingleImageFilter_h

#include "otbImageListToImageFilter.h"

namespace otb
{
/** \class ImageListToSingleImageFilter
 *  \brief This class aims at converting a image list to one (scalar or vector) image.
 *
 * This class takes a image list image represented as an otb::ImageList and produces a
 * output which contains of scalar/vector images corresponding to the element selected.
 * This filter avoid to break the pipeline after the use of an filter which derive
 * from ImageToImagelistFilter class.
 *
 *
 * \ingroup Streamed
 *
 * \ingroup OTBObjectList
 */

template <class TInputImageType>
class ITK_EXPORT ImageListToSingleImageFilter
  : public ImageListToImageFilter<TInputImageType, TInputImageType>
{
public:
  /** Standard typedefs */
  typedef ImageListToSingleImageFilter              Self;
  typedef ImageListToImageFilter
      <TInputImageType, TInputImageType>            Superclass;
  typedef itk::SmartPointer<Self>                   Pointer;
  typedef itk::SmartPointer<const Self>             ConstPointer;

  typedef TInputImageType                           InputImageType;
  typedef typename InputImageType::Pointer          InputImagePointerType;
  typedef ImageList<InputImageType>                 InputImageListType;
  typedef TInputImageType                           OutputImageType;
  typedef typename OutputImageType::Pointer         OutputImagePointerType;

  /** Type macro */
  itkNewMacro(Self);

  /** Creation through object factory macro */
  itkTypeMacro(ImageListToSingleImageFilter, ImageListToImageFilter);

  /** Set/Get the position of the extracted image from the image list */
  itkGetMacro(ExtractedImagePosition, unsigned int);
  itkSetMacro(ExtractedImagePosition, unsigned int);

  InputImagePointerType GetOutput(void);

protected:
  /** Constructor */
  ImageListToSingleImageFilter();
  /** Destructor */
  ~ImageListToSingleImageFilter() ITK_OVERRIDE {}

  /** Main computation method */
  void GenerateData() ITK_OVERRIDE;

  /**PrintSelf method */
  void PrintSelf(std::ostream& os, itk::Indent indent) const ITK_OVERRIDE;


private:
  ImageListToSingleImageFilter(const Self &); //purposely not implemented
  void operator =(const Self&); //purposely not implemented

  unsigned int m_ExtractedImagePosition;

}; // end of class

} // end of namespace

#ifndef OTB_MANUAL_INSTANTIATION
#include "otbImageListToSingleImageFilter.txx"
#endif

#endif
