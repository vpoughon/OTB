/*=========================================================================

  Program:   ORFEO Toolbox
  Language:  C++


  Copyright (c) Centre National d'Etudes Spatiales. All rights reserved.
  See OTBCopyright.txt for details.


     This software is distributed WITHOUT ANY WARRANTY; without even
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
     PURPOSE.  See the above copyright notices for more information.

=========================================================================*/
#ifndef otb_boost_string_header_h
#define otb_boost_string_header_h

#if defined(__GNUC__) || defined(__clang__)
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wshadow"
#include <boost/algorithm/string.hpp>
#include <boost/algorithm/string/predicate.hpp>
#pragma GCC diagnostic pop
#else
#include <boost/algorithm/string.hpp>
#include <boost/algorithm/string/predicate.hpp>
#endif


#endif
