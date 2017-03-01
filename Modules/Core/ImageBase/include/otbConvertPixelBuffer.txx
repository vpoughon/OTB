/*=========================================================================

  Program:   Insight Segmentation & Registration Toolkit
  Language:  C++

  Copyright (c) Insight Software Consortium. All rights reserved.
  See ITKCopyright.txt or http://www.itk.org/HTML/Copyright.htm for details.

     This software is distributed WITHOUT ANY WARRANTY; without even
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
     PURPOSE.  See the above copyright notices for more information.

=========================================================================*/
#ifndef otbConvertPixelBuffer_txx
#define otbConvertPixelBuffer_txx
#include "otbConvertPixelBuffer.h"

#include "itkConvertPixelBuffer.h"

namespace otb
{
template < typename InputPixelType,
           typename OutputPixelType,
           class OutputConvertTraits
           >
void
ConvertPixelBuffer<InputPixelType, OutputPixelType, OutputConvertTraits>
::Convert(InputPixelType* inputData,
          int inputNumberOfComponents,
          OutputPixelType* outputData , size_t size)
{
  if ((OutputConvertTraits::GetNumberOfComponents() == 2) &&
      inputNumberOfComponents == 1)
    {
    // OTB patch : monoband to complex
    ConvertGrayToComplex(inputData,outputData,size);
    }
  else
    {
    // use ITK pixel buffer converter  
    itk::ConvertPixelBuffer<
      InputPixelType,
      OutputPixelType,
      OutputConvertTraits>
      ::Convert(inputData,inputNumberOfComponents,outputData,size);
    }
}

// Convert Grayscale to Complex
template < typename InputPixelType,
           typename OutputPixelType,
           class OutputConvertTraits
           >
void
ConvertPixelBuffer<InputPixelType, OutputPixelType, OutputConvertTraits>
::ConvertGrayToComplex(InputPixelType* inputData,
                   OutputPixelType* outputData , size_t size)
{
  InputPixelType* endInput = inputData + size;
  while(inputData != endInput)
    {
    OutputConvertTraits::SetNthComponent(0, *outputData,
      static_cast<OutputComponentType>
      (*inputData));
    OutputConvertTraits::SetNthComponent(1, *outputData,
      static_cast<OutputComponentType>
      (0.));
    inputData++;
    outputData++;
    }
}

/* To be able to convert transparently*/

template<typename InputType, typename OutputType>
OutputType
ComplexCast(const std::complex<InputType>& in, const OutputType& itkNotUsed(dummy))
{
  typedef typename itk::NumericTraits<std::complex<InputType> >::RealType       RealType;
  typedef typename itk::NumericTraits<std::complex<InputType> >::ScalarRealType ScalarRealType;

  RealType    inReal( static_cast<ScalarRealType>(in.real()), static_cast<ScalarRealType>(in.imag()) );

  return static_cast < OutputType >( vcl_abs(inReal) );
}

template<typename InputType, typename OutputType>
std::complex<OutputType>
ComplexCast(const std::complex<InputType>& in, const std::complex<OutputType>& itkNotUsed(dummy))
{
  typedef typename itk::NumericTraits<std::complex<InputType> >::RealType       RealType;
  typedef typename itk::NumericTraits<std::complex<InputType> >::ScalarRealType ScalarRealType;

  RealType    inReal( static_cast<ScalarRealType>(in.real()), static_cast<ScalarRealType>(in.imag()) );

  return static_cast < std::complex<OutputType> >( inReal );
}

template < typename InputPixelType,
           typename OutputPixelType,
           class OutputConvertTraits
           >
void
ConvertPixelBuffer<InputPixelType, OutputPixelType, OutputConvertTraits>
::ConvertComplexToGray(std::complex<InputPixelType>* inputData,
                      int itkNotUsed(inputNumberOfComponents),
                      OutputPixelType* outputData , size_t size)
{
  OutputPixelType dummy;
  std::complex<InputPixelType>* endInput = inputData + size;
  while(inputData != endInput)
    {
    OutputConvertTraits::SetNthComponent(0, *outputData,
      static_cast<OutputPixelType> (ComplexCast(*inputData,dummy)));
    inputData++;
    outputData++;
    }
}

template < typename InputPixelType,
           typename OutputPixelType,
           class OutputConvertTraits >
void
ConvertPixelBuffer<InputPixelType, OutputPixelType, OutputConvertTraits>
::ConvertVectorImage(InputPixelType* inputData,
                     int inputNumberOfComponents,
                     OutputPixelType* outputData , size_t size)
{
  itk::ConvertPixelBuffer<
    InputPixelType,
    OutputPixelType,
    OutputConvertTraits>
    ::ConvertVectorImage(inputData,
                          inputNumberOfComponents,
                          outputData,size);
}

template < typename InputPixelType,
           typename OutputPixelType,
           class OutputConvertTraits >
void
ConvertPixelBuffer<InputPixelType, OutputPixelType, OutputConvertTraits>
::ConvertComplexVectorImageToVectorImage(std::complex<InputPixelType>* inputData,
                     int inputNumberOfComponents,
                     OutputPixelType* outputData , size_t size)
{
  size_t length = size* (size_t)inputNumberOfComponents;
  for( size_t i=0; i< length/2; i++ )
    {
    OutputConvertTraits::SetNthComponent( 0, *outputData, (*inputData).real());
    ++outputData;
    OutputConvertTraits::SetNthComponent( 0, *outputData, (*inputData).imag());
    ++outputData;
    ++inputData;
    }
}

template < typename InputPixelType,
           typename OutputPixelType,
           class OutputConvertTraits >
void
ConvertPixelBuffer<InputPixelType, OutputPixelType, OutputConvertTraits>
::ConvertComplexVectorImageToVectorImageComplex(std::complex<InputPixelType>* inputData,
                     int inputNumberOfComponents,
                     OutputPixelType* outputData , size_t size)
{
  size_t length = size* (size_t)inputNumberOfComponents;
  OutputPixelType dummy;
  for( size_t i=0; i< length; i++ )
    {
    OutputConvertTraits::SetNthComponent( 0, *outputData,
                                          ComplexCast(*inputData, dummy));
    ++outputData;
    ++inputData;
    }
}

}// end namespace otb

#endif
