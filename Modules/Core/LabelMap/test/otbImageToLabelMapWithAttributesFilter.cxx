/*=========================================================================

  Program:   ORFEO Toolbox
  Language:  C++


  Copyright (c) Centre National d'Etudes Spatiales. All rights reserved.
  See OTBCopyright.txt for details.


  This software is distributed WITHOUT ANY WARRANTY; without even
  the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
  PURPOSE.  See the above copyright notices for more information.

=========================================================================*/


#include "otbImage.h"
#include "otbVectorImage.h"
#include "otbImageToLabelMapWithAttributesFilter.h"
#include "otbImageFileReader.h"

int otbImageToLabelMapWithAttributesFilter(int itkNotUsed(argc), char* argv[])
{
  const char * infname = argv[1];
  const char * lfname  = argv[2];

  // Convenient typedefs
  typedef otb::VectorImage<double, 2>                           ImageType;
  typedef otb::Image<unsigned int, 2>                           LabeledImageType;
  typedef otb::AttributesMapLabelObjectWithClassLabel<double, 2, double, double> LabelObjectType;

  typedef otb::ImageToLabelMapWithAttributesFilter<ImageType,
    LabeledImageType, unsigned int, LabelObjectType>                            FilterType;
  typedef otb::ImageFileReader<ImageType>                      ReaderType;
  typedef otb::ImageFileReader<LabeledImageType>               LabeledReaderType;

  // SmartPointer instantiation
  FilterType::Pointer         filter = FilterType::New();
  ReaderType::Pointer         reader = ReaderType::New();
  LabeledReaderType::Pointer  labeledReader = LabeledReaderType::New();

  // Inputs
  reader->SetFileName(infname);
  reader->UpdateOutputInformation();

  labeledReader->SetFileName(lfname);
  labeledReader->UpdateOutputInformation();

  // Filter
  filter->SetInput(reader->GetOutput());
  filter->SetLabeledImage(labeledReader->GetOutput());
  filter->Update();


  // tests
  std::vector<std::string> features = filter->GetOutput()->GetNthLabelObject(0)->GetAvailableAttributes();

  for(std::vector<std::string>::const_iterator fit = features.begin(); fit!=features.end(); ++fit)
    {
    std::cout <<"Label " << *fit << std::endl;

    }


  return EXIT_SUCCESS;
}
