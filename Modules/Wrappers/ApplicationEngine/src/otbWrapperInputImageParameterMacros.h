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

#ifndef otbWrapperInputImageParameterMacros__h
#define otbWrapperInputImageParameterMacros__h

#define otbGetImageMacro(image)                       \
  image##Type *                                       \
  InputImageParameter::Get##image ()                  \
  {                                                   \
    return this->GetImage< image##Type > ();          \
  }


#define otbCastImageMacro(InputImageType, OutputImageType, theMethod)   \
  template<> OutputImageType *                                          \
  InputImageParameter::CastImage<InputImageType , OutputImageType>()    \
  {                                                                     \
    return this->theMethod<InputImageType , OutputImageType>();         \
  }

#define otbGenericCastImageMacro(InputImageType, theMethod, prefix)     \
  otbCastImageMacro(InputImageType, UInt8##prefix##ImageType, theMethod) \
  otbCastImageMacro(InputImageType, UInt16##prefix##ImageType, theMethod) \
  otbCastImageMacro(InputImageType, Int16##prefix##ImageType, theMethod) \
  otbCastImageMacro(InputImageType, UInt32##prefix##ImageType, theMethod) \
  otbCastImageMacro(InputImageType, Int32##prefix##ImageType, theMethod) \
  otbCastImageMacro(InputImageType, Float##prefix##ImageType, theMethod) \
  otbCastImageMacro(InputImageType, Double##prefix##ImageType, theMethod)


#endif
