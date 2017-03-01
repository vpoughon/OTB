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
#include "otbCommandProgressUpdate.h"
#include "otbCommandLineArgumentParser.h"

#include "otbMNFImageFilter.h"

#include "otbLocalActivityVectorImageFilter.h"

int otbMNFImageFilterNewTest ( int itkNotUsed(argc), char* itkNotUsed(argv) [] )
{
  const unsigned int Dimension = 2;
  typedef double PixelType;
  typedef otb::VectorImage< PixelType, Dimension > ImageType;

  typedef otb::LocalActivityVectorImageFilter< ImageType, ImageType > NoiseFilterType;

  typedef otb::MNFImageFilter< ImageType, ImageType,
    NoiseFilterType, otb::Transform::FORWARD > FilterType;
  FilterType::Pointer filter = FilterType::New();

  typedef otb::MNFImageFilter< ImageType, ImageType,
      NoiseFilterType, otb::Transform::INVERSE > InvFilterType;
    InvFilterType::Pointer invFilter = InvFilterType::New();

  return EXIT_SUCCESS;
}

int otbMNFImageFilterTest ( int argc, char* argv[] )
{
  typedef otb::CommandLineArgumentParser ParserType;
  ParserType::Pointer parser = ParserType::New();

  parser->AddInputImage();
  parser->AddOption( "--NumComponents", "Number of components to keep for output", "-n", 1, false );
  parser->AddOption( "--Inverse", "Performs also the inverse transformation (give the output name)", "-inv", 1, false );
  parser->AddOption( "--Radius", "Set the radius of the sliding window (def.1)", "-r", 2, false );
  parser->AddOption( "--Normalize", "center and reduce data before MNF", "-norm", 0, false );
  parser->AddOutputImage();

  typedef otb::CommandLineArgumentParseResult ParserResultType;
  ParserResultType::Pointer  parseResult = ParserResultType::New();

  try
  {
    parser->ParseCommandLine( argc, argv, parseResult );
  }
  catch( itk::ExceptionObject & err )
  {
    std::cerr << argv[0] << " applies MNF transformations\n";
    std::string descriptionException = err.GetDescription();
    if ( descriptionException.find("ParseCommandLine(): Help Parser")
        != std::string::npos )
      return EXIT_SUCCESS;
    if(descriptionException.find("ParseCommandLine(): Version Parser")
        != std::string::npos )
      return EXIT_SUCCESS;
    return EXIT_FAILURE;
  }

  std::string inputImageName = parseResult->GetInputImage();
  std::string outputImageName = parseResult->GetOutputImage();
  const unsigned int nbComponents = parseResult->IsOptionPresent("--NumComponents") ?
    parseResult->GetParameterUInt("--NumComponents") : 0;
  unsigned int radiusX = 1;
  unsigned int radiusY = 1;
  if ( parseResult->IsOptionPresent("--Radius") )
  {
    radiusX = parseResult->GetParameterUInt("--Radius", 0);
    radiusY = parseResult->GetParameterUInt("--Radius", 1);
  }
  const bool normalization = parseResult->IsOptionPresent("--Normalize");

  // Main type definition
  const unsigned int Dimension = 2;
  typedef double PixelType;
  typedef otb::VectorImage< PixelType, Dimension > ImageType;

  // Reading input images
  typedef otb::ImageFileReader<ImageType> ReaderType;
  ReaderType::Pointer reader = ReaderType::New();
  reader->SetFileName(inputImageName);

  // Noise filtering
  typedef otb::LocalActivityVectorImageFilter< ImageType, ImageType > NoiseFilterType;
  NoiseFilterType::RadiusType radius = {{ radiusX, radiusY }};

  // Image filtering
  typedef otb::MNFImageFilter< ImageType, ImageType,
    NoiseFilterType, otb::Transform::FORWARD > FilterType;
  FilterType::Pointer filter = FilterType::New();
  filter->SetInput( reader->GetOutput() );
  filter->SetNumberOfPrincipalComponentsRequired( nbComponents );
  filter->SetUseNormalization( normalization );
  filter->GetNoiseImageFilter()->SetRadius( radius );

  typedef otb::CommandProgressUpdate< FilterType > CommandType;
  CommandType::Pointer observer = CommandType::New();
  filter->AddObserver( itk::ProgressEvent(), observer );

  // Writing
  typedef otb::ImageFileWriter< ImageType > ImageWriterType;
  ImageWriterType::Pointer writer = ImageWriterType::New();
  writer->SetFileName( outputImageName );
  writer->SetInput( filter->GetOutput() );
  writer->Update();


  if ( parseResult->IsOptionPresent("--Inverse") )
  {
    typedef otb::MNFImageFilter< ImageType, ImageType,
      NoiseFilterType, otb::Transform::INVERSE > InvFilterType;
    InvFilterType::Pointer invFilter = InvFilterType::New();
    invFilter->SetInput( filter->GetOutput() );
    invFilter->SetMeanValues( filter->GetMeanValues() );
    if ( normalization )
      invFilter->SetStdDevValues( filter->GetStdDevValues() );
    invFilter->SetTransformationMatrix( filter->GetTransformationMatrix() );

    typedef otb::CommandProgressUpdate< InvFilterType > CommandType2;
    CommandType2::Pointer invObserver = CommandType2::New();
    invFilter->AddObserver( itk::ProgressEvent(), invObserver );

    ImageWriterType::Pointer invWriter = ImageWriterType::New();
    invWriter->SetFileName( parseResult->GetParameterString("--Inverse") );
    invWriter->SetInput( invFilter->GetOutput() );
    invWriter->Update();
  }

  return EXIT_SUCCESS;
}
