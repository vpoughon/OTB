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

#include "otbWrapperApplication.h"
#include "otbWrapperApplicationFactory.h"

#include "otbMultiToMonoChannelExtractROI.h"
#include "otbStreamingCompareImageFilter.h"

namespace otb
{
namespace Wrapper
{


class CompareImages : public Application
{
public:
  /** Standard class typedefs. */
  typedef CompareImages             Self;
  typedef Application                   Superclass;
  typedef itk::SmartPointer<Self>       Pointer;
  typedef itk::SmartPointer<const Self> ConstPointer;

  /** Standard macro */
  itkNewMacro(Self);

  itkTypeMacro(CompareImages, otb::Application);

  /** Filters typedef */
  typedef otb::MultiToMonoChannelExtractROI<FloatVectorImageType::InternalPixelType, FloatVectorImageType::InternalPixelType> ExtractROIMonoFilterType;
  typedef otb::StreamingCompareImageFilter<FloatImageType> StreamingCompareImageFilterType;

private:
  void DoInit() ITK_OVERRIDE
  {
    SetName("CompareImages");
    SetDescription("Estimator between 2 images.");

    // Documentation
    SetDocName("Images comparison");
    SetDocLongDescription("This application computes MSE (Mean Squared Error), MAE (Mean Absolute Error) and PSNR (Peak Signal to Noise Ratio) between the channel of two images (reference and measurement). The user has to set the used channel and can specify a ROI.");
    SetDocLimitations("None");
    SetDocAuthors("OTB-Team");
    SetDocSeeAlso("BandMath application, ImageStatistics");

	AddDocTag("Miscellaneous");
    AddDocTag("Statistics");
	AddDocTag(Tags::Manip);

    AddParameter(ParameterType_Group, "ref", "Reference image properties");
    AddParameter(ParameterType_InputImage,  "ref.in",   "Reference image");
    SetParameterDescription("ref.in", "Image used as reference in the comparison");
    AddParameter(ParameterType_Int,  "ref.channel",   "Reference image channel");
    SetParameterDescription("ref.channel", "Used channel for the reference image");
    SetDefaultParameterInt("ref.channel", 1);
    SetMinimumParameterIntValue("ref.channel", 1);

    AddParameter(ParameterType_Group, "meas", "Measured image properties");
    AddParameter(ParameterType_InputImage,  "meas.in",   "Measured image");
    SetParameterDescription("meas.in", "Image used as measured in the comparison");
    AddParameter(ParameterType_Int,  "meas.channel",   "Measured image channel");
    SetParameterDescription("meas.channel", "Used channel for the measured image");
    SetDefaultParameterInt("meas.channel", 1);
    SetMinimumParameterIntValue("meas.channel", 1);

    AddParameter(ParameterType_Group, "roi", "Region Of Interest (relative to reference image)");

    AddParameter(ParameterType_Int,  "roi.startx", "Start X");
    SetDefaultParameterInt("roi.startx", 0);
    SetMinimumParameterIntValue("roi.startx", 0);
    SetParameterDescription("roi.startx", "ROI start x position.");

    AddParameter(ParameterType_Int,  "roi.starty", "Start Y");
    SetDefaultParameterInt("roi.starty", 0);
    SetMinimumParameterIntValue("roi.starty", 0);
    SetParameterDescription("roi.starty", "ROI start y position.");

    AddParameter(ParameterType_Int,  "roi.sizex",  "Size X");
    SetDefaultParameterInt("roi.sizex",  0);
    SetMinimumParameterIntValue("roi.sizex",  1);
    SetParameterDescription("roi.sizex","Size along x in pixels.");

    AddParameter(ParameterType_Int,  "roi.sizey",  "Size Y");
    SetDefaultParameterInt("roi.sizey", 0);
    SetMinimumParameterIntValue("roi.sizey",  1);
    SetParameterDescription("roi.sizey","Size along y in pixels.");

    AddParameter(ParameterType_Float, "mse",  "MSE");
    SetParameterDescription("mse", "Mean Squared Error value");
    SetParameterRole("mse", Role_Output );

    AddParameter(ParameterType_Float, "mae",  "MAE");
    SetParameterDescription("mae", "Mean Absolute Error value");
    SetParameterRole("mae", Role_Output );

    AddParameter(ParameterType_Float, "psnr",  "PSNR");
    SetParameterDescription("psnr", "Peak Signal to Noise Ratio value");
    SetParameterRole("psnr", Role_Output);
    
    AddParameter(ParameterType_Float, "count",  "count");
    SetParameterDescription("count", "Nb of pixels which are different");
    SetParameterRole("count", Role_Output);

    AddRAMParameter();

    // Doc example parameter settings
    SetDocExampleParameterValue("ref.in", "GomaApres.png");
    SetDocExampleParameterValue("ref.channel", "1");
    SetDocExampleParameterValue("meas.in", "GomaAvant.png");
    SetDocExampleParameterValue("meas.channel", "2");
    SetDocExampleParameterValue("roi.startx", "20");
    SetDocExampleParameterValue("roi.starty", "30");
    SetDocExampleParameterValue("roi.sizex", "150");
    SetDocExampleParameterValue("roi.sizey", "200");
  }

  void DoUpdateParameters() ITK_OVERRIDE
  {
    // Set channel interval
    if( HasValue("ref.in") )
      {
      SetMaximumParameterIntValue("ref.channel", this->GetParameterImage("ref.in")->GetNumberOfComponentsPerPixel());
      }
    if( HasValue("meas.in") )
      {
      SetMaximumParameterIntValue("meas.channel", this->GetParameterImage("meas.in")->GetNumberOfComponentsPerPixel());
      }

    // ROI

    if ( HasValue("ref.in") )
      {
      FloatVectorImageType::RegionType largestRegion = this->GetParameterImage("ref.in")->GetLargestPossibleRegion();

      // Put the limit of the index and the size relative the image
      SetMinimumParameterIntValue("roi.sizex", 1);
      SetMaximumParameterIntValue("roi.sizex", largestRegion.GetSize(0));

      SetMinimumParameterIntValue("roi.sizey", 1);
      SetMaximumParameterIntValue("roi.sizey", largestRegion.GetSize(1));

      SetMinimumParameterIntValue("roi.startx", 0);
      SetMaximumParameterIntValue("roi.startx", largestRegion.GetSize(0) - 1);

      SetMinimumParameterIntValue("roi.starty", 0);
      SetMaximumParameterIntValue("roi.starty", largestRegion.GetSize(1) - 1);

      }
  }


  void DoExecute() ITK_OVERRIDE
  {
    // Init filters
    m_ExtractRefFilter = ExtractROIMonoFilterType::New();
    m_ExtractMeasFilter = ExtractROIMonoFilterType::New();
    m_CompareFilter = StreamingCompareImageFilterType::New();

    // Get input image pointers
    FloatVectorImageType::Pointer refIm = this->GetParameterImage("ref.in");
    FloatVectorImageType::Pointer measIm = this->GetParameterImage("meas.in");

    // Get the region of interest
    FloatVectorImageType::RegionType region;
    region.SetIndex(0, GetParameterInt("roi.startx"));
    region.SetIndex(1, GetParameterInt("roi.starty"));
    region.SetSize(0, GetParameterInt("roi.sizex"));
    region.SetSize(1, GetParameterInt("roi.sizey"));

    if (region.GetNumberOfPixels() == 0)
      {
      otbAppLogINFO( << "Using whole reference image since the ROI contains no pixels or is not specified" );
      region = GetParameterImage("ref.in")->GetLargestPossibleRegion();
      }

    otbAppLogDEBUG( << "Region of interest used for comparison : " << region );

    if( !region.Crop(refIm->GetLargestPossibleRegion()) || !region.Crop(measIm->GetLargestPossibleRegion()) )
      {
      otbAppLogFATAL( << "ROI is not contained in the images regions");
      }

    m_ExtractRefFilter->SetInput( refIm );
    m_ExtractMeasFilter->SetInput( measIm );

    m_ExtractRefFilter->SetExtractionRegion(region);
    m_ExtractMeasFilter->SetExtractionRegion(region);

    // Set channels to extract
    otbAppLogINFO( << "reference image channel "<<this->GetParameterInt("ref.channel")<<" is compared with measured image channel "<<this->GetParameterInt("meas.channel"));
    m_ExtractRefFilter->SetChannel( this->GetParameterInt("ref.channel") );
    m_ExtractMeasFilter->SetChannel( this->GetParameterInt("meas.channel") );

    // Compute comparison
    m_CompareFilter->SetInput1(m_ExtractRefFilter->GetOutput());
    m_CompareFilter->SetInput2(m_ExtractMeasFilter->GetOutput());
    m_CompareFilter->SetPhysicalSpaceCheck(false);
    m_CompareFilter->GetStreamer()->SetAutomaticAdaptativeStreaming(GetParameterInt("ram"));
    AddProcess(m_CompareFilter->GetStreamer(), "Comparing...");
    m_CompareFilter->Update();

    // Show result
    otbAppLogINFO( << "MSE: " << m_CompareFilter->GetMSE() );
    otbAppLogINFO( << "MAE: " << m_CompareFilter->GetMAE() );
    otbAppLogINFO( << "PSNR: " << m_CompareFilter->GetPSNR() );
    otbAppLogINFO( << "Number of Pixel different: " << m_CompareFilter->GetDiffCount() );

    SetParameterFloat( "mse",m_CompareFilter->GetMSE() , false);
    SetParameterFloat( "mae",m_CompareFilter->GetMAE() , false);
    SetParameterFloat( "psnr",m_CompareFilter->GetPSNR() , false);
    SetParameterFloat( "count",m_CompareFilter->GetDiffCount() , false);
  }


  ExtractROIMonoFilterType::Pointer m_ExtractRefFilter;
  ExtractROIMonoFilterType::Pointer m_ExtractMeasFilter;
  StreamingCompareImageFilterType::Pointer m_CompareFilter;
};

}
}

OTB_APPLICATION_EXPORT(otb::Wrapper::CompareImages)
