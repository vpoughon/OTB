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

#include "otbMeanShiftSmoothingImageFilter.h"

namespace otb
{
namespace Wrapper
{


class MeanShiftSmoothing : public Application
{
public:
  /** Standard class typedefs. */
  typedef MeanShiftSmoothing         Self;
  typedef Application                   Superclass;
  typedef itk::SmartPointer<Self>       Pointer;
  typedef itk::SmartPointer<const Self> ConstPointer;

  typedef otb::MeanShiftSmoothingImageFilter<FloatVectorImageType, FloatVectorImageType> MSFilterType;

  /** Standard macro */
  itkNewMacro(Self);

  itkTypeMacro(MeanShiftSmoothing, otb::Application);

private:
  void DoInit() ITK_OVERRIDE
  {
    SetName("MeanShiftSmoothing");
    SetDescription("Perform mean shift filtering");

    // Documentation
    SetDocName("Exact Large-Scale Mean-Shift segmentation, step 1 (smoothing)");
    SetDocLongDescription("This application performs mean shift fitlering (multi-threaded).");
    SetDocLimitations("With mode search option, the result will slightly depend on thread number.");
    SetDocAuthors("OTB-Team");
    SetDocSeeAlso(" ");

    AddDocTag(Tags::Filter);
    AddDocTag("LSMS");

    AddParameter(ParameterType_InputImage,   "in",     "Input Image");
    SetParameterDescription( "in", "The input image." );

    AddParameter(ParameterType_OutputImage,  "fout",    "Filtered output");
    SetParameterDescription( "fout", "The filtered output image." );

    AddParameter(ParameterType_OutputImage,  "foutpos",    "Spatial image");
    SetParameterDescription( "foutpos", " The spatial image output. Spatial image output is a displacement map (pixel position after convergence).");
    MandatoryOff("foutpos");

    AddRAMParameter();

    AddParameter(ParameterType_Int, "spatialr", "Spatial radius");
    SetParameterDescription("spatialr", "Spatial radius of the neighborhood.");
    SetDefaultParameterInt("spatialr", 5);
    MandatoryOff("spatialr");

    AddParameter(ParameterType_Float, "ranger", "Range radius");
    SetParameterDescription("ranger", "Range radius defining the radius (expressed in radiometry unit) in the multi-spectral space.");
    SetDefaultParameterFloat("ranger", 15.0);
    MandatoryOff("ranger");

    AddParameter(ParameterType_Float, "thres", "Mode convergence threshold");
    SetParameterDescription("thres", "Algorithm iterative scheme will stop if mean-shift "
                               "vector is below this threshold or if iteration number reached maximum number of iterations.");
    SetMinimumParameterFloatValue("thres", 0.0);
    SetDefaultParameterFloat("thres", 0.1);
    MandatoryOff("thres");

    AddParameter(ParameterType_Int, "maxiter", "Maximum number of iterations");
    SetParameterDescription("maxiter", "Algorithm iterative scheme will stop if convergence hasn't been reached after the maximum number of iterations.");
    SetDefaultParameterInt("maxiter", 100);
    SetMinimumParameterIntValue("maxiter", 1);
    MandatoryOff("maxiter");

    AddParameter(ParameterType_Float, "rangeramp", "Range radius coefficient");
    SetParameterDescription("rangeramp", "This coefficient makes dependent the ranger of the colorimetry of the filtered pixel : y = rangeramp*x+ranger.");
    SetDefaultParameterFloat("rangeramp", 0.);
    SetMinimumParameterFloatValue("rangeramp", 0);
    MandatoryOff("rangeramp");

    AddParameter(ParameterType_Empty, "modesearch", "Mode search.");
    SetParameterDescription("modesearch", "If activated pixel iterative convergence is stopped if the path crosses an already converged pixel. Be careful, with this option, the result will slightly depend on thread number");
    DisableParameter("modesearch");


    // Doc example parameter settings
    SetDocExampleParameterValue("in", "maur_rgb.png");
    SetDocExampleParameterValue("fout", "MeanShift_FilterOutput.tif");
    SetDocExampleParameterValue("foutpos", "MeanShift_SpatialOutput.tif");
    SetDocExampleParameterValue("spatialr", "16");
    SetDocExampleParameterValue("ranger", "16");
    SetDocExampleParameterValue("thres", "0.1");
    SetDocExampleParameterValue("maxiter", "100");

  }

  void DoUpdateParameters() ITK_OVERRIDE
  {}

  void DoExecute() ITK_OVERRIDE
  {
    FloatVectorImageType* input = GetParameterImage("in");

    m_Filter = MSFilterType::New();

    m_Filter->SetInput(input);

    m_Filter->SetSpatialBandwidth(GetParameterInt("spatialr"));
    m_Filter->SetRangeBandwidth(GetParameterFloat("ranger"));
    m_Filter->SetThreshold(GetParameterFloat("thres"));
    m_Filter->SetMaxIterationNumber(GetParameterInt("maxiter"));
    m_Filter->SetRangeBandwidthRamp(GetParameterFloat("rangeramp"));
    m_Filter->SetModeSearch(IsParameterEnabled("modesearch"));

    //Compute the margin used to ensure exact results (tile wise smoothing)
    //This margin is valid for the default uniform kernel used by the
    //MeanShiftSmoothing filter (bandwidth equal to radius in this case)
    const unsigned int margin = (m_Filter->GetMaxIterationNumber() * m_Filter->GetSpatialBandwidth()) + 1;
    
    otbAppLogINFO(<<"Margin of " << margin << " pixels applied to each tile to stabilized mean shift filtering." << std::endl);

    if ( margin > std::min(input->GetLargestPossibleRegion().GetSize()[0],input->GetLargestPossibleRegion().GetSize()[1]) )
      {
      otbAppLogWARNING(<<"Margin value exceed the input image size." << std::endl);
      }

    SetParameterOutputImage("fout", m_Filter->GetOutput());
    if (IsParameterEnabled("foutpos") && HasValue("foutpos"))
      {
      SetParameterOutputImage("foutpos", m_Filter->GetSpatialOutput());
      }
    if(!IsParameterEnabled("modesearch"))
      {
      otbAppLogINFO(<<"Mode Search is disabled." << std::endl);
      }
   }

  MSFilterType::Pointer m_Filter;

};


}
}

OTB_APPLICATION_EXPORT(otb::Wrapper::MeanShiftSmoothing)
