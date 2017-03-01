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

#ifndef otbStreamingResampleImageFilter_txx
#define otbStreamingResampleImageFilter_txx

#include "otbStreamingResampleImageFilter.h"
#include "itkProgressAccumulator.h"

namespace otb
{

template <class TInputImage, class TOutputImage, class TInterpolatorPrecisionType>
StreamingResampleImageFilter<TInputImage, TOutputImage, TInterpolatorPrecisionType>
::StreamingResampleImageFilter()
{
  // internal filters instantiation
  m_DisplacementFilter = DisplacementFieldGeneratorType::New();
  m_WarpFilter        = WarpImageFilterType::New();

  // Initialize the displacement field spacing to zero : inconsistent
  // value
  this->SetDisplacementFieldSpacing(itk::NumericTraits<SpacingType>::ZeroValue());

  // Wire minipipeline
  m_WarpFilter->SetDisplacementField(m_DisplacementFilter->GetOutput());
}

template <class TInputImage, class TOutputImage, class TInterpolatorPrecisionType>
void
StreamingResampleImageFilter<TInputImage, TOutputImage, TInterpolatorPrecisionType>
::GenerateData()
{
  // Set up progress reporting
  typename itk::ProgressAccumulator::Pointer progress = itk::ProgressAccumulator::New();
  progress->SetMiniPipelineFilter(this);
  progress->RegisterInternalFilter(m_WarpFilter, 1.f);

  m_WarpFilter->GraftOutput(this->GetOutput());
  m_WarpFilter->UpdateOutputData(m_WarpFilter->GetOutput());
  this->GraftOutput(m_WarpFilter->GetOutput());
}

/**
 *
 */
template <class TInputImage, class TOutputImage, class TInterpolatorPrecisionType>
void
StreamingResampleImageFilter<TInputImage, TOutputImage, TInterpolatorPrecisionType>
::GenerateOutputInformation()
{
  // check the output spacing of the displacement field
  if(this->GetDisplacementFieldSpacing()== itk::NumericTraits<SpacingType>::ZeroValue())
    {
    this->SetDisplacementFieldSpacing(2.*this->GetOutputSpacing());
    }

  // Retrieve output largest region
  SizeType largestSize       = this->GetOutputSize();

  // Set up displacement field filter
  SizeType displacementFieldLargestSize;

  for(unsigned int dim = 0; dim < InputImageType::ImageDimension; ++dim)
    {
    // vcl_ceil to avoid numerical problems due to division of
    // spacings
    // + 1 :  We need to enlarge the displacement field size cause
    // itk::WarpImageFilter::EvaluateDisplacementAtPhysicalPoint needs
    // 4 neighbors and in the edges we can need 1 neighbor pixel
    // outside the field
    displacementFieldLargestSize[dim] = static_cast<unsigned int>(
      vcl_ceil( largestSize[dim]*
                vcl_abs(this->GetOutputSpacing()[dim] /
                        this->GetDisplacementFieldSpacing()[dim]))) + 1;
    }
  m_DisplacementFilter->SetOutputSize(displacementFieldLargestSize);
  m_DisplacementFilter->SetOutputIndex(this->GetOutputStartIndex());

  m_WarpFilter->SetInput(this->GetInput());
  m_WarpFilter->GraftOutput(this->GetOutput());
  m_WarpFilter->UpdateOutputInformation();
  this->GraftOutput(m_WarpFilter->GetOutput());
}

template <class TInputImage, class TOutputImage, class TInterpolatorPrecisionType>
void
StreamingResampleImageFilter<TInputImage, TOutputImage, TInterpolatorPrecisionType>
::PropagateRequestedRegion(itk::DataObject *output)
{
  if (this->m_Updating) return;

  m_WarpFilter->GetOutput()->SetRequestedRegion(output);
  m_WarpFilter->GetOutput()->PropagateRequestedRegion();
}

/**
 * Method used to copy the parameters of the input image
 *
 */
template <class TInputImage, class TOutputImage, class TInterpolatorPrecisionType>
void
StreamingResampleImageFilter<TInputImage, TOutputImage, TInterpolatorPrecisionType>
::SetOutputParametersFromImage(const ImageBaseType * image)
{
  this->SetOutputOrigin ( image->GetOrigin() );
  this->SetOutputSpacing ( image->GetSpacing() );
  this->SetOutputStartIndex ( image->GetLargestPossibleRegion().GetIndex() );
  this->SetOutputSize ( image->GetLargestPossibleRegion().GetSize() );
}


template <class TInputImage, class TOutputImage, class TInterpolatorPrecisionType>
void
StreamingResampleImageFilter<TInputImage, TOutputImage, TInterpolatorPrecisionType>
::PrintSelf(std::ostream& os, itk::Indent indent) const
{
  Superclass::PrintSelf(os, indent);
  os << indent << "OutputOrigin: " << this->GetOutputOrigin() << std::endl;
  os << indent << "OutputSpacing: " << this->GetOutputSpacing() << std::endl;
  os << indent << "OutputStartIndex: " << this->GetOutputStartIndex() << std::endl;
  os << indent << "OutputSize: " << this->GetOutputSize() << std::endl;
}


}
#endif
