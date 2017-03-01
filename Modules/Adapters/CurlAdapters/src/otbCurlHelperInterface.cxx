/*=========================================================================

  Program:   ORFEO Toolbox
  Language:  C++


  Copyright (c) Centre National d'Etudes Spatiales. All rights reserved.
  See OTBCopyright.txt for details.


     This software is distributed WITHOUT ANY WARRANTY; without even
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
     PURPOSE.  See the above copyright notices for more information.

=========================================================================*/

#include "otbConfigure.h" // for OTB_USE_CURL
#include "otbCurlHelperInterface.h"

#ifdef OTB_USE_CURL
  #include "otb_curl.h"
#endif

namespace otb {

bool
CurlHelperInterface::IsCurlAvailable()
{
#ifdef OTB_USE_CURL
  const bool curlAvailable = true;
#else
  const bool curlAvailable = false;
#endif

  return curlAvailable;
}

bool
CurlHelperInterface::IsCurlMultiAvailable()
{
#ifdef OTB_CURL_MULTI_AVAILABLE
  const bool curlMultiAvailable = true;
#else
  const bool curlMultiAvailable = false;
#endif

  return curlMultiAvailable;
}

}
