/*=========================================================================

  Program:   ORFEO Toolbox
  Language:  C++


  Copyright (c) Centre National d'Etudes Spatiales. All rights reserved.
  See OTBCopyright.txt for details.


     This software is distributed WITHOUT ANY WARRANTY; without even
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
     PURPOSE.  See the above copyright notices for more information.

=========================================================================*/
#ifndef otbPeriodicSampler_h
#define otbPeriodicSampler_h

#include "otbSamplerBase.h"

namespace otb
{

/**
 * \class PeriodicSampler
 *
 * \brief Periodic sampler for iteration loops
 * 
 * This class allows doing periodic sampling during an iteration loop.
 *
 * \ingroup OTBStatistics
 */
class ITK_EXPORT PeriodicSampler : public SamplerBase
{
public:
  typedef PeriodicSampler  Self;
  typedef SamplerBase      Superclass;
  typedef itk::SmartPointer<Self>       Pointer;
  typedef itk::SmartPointer<const Self> ConstPointer;

  /** Internal parameters, only contains an offset to shift the periodic 
   * sampling
   */
  typedef struct Parameter
    {
    /** Offset that shifts the whole periodic sampling
     *  (disabled if jitter is used) */
    unsigned long Offset;

    /** Maximum jitter to introduce (0 means no jitter) */
    unsigned long MaxJitter;

    /** Maximum buffer size for internal jitter values */
    unsigned long MaxBufferSize;
    
    bool operator!=(const struct Parameter  & param) const;
    } ParameterType; 

  /** Method for creation through the object factory. */
  itkNewMacro(Self);

  /** Runtime information support. */
  itkTypeMacro(PeriodicSampler,SamplerBase);
  
  /** Setter for internal parameters */
  void SetParameters(const ParameterType &param)
    {
    if (m_Parameters != param)
      {
      this->Modified();
      m_Parameters = param;
      }
    }

  /** Getter for internal parameters */
  ParameterType GetParameters()
    {
    return m_Parameters;
    }

  /**
   * Method that resets the internal state of the sampler
   */
  void Reset(void) ITK_OVERRIDE;
  
  /**
   * Method to call during iteration, returns true if the sample is selected,
   * and false otherwise.
   */
  bool TakeSample(void);

protected:
  /** Constructor */
  PeriodicSampler();
   
  /** Destructor */
  ~PeriodicSampler() ITK_OVERRIDE {}

private:
  // Not implemented
  PeriodicSampler(const Self&);
  void operator=(const Self&);
  
  /** Internal parameters for the sampler */
  ParameterType m_Parameters;

  /** Internal width for jitter */
  double m_JitterSize;

  /** Internal current offset value
   *  (either fixed, or reset each time a sample is taken)*/
  double m_OffsetValue;

  /** jitter offsets computed up to MaxBufferSize */
  std::vector<double> m_JitterValues;
};

} // namespace otb
#endif
