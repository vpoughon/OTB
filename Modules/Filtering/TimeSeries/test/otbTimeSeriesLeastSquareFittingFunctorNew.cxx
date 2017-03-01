/*=========================================================================

  Program:   ORFEO Toolbox
  Language:  C++


  Copyright (c) Centre National d'Etudes Spatiales. All rights reserved.
  See OTBCopyright.txt for details.


  This software is distributed WITHOUT ANY WARRANTY; without even
  the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
  PURPOSE.  See the above copyright notices for more information.

=========================================================================*/


#include "otbTimeSeriesLeastSquareFittingFunctor.h"
#include "otbTimeSeries.h"

int otbTimeSeriesLeastSquareFittingFunctorNew(int itkNotUsed(argc), char* itkNotUsed(argv)[])
{

  typedef float PixelType;
  typedef unsigned int DoYType;
  typedef itk::FixedArray< PixelType > SeriesType;
  typedef itk::FixedArray< DoYType > DatesType;
  typedef double CoefficientPrecisionType;
  const unsigned int Degree = 2;
  typedef otb::PolynomialTimeSeries< Degree, CoefficientPrecisionType > FunctionType;

  typedef otb::Functor::TimeSeriesLeastSquareFittingFunctor<SeriesType, FunctionType, DatesType> FunctorType;

  FunctorType f;

  return EXIT_SUCCESS;
}
