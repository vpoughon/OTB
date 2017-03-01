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

#include "otbImageListToVectorImageFilter.h"
#include "otbMultiToMonoChannelExtractROI.h"
#include "otbImageList.h"

namespace otb
{
namespace Wrapper
{


class ConcatenateImages : public Application
{
public:
  /** Standard class typedefs. */
  typedef ConcatenateImages             Self;
  typedef Application                   Superclass;
  typedef itk::SmartPointer<Self>       Pointer;
  typedef itk::SmartPointer<const Self> ConstPointer;

  /** Standard macro */
  itkNewMacro(Self);

  itkTypeMacro(ConcatenateImages, otb::Application);

  /** Filters typedef */
  typedef otb::ImageList<FloatImageType>  ImageListType;
  typedef ImageListToVectorImageFilter<ImageListType,
                                       FloatVectorImageType >                   ListConcatenerFilterType;
  typedef MultiToMonoChannelExtractROI<FloatVectorImageType::InternalPixelType,
                                       FloatImageType::PixelType>               ExtractROIFilterType;
  typedef ObjectList<ExtractROIFilterType>                                      ExtractROIFilterListType;

private:
  void DoInit() ITK_OVERRIDE
  {
    SetName("ConcatenateImages");
    SetDescription("Concatenate a list of images of the same size into a single multi-channel one.");

    // Documentation
    SetDocName("Images Concatenation");
    SetDocLongDescription("This application performs images channels concatenation. It will walk the input image list (single or multi-channel) and generates a single multi-channel image. The channel order is the one of the list.");
    SetDocLimitations("All input images must have the same size.");
    SetDocAuthors("OTB-Team");
    SetDocSeeAlso("Rescale application, Convert");

    AddDocTag(Tags::Manip);
    AddDocTag("Concatenation");
    AddDocTag("Multi-channel");

    m_Concatener = ListConcatenerFilterType::New();
    m_ExtractorList = ExtractROIFilterListType::New();
    m_ImageList = ImageListType::New();

    AddParameter(ParameterType_InputImageList,  "il",   "Input images list");
    SetParameterDescription("il", "The list of images to concatenate");

    AddParameter(ParameterType_OutputImage, "out",  "Output Image");
    SetParameterDescription("out", "The concatenated output image");

    AddRAMParameter();

    // Doc example parameter settings
    SetDocExampleParameterValue("il", "GomaAvant.png GomaApres.png");
    SetDocExampleParameterValue("out", "otbConcatenateImages.tif");
  }

  void DoUpdateParameters() ITK_OVERRIDE
  {
    // Nothing to do here for the parameters : all are independent

    // Reinitialize the object
    m_Concatener = ListConcatenerFilterType::New();
    m_ImageList = ImageListType::New();
    m_ExtractorList = ExtractROIFilterListType::New();
  }

  void DoExecute() ITK_OVERRIDE
  {
    // Get the input image list
    FloatVectorImageListType::Pointer inList = this->GetParameterImageList("il");

    if( inList->Size() == 0 )
      {
      itkExceptionMacro("No input Image set...");
      }

    inList->GetNthElement(0)->UpdateOutputInformation();
    FloatVectorImageType::SizeType size = inList->GetNthElement(0)->GetLargestPossibleRegion().GetSize();

    // Split each input vector image into image
    // and generate an mono channel image list
    for( unsigned int i=0; i<inList->Size(); i++ )
      {
      FloatVectorImageType::Pointer vectIm = inList->GetNthElement(i);
      vectIm->UpdateOutputInformation();
      if( size != vectIm->GetLargestPossibleRegion().GetSize() )
        {
        itkExceptionMacro("Input Image size mismatch...");
        }

      for( unsigned int j=0; j<vectIm->GetNumberOfComponentsPerPixel(); j++)
        {
        ExtractROIFilterType::Pointer extractor = ExtractROIFilterType::New();
        extractor->SetInput( vectIm );
        extractor->SetChannel( j+1 );
        extractor->UpdateOutputInformation();
        m_ExtractorList->PushBack( extractor );
        m_ImageList->PushBack( extractor->GetOutput() );
        }
      }


    m_Concatener->SetInput( m_ImageList );

    SetParameterOutputImage("out", m_Concatener->GetOutput());
  }


  ListConcatenerFilterType::Pointer  m_Concatener;
  ExtractROIFilterListType::Pointer  m_ExtractorList;
  ImageListType::Pointer        m_ImageList;
};

}
}

OTB_APPLICATION_EXPORT(otb::Wrapper::ConcatenateImages)
