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

#include "otbMultiChannelExtractROI.h"

namespace otb
{
namespace Wrapper
{

class PixelValue : public Application
{
public:
  /** Standard class typedefs. */
  typedef PixelValue                     Self;
  typedef Application                   Superclass;
  typedef itk::SmartPointer<Self>       Pointer;
  typedef itk::SmartPointer<const Self> ConstPointer;

  typedef otb::MultiChannelExtractROI<FloatVectorImageType::InternalPixelType,
                                      FloatVectorImageType::InternalPixelType> ExtractROIFilterType;

  /** Standard macro */
  itkNewMacro(Self);

  itkTypeMacro(PixelValue, otb::Application);

private:
  void DoInit() ITK_OVERRIDE
  {
    SetName("PixelValue");
    SetDescription("Get the value of a pixel.");

    // Documentation
    SetDocName("Pixel Value");
    SetDocLongDescription("Get the value of a pixel.\nPay attention, index starts at 0.");
    SetDocLimitations("None");
    SetDocAuthors("OTB-Team");
    SetDocSeeAlso(" ");

	AddDocTag("Miscellaneous");
    AddDocTag("Utilities");
    AddDocTag("Coordinates");
    AddDocTag("Raster");

    AddParameter(ParameterType_InputImage,  "in",   "Input Image");
    SetParameterDescription("in", "Input image");

    AddParameter(ParameterType_Int,"coordx","Col index");
    SetParameterDescription("coordx","Column index of the wanted pixel (starts at 0).");
    SetMinimumParameterIntValue("coordx", 0);

    AddParameter(ParameterType_Int,"coordy","Line index");
    SetParameterDescription("coordy","Line index of the wanted pixel (starts at 0).");
    SetMinimumParameterIntValue("coordy", 0);

    AddParameter(ParameterType_ListView,"cl","Channels");
    SetParameterDescription("cl","Displayed channels");
    MandatoryOff("cl");

    AddParameter(ParameterType_String,"value","Pixel Value");
    SetParameterDescription("value", "Pixel radiometric value");
    SetParameterRole("value", Role_Output);

    // Doc example parameter settings
    SetDocExampleParameterValue("in", "QB_Toulouse_Ortho_XS.tif");
    SetDocExampleParameterValue("coordx", "50");
    SetDocExampleParameterValue("coordy", "100");
    SetDocExampleParameterValue("cl", "Channel1");
  }

  void DoUpdateParameters() ITK_OVERRIDE
  {
    if ( HasValue("in") )
      {
      ExtractROIFilterType::InputImageType* inImage = GetParameterImage("in");

      // Update the values of the channels to be selected
      unsigned int nbComponents = inImage->GetNumberOfComponentsPerPixel();
      ClearChoices("cl");
      for (unsigned int idx = 0; idx < nbComponents; ++idx)
        {
        std::ostringstream key, item;
        key<<"cl.channel"<<idx+1;
        item<<"Channel"<<idx+1;
        AddChoice(key.str(), item.str());
        }

      ExtractROIFilterType::InputImageType::RegionType  largestRegion = inImage->GetLargestPossibleRegion();
      SetMaximumParameterIntValue("coordx", largestRegion.GetSize(0)-1);
      SetMaximumParameterIntValue("coordy", largestRegion.GetSize(1)-1);
      }
  }

  void DoExecute() ITK_OVERRIDE
  {
    std::ostringstream ossOutput;
    FloatVectorImageType::Pointer inImage = GetParameterImage("in");

    ExtractROIFilterType::Pointer extractor = ExtractROIFilterType::New();
    extractor->SetInput(inImage);

    // Create the region
    FloatVectorImageType::IndexType id;
    id[0] = GetParameterInt("coordx");
    id[1] = GetParameterInt("coordy");

    FloatVectorImageType::SizeType size;
    size.Fill(0);

    FloatVectorImageType::RegionType region;
    region.SetSize(size);
    region.SetIndex(id);

    extractor->SetExtractionRegion(region);

    // Extract the channels if needed
    if ( GetParameterByKey("cl")->GetActive() )
      {
      for (unsigned int idx = 0; idx < GetSelectedItems("cl").size(); ++idx)
        {
        extractor->SetChannel(GetSelectedItems("cl")[idx] + 1 );
        }
      }

    extractor->Update();

    // Display the pixel value
    id.Fill(0);
    std::ostringstream oss;
    oss << extractor->GetOutput()->GetPixel(id)<<std::endl;

    SetParameterString("value", oss.str(), false);

    //Display image information in the dedicated logger
    otbAppLogINFO( << oss.str() );
  }

};

}
}

OTB_APPLICATION_EXPORT(otb::Wrapper::PixelValue)
