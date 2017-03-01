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

#ifndef otbCompacityPathFunction_h
#define otbCompacityPathFunction_h

#include "otbPathFunction.h"
#include "itkVectorContainer.h"

namespace otb
{

/**
 * \class CompacityPathFunction
 * \brief Calculate the compacity of a path.
 * The formula of the compacity is :
 * \f[ compacity = 4 \pi Surface / Perimeter^{2} \f]
 *
 * The path must contain at least 3 points.
 * The result value is comprise between 0.0 and 1.0
 *
 * \ingroup PathFunctions
 *
 * \ingroup OTBPath
 */

template <class TInputPath,
    class TOutput      = double>
class ITK_EXPORT CompacityPathFunction :
  public PathFunction<TInputPath, TOutput>
{
public:
  /** Standard class typedefs. */
  typedef CompacityPathFunction             Self;
  typedef PathFunction<TInputPath, TOutput> Superclass;
  typedef itk::SmartPointer<Self>           Pointer;
  typedef itk::SmartPointer<const Self>     ConstPointer;

  /** Run-time type information (and related methods). */
  itkTypeMacro(CompacityPathFunction, PathFunction);

  /** Method for creation through the object factory. */
  itkNewMacro(Self);

  /** InputPathType typedef support. */
  typedef typename Superclass::InputPathType         PathType;
  typedef typename Superclass::InputPathConstPointer PathConstPointer;
  typedef typename PathType::ContinuousIndexType     VertexType;
  typedef itk::VectorContainer<unsigned, VertexType> VertexListType;
  typedef typename VertexListType::ConstPointer      VertexListPointer;
  typedef TOutput                                    OutputType;

  typedef double RealType;

  /** Evaluate the function at non-integer positions */
  OutputType Evaluate(const PathType& path) const ITK_OVERRIDE;
  virtual OutputType Evaluate() const;

protected:
  CompacityPathFunction() {};
  ~CompacityPathFunction() ITK_OVERRIDE {}
  void PrintSelf(std::ostream& os, itk::Indent indent) const ITK_OVERRIDE;

private:
  CompacityPathFunction(const Self &);  //purposely not implemented
  void operator =(const Self&);  //purposely not implemented

};

} // namespace otb

#ifndef OTB_MANUAL_INSTANTIATION
#include "otbCompacityPathFunction.txx"
#endif

#endif
