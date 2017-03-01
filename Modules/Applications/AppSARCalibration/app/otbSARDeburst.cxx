/*=========================================================================

 Program:   ORFEO Toolbox
 Language:  C++


 Copyright (c) Centre National d'Etudes Spatiales. All rights reserved.
 See OTBCopyright.txt for details.


 This software is distributed WITHOUT ANY WARRANTY; without even
 the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
 PURPOSE.  See the above copyright notices for more information.

 =========================================================================*/
#include "otbWrapperApplication.h"
#include "otbWrapperApplicationFactory.h"

#include "otbSarDeburstImageFilter.h"

namespace otb
{
namespace Wrapper
{
class SARDeburst : public Application
{
public:
  /** Standard class typedefs. */
  typedef SARDeburst     Self;
  typedef Application                   Superclass;
  typedef itk::SmartPointer<Self>       Pointer;
  typedef itk::SmartPointer<const Self> ConstPointer;

  /** Standard macro */
  itkNewMacro(Self);

  itkTypeMacro(SARDeburst, otb::Application);

  typedef otb::SarDeburstImageFilter<FloatVectorImageType>     DeburstFilterType;

private:
  void DoInit() ITK_OVERRIDE
  {
    SetName("SARDeburst");
    SetDescription("This application performs a deburst operation by removing redundant lines. \n");

    // Documentation
    SetDocName("SAR Deburst");
    SetDocLongDescription("This application performs a deburst operation by removing redundant lines between burst. This operation is useful when dealing with Sentinel1 IW SLC products, where each subswath is composed of several overlapping burst separated by black lines. Lines to remove are computed by SAR sensor model in OSSIM plugins. The output image is smaller in azimuth direction than the input line, because of removed lines. Note that the output sensor model is updated accordingly. This deburst filter is the perfect preprocessing step to orthorectify S1 IW SLC product with OTB without suffering from artifacts caused by bursts separation.\n");
    SetDocLimitations("Only Sentinel1 IW SLC products are supported for now.");
    SetDocAuthors("OTB-Team");
    SetDocSeeAlso("OrthoRectification");

    AddDocTag(Tags::Calibration);
    AddDocTag(Tags::SAR);

    AddParameter(ParameterType_InputImage,  "in", "Input Image");
    SetParameterDescription("in", "Input image");

    AddParameter(ParameterType_OutputImage,  "out", "Output Image");
    SetParameterDescription("out", "Output deburst image");

    AddRAMParameter();

    SetDocExampleParameterValue("in","s1_iw_slc.tif");
    SetDocExampleParameterValue("out","s1_iw_slc_deburst.tif");
    
    
  }

  void DoUpdateParameters() ITK_OVERRIDE
  {}

  void DoExecute() ITK_OVERRIDE
  {
    // Get the input complex image
    FloatVectorImageType*  in = GetParameterImage("in");

    // Set the filer input
    m_DeburstFilter = DeburstFilterType::New();
    m_DeburstFilter->SetInput(in);

    // Set the output image
    SetParameterOutputImage("out", m_DeburstFilter->GetOutput());
  }

  DeburstFilterType::Pointer   m_DeburstFilter;

};
}
}

OTB_APPLICATION_EXPORT(otb::Wrapper::SARDeburst)
