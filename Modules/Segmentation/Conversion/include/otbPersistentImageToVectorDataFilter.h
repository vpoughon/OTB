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
#ifndef otbPersistentImageToVectorDataFilter_h
#define otbPersistentImageToVectorDataFilter_h

#include "otbPersistentImageFilter.h"
#include "itkExtractImageFilter.h"

#include "otbConcatenateVectorDataFilter.h"
#include "otbOGRVectorDataIO.h"
#include "itkMacro.h"

namespace otb
{

/** \class PersistentImageToVectorDataFilter
 *  \brief Perform vectorization in a persistent way.
 *
 *  This filter is a generic PersistentImageFilter, which encapsulate any filter
 *  which produces VectorData from an input Image.
 *
 *  It provides a default implementation which merge
 *  the VectorData from the different tiles/strips used during streaming into
 *  a single VectorData, which can be accessed via GetVectorData()
 *
 * \sa PersistentImageFilter
 *
 *
 * \ingroup OTBConversion
 */
template<class TImage, class TOutputVectorData>
class ITK_EXPORT PersistentImageToVectorDataFilter :
  public PersistentImageFilter<TImage, TImage>
{
public:
  /** Standard Self typedef */
  typedef PersistentImageToVectorDataFilter               Self;
  typedef PersistentImageFilter<TImage, TImage>            Superclass;
  typedef itk::SmartPointer<Self>                         Pointer;
  typedef itk::SmartPointer<const Self>                   ConstPointer;

  /** Runtime information support. */
  itkTypeMacro(PersistentImageToVectorDataFilter, PersistentImageFilter);

  typedef TImage                                     InputImageType;
  typedef typename InputImageType::Pointer           InputImagePointer;
  typedef typename InputImageType::RegionType        RegionType;
  typedef typename InputImageType::SizeType          SizeType;
  typedef typename InputImageType::IndexType         IndexType;
  typedef typename InputImageType::PixelType         PixelType;
  typedef typename InputImageType::InternalPixelType InternalPixelType;

  typedef TOutputVectorData                          OutputVectorDataType;
  typedef typename TOutputVectorData::Pointer        OutputVectorDataPointerType;

  typedef itk::ExtractImageFilter<InputImageType, InputImageType> ExtractImageFilterType;
  typedef typename ExtractImageFilterType::Pointer                ExtractImageFilterPointerType;

  typedef otb::ConcatenateVectorDataFilter<OutputVectorDataType> ConcatenateVectorDataFilterType;
  typedef typename ConcatenateVectorDataFilterType::Pointer      ConcatenateVectorDataFilterPointerType;

  typedef otb::OGRVectorDataIO       OGRVectorDataIOType;
  typedef typename OGRVectorDataIOType::Pointer   OGRVectorDataIOPointerType;

  /** Smart Pointer type to a DataObject. */
  typedef itk::DataObject::Pointer DataObjectPointer;

  OutputVectorDataType* GetOutputVectorData() const;

  void AllocateOutputs() ITK_OVERRIDE;

  void Reset(void) ITK_OVERRIDE;

  void Synthetize(void) ITK_OVERRIDE;

  /** Specify the name of the output shapefile to write. */
  itkSetStringMacro(FileName);
  itkGetStringMacro(FileName);

protected:
  PersistentImageToVectorDataFilter();
  ~PersistentImageToVectorDataFilter() ITK_OVERRIDE {}

  void PrintSelf(std::ostream& os, itk::Indent indent) const ITK_OVERRIDE;

  void GenerateData() ITK_OVERRIDE;

  ExtractImageFilterPointerType          m_ExtractFilter;

  OutputVectorDataPointerType m_OutputVectorData;

private:
  PersistentImageToVectorDataFilter(const Self &); //purposely not implemented
  void operator =(const Self&); //purposely not implemented

  virtual OutputVectorDataPointerType ProcessTile() = 0;

  OGRVectorDataIOPointerType m_VectorDataIO;
  std::string m_FileName;

}; // end of class
} // end namespace otb

#ifndef OTB_MANUAL_INSTANTIATION
#include "otbPersistentImageToVectorDataFilter.txx"
#endif

#endif
