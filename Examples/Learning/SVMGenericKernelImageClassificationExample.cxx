/*
 * Copyright (C) 2005-2016 Centre National d'Etudes Spatiales (CNES)
 * Copyright (C) 2007-2012 Institut Mines Telecom / Telecom Bretagne
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



#include <fstream>

#include "otbImageFileReader.h"
#include "otbImageFileWriter.h"
#include "itkRescaleIntensityImageFilter.h"
#include "otbImage.h"
#include "otbVectorImage.h"

//  Software Guide : BeginLatex
// This example illustrates the modifications to be added to use the
// \doxygen{otb}{SVMClassifier} class for performing SVM
// classification on images with a user-defined kernel.
// In this example, we will use an SVM model estimated in the previous
// section to separate between water and non-water pixels by using the RGB
// values only.
// The first thing to do is include the header file for the
// class as well as the header of the appropriated kernel to be used.
//
//
//  Software Guide : EndLatex

#include "itkImageToListSampleAdaptor.h"

//  Software Guide : BeginCodeSnippet
#include "otbSVMClassifier.h"
#include "otbMixturePolyRBFKernelFunctor.h"
//  Software Guide : EndCodeSnippet

int main(int argc, char* argv[])
{

  if (argc != 4)
    {
    std::cout << "Usage : " << argv[0]
              << " inputImage outputImage modelFile " << std::endl;
    return EXIT_FAILURE;
    }

  const char * imageFilename  = argv[1];
  const char * modelFilename  = argv[3];
  const char * outputFilename = argv[2];

  typedef double                 PixelType;
  typedef int                    LabelPixelType;

  const unsigned int Dimension = 2;

  typedef otb::Image<itk::FixedArray<PixelType, 3>,
      Dimension>          InputImageType;

  typedef otb::ImageFileReader<InputImageType> ReaderType;

  ReaderType::Pointer reader = ReaderType::New();
  reader->SetFileName(imageFilename);
  reader->Update();

  typedef itk::Statistics::ImageToListSampleAdaptor<InputImageType> SampleType;
  SampleType::Pointer sample = SampleType::New();
  sample->SetImage(reader->GetOutput());

// Software Guide : BeginLatex
//
// We need to declare the SVM model which is to be used by the
// classifier. The SVM model is templated over the type of value used
// for the measures and the type of pixel used for the labels.
//
// Software Guide : EndLatex

// Software Guide : BeginCodeSnippet
  typedef otb::SVMModel<PixelType, LabelPixelType> ModelType;
  ModelType::Pointer model = ModelType::New();
// Software Guide : EndCodeSnippet

// Software Guide : BeginLatex
//
// After instantiation, we can load a model saved to a file (see
// section \ref{ssec:LearningFromImages} for an example of model
// estimation and storage to a file).
//
// When using a user defined kernel, an explicit instantiation has
// to be performed.
//
// Software Guide : EndLatex

// Software Guide : BeginCodeSnippet
  otb::MixturePolyRBFKernelFunctor myKernel;
  model->SetKernelFunctor(&myKernel);
// Software Guide : EndCodeSnippet

// Software Guide : BeginLatex
//
// Then, the rest of the classification program remains unchanged.
//
// Software Guide : EndLatex

// Software Guide : BeginCodeSnippet
  model->LoadModel(modelFilename);
// Software Guide : EndCodeSnippet

  typedef otb::SVMClassifier<SampleType, LabelPixelType> ClassifierType;
  ClassifierType::Pointer classifier = ClassifierType::New();

  int numberOfClasses = model->GetNumberOfClasses();
  classifier->SetNumberOfClasses(numberOfClasses);
  classifier->SetModel(model);
  classifier->SetInput(sample.GetPointer());
  classifier->Update();

  typedef ClassifierType::ClassLabelType         OutputPixelType;
  typedef otb::Image<OutputPixelType, Dimension> OutputImageType;

  OutputImageType::Pointer outputImage = OutputImageType::New();

  typedef itk::Index<Dimension>       myIndexType;
  typedef itk::Size<Dimension>        mySizeType;
  typedef itk::ImageRegion<Dimension> myRegionType;

  mySizeType size;
  size[0] = reader->GetOutput()->GetRequestedRegion().GetSize()[0];
  size[1] = reader->GetOutput()->GetRequestedRegion().GetSize()[1];

  myIndexType start;
  start[0] = 0;
  start[1] = 0;

  myRegionType region;
  region.SetIndex(start);
  region.SetSize(size);

  outputImage->SetRegions(region);
  outputImage->Allocate();

  ClassifierType::OutputType* membershipSample =
    classifier->GetOutput();
  ClassifierType::OutputType::ConstIterator m_iter =
    membershipSample->Begin();
  ClassifierType::OutputType::ConstIterator m_last =
    membershipSample->End();

  typedef itk::ImageRegionIterator<OutputImageType> OutputIteratorType;
  OutputIteratorType outIt(outputImage,
                           outputImage->GetBufferedRegion());

  outIt.GoToBegin();

  while (m_iter != m_last && !outIt.IsAtEnd())
    {
    outIt.Set(m_iter.GetClassLabel());
    ++m_iter;
    ++outIt;
    }

  typedef otb::Image<unsigned char, Dimension> FileImageType;
  typedef itk::RescaleIntensityImageFilter<OutputImageType,
      FileImageType> RescalerType;

  RescalerType::Pointer rescaler = RescalerType::New();
  rescaler->SetOutputMinimum(itk::NumericTraits<unsigned char>::min());
  rescaler->SetOutputMaximum(itk::NumericTraits<unsigned char>::max());
  rescaler->SetInput(outputImage);

  typedef otb::ImageFileWriter<FileImageType> WriterType;

  WriterType::Pointer writer = WriterType::New();
  writer->SetFileName(outputFilename);
  writer->SetInput(rescaler->GetOutput());
  writer->Update();

  return EXIT_SUCCESS;
}
