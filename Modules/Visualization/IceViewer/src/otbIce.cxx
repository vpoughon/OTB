/*=========================================================================

  Program:   ORFEO Toolbox
  Language:  C++


  Copyright (c) Centre National d'Etudes Spatiales. All rights reserved.
  See OTBCopyright.txt for details.


     This software is distributed WITHOUT ANY WARRANTY; without even
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
     PURPOSE.  See the above copyright notices for more information.

=========================================================================*/
#include "otbIceViewer.h"
#include "otbDEMHandler.h"



void error_callback(int, const char* description)
{
  std::cerr<<description<<std::endl;
}

int main(int argc, char * argv[])
{
  if(argc < 2)
    {
    std::cerr<<"Usage: "<<argv[0]<<" img1 ... imgN"<<std::endl<<std::endl;
    
    return EXIT_FAILURE;
    }

  char * demdir = getenv("OTB_DEM_DIR");
  char * geoidfile = getenv("OTB_GEOID_FILE");

  otb::DEMHandler::Pointer demHandler = otb::DEMHandler::Instance();
  
  if(demdir != ITK_NULLPTR)
    {
    std::cout<<"Configuring DEM directory: "<<demdir<<std::endl;
    demHandler->OpenDEMDirectory(demdir);
    }

  if(geoidfile != ITK_NULLPTR)
    {
    std::cout<<"Configuring geoid file: "<<geoidfile<<std::endl;
    demHandler->OpenGeoidFile(geoidfile);
    }

  otb::IceViewer::Pointer viewer = otb::IceViewer::New();

  // Initialize viewer
  try
    {
    viewer->Initialize(800,600);
    }
  catch(itk::ExceptionObject& err)
    {
    std::cerr<<"Failed to initialized viewer: "<<err<<std::endl;
    return EXIT_FAILURE;
    }

  for(int i = 1; i<argc;++i)
    {
    try
      {
      viewer->AddImage(argv[i],argv[i]);
      }
    catch(itk::ExceptionObject & err)
      {
      std::cerr<<"Failed to open object as image: "<<err<<std::endl;
      try
        {
        viewer->AddVector(argv[i],argv[i]);
        }
      catch(itk::ExceptionObject & err2)
        {
        std::cerr << "Failed to open object as vector: " << err2 << std::endl;
        std::cerr << "Could not open file " << argv[i] << " as an image or a vector, skipping." << std::endl;
        }
      }
    catch(std::runtime_error & err)
      {
      std::cerr<<"Runtime error: "<< err.what() <<std::endl;
      return EXIT_FAILURE;
      }
    }

  std::cout<<"Press F1 for help"<<std::endl;

  viewer->Start();
  
  
  return EXIT_SUCCESS;
}
