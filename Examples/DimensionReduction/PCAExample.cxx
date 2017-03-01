/*=========================================================================

  Program:   ORFEO Toolbox
  Language:  C++


  Copyright (c) Centre National d'Etudes Spatiales. All rights reserved.
  See OTBCopyright.txt for details.


  This software is distributed WITHOUT ANY WARRANTY; without even
  the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
  PURPOSE.  See the above copyright notices for more information.

=========================================================================*/
#include "otbVectorImage.h"
#include "otbImageFileReader.h"
#include "otbImageFileWriter.h"
#include "otbPrintableImageFilter.h"

//  Software Guide : BeginCommandLineArgs
//    INPUTS: {wv2_cannes_8bands.tif}
//    OUTPUTS: {PCAOutput.tif}, {InversePCAOutput.tif}, {input-pretty.png}, {output-pretty.png}, {invoutput-pretty.png}
//    8
//  Software Guide : EndCommandLineArgs

// Software Guide : BeginLatex
//
// This example illustrates the use of the
// \doxygen{otb}{PCAImageFilter}.
// This filter computes a Principal Component Analysis using an
// efficient method based on the inner product in order to compute the
// covariance matrix.
//
// The first step required to use this filter is to include its header file.
//
// Software Guide : EndLatex

// Software Guide : BeginCodeSnippet
#include "otbPCAImageFilter.h"
// Software Guide : EndCodeSnippet

int main(int itkNotUsed(argc), char* argv[])
{
  typedef double PixelType;
  const unsigned int Dimension = 2;
  const char *       inputFileName = argv[1];
  const char *       outputFilename = argv[2];
  const char *       outputInverseFilename = argv[3];
  const unsigned int numberOfPrincipalComponentsRequired(atoi(argv[7]));
  const char *       inpretty = argv[4];
  const char *       outpretty = argv[5];
  const char *       invoutpretty = argv[6];


  // Software Guide : BeginLatex
  //
  // We start by defining the types for the images and the reader and
  // the writer. We choose to work with a \doxygen{otb}{VectorImage},
  // since we will produce a multi-channel image (the principal
  // components) from a multi-channel input image.
  //
  // Software Guide : EndLatex

  // Software Guide : BeginCodeSnippet
  typedef otb::VectorImage<PixelType, Dimension> ImageType;
  typedef otb::ImageFileReader<ImageType>        ReaderType;
  typedef otb::ImageFileWriter<ImageType>        WriterType;
  // Software Guide : EndCodeSnippet
  // Software Guide : BeginLatex
  //
  // We instantiate now the image reader and we set the image file name.
  //
  // Software Guide : EndLatex

  // Software Guide : BeginCodeSnippet
  ReaderType::Pointer reader     = ReaderType::New();
  reader->SetFileName(inputFileName);
  // Software Guide : EndCodeSnippet
  // Software Guide : BeginLatex
  //
  // We define the type for the filter. It is templated over the input
  // and the output image types and also the transformation direction. The
  // internal structure of this filter is a filter-to-filter like structure.
  // We can now the instantiate the filter.
  //
  // Software Guide : EndLatex

  // Software Guide : BeginCodeSnippet
  typedef otb::PCAImageFilter<ImageType, ImageType,
                              otb::Transform::FORWARD> PCAFilterType;
  PCAFilterType::Pointer pcafilter     = PCAFilterType::New();
  // Software Guide : EndCodeSnippet
  // Software Guide : BeginLatex
  //
  // The only parameter needed for the PCA is the number of principal
  // components required as output. Principal components are linear combination of input components
  // (here the input image  bands),
  // which are selected using Singular Value Decomposition eigen vectors sorted by eigen value.
  // We can choose to get less Principal Components than
  // the number of input bands.
  //
  // Software Guide : EndLatex

  // Software Guide : BeginCodeSnippet
  pcafilter->SetNumberOfPrincipalComponentsRequired(
    numberOfPrincipalComponentsRequired);
  // Software Guide : EndCodeSnippet
  // Software Guide : BeginLatex
  //
  // We now instantiate the writer and set the file name for the
  // output image.
  //
  // Software Guide : EndLatex

  // Software Guide : BeginCodeSnippet
  WriterType::Pointer writer     = WriterType::New();
  writer->SetFileName(outputFilename);
  // Software Guide : EndCodeSnippet
  // Software Guide : BeginLatex
  //
  // We finally plug the pipeline and trigger the PCA computation with
  // the method \code{Update()} of the writer.
  //
  // Software Guide : EndLatex

  // Software Guide : BeginCodeSnippet
  pcafilter->SetInput(reader->GetOutput());
  writer->SetInput(pcafilter->GetOutput());

  writer->Update();
  // Software Guide : EndCodeSnippet

  // Software Guide : BeginLatex
  //
  // \doxygen{otb}{PCAImageFilter} allows also to compute inverse
  // transformation from PCA coefficients. In reverse mode, the
  // covariance matrix or the transformation matrix
  // (which may not be square) has to be given.
  //
  // Software Guide : EndLatex

  // Software Guide : BeginCodeSnippet
  typedef otb::PCAImageFilter< ImageType, ImageType,
                               otb::Transform::INVERSE > InvPCAFilterType;
  InvPCAFilterType::Pointer invFilter = InvPCAFilterType::New();

  invFilter->SetInput(pcafilter->GetOutput());
  invFilter->SetTransformationMatrix(pcafilter->GetTransformationMatrix());

  WriterType::Pointer invWriter = WriterType::New();
  invWriter->SetFileName(outputInverseFilename );
  invWriter->SetInput(invFilter->GetOutput() );

  invWriter->Update();
  // Software Guide : EndCodeSnippet

  //  Software Guide : BeginLatex
  // Figure~\ref{fig:PCA_FILTER} shows the result of applying forward
  // and reverse PCA transformation to a 8 bands Worldview2 image.
  // \begin{figure}
  // \center
  // \includegraphics[width=0.32\textwidth]{input-pretty.eps}
  // \includegraphics[width=0.32\textwidth]{output-pretty.eps}
  // \includegraphics[width=0.32\textwidth]{invoutput-pretty.eps}
  // \itkcaption[PCA Filter (forward trasnformation)]{Result of applying the
  // \doxygen{otb}{PCAImageFilter} to an image. From left
  // to right:
  // original image, color composition with first three principal
  // components and output of the
  // inverse mode (the input RGB image).}
  // \label{fig:PCA_FILTER}
  // \end{figure}
  //
  //  Software Guide : EndLatex

  // This is for rendering in software guide
  typedef otb::PrintableImageFilter<ImageType,ImageType> PrintFilterType;
  typedef PrintFilterType::OutputImageType               VisuImageType;
  typedef otb::ImageFileWriter<VisuImageType>            VisuWriterType;

  PrintFilterType::Pointer inputPrintFilter = PrintFilterType::New();
  PrintFilterType::Pointer outputPrintFilter = PrintFilterType::New();
  PrintFilterType::Pointer invertOutputPrintFilter = PrintFilterType::New();
  VisuWriterType::Pointer inputVisuWriter = VisuWriterType::New();
  VisuWriterType::Pointer outputVisuWriter = VisuWriterType::New();
  VisuWriterType::Pointer invertOutputVisuWriter = VisuWriterType::New();

  inputPrintFilter->SetInput(reader->GetOutput());
  inputPrintFilter->SetChannel(5);
  inputPrintFilter->SetChannel(3);
  inputPrintFilter->SetChannel(2);
  outputPrintFilter->SetInput(pcafilter->GetOutput());
  outputPrintFilter->SetChannel(1);
  outputPrintFilter->SetChannel(2);
  outputPrintFilter->SetChannel(3);
  invertOutputPrintFilter->SetInput(invFilter->GetOutput());
  invertOutputPrintFilter->SetChannel(5);
  invertOutputPrintFilter->SetChannel(3);
  invertOutputPrintFilter->SetChannel(2);

  inputVisuWriter->SetInput(inputPrintFilter->GetOutput());
  outputVisuWriter->SetInput(outputPrintFilter->GetOutput());
  invertOutputVisuWriter->SetInput(invertOutputPrintFilter->GetOutput());

  inputVisuWriter->SetFileName(inpretty);
  outputVisuWriter->SetFileName(outpretty);
  invertOutputVisuWriter->SetFileName(invoutpretty);

  inputVisuWriter->Update();
  outputVisuWriter->Update();
  invertOutputVisuWriter->Update();

  return EXIT_SUCCESS;
}
