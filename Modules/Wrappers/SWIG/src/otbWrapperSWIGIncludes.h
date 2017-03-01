/*=========================================================================

  Program:   ORFEO Toolbox
  Language:  C++


  Copyright:
    Centre National d'Etudes Spatiales,
    CS Systemes d'information.

 See OTBCopyright.txt, CSCopyright.txt for details.
 All rights reserved.

 This software is distributed WITHOUT ANY WARRANTY; without even
 the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
 PURPOSE.  See the above copyright notices for more information.

=========================================================================*/
#ifndef otbWrapperSWIGIncludes_h
#define otbWrapperSWIGIncludes_h

#include "otbWrapperApplicationRegistry.h"
#include "otbWrapperAddProcessToWatchEvent.h"
#include "otbWrapperDocExampleStructure.h"

typedef otb::Wrapper::Application                        Application;
typedef otb::Wrapper::Application::Pointer               Application_Pointer;
typedef otb::Wrapper::ApplicationRegistry                Registry;
typedef otb::Wrapper::AddProcessToWatchEvent             AddProcessToWatchEvent;
typedef otb::Wrapper::DocExampleStructure                DocExampleStructure;
typedef otb::Wrapper::Parameter                          Parameter;
typedef otb::Wrapper::OutputImageParameter               OutputImageParameter;
typedef otb::Wrapper::InputImageParameter                InputImageParameter;
typedef otb::Wrapper::ComplexOutputImageParameter        ComplexOutputImageParameter;
typedef otb::Wrapper::ComplexInputImageParameter         ComplexInputImageParameter;

#endif
