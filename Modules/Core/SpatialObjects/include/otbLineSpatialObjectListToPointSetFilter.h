/*=========================================================================

  Program:   ORFEO Toolbox
  Language:  C++


  Copyright (c) Centre National d'Etudes Spatiales. All rights reserved.
  See OTBCopyright.txt for details.


     This software is distributed WITHOUT ANY WARRANTY; without even
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
     PURPOSE.  See the above copyright notices for more information.

=========================================================================*/
#ifndef otbLineSpatialObjectListToPointSetFilter_h
#define otbLineSpatialObjectListToPointSetFilter_h


#include "itkProcessObject.h"
#include "otbLineSpatialObjectList.h"

namespace otb
{
/** \class LineSpatialObjectListToPointSetFilter
 *  \brief Base class for all process objects that output PointSets And use LineSpatialObjectList
 *         as input.
 *
 *
 *
 * \ingroup OTBSpatialObjects
 */

template <class TLinesList, class TPointSet>
class ITK_EXPORT LineSpatialObjectListToPointSetFilter : public itk::ProcessObject
{
public:

  /** Standard class typedefs. */
  typedef LineSpatialObjectListToPointSetFilter Self;
  typedef itk::ProcessObject                    Superclass;
  typedef itk::SmartPointer<Self>               Pointer;
  typedef itk::SmartPointer<const Self>         ConstPointer;

  /** Method for creation through the object factory. */
  itkNewMacro(Self);

  /** Run-time type information (and related methods). */
  itkTypeMacro(LineSpatialObjectListToPointSetFilter, itk::ProcessObject);

  /** Some convenient typedefs. */
  typedef TLinesList                       LinesListType;
  typedef typename LinesListType::LineType LineType;

  /** typedef support for output*/
  typedef TPointSet PointSetType;

  typedef itk::ProcessObject ProcessObjectType;

  /** Set/Get the input image */
  using Superclass::SetInput;
  virtual void SetInput(const LinesListType *list);
  virtual const LinesListType* GetInput(void);

  /** Set/Get the list of LineSpatialObject of this process object.  */
  using Superclass::SetOutput;
  virtual void SetOutput(const PointSetType *pointSet);
  virtual PointSetType* GetOutput(void);

protected:
  LineSpatialObjectListToPointSetFilter();
  ~LineSpatialObjectListToPointSetFilter() ITK_OVERRIDE {}
  void PrintSelf(std::ostream& os, itk::Indent indent) const ITK_OVERRIDE;

private:
  LineSpatialObjectListToPointSetFilter(const Self &); //purposely not implemented
  void operator =(const Self&); //purposely not implemented

};

} // end namespace otb

#ifndef OTB_MANUAL_INSTANTIATION
#include "otbLineSpatialObjectListToPointSetFilter.txx"
#endif

#endif
