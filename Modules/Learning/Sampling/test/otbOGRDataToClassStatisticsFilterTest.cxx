/*=========================================================================

  Program:   ORFEO Toolbox
  Language:  C++


  Copyright (c) Centre National d'Etudes Spatiales. All rights reserved.
  See OTBCopyright.txt for details.


     This software is distributed WITHOUT ANY WARRANTY; without even
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
     PURPOSE.  See the above copyright notices for more information.

=========================================================================*/

#include "otbOGRDataToClassStatisticsFilter.h"
#include "otbVectorImage.h"
#include "otbImage.h"
#include <fstream>

int otbOGRDataToClassStatisticsFilterNew(int itkNotUsed(argc), char* itkNotUsed(argv) [])
{
  typedef otb::VectorImage<float> InputImageType;
  typedef otb::Image<unsigned char> MaskImageType;
  typedef otb::OGRDataToClassStatisticsFilter<InputImageType,MaskImageType> FilterType;
  
  FilterType::Pointer filter = FilterType::New();
  std::cout << filter << std::endl;
  return EXIT_SUCCESS;
}

int otbOGRDataToClassStatisticsFilter(int argc, char* argv[])
{
  typedef otb::VectorImage<float> InputImageType;
  typedef otb::Image<unsigned char> MaskImageType;
  typedef otb::OGRDataToClassStatisticsFilter<InputImageType,MaskImageType> FilterType;
  
  if (argc < 3)
    {
    std::cout << "Usage : "<<argv[0]<< " input_vector  output_stats" << std::endl;
    }
  
  std::string vectorPath(argv[1]);
  std::string outputPath(argv[2]);
  
  otb::ogr::DataSource::Pointer vectors = otb::ogr::DataSource::New(vectorPath);
  
  InputImageType::RegionType region;
  region.SetSize(0,99);
  region.SetSize(1,50);
  
  InputImageType::PointType origin;
  origin.Fill(0.5);
  
  InputImageType::SpacingType spacing;
  spacing[0] = 1.0;
  spacing[1] = -1.0;
  
  InputImageType::PixelType pixel(3);
  pixel.Fill(1);
  
  InputImageType::Pointer inputImage = InputImageType::New();
  inputImage->SetNumberOfComponentsPerPixel(3);
  inputImage->SetLargestPossibleRegion(region);
  inputImage->SetOrigin(origin);
  inputImage->SetSpacing(spacing);
  // Don't allocate the input image, the filter should not need it
  //inputImage->Allocate();
  //inputImage->FillBuffer(pixel);
  
  MaskImageType::Pointer mask = MaskImageType::New();
  mask->SetRegions(region);
  mask->SetOrigin(origin);
  mask->SetSpacing(spacing);
  mask->Allocate();
  itk::ImageRegionIterator<MaskImageType> it(mask,region);
  unsigned int count = 0;
  for (it.GoToBegin(); !it.IsAtEnd() ; ++it, ++count)
    {
    it.Set(count % 2);
    }
    
  std::string fieldName("Label");
  
  FilterType::Pointer filter = FilterType::New();
  filter->SetInput(inputImage);
  filter->SetMask(mask);
  filter->SetOGRData(vectors);
  filter->SetFieldName(fieldName);
  filter->SetLayerIndex(0);
  
  filter->Update();
  
  FilterType::ClassCountMapType &classCount = filter->GetClassCountOutput()->Get();
  FilterType::PolygonSizeMapType &polySize = filter->GetPolygonSizeOutput()->Get();
  FilterType::ClassCountMapType::const_iterator itClass;
  FilterType::PolygonSizeMapType::const_iterator itPoly;
  
  std::ofstream ofs;
  ofs.open(outputPath.c_str());
  ofs << "# Layer 0 : polygons"<<std::endl;
  ofs << "# Class sample counts"<<std::endl;
  for (itClass = classCount.begin(); itClass != classCount.end() ; ++itClass)
    {
    ofs << "class "<< itClass->first << " = "<< itClass->second << std::endl;
    }
  ofs << "# Vector sizes"<<std::endl;
  for (itPoly = polySize.begin() ; itPoly != polySize.end() ; ++itPoly)
    {
    ofs << "feature " << itPoly->first << " = "<< itPoly->second << std::endl;
    }
  
  filter->SetLayerIndex(1);
  filter->Update();
  
  ofs << "# Layer 1 : lines"<<std::endl;
  ofs << "# Class sample counts"<<std::endl;
  for (itClass = classCount.begin() ; itClass != classCount.end() ; ++itClass)
    {
    ofs << "class "<< itClass->first << " = "<< itClass->second << std::endl;
    }
  ofs << "# Vector sizes"<<std::endl;
  for (itPoly = polySize.begin() ; itPoly != polySize.end() ; ++itPoly)
    {
    ofs << "feature " << itPoly->first << " = "<< itPoly->second << std::endl;
    }
  
  filter->SetLayerIndex(2);
  filter->Update();
  
  ofs << "# Layer 2 : points"<<std::endl;
  ofs << "# Class sample counts"<<std::endl;
  for (itClass = classCount.begin(); itClass != classCount.end() ; ++itClass)
    {
    ofs << "class "<< itClass->first << " = "<< itClass->second << std::endl;
    }
  ofs << "# Vector sizes"<<std::endl;
  for (itPoly = polySize.begin() ; itPoly != polySize.end() ; ++itPoly)
    {
    ofs << "feature " << itPoly->first << " = "<< itPoly->second << std::endl;
    }

  ofs.close();
  return EXIT_SUCCESS;
}
