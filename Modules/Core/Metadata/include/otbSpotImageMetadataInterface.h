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

#ifndef otbSpotImageMetadataInterface_h
#define otbSpotImageMetadataInterface_h

#include "otbOpticalImageMetadataInterface.h"

namespace otb
{
/** \class SpotImageMetadataInterface
 *
 * \brief Creation of an "otb" SpotImageMetadataInterface that gets metadata.
 *
 *
 * \ingroup OTBMetadata
 */
class OTBMetadata_EXPORT SpotImageMetadataInterface : public OpticalImageMetadataInterface
{
public:

  typedef SpotImageMetadataInterface    Self;
  typedef OpticalImageMetadataInterface    Superclass;
  typedef itk::SmartPointer<Self>       Pointer;
  typedef itk::SmartPointer<const Self> ConstPointer;

  /** Method for creation through the object factory. */
  itkNewMacro(Self);

  /** Run-time type information (and related methods). */
  itkTypeMacro(SpotImageMetadataInterface, OpticalImageMetadataInterface);

  typedef Superclass::ImageType                ImageType;
  typedef Superclass::MetaDataDictionaryType   MetaDataDictionaryType;
  typedef Superclass::VectorType               VectorType;
  typedef Superclass::VariableLengthVectorType VariableLengthVectorType;
  typedef Superclass::ImageKeywordlistType     ImageKeywordlistType;

  /** Get the radiometric bias from the ossim metadata */
  VariableLengthVectorType GetPhysicalBias() const ITK_OVERRIDE;

  /** Get the radiometric gain from the ossim metadata */
  VariableLengthVectorType GetPhysicalGain() const ITK_OVERRIDE;

  /** Get the solar irradiance from the ossim metadata */
  VariableLengthVectorType GetSolarIrradiance() const ITK_OVERRIDE;

  /** Get the imaging acquisition day from the ossim metadata : IMAGING_DATE metadata variable */
  int GetDay() const ITK_OVERRIDE;

  /** Get the imaging acquisition month from the ossim metadata : IMAGING_DATE metadata variable */
  int GetMonth() const ITK_OVERRIDE;

  /** Get the imaging acquisition year from the ossim metadata : IMAGING_DATE metadata variable */
  int GetYear() const ITK_OVERRIDE;

  /** Get the imaging acquisition hour from the ossim metadata : IMAGING_DATE metadata variable */
  int GetHour() const ITK_OVERRIDE;

  /** Get the imaging acquisition year from the ossim metadata : IMAGING_DATE metadata variable */
  int GetMinute() const ITK_OVERRIDE;

  /** Get the imaging production day from the ossim metadata : DATASET_PRODUCTION_DATE metadata variable */
  int GetProductionDay() const ITK_OVERRIDE;

  /** Get the imaging production month from the ossim metadata : DATASET_PRODUCTION_DATE metadata variable */
  int GetProductionMonth() const ITK_OVERRIDE;

  /** Get the imaging production year from the ossim metadata : DATASET_PRODUCTION_DATE metadata variable */
  int GetProductionYear() const ITK_OVERRIDE;

  /** Get the sat elevation from the ossim metadata */
  double GetSatElevation() const ITK_OVERRIDE;

  /** Get the sat azimuth from the ossim metadata */
  double GetSatAzimuth() const ITK_OVERRIDE;

  /** Get the first wavelength for the spectral band definition */
  VariableLengthVectorType GetFirstWavelengths() const ITK_OVERRIDE;

  /** Get the last wavelength for the spectral band definition */
  VariableLengthVectorType GetLastWavelengths() const ITK_OVERRIDE;

  /** Get the enhanced band names (here nothing because the metadata did not provide band names) */
  std::vector<std::string> GetEnhancedBandNames() const ITK_OVERRIDE
  {
    return this->Superclass::GetBandName();
  }

  /** Get Instrument */
  std::string GetInstrument() const;

  /** Get Instrument Index */
  unsigned int GetInstrumentIndex() const;

  /** This method is to handle the permutation of the spectral band by some image provider
   * in most cases, this method won't change the value, but for SPOT data, the bands are set up as
   *  2 1 0 3 in the tiff file, this method which is overloaded for SPOT enables to retrieve the
   *  proper band. */
  unsigned int BandIndexToWavelengthPosition(unsigned int i) const ITK_OVERRIDE;

  /** Get the 3 spectral band numbers corresponding to the default display for visualization,
   *  in the order R, G, B */
  std::vector<unsigned int> GetDefaultDisplay() const ITK_OVERRIDE;

  bool CanRead() const ITK_OVERRIDE;

  /** Vector that contains the filter function value in 6S format (step of 0.0025 micro m).
     * There values a computed by 6S. */
  WavelengthSpectralBandVectorType GetSpectralSensitivity()  const ITK_OVERRIDE;

protected:
  SpotImageMetadataInterface();
  ~SpotImageMetadataInterface() ITK_OVERRIDE {}

private:

  SpotImageMetadataInterface(const Self &); //purposely not implemented
  void operator =(const Self&); //purposely not implemented

};

} // end namespace otb

#endif
