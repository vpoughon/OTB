/*=========================================================================

  Program:   ORFEO Toolbox
  Language:  C++
  Date:      $Date$
  Version:   $Revision$


  Copyright (c) Centre National d'Etudes Spatiales. All rights reserved.
  See OTBCopyright.txt for details.

  Some parts of this code are derived from ITK. See ITKCopyright.txt
  for details.


     This software is distributed WITHOUT ANY WARRANTY; without even
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
     PURPOSE.  See the above copyright notices for more information.

=========================================================================*/
#ifndef __otbStreamingLineSegmentDetector_txx
#define __otbStreamingLineSegmentDetector_txx

#include "otbStreamingLineSegmentDetector.h"

namespace otb
{

template<class TInputImage>
PersistentStreamingLineSegmentDetector<TInputImage>
::PersistentStreamingLineSegmentDetector()
{
}

template<class TInputImage>
PersistentStreamingLineSegmentDetector<TInputImage>
::~PersistentStreamingLineSegmentDetector()
{
}

template<class TInputImage>
void
PersistentStreamingLineSegmentDetector<TInputImage>
::GenerateInputRequestedRegion()
{
  Superclass::GenerateInputRequestedRegion();

  if (this->GetInput())
    {
    InputImagePointerType input = const_cast<InputImageType *> (this->GetInput());

    typename InputImageType::RegionType region = this->GetOutput()->GetRequestedRegion();

    region.PadByRadius(1);
    region.Crop(input->GetLargestPossibleRegion());

    input->SetRequestedRegion(region);
    }
}

template<class TInputImage>
typename PersistentStreamingLineSegmentDetector<TInputImage>::OutputVectorDataPointerType
PersistentStreamingLineSegmentDetector<TInputImage>
::ProcessTile(const InputImageType* inputImage)
{
  typename LSDType::Pointer lsd = LSDType::New();
  lsd->SetInput(inputImage);
  lsd->UpdateOutputInformation();
  lsd->Update();
  return lsd->GetOutput();
}


} // end namespace otb
#endif
