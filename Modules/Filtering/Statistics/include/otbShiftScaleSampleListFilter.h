/*=========================================================================

  Program:   ORFEO Toolbox
  Language:  C++


  Copyright (c) Centre National d'Etudes Spatiales. All rights reserved.
  See OTBCopyright.txt for details.


     This software is distributed WITHOUT ANY WARRANTY; without even
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
     PURPOSE.  See the above copyright notices for more information.

=========================================================================*/
#ifndef otbShiftScaleSampleListFilter_h
#define otbShiftScaleSampleListFilter_h

#include "otbListSampleToListSampleFilter.h"


namespace otb {
namespace Statistics {

/** \class ShiftScaleSampleListFilter
 *  \brief This class generate a shifted and scaled version of the input sample list
 *
 *  For each component of the sample, the following formula is applied :
 *
 *  \f[ output = \frac{input - shift}{scale} \f]
 *
 *  Beware that the behaviour differs from itk::ShiftScaleImageFilter
 *  (which add shift instead of subtracting it).
 *
 * Standard casting is applied between input and output type.
 *
 * Shifts and scales can be set via the SetShift() and SetScales() methods.
 *
 * \sa ListSampleToListSampleFilter
 *
 * \ingroup OTBStatistics
 */
template < class TInputSampleList, class TOutputSampleList = TInputSampleList >
class ITK_EXPORT ShiftScaleSampleListFilter :
  public otb::Statistics::ListSampleToListSampleFilter<TInputSampleList, TOutputSampleList>
{
public:
  /** Standard class typedefs */
  typedef ShiftScaleSampleListFilter                 Self;
  typedef otb::Statistics::ListSampleToListSampleFilter
  <TInputSampleList, TOutputSampleList>               Superclass;
  typedef itk::SmartPointer< Self >                  Pointer;
  typedef itk::SmartPointer<const Self>              ConstPointer;

  /** Run-time type information (and related methods). */
  itkTypeMacro(ShiftScaleSampleListFilter, otb::Statistics::ListSampleToListSampleFilter);

  /** Method for creation through the object factory. */
  itkNewMacro(Self);

  /** InputSampleList typedefs */
  typedef TInputSampleList                                    InputSampleListType;
  typedef typename InputSampleListType::Pointer               InputSampleListPointer;
  typedef typename InputSampleListType::ConstPointer          InputSampleListConstPointer;
  typedef typename InputSampleListType::MeasurementVectorType InputMeasurementVectorType;
  typedef typename InputMeasurementVectorType::ValueType      InputValueType;

  /** OutputSampleList typedefs */
  typedef TOutputSampleList                                    OutputSampleListType;
  typedef typename OutputSampleListType::Pointer               OutputSampleListPointer;
  typedef typename OutputSampleListType::ConstPointer          OutputSampleListConstPointer;
  typedef typename OutputSampleListType::MeasurementVectorType OutputMeasurementVectorType;
  typedef typename OutputMeasurementVectorType::ValueType      OutputValueType;

  /** Set/Get the Shifts for this sample list */
  itkSetMacro(Shifts, InputMeasurementVectorType);
  itkGetMacro(Shifts, InputMeasurementVectorType);

  /** Set/Get the Scales for this sample list */
  itkSetMacro(Scales, InputMeasurementVectorType);
  itkGetMacro(Scales, InputMeasurementVectorType);

protected:
  /** This method causes the filter to generate its output. */
   void GenerateData() ITK_OVERRIDE;

  ShiftScaleSampleListFilter();
  ~ShiftScaleSampleListFilter() ITK_OVERRIDE {}
  void PrintSelf(std::ostream& os, itk::Indent indent) const ITK_OVERRIDE;

private:
  ShiftScaleSampleListFilter(const Self&); //purposely not implemented
  void operator=(const Self&); //purposely not implemented

  /** The vector of Shifts */
  InputMeasurementVectorType m_Shifts;

  /** The vector of Scales */
  InputMeasurementVectorType m_Scales;

}; // end of class ShiftScaleSampleListFilter

} // end of namespace Statistics
} // end of namespace otb

#ifndef OTB_MANUAL_INSTANTIATION
#include "otbShiftScaleSampleListFilter.txx"
#endif

#endif
