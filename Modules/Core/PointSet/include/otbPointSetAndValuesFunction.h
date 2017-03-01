/*=========================================================================

  Program:   ORFEO Toolbox
  Language:  C++


  Copyright (c) Centre National d'Etudes Spatiales. All rights reserved.
  See OTBCopyright.txt for details.


     This software is distributed WITHOUT ANY WARRANTY; without even
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
     PURPOSE.  See the above copyright notices for more information.

=========================================================================*/
#ifndef otbPointSetAndValuesFunction_h
#define otbPointSetAndValuesFunction_h

#include "itkFunctionBase.h"
#include "itkContinuousIndex.h"
#include "itkVectorContainer.h"
#include "itkPointSet.h"

namespace otb
{
/** \class PointSetAndValuesFunction
 *  \brief Base class for function needing a point set and a set of associated value to compute the output.
 *
 * \ingroup OTBPointSet
 */
template <class TPointSet, class TValue, class TCoordRep = double>
class ITK_EXPORT PointSetAndValuesFunction
  : public itk::FunctionBase<itk::Point<TCoordRep, TPointSet::PointDimension>, TValue>
{
public:
  /** Standard typedefs */
  typedef PointSetAndValuesFunction Self;
  typedef itk::FunctionBase<
             itk::Point<TCoordRep, TPointSet::PointDimension>,
             TValue
             > Superclass;
  typedef itk::SmartPointer<Self>
  Pointer;
  typedef itk::SmartPointer<const Self>
  ConstPointer;

  /** Creation through object factory macro */
  itkTypeMacro(PointSetAndValuesFunction, itk::FunctionBase);

  typedef TPointSet                           PointSetType;
  typedef typename PointSetType::ConstPointer PointSetConstPointerType;
  typedef TValue                              ValueType;
  typedef TCoordRep                           CoordRepType;
  typedef typename PointSetType::PointType    PointType;

  typedef itk::Index<PointType::PointDimension>                         IndexType;
  typedef itk::ContinuousIndex<CoordRepType, PointType::PointDimension> ContinuousIndexType;

  typedef itk::VectorContainer<unsigned long, ValueType> ValueVectorType;
  typedef typename ValueVectorType::ConstPointer         ValueVectorPointerType;

  itkSetObjectMacro(ValueVector, ValueVectorType);
  itkGetObjectMacro(ValueVector, ValueVectorType);

  /**
   * Set the point set.
   * \param the point set
   */
  virtual void SetPointSet(const PointSetType * ptr);
  /**
   * Get the point set.
   * \return the point set
   */
  const PointSetType * GetPointSet() const
  {
    return m_PointSet.GetPointer();
  }

  /** Evaluate the function at specified Point position.
   * Subclasses must provide this method. */
  virtual TValue Evaluate(const PointType& point) const = 0;

  /** Evaluate the function at specified Index position.
   * Subclasses must provide this method. */
  virtual TValue EvaluateAtIndex(const IndexType& index) const = 0;

  /** Evaluate the function at specified ContinuousIndex position.
   * Subclasses must provide this method. */
  virtual TValue EvaluateAtContinuousIndex(const ContinuousIndexType& index) const = 0;

protected:
  /** Constructor */
  PointSetAndValuesFunction()
    {
    m_PointSet = PointSetType::New();
    m_ValueVector = ValueVectorType::New();

    }
  /** Destructor */
  virtual ~PointSetAndValuesFunction() {}
  /**PrintSelf method */
  virtual void PrintSelf(std::ostream& os, itk::Indent indent) const;

private:
  PointSetAndValuesFunction(const Self &); //purposely not implemented
  void operator =(const Self&); //purposely not implemented

  /** PointSet */
  PointSetConstPointerType m_PointSet;
  /** value vector */
  ValueVectorPointerType m_ValueVector;
};
} // End namespace otb
#endif
