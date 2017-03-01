/*=========================================================================

  Program:   ORFEO Toolbox
  Language:  C++


  Copyright (c) Centre National d'Etudes Spatiales. All rights reserved.
  See OTBCopyright.txt for details.


     This software is distributed WITHOUT ANY WARRANTY; without even
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
     PURPOSE.  See the above copyright notices for more information.

=========================================================================*/
#ifndef otbLabelMapToSampleListFilter_h
#define otbLabelMapToSampleListFilter_h

#include <algorithm>

#include "itkProcessObject.h"
#include "otbAttributesMapLabelObject.h"

namespace otb
{
/** \class LabelMapToSampleListFilter
 *
 * \brief This class converts a LabelObjectMap to a SampleList for
 * learning and classification.
 *
 * The conversion from label object to measurement vector is made
 * through a functor. This allows supporting any kind of LabelObject
 * via proper redefinition of the functor.
 *
 * \ingroup OTBLabelMap
 */

template <class TInputLabelMap, class TOutputSampleList,
    class TMeasurementFunctor = Functor::AttributesMapMeasurementFunctor
    <typename TInputLabelMap::LabelObjectType, typename TOutputSampleList::MeasurementVectorType > >
class ITK_EXPORT LabelMapToSampleListFilter : public itk::ProcessObject
{
public:
  /** Standard class typedefs. */
  typedef LabelMapToSampleListFilter    Self;
  typedef itk::ProcessObject            Superclass;
  typedef itk::SmartPointer<Self>       Pointer;
  typedef itk::SmartPointer<const Self> ConstPointer;

  /** Method for creation through the object factory. */
  itkNewMacro(Self);

  /** Run-time type information (and related methods). */
  itkTypeMacro(LabelMapToSampleListFilter, ProcessObject);

  /** template typedefs */
  typedef TInputLabelMap                              InputLabelMapType;
  typedef typename InputLabelMapType::ConstPointer    InputLabelMapConstPointerType;
  typedef typename InputLabelMapType::LabelObjectType LabelObjectType;

  typedef typename InputLabelMapType::ConstIterator   ConstIteratorType;

  typedef TOutputSampleList                           OutputSampleListType;
  typedef typename OutputSampleListType::Pointer      OutputSampleListPointerType;
  typedef typename OutputSampleListType
  ::MeasurementVectorType                             MeasurementVectorType;

  typedef TMeasurementFunctor                         MeasurementFunctorType;

  /** DataObject typedef*/
  typedef typename Superclass::DataObjectPointer      DataObjectPointerType;
  typedef itk::ProcessObject::DataObjectPointerArraySizeType DataObjectPointerArraySizeType;

  /** Set/Get the input label map */
  void SetInputLabelMap(const InputLabelMapType * inputLabelMap);
  const InputLabelMapType* GetInputLabelMap() const;

  /** Get the output SampleList*/
  const OutputSampleListType* GetOutputSampleList();

  /** Get a hook on the functor for settings */
  void SetMeasurementFunctor(const MeasurementFunctorType& functor)
  {
    m_MeasurementFunctor = functor;
  }

  MeasurementFunctorType & GetMeasurementFunctor()
  {
    return m_MeasurementFunctor;
  }

protected:
  LabelMapToSampleListFilter();
  ~LabelMapToSampleListFilter() ITK_OVERRIDE;

  void GenerateData() ITK_OVERRIDE;

  /** Make Output */
  DataObjectPointerType MakeOutput(DataObjectPointerArraySizeType idx) ITK_OVERRIDE;
  using Superclass::MakeOutput;

  void PrintSelf(std::ostream& os, itk::Indent indent) const ITK_OVERRIDE;

private:
  LabelMapToSampleListFilter(const Self&); //purposely not implemented
  void operator=(const Self&); //purposely not implemented

  /** The functor used to build the measurement vector */
  MeasurementFunctorType        m_MeasurementFunctor;
};

} // end namespace otb

#ifndef OTB_MANUAL_INSTANTIATION
#include "otbLabelMapToSampleListFilter.txx"
#endif

#endif
