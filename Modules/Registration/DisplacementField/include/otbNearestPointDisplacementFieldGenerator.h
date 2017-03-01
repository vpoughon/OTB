/*=========================================================================

  Program:   ORFEO Toolbox
  Language:  C++


  Copyright (c) Centre National d'Etudes Spatiales. All rights reserved.
  See OTBCopyright.txt for details.


     This software is distributed WITHOUT ANY WARRANTY; without even
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
     PURPOSE.  See the above copyright notices for more information.

=========================================================================*/
#ifndef otbNearestPointDisplacementFieldGenerator_h
#define otbNearestPointDisplacementFieldGenerator_h

#include "otbPointSetToDisplacementFieldGenerator.h"

namespace otb
{
/** \class NearestPointDisplacementFieldGenerator
 *  \brief This class implements the simplest way to displacement field generation using a point set.
 *  In each pixel location, the displacement is considered to be the displacement of the nearest seed point in the point set.
 *
 * \ingroup DisparityMap
 *
 * \ingroup OTBDisplacementField
 */
template <class TPointSet, class TDisplacementField>
class ITK_EXPORT NearestPointDisplacementFieldGenerator
  : public PointSetToDisplacementFieldGenerator<TPointSet, TDisplacementField>
{
public:
  /** Standard typedefs */
  typedef NearestPointDisplacementFieldGenerator                             Self;
  typedef PointSetToDisplacementFieldGenerator<TPointSet, TDisplacementField> Superclass;
  typedef itk::SmartPointer<Self>                                           Pointer;
  typedef itk::SmartPointer<const Self>                                     ConstPointer;

  /** Type macro */
  itkNewMacro(Self);

  /** Creation through object factory macro */
  itkTypeMacro(NearestPointDisplacementFieldGenerator, PointSetToDisplacementFieldGenerator);

  /** Template parameters typedefs */
  typedef typename Superclass::PointSetType                PointSetType;
  typedef typename Superclass::PointSetPointerType         PointSetPointerType;
  typedef typename Superclass::DisplacementFieldType        DisplacementFieldType;
  typedef typename Superclass::DisplacementFieldPointerType DisplacementFieldPointerType;
  typedef typename Superclass::IndexType                   IndexType;
  typedef typename DisplacementFieldType::PixelType         PixelType;
  typedef typename Superclass::ValueType                   ValueType;
  typedef typename Superclass::IndexVectorType             IndexVectorType;

protected:
  /** Constructor */
  NearestPointDisplacementFieldGenerator() {};
  /** Destructor */
  ~NearestPointDisplacementFieldGenerator() ITK_OVERRIDE {}
  /**PrintSelf method */
  void PrintSelf(std::ostream& os, itk::Indent indent) const ITK_OVERRIDE;
  /** Main computation method */
  void GenerateData() ITK_OVERRIDE;

private:
  NearestPointDisplacementFieldGenerator(const Self &); //purposely not implemented
  void operator =(const Self&); //purposely not implemented
};
} // End namespace otb
#ifndef OTB_MANUAL_INSTANTIATION
#include "otbNearestPointDisplacementFieldGenerator.txx"
#endif

#endif
