/*=========================================================================

  Program:   ORFEO Toolbox
  Language:  C++


  Copyright (c) Centre National d'Etudes Spatiales. All rights reserved.
  See OTBCopyright.txt for details.


     This software is distributed WITHOUT ANY WARRANTY; without even
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
     PURPOSE.  See the above copyright notices for more information.

=========================================================================*/
#ifndef otbParserX_h
#define otbParserX_h

#include "itkLightObject.h"
#include "itkObjectFactory.h"

#if defined(__clang__)
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wc++11-extensions"

/* Apple's 3.6.0 based clang doesn't support -Winconsistent-missing-override */
#if defined(__apple_build_version__) &&  __apple_build_version__ >= 7000053
#pragma clang diagnostic ignored "-Winconsistent-missing-override"
#endif

#include "mpParser.h"
#pragma clang diagnostic pop

#else
#include "mpParser.h"
#endif

namespace otb
{

class ParserXImpl;


/** \class ParserX
 * \brief  Definition of the standard floating point parser.
 * Standard implementation of the mathematical expressions parser.
 *
 * \sa BandMathImageFilter
 *
 *
 * \ingroup OTBMathParserX
 */
class ITK_EXPORT ParserX : public itk::LightObject
{
public:
  /** Standard class typedefs. */
  typedef ParserX                                   Self;
  typedef itk::LightObject                         Superclass;
  typedef itk::SmartPointer<Self>                  Pointer;
  typedef itk::SmartPointer<const Self>            ConstPointer;

  /** New macro for creation of through a Smart Pointer */
  itkNewMacro(Self);

  /** Run-time type information (and related methods) */
  itkTypeMacro(ParserX, itk::LightObject);

  /** Convenient type definitions */
  typedef ParserX                                   ParserXType;
  typedef mup::Value                                ValueType;
  typedef mup::IValue                               IValueType;

  /** Set the expression to be parsed */
  virtual void SetExpr(const std::string & Expression);

  /** Trigger the parsing */
  ValueType Eval();

  /** Trigger the parsing but return a const ref */
  const IValueType & EvalRef();

  /** Define a variable */
  void DefineVar(const std::string &sName, ValueType *fVar);

  /** Define a constant */
  //void DefineConst(const std::string &sName, ValueType *fVar);

  /** Clear all the defined variables */
  void ClearVar();

  /** Return the expression to be parsed */
  const std::string& GetExpr() const;

  /** Return the list of variables */
  const mup::var_maptype& GetVar() const;

  /** Return the list of expression variables (only make sense after having set up an expression) */
  const mup::var_maptype& GetExprVar() const;

  /**  Check Expression **/
  bool CheckExpr();

protected:
  ParserX();
  ~ParserX() ITK_OVERRIDE;
  void PrintSelf(std::ostream& os, itk::Indent indent) const ITK_OVERRIDE;


private:
  ParserX(const Self &);             //purposely not implemented
  void operator =(const Self &);    //purposely not implemented

  typedef itk::SmartPointer<ParserXImpl> ParserXImplPtr;
  ParserXImplPtr m_InternalParserX;
}; // end class

}//end namespace otb

#endif
