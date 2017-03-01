/*=========================================================================

  Program:   ORFEO Toolbox
  Language:  C++


  Copyright (c) Centre National d'Etudes Spatiales. All rights reserved.
  See OTBCopyright.txt for details.


     This software is distributed WITHOUT ANY WARRANTY; without even
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
     PURPOSE.  See the above copyright notices for more information.

=========================================================================*/
#ifndef otbWavelengthSpectralBands_h
#define otbWavelengthSpectralBands_h

#include "otbObjectList.h"
#include "otbFilterFunctionValues.h"
#include "OTBOpticalCalibrationExport.h"

namespace otb
{
/** \class WavelengthSpectralBands
 *  \brief This class contains the values of the filter functions
 *
 * \ingroup IO
 *
 * \ingroup OTBOpticalCalibration
 */
class OTBOpticalCalibration_EXPORT WavelengthSpectralBands : public itk::DataObject
{
public:
  /** Standard typedefs */
  typedef WavelengthSpectralBands       Self;
  typedef itk::DataObject               Superclass;
  typedef itk::SmartPointer<Self>       Pointer;
  typedef itk::SmartPointer<const Self> ConstPointer;

  /** Type macro */
  itkTypeMacro(WavelengthSpectralBands, DataObject);

  /** Creation through object factory macro */
  itkNewMacro(Self);

  typedef FilterFunctionValues                              FilterFunctionValuesType;
  typedef ObjectList <FilterFunctionValuesType>             InternalWavelengthSpectralBandListType;
  typedef InternalWavelengthSpectralBandListType::Pointer   WavelengthSpectralBandListType;
  //typedef std::map <FilterFunctionValuesType>        FilterFunctionValuesMapType;

  /** Set the number of bands. */
  itkSetMacro(NbBands, unsigned int);
  /** Get the number of bands. */
  itkGetMacro(NbBands, unsigned int);

protected:
  /** Constructor */
  WavelengthSpectralBands();
  /** Destructor */
  ~WavelengthSpectralBands() ITK_OVERRIDE {}

  /** PrintSelf method */
  void PrintSelf(std::ostream& os, itk::Indent indent) const ITK_OVERRIDE;

private:
  WavelengthSpectralBands(const Self &); //purposely not implemented
  void operator =(const Self&); //purposely not implemented

  /** List that contains the filter function value. */
  WavelengthSpectralBandListType m_WavelengthSpectralBandsList;
  unsigned int                   m_NbBands;
};

} //end namespace

#endif
