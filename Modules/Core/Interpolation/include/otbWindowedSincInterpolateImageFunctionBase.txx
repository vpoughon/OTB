/*=========================================================================

  Program:   ORFEO Toolbox
  Language:  C++


  Copyright (c) Centre National d'Etudes Spatiales. All rights reserved.
  See OTBCopyright.txt for details.


     This software is distributed WITHOUT ANY WARRANTY; without even
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
     PURPOSE.  See the above copyright notices for more information.

=========================================================================*/
#ifndef otbWindowedSincInterpolateImageFunctionBase_txx
#define otbWindowedSincInterpolateImageFunctionBase_txx

#include "otbWindowedSincInterpolateImageFunctionBase.h"

namespace otb
{
/** Constructor */
template<class TInputImage, class TWindowFunction, class TBoundaryCondition, class TCoordRep>
WindowedSincInterpolateImageFunctionBase<TInputImage, TWindowFunction, TBoundaryCondition, TCoordRep>
::WindowedSincInterpolateImageFunctionBase()
{
}

/** Destructor */
template<class TInputImage, class TWindowFunction, class TBoundaryCondition, class TCoordRep>
WindowedSincInterpolateImageFunctionBase<TInputImage, TWindowFunction, TBoundaryCondition, TCoordRep>
::~WindowedSincInterpolateImageFunctionBase()
{
}

template<class TInputImage, class TWindowFunction, class TBoundaryCondition, class TCoordRep>
void
WindowedSincInterpolateImageFunctionBase<TInputImage, TWindowFunction, TBoundaryCondition, TCoordRep>
::PrintSelf(std::ostream& os, itk::Indent indent) const
{
  Superclass::PrintSelf(os, indent);
}

} //namespace otb
#endif
