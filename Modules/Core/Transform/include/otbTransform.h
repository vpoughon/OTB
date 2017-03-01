/*=========================================================================

  Program:   ORFEO Toolbox
  Language:  C++


  Copyright (c) Centre National d'Etudes Spatiales. All rights reserved.
  See OTBCopyright.txt for details.


     This software is distributed WITHOUT ANY WARRANTY; without even
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
     PURPOSE.  See the above copyright notices for more information.

=========================================================================*/
#ifndef otbTransform_h
#define otbTransform_h

#include "itkTransform.h"
#include "vnl/vnl_vector_fixed.h"


namespace otb
{
/** \class Transform
 * \brief Class to overload method passed to virtual pure in ITK V4.
 *
 *
 *
 * \ingroup OTBTransform
 */
template< class TScalarType,
          unsigned int NInputDimensions = 3,
          unsigned int NOutputDimensions = 3 >
class ITK_EXPORT Transform : public itk::Transform<TScalarType,          // Data type for scalars
      NInputDimensions,                                                       // Number of dimensions in the input space
      NOutputDimensions>                                                       // Number of dimensions in the output space
{
public:
  /** Standard class typedefs. */
  typedef Transform                  Self;
  typedef itk::Transform<TScalarType,
      NInputDimensions,
      NOutputDimensions>             Superclass;
  typedef itk::SmartPointer< Self >       Pointer;
  typedef itk::SmartPointer< const Self > ConstPointer;

  /** Run-time type information (and related methods). */
  itkTypeMacro(Transform, itk::Transform);

  /** Dimension of the domain space. */
  itkStaticConstMacro(InputSpaceDimension, unsigned int, NInputDimensions);
  itkStaticConstMacro(OutputSpaceDimension, unsigned int, NOutputDimensions);

  /** Get the size of the input space */
  unsigned int GetInputSpaceDimension(void) const ITK_OVERRIDE { return NInputDimensions; }

  /** Get the size of the output space */
  unsigned int GetOutputSpaceDimension(void) const ITK_OVERRIDE { return NOutputDimensions; }

  /** Type of the scalar representing coordinate and vector elements. */
  typedef  TScalarType ScalarType;

  /** Type of the input parameters. */
  typedef typename Superclass::ParametersType         ParametersType;
  typedef typename Superclass::ParametersValueType    ParametersValueType;
  typedef typename Superclass::NumberOfParametersType NumberOfParametersType;

  /** Type of the Jacobian matrix. */
  typedef  itk::Array2D< double > JacobianType;

  /** Standard vector type for this class. */
  typedef itk::Vector< TScalarType, NInputDimensions >  InputVectorType;
  typedef itk::Vector< TScalarType, NOutputDimensions > OutputVectorType;

  /** Standard covariant vector type for this class */
  typedef itk::CovariantVector< TScalarType, NInputDimensions >  InputCovariantVectorType;
  typedef itk::CovariantVector< TScalarType, NOutputDimensions > OutputCovariantVectorType;

  /** Standard vnl_vector type for this class. */
  typedef vnl_vector_fixed< TScalarType, NInputDimensions >  InputVnlVectorType;
  typedef vnl_vector_fixed< TScalarType, NOutputDimensions > OutputVnlVectorType;

  /** Standard coordinate point type for this class */
  typedef itk::Point< TScalarType, NInputDimensions >  InputPointType;
  typedef itk::Point< TScalarType, NOutputDimensions > OutputPointType;

  /** Base inverse transform type. This type should not be changed to the
   * concrete inverse transform type or inheritance would be lost. */
  typedef typename Superclass::InverseTransformBaseType InverseTransformBaseType;

  typedef typename Superclass::InverseTransformBasePointer InverseTransformBasePointer;

  /**  Method to transform a point. */

  OutputPointType TransformPoint(const InputPointType  & ) const ITK_OVERRIDE
    { return OutputPointType(); }
  
  using Superclass::TransformVector;
  /**  Method to transform a vector. */
  OutputVectorType    TransformVector(const InputVectorType &) const ITK_OVERRIDE
  { return OutputVectorType(); }

  /**  Method to transform a vnl_vector. */
  virtual OutputVnlVectorType TransforVector(const InputVnlVectorType &) const
    { return OutputVnlVectorType(); }

  using Superclass::TransformCovariantVector;
  /**  Method to transform a CovariantVector. */
  OutputCovariantVectorType TransformCovariantVector(
    const InputCovariantVectorType &) const ITK_OVERRIDE
  { return OutputCovariantVectorType(); }


  /** Set the transformation parameters and update internal transformation.
   * SetParameters gives the transform the option to set it's
   * parameters by keeping a reference to the parameters, or by
   * copying.  To force the transform to copy it's parameters call
   * SetParametersByValue.
   * \sa SetParametersByValue
   */
    void SetParameters( const ParametersType & ) ITK_OVERRIDE
    { itkExceptionMacro( << "Subclasses should ITK_OVERRIDE this method (SetParameters)" ) }

  void ComputeJacobianWithRespectToParameters(const InputPointType  &, JacobianType& ) const ITK_OVERRIDE
  {
    itkExceptionMacro(<<  "Subclasses should ITK_OVERRIDE this method (ComputeJacobianWithRespectToParameters)" );
  }

  /** Set the transformation parameters and update internal transformation.
   * This method forces the transform to copy the parameters.  The
   * default implementation is to call SetParameters.  This call must
   * be overridden if the transform normally implements SetParameters
   * by keeping a reference to the parameters.
   * \sa SetParameters
   */
  void SetParametersByValue(const ParametersType & p) ITK_OVERRIDE
  { this->SetParameters (p); }

  /** Get the Transformation Parameters. */
  const ParametersType & GetParameters(void) const ITK_OVERRIDE
  {
    return m_Parameters;
  }

  /** Set the fixed parameters and update internal transformation. */
  void SetFixedParameters( const ParametersType & ) ITK_OVERRIDE
    { itkExceptionMacro( << "Subclasses should ITK_OVERRIDE this method (SetFixedParameters)" ) }

  /** Get the Fixed Parameters. */
  const ParametersType& GetFixedParameters(void) const ITK_OVERRIDE
    {
    itkExceptionMacro( << "Subclasses should ITK_OVERRIDE this method (GetFixedParameters)" );
    // Next line is needed to avoid errors due to:
    // "function must return a value".
    return this->m_FixedParameters;
    }

  /** Compute the Jacobian of the transformation
   *
   * This method computes the Jacobian matrix of the transformation
   * at a given input point. The rank of the Jacobian will also indicate
   * if the transform is invertible at this point.
   *
   * The Jacobian is be expressed as a matrix of partial derivatives of the
   * output point components with respect to the parameters that defined
   * the transform:
   *
   * \f[
   *
  J=\left[ \begin{array}{cccc}
  \frac{\partial x_{1}}{\partial p_{1}} &
  \frac{\partial x_{1}}{\partial p_{2}} &
  \cdots  & \frac{\partial x_{1}}{\partial p_{m}}\\
  \frac{\partial x_{2}}{\partial p_{1}} &
  \frac{\partial x_{2}}{\partial p_{2}} &
  \cdots  & \frac{\partial x_{2}}{\partial p_{m}}\\
  \vdots  & \vdots  & \ddots  & \vdots \\
  \frac{\partial x_{n}}{\partial p_{1}} &
  \frac{\partial x_{n}}{\partial p_{2}} &
  \cdots  & \frac{\partial x_{n}}{\partial p_{m}}
  \end{array}\right]
   *
   * \f]
   * */
  virtual const JacobianType & GetJacobian(const InputPointType  &) const
    {
    itkExceptionMacro( << "Subclass should ITK_OVERRIDE this method (GetJacobian)" );
    // Next line is needed to avoid errors due to:
    // "function must return a value" .
    return this->m_Jacobian;
    }

  /** Return the number of parameters that completely define the Transfom  */
  NumberOfParametersType GetNumberOfParameters(void) const ITK_OVERRIDE
  { return this->m_Parameters.Size(); }

protected:
  Transform(): Superclass::Transform()
  {}

  Transform(NumberOfParametersType numberOfParameters)
    : Superclass::Transform(numberOfParameters)
  {}

  ~Transform() ITK_OVERRIDE {}

  void PrintSelf(std::ostream& os, itk::Indent indent) const ITK_OVERRIDE
  {
    Superclass::PrintSelf(os, indent);
#if 0
    os << indent << "Parameters : " << m_Parameters << std::endl;
    os << indent << "FixedParameters : " << m_FixedParameters << std::endl;
    os << indent << "Jacobian : " << m_Jacobian << std::endl;
#endif
  }


  mutable ParametersType m_Parameters;
  mutable ParametersType m_FixedParameters;

  mutable JacobianType m_Jacobian;
private:
  Transform(const Self &);      //purposely not implemented
  void operator=(const Self &); //purposely not implemented
};
} // end namespace otb

#endif
