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

#ifndef otbExtendedFilenameToReaderOptions_h
#define otbExtendedFilenameToReaderOptions_h

#include "otbExtendedFilenameHelper.h"

namespace otb
{

/** \class ExtendedFilenameToReaderOptions
 *  \brief Converts an extended filename to reader options.
 *
 * Available options for extended file name are:
 * - &geom : to specify an external geom file
 * - &sdataidx : sub-dataset index for composite files
 * - &resol : resolution factor for jpeg200 files
 * - &skipcarto : switch to skip the cartographic information
 * - &skipgeom  : switch to skip the geometric information
 *
 *  \sa ImageFileReader
 *
 * \ingroup OTBExtendedFilename
 */

class ITK_EXPORT ExtendedFilenameToReaderOptions : public ExtendedFilenameHelper
{
public:
/** Standard class typedefs. */
  typedef ExtendedFilenameToReaderOptions        Self;
  typedef itk::SmartPointer<Self>                Pointer;
  typedef itk::SmartPointer<const Self>          ConstPointer;
  typedef ExtendedFilenameHelper                 Superclass;

  itkTypeMacro(ExtendedFilenameToReaderOptions, otb::ExtendedFilenameHelper);
  itkNewMacro(Self);

  typedef Superclass                                FNameHelperType;
  typedef FNameHelperType::OptionMapType            MapType;
  typedef MapType::iterator                         MapIteratorType;

  /** The reader option structure. */
  struct OptionType
  {
    std::pair< bool, std::string  >  simpleFileName;
    std::pair< bool, std::string  >  extGEOMFileName;
    std::pair< bool, unsigned int >  subDatasetIndex;
    std::pair< bool, unsigned int >  resolutionFactor;
    std::pair< bool, bool         >  skipCarto;
    std::pair< bool, bool         >  skipGeom;
    std::pair< bool, bool         >  skipRpcTag;
    std::vector<std::string>         optionList;
  };

  /* Set Methods */
  void SetExtendedFileName(const char * extFname) ITK_OVERRIDE;
  /* Get Methods */
  bool SimpleFileNameIsSet () const;
  bool ExtGEOMFileNameIsSet () const;
  const char* GetExtGEOMFileName () const;
  bool SubDatasetIndexIsSet () const;
  unsigned int GetSubDatasetIndex () const;
  bool ResolutionFactorIsSet () const;
  unsigned int GetResolutionFactor () const;
  bool SkipCartoIsSet () const;
  bool GetSkipCarto () const;
  bool SkipGeomIsSet () const;
  bool GetSkipGeom () const;
  bool SkipRpcTagIsSet () const;
  bool GetSkipRpcTag () const;

protected:
  ExtendedFilenameToReaderOptions();
  ~ExtendedFilenameToReaderOptions() ITK_OVERRIDE {}

private:
  ExtendedFilenameToReaderOptions(const Self &);  //purposely not implemented
  void operator =(const Self&);  //purposely not implemented

  OptionType               m_Options;

};
} // end namespace otb

#endif // otbExtendedFilenameToReaderOptions_h
