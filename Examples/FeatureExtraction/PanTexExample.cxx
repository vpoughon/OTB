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



//  Software Guide : BeginCommandLineArgs
//    INPUTS: {ROI_QB_MUL_1.png}
//    OUTPUTS: {PanTexOutput.tif}, {pretty_PanTexInput.png}, {pretty_PanTexOutput.png}
//  Software Guide : EndCommandLineArgs

#include "itkMacro.h"
#include "otbImage.h"
#include "otbImageFileReader.h"
#include "otbImageFileWriter.h"
#include "itkUnaryFunctorImageFilter.h"
#include "itkRescaleIntensityImageFilter.h"

// Software Guide : BeginLatex
//
// This example illustrates the use of the
// \doxygen{otb}{ScalarImageToPanTexTextureFilter}. This texture parameter was
// first introduced in \cite{PanTex} and is very useful for urban area
// detection.
// \relatedClasses
//  \begin{itemize}
//  \item \doxygen{otb}{ScalarImageToTexturesFilter}
//  \item \doxygen{otb}{ScalarImageToAdvancedTexturesFilter}
//  \end{itemize}
//
// The first step required to use this filter is to include its header file.
//
// Software Guide : EndLatex

// Software Guide : BeginCodeSnippet
#include "otbScalarImageToPanTexTextureFilter.h"
// Software Guide : EndCodeSnippet

int main(int argc, char * argv[])
{
  // Parse command line parameters
  if (argc != 5)
    {
    std::cerr << "Usage: " << argv[0] << " <inputImage> ";
    std::cerr << " <outputImage> <inputRescaled> <outputRescaled> ";
    std::cerr << std::endl;
    return EXIT_FAILURE;
    }

  const char* infname   = argv[1];
  const char* outfname  = argv[2];
  const char* inprettyfname  = argv[3];
  const char* outprettyfname  = argv[4];

  typedef double PixelType;
  const int Dimension = 2;
  typedef otb::Image<PixelType, Dimension> ImageType;

  // Software Guide : BeginLatex
//
// After defining the types for the pixels and the images used in the
// example, we define the type for the PanTex filter. It is
// templated by the input and output image types.
//
// Software Guide : EndLatex

  // Software Guide : BeginCodeSnippet
  typedef otb::ScalarImageToPanTexTextureFilter
  <ImageType, ImageType> PanTexTextureFilterType;
  // Software Guide : EndCodeSnippet
  typedef otb::ImageFileReader<ImageType> ReaderType;
  typedef otb::ImageFileWriter<ImageType> WriterType;

  ReaderType::Pointer reader  = ReaderType::New();
  WriterType::Pointer writer = WriterType::New();

  reader->SetFileName(infname);
  writer->SetFileName(outfname);

  // Software Guide : BeginLatex
//
// We can now instatiate the filter.
//
// Software Guide : EndLatex

  // Software Guide : BeginCodeSnippet
  PanTexTextureFilterType::Pointer textureFilter = PanTexTextureFilterType::New();
  // Software Guide : EndCodeSnippet

  // Software Guide : BeginLatex
  //
  // Then, we set the parameters of the filter.The radius of
  // the neighborhood to compute the texture.
  // The number of bins per axis for histogram generation (it is the
  // size of the co-occurrence matrix). Moreover, we have to specify
  // the Min/Max in the input image. In the example, image Min/Max is set
  // by the user to 0 and 255. Alternatively you can use the class \doxygen{itk}{MinimumMaximumImageCalculator}
  // to calculate these values.
  //
  // Software Guide : EndLatex

  // Software Guide : BeginCodeSnippet
  PanTexTextureFilterType::SizeType sradius;
  sradius.Fill(4);
  textureFilter->SetNumberOfBinsPerAxis(8);
  textureFilter->SetRadius(sradius);
  textureFilter->SetInputImageMinimum(0);
  textureFilter->SetInputImageMaximum(255);
  // Software Guide : EndCodeSnippet

  // Software Guide : BeginLatex
  //
  // We can now plug the pipeline and trigger the execution by calling
  // the \code{Update} method of the writer.
  //
  // Software Guide : EndLatex
  // Software Guide : BeginCodeSnippet
  textureFilter->SetInput(reader->GetOutput());
  writer->SetInput(textureFilter->GetOutput());

  writer->Update();
  // Software Guide : EndCodeSnippet

  //  Software Guide : BeginLatex
  // Figure~\ref{fig:PANTEXFILTER} shows the result of applying
  // the PanTex computation.
  // \begin{figure}
  // \center
  // \includegraphics[width=0.40\textwidth]{pretty_PanTexInput.eps}
  // \includegraphics[width=0.40\textwidth]{pretty_PanTexOutput.eps}
  // \itkcaption[PanTex Filter]{Result of applying the
  // \doxygen{otb}{ScalarImageToPanTexTextureFilter} to an image. From left to right:
  // original image, PanTex feature.}
  // \label{fig:PANTEXFILTER}
  // \end{figure}
  //
  //  Software Guide : EndLatex

  // Pretty image creation for printing

  typedef otb::Image<unsigned char,
      Dimension>
  OutputPrettyImageType;
  typedef otb::ImageFileWriter<OutputPrettyImageType>
  WriterPrettyOutputType;
  typedef itk::RescaleIntensityImageFilter<ImageType,
      OutputPrettyImageType>
  RescalerOutputType;

  RescalerOutputType::Pointer     outputRescaler     = RescalerOutputType::New();
  WriterPrettyOutputType::Pointer prettyOutputWriter =
    WriterPrettyOutputType::New();
  outputRescaler->SetInput(textureFilter->GetOutput());
  outputRescaler->SetOutputMinimum(0);
  outputRescaler->SetOutputMaximum(255);
  prettyOutputWriter->SetFileName(outprettyfname);
  prettyOutputWriter->SetInput(outputRescaler->GetOutput());

  prettyOutputWriter->Update();

  outputRescaler->SetInput(reader->GetOutput());
  outputRescaler->SetOutputMinimum(0);
  outputRescaler->SetOutputMaximum(255);
  prettyOutputWriter->SetFileName(inprettyfname);
  prettyOutputWriter->SetInput(outputRescaler->GetOutput());

  prettyOutputWriter->Update();

  return EXIT_SUCCESS;
}
