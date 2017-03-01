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

#ifndef otbSharkUtils_h
#define otbSharkUtils_h

#include "otb_shark.h"
#include "itkMacro.h"

#if defined(__GNUC__) || defined(__clang__)
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wshadow"
#endif
#include <shark/Data/Dataset.h>
#if defined(__GNUC__) || defined(__clang__)
#pragma GCC diagnostic pop
#endif

namespace otb
{
namespace Shark
{
template <class T> void ListSampleRangeToSharkVector(const T * listSample, std::vector<shark::RealVector> & output, unsigned int start, unsigned int size)
{
  assert(listSample != ITK_NULLPTR);

  if(start+size>listSample->Size())
    {
    itkGenericExceptionMacro(<<"Requested range ["<<start<<", "<<start+size<<"[ is out of bound for input list sample (range [0, "<<listSample->Size()<<"[");
    }
  
  output.clear();
      
  // Sample index
  unsigned int sampleIdx = start;
    
  //Check for valid listSample
  if(listSample->Size()>0)
    {
    // Retrieve samples size alike
    const unsigned int sampleSize = listSample->GetMeasurementVectorSize();

    // Fill the output vector

    for (auto const endOfRange = start+size ; sampleIdx < endOfRange ; ++sampleIdx)
      {
      // Retrieve sample
      typename T::MeasurementVectorType const & sample = listSample->GetMeasurementVector(sampleIdx);
	   
      // // Define a shark::RealVector
      // shark::RealVector rv(sampleSize);
      // // Loop on sample size
      // for(unsigned int i = 0; i < sampleSize; ++i)
      //   {
      //   rv[i] = sample[i];
      //   }
      // using std::move;
      // output.emplace_back(move(rv));

      output.emplace_back(&sample[0], &sample[0]+sampleSize);
      }
    }
}

template <class T> void ListSampleRangeToSharkVector(const T * listSample, std::vector<unsigned int> & output, unsigned int start, unsigned int size)
{
  assert(listSample != ITK_NULLPTR);

  if(start+size>listSample->Size())
    {
    itkGenericExceptionMacro(<<"Requested range ["<<start<<", "<<start+size<<"[ is out of bound for input list sample (range [0, "<<listSample->Size()<<"[");
    }

  output.clear();
  
  // Sample index
  unsigned int sampleIdx = start;
    
  //Check for valid listSample
  if(listSample->Size()>0)
    {
    // Fill the output vector
    while(sampleIdx<start+size)
      {
      // Retrieve sample
      typename T::MeasurementVectorType const & sample = listSample->GetMeasurementVector(sampleIdx);
	   
      // Define a shark::RealVector
      output.push_back(sample[0]);
      ++sampleIdx;
      }
    } 
}

template <class T> void ListSampleToSharkVector(const T * listSample, std::vector<shark::RealVector> & output)
{
  assert(listSample != ITK_NULLPTR);
  ListSampleRangeToSharkVector(listSample,output,0U,static_cast<unsigned int>(listSample->Size()));
}

template <class T> void ListSampleToSharkVector(const T * listSample, std::vector<unsigned int> & output)
{
  assert(listSample != ITK_NULLPTR);
  ListSampleRangeToSharkVector(listSample,output,0, static_cast<unsigned int>(listSample->Size()));
}
  
}
}

#endif

