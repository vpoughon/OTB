/*=========================================================================

  Program:   ORFEO Toolbox
  Language:  C++


  Copyright (c) Centre National d'Etudes Spatiales. All rights reserved.
  See OTBCopyright.txt for details.


     This software is distributed WITHOUT ANY WARRANTY; without even
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
     PURPOSE.  See the above copyright notices for more information.

=========================================================================*/
#include "itkMacro.h"
#include "otbSarBrightnessFunctor.h"
#include "otbMath.h"

int otbSarBrightnessFunctor(int itkNotUsed(argc), char * itkNotUsed(argv)[])
{
  typedef double                   ScalarType;

  typedef otb::Functor::SarBrightnessFunctor<ScalarType, ScalarType> FunctorType;

  FunctorType funct;

  funct.SetNoise( 10.0);
  if( vcl_abs(funct.GetNoise() -10.0) > 0.0)
  {
    return false;
  }
  funct.SetScale( 10.0);
  if( vcl_abs(funct.GetScale() -10.0) > 0.0)
  {
    return false;
  }
  funct.SetAntennaPatternNewGain( 10.0);
  if( vcl_abs(funct.GetAntennaPatternNewGain() -10.0) > 0.0)
  {
    return false;
  }
  funct.SetAntennaPatternOldGain( 10.0);
  if( vcl_abs(funct.GetAntennaPatternOldGain() -10.0) > 0.0)
  {
    return false;
  }

  funct.SetRangeSpreadLoss( 10.0);
  if( vcl_abs(funct.GetRangeSpreadLoss() -10.0) > 0.0)
  {
    return false;
  }
  std::cout << "First  BetaNaught : " << funct.operator ()( 0.) << std::endl;
  std::cout << "Second BetaNaught : " << funct.operator ()( 1.) << std::endl;


  return EXIT_SUCCESS;
}
