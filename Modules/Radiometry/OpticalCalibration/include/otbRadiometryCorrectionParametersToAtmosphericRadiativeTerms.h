/*=========================================================================

  Program:   ORFEO Toolbox
  Language:  C++


  Copyright (c) Centre National d'Etudes Spatiales. All rights reserved.
  See OTBCopyright.txt for details.


     This software is distributed WITHOUT ANY WARRANTY; without even
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
     PURPOSE.  See the above copyright notices for more information.

=========================================================================*/
#ifndef otbRadiometryCorrectionParametersToAtmosphericRadiativeTerms_h
#define otbRadiometryCorrectionParametersToAtmosphericRadiativeTerms_h

#include "otbAtmosphericRadiativeTerms.h"
#include "otbImageMetadataCorrectionParameters.h"
#include "otbSIXSTraits.h"
#include "otbMacro.h"

namespace otb
{

/** \class RadiometryCorrectionParametersToAtmosphericRadiativeTerms
   * \brief TODO.
   *
   * TODO
   * \ingroup Radiometry
   *
 *
 * \ingroup OTBOpticalCalibration
 */
  class RadiometryCorrectionParametersToAtmosphericRadiativeTerms
  {
  public:

    /** Call the varSol function*/
    static AtmosphericRadiativeTerms::Pointer Compute(AtmosphericCorrectionParameters* paramAtmo, ImageMetadataCorrectionParameters* paramAcqui)
    {
      AtmosphericRadiativeTerms::Pointer radTermsOut = AtmosphericRadiativeTerms::New();

      typedef AtmosphericCorrectionParameters::WavelengthSpectralBandVectorType WavelengthSpectralBandVectorType;
      WavelengthSpectralBandVectorType WavelengthSpectralBandVector = paramAcqui->GetWavelengthSpectralBand();
      unsigned int NbBand = WavelengthSpectralBandVector->Size();

      radTermsOut->ValuesInitialization(NbBand);

      double atmosphericReflectance(0.);
      double atmosphericSphericalAlbedo(0.);
      double totalGaseousTransmission(0.);
      double downwardTransmittance(0.);
      double upwardTransmittance(0.);
      double upwardDiffuseTransmittance(0.);
      double upwardDirectTransmittance(0.);
      double upwardDiffuseTransmittanceForRayleigh(0.);
      double upwardDiffuseTransmittanceForAerosol(0.);
  
        for (unsigned int i = 0; i < NbBand; ++i)
        {
          atmosphericReflectance = 0.;
          atmosphericSphericalAlbedo = 0.;
          totalGaseousTransmission = 0.;
          downwardTransmittance = 0.;
          upwardTransmittance = 0.;
          upwardDiffuseTransmittance = 0.;
          upwardDirectTransmittance = 0.;
          upwardDiffuseTransmittanceForRayleigh = 0.;
          upwardDiffuseTransmittanceForAerosol = 0.;
          SIXSTraits::ComputeAtmosphericParameters(
            paramAcqui->GetSolarZenithalAngle(),                  /** The Solar zenithal angle */
            paramAcqui->GetSolarAzimutalAngle(),                  /** The Solar azimutal angle */
            paramAcqui->GetViewingZenithalAngle(),                /** The Viewing zenithal angle */
            paramAcqui->GetViewingAzimutalAngle(),                /** The Viewing azimutal angle */
            paramAcqui->GetMonth(),                               /** The Month */
            paramAcqui->GetDay(),                                 /** The Day (in the month) */
            paramAtmo->GetAtmosphericPressure(),                 /** The Atmospheric pressure */
            paramAtmo->GetWaterVaporAmount(),                    /** The Water vapor amount (Total water vapor content over vertical atmospheric column) */
            paramAtmo->GetOzoneAmount(),                         /** The Ozone amount (Stratospheric ozone layer content) */
            paramAtmo->GetAerosolModel(),                        /** The Aerosol model */
            paramAtmo->GetAerosolOptical(),                      /** The Aerosol optical (radiative impact of aerosol for the reference wavelength 550-nm) */
            paramAcqui->GetWavelengthSpectralBand()->GetNthElement(i), /** Wavelength for the spectral band definition */
            /** Note : The Max wavelength spectral band value must be updated ! */
            atmosphericReflectance,                          /** Atmospheric reflectance */
            atmosphericSphericalAlbedo,                      /** atmospheric spherical albedo */
            totalGaseousTransmission,                        /** Total gaseous transmission */
            downwardTransmittance,                           /** downward transmittance */
            upwardTransmittance,                             /** upward transmittance */
            upwardDiffuseTransmittance,                      /** Upward diffuse transmittance */
            upwardDirectTransmittance,                       /** Upward direct transmittance */
            upwardDiffuseTransmittanceForRayleigh,           /** Upward diffuse transmittance for rayleigh */
            upwardDiffuseTransmittanceForAerosol             /** Upward diffuse transmittance for aerosols */
            );

          radTermsOut->SetIntrinsicAtmosphericReflectance(i, atmosphericReflectance);
          radTermsOut->SetSphericalAlbedo(i, atmosphericSphericalAlbedo);
          radTermsOut->SetTotalGaseousTransmission(i, totalGaseousTransmission);
          radTermsOut->SetDownwardTransmittance(i, downwardTransmittance);
          radTermsOut->SetUpwardTransmittance(i, upwardTransmittance);
          radTermsOut->SetUpwardDiffuseTransmittance(i, upwardDiffuseTransmittance);
          radTermsOut->SetUpwardDirectTransmittance(i, upwardDirectTransmittance);
          radTermsOut->SetUpwardDiffuseTransmittanceForRayleigh(i, upwardDiffuseTransmittanceForRayleigh);
          radTermsOut->SetUpwardDiffuseTransmittanceForAerosol(i, upwardDiffuseTransmittanceForAerosol);
          radTermsOut->SetWavelengthSpectralBand(i, paramAcqui->GetWavelengthSpectralBand()->GetNthElement(i)->GetCenterSpectralValue());
        }

      return radTermsOut;
    }
  };
} //end namespace otb
#endif
