/*=========================================================================

  Program:   ORFEO Toolbox
  Language:  C++


  Copyright (c) Centre National d'Etudes Spatiales. All rights reserved.
  See OTBCopyright.txt for details.


     This software is distributed WITHOUT ANY WARRANTY; without even
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
     PURPOSE.  See the above copyright notices for more information.

=========================================================================*/

#ifndef otbImageListToSingleImageFilter_txx
#define otbImageListToSingleImageFilter_txx

#include "itkImageRegionConstIteratorWithIndex.h"
#include "itkImageRegionIteratorWithIndex.h"
#include "itkProgressReporter.h"
#include "otbImageListToSingleImageFilter.h"

namespace otb
{
/**
 * Constructor
 */
template <class TImageType>
ImageListToSingleImageFilter<TImageType>
::ImageListToSingleImageFilter()
 :m_ExtractedImagePosition(0)
{
  this->SetNumberOfRequiredInputs(1);
  this->SetNumberOfRequiredOutputs(1);
}

template <class TImageType>
typename ImageListToSingleImageFilter<TImageType>::OutputImagePointerType
ImageListToSingleImageFilter<TImageType>
::GetOutput()
{
  // If there is no input
  if (this->GetNumberOfInputs() != 1)
    {
    // exit
    return ITK_NULLPTR;
    }
  // else return the first input
  return static_cast<OutputImagePointerType>(
       this->GetInput()->GetNthElement(m_ExtractedImagePosition));
}

/**
 * Main computation method
 */
template <class TImageType>
void
ImageListToSingleImageFilter<TImageType>
::GenerateData(void)
{
  OutputImagePointerType  outputPtr = this->GetOutput();
  InputImagePointerType inputPtr = this->GetInput()->GetNthElement(m_ExtractedImagePosition);

  typedef itk::ImageRegionConstIteratorWithIndex<InputImageType> InputIteratorType;
  typedef itk::ImageRegionIteratorWithIndex<OutputImageType>     OutputIteratorType;

  outputPtr->SetBufferedRegion(outputPtr->GetRequestedRegion());
  outputPtr->Allocate();

  itk::ProgressReporter progress(this, 0, outputPtr->GetRequestedRegion().GetNumberOfPixels());

  OutputIteratorType outputIt(outputPtr, outputPtr->GetRequestedRegion());
  outputIt.GoToBegin();

  InputIteratorType inputIt(inputPtr, outputPtr->GetRequestedRegion());
  inputIt.GoToBegin();
  while (!inputIt.IsAtEnd())
    {

    if ( !(outputIt).IsAtEnd())
      {
      outputIt.Set(inputIt.Get());
      ++outputIt;
      }
    else
      {
      itkGenericExceptionMacro("End of image at index " << outputIt.GetIndex() << " !");
      }
    ++inputIt;
    }
}

/**
 * PrintSelf Method
 */
template <class TImageType>
void
ImageListToSingleImageFilter<TImageType>
::PrintSelf(std::ostream& os, itk::Indent indent) const
{
  Superclass::PrintSelf(os, indent);
}

} // End namespace otb
#endif
