/*=========================================================================

  Program:   ORFEO Toolbox
  Language:  C++


  Copyright (c) Centre National d'Etudes Spatiales. All rights reserved.
  See OTBCopyright.txt for details.


     This software is distributed WITHOUT ANY WARRANTY; without even
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
     PURPOSE.  See the above copyright notices for more information.

=========================================================================*/

#include "otbGDALDriverManagerWrapper.h"
#include "otbGDALImageIO.h"
#include "otbStandardOneLineFilterWatcher.h"

using namespace otb;

int otbGDALOverviewsBuilderNew(int itkNotUsed(argc), char* itkNotUsed(argv) [])
{
  typedef otb::GDALOverviewsBuilder GDALOverviewsBuilderType;
  GDALOverviewsBuilderType::Pointer object = GDALOverviewsBuilderType::New();

  std::cout << object << std::endl;

  return EXIT_SUCCESS;
}

int otbGDALOverviewsBuilder(int itkNotUsed(argc), char* argv[])
{
  const char * inputFilename  = argv[1];
  int nbResolution = atoi(argv[2]);
  std::string filename(inputFilename);

  typedef otb::GDALOverviewsBuilder FilterType;
  FilterType::Pointer filter = FilterType::New();

  otb::GDALResamplingType resamp = GDAL_RESAMPLING_AVERAGE;

  filter->SetInputFileName(filename);
  filter->SetNbResolutions(nbResolution);
  filter->SetResamplingMethod(resamp);

  {
    StandardOneLineFilterWatcher watcher(filter,"Overviews creation");
    filter->Update();
  }

  otb::GDALImageIO::Pointer io = otb::GDALImageIO::New();
  io->SetFileName(inputFilename);
  bool canRead = io->CanReadFile(inputFilename);

  if(!canRead)
    {
    std::cerr<<"Failed to read file "<< inputFilename <<" with GdalImageIO."<<std::endl;
    return EXIT_FAILURE;
    }
  
  io->ReadImageInformation();
  //std::cout << io->GetOverviewsCount() << std::endl;

  if (io->GetOverviewsCount() != static_cast<unsigned int>(nbResolution) )
    {
    std::cout << "Got "<<io->GetOverviewsCount()<< " overviews, expected "<< nbResolution << std::endl;
    return EXIT_FAILURE;
    }

  return EXIT_SUCCESS;
}
