/*=========================================================================

   Program:   ORFEO Toolbox
   Language:  C++


   Copyright (c) Centre National d'Etudes Spatiales. All rights reserved.
   See OTBCopyright.txt for details.


     This software is distributed WITHOUT ANY WARRANTY; without even
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
     PURPOSE.  See the above copyright notices for more information.

   =========================================================================*/
#ifndef otbNumberOfDivisionsStrippedStreamingManager_txx
#define otbNumberOfDivisionsStrippedStreamingManager_txx

#include "otbNumberOfDivisionsStrippedStreamingManager.h"
#include "otbMacro.h"

namespace otb
{

template <class TImage>
NumberOfDivisionsStrippedStreamingManager<TImage>::NumberOfDivisionsStrippedStreamingManager()
  : m_NumberOfDivisions(0)
{
}

template <class TImage>
NumberOfDivisionsStrippedStreamingManager<TImage>::~NumberOfDivisionsStrippedStreamingManager()
{
}

template <class TImage>
void
NumberOfDivisionsStrippedStreamingManager<TImage>::PrepareStreaming( itk::DataObject * /*input*/, const RegionType &region )
{
  otbMsgDevMacro(<< "Activating NumberOfDivisionsStrippedStreamingManager streaming mode")
  if (m_NumberOfDivisions < 1)
    {
    itkWarningMacro(<< "NumberOfDivisions set to 0 : streaming disabled")
    m_NumberOfDivisions = 1;
    }

  this->m_Splitter = itk::ImageRegionSplitterSlowDimension::New();
  this->m_ComputedNumberOfSplits = this->m_Splitter->GetNumberOfSplits(region, m_NumberOfDivisions);
  otbMsgDevMacro(<< "Computed number of split : " << this->m_ComputedNumberOfSplits)
  // Save the region to generate the splits later
  this->m_Region = region;
}

} // End namespace otb

#endif

