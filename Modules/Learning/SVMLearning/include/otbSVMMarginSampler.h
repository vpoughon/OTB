/*=========================================================================

  Program:   ORFEO Toolbox
  Language:  C++


  Copyright (c) Centre National d'Etudes Spatiales. All rights reserved.
  See OTBCopyright.txt for details.


     This software is distributed WITHOUT ANY WARRANTY; without even
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
     PURPOSE.  See the above copyright notices for more information.

=========================================================================*/
#ifndef otbSVMMarginSampler_h
#define otbSVMMarginSampler_h

#include "itkSampleClassifierFilter.h"
#include "itkVectorImage.h"

namespace otb
{

/** \class SVMMarginSampler
 *  \brief Implement one iteration of active learning by margin
 *  \ingroup ActiveLearningFilters
 *
 * \ingroup OTBSVMLearning
 */

template< class TSample, class TModel >
class ITK_EXPORT SVMMarginSampler :
      public itk::Statistics::SampleClassifierFilter< TSample >
{
public:
  /** Standard class typedef*/
  typedef SVMMarginSampler Self;
  typedef itk::Statistics::SampleClassifierFilter< TSample > Superclass;
  typedef itk::SmartPointer< Self > Pointer;
  typedef itk::SmartPointer<const Self> ConstPointer;

  /** Standard macros */
  itkTypeMacro(SVMMarginSampler, itk::Statistics::SampleClassifierFilter);
  itkNewMacro(Self);

  /** Output type for GetClassSample method */
  typedef typename Superclass::MembershipSampleType   OutputType;

  /** typedefs from TSample object */
  typedef typename TSample::MeasurementType MeasurementType;
  typedef typename TSample::MeasurementVectorType MeasurementVectorType;
  typedef std::pair<unsigned int, double> IndexAndDistanceType;
  typedef std::vector<IndexAndDistanceType> IndexAndDistanceVectorType;
  typedef std::vector<unsigned int>         IndexVectorType;


  static bool Compare(const IndexAndDistanceType&  l1, const IndexAndDistanceType & l2)
    {
      bool resp = l2.second > l1.second;
      return resp;
    }

  /** Type definitions for the SVM Model. */
  typedef TModel                                     SVMModelType;
  typedef typename SVMModelType::Pointer             SVMModelPointer;
  typedef typename SVMModelType::DistancesVectorType DistancesVectorType;

  itkSetMacro(NumberOfCandidates, unsigned int);
  itkGetMacro(NumberOfCandidates, unsigned int);

  /** Set the model */
  itkSetObjectMacro(Model, SVMModelType);

  /** Get the number of classes. */
  itkGetObjectMacro(Model, SVMModelType);

  const IndexVectorType & GetMarginSamples()
  {
    return m_MarginSamples;
  }

protected:
  SVMMarginSampler();
  ~SVMMarginSampler() ITK_OVERRIDE {}
  void PrintSelf(std::ostream& os, itk::Indent indent) const ITK_OVERRIDE;

  /** Starts the classification process */
  void GenerateData() ITK_OVERRIDE;
  virtual void DoMarginSampling();

private:
  /** Output pointer (MembershipSample) */
  //typename OutputType::Pointer m_Output;

  SVMModelPointer m_Model;

  unsigned int m_NumberOfCandidates;

  IndexVectorType m_MarginSamples;

}; // end of class


} // end of namespace otb


#ifndef OTB_MANUAL_INSTANTIATION
#include "otbSVMMarginSampler.txx"
#endif

#endif


