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


#include <iostream>

#include "otbImage.h"
#include "otbImageFileReader.h"
#include "otbImageFileWriter.h"
#include "otbCommandProgressUpdate.h"
#include "otbCommandLineArgumentParser.h"

#include "otbKullbackLeiblerSupervizedDistanceImageFilter.h"

int main(int argc, char * argv[])
{
  try
    {

    typedef otb::CommandLineArgumentParser ParserType;
    ParserType::Pointer parser = ParserType::New();
    parser->AddOption("--InputImage1", "Give Before image", "-1", 1, true);
    parser->AddOption("--InputImage2", "Give After image", "-2", 1, true);
    parser->AddOption("--Roi", "Give ROI image", "-r", 1, true);
    parser->AddOption("--winSize",
                      "Sliding window size (def. 35)",
                      "-w",
                      1,
                      false);
    parser->AddOutputImage();

    typedef otb::CommandLineArgumentParseResult ParserResultType;
    ParserResultType::Pointer parseResult = ParserResultType::New();

    try
      {
      parser->ParseCommandLine(argc, argv, parseResult);
      }
    catch (itk::ExceptionObject& err)
      {
      std::string descriptionException = err.GetDescription();
      if (descriptionException.find("ParseCommandLine(): Help Parser")
          != std::string::npos) return EXIT_SUCCESS;
      if (descriptionException.find("ParseCommandLine(): Version Parser")
          != std::string::npos) return EXIT_SUCCESS;
      return EXIT_FAILURE;
      }

    /*
     *  Types declaration
     */

    const unsigned int Dimension = 2;

    typedef double        InputPixelType;
    typedef unsigned char TrainingPixelType;

    typedef otb::Image<InputPixelType, Dimension> ImageType;
    typedef otb::ImageFileReader<ImageType>       ReaderType;

    typedef otb::Image<TrainingPixelType, Dimension> TrainingImageType;
    typedef otb::ImageFileReader<TrainingImageType>  TrainingReaderType;

    /*
     * Extract command line parameters
     */

    std::string inputImageFileName1 = parseResult->GetParameterString(
      "--InputImage1");
    std::string inputImageFileName2 = parseResult->GetParameterString(
      "--InputImage2");
    std::string inputTrainingImageFileName = parseResult->GetParameterString(
      "--Roi");
    std::string outputImageFileName = parseResult->GetOutputImage();

    int winSize = 35;
    if (parseResult->IsOptionPresent("--winSize"))
      winSize =
        parseResult->GetParameterInt("--winSize");

    /*
     *  JustDoIt
     */

    ImageType::Pointer  img1 = ImageType::New();
    ReaderType::Pointer reader1 = ReaderType::New();
    reader1->SetFileName(inputImageFileName1);
    //reader1->Update();
    img1 = reader1->GetOutput();

    ImageType::Pointer  img2 = ImageType::New();
    ReaderType::Pointer reader2 = ReaderType::New();
    reader2->SetFileName(inputImageFileName2);
    //reader2->Update();
    img2 = reader2->GetOutput();

    TrainingImageType::Pointer  imgRoi = TrainingImageType::New();
    TrainingReaderType::Pointer readerRoi = TrainingReaderType::New();
    readerRoi->SetFileName(inputTrainingImageFileName);
    //readerRoi->Update();
    imgRoi = readerRoi->GetOutput();

    typedef otb::KullbackLeiblerSupervizedDistanceImageFilter<
        ImageType, ImageType, TrainingImageType, ImageType> FilterType;

    FilterType::Pointer changeDetector = FilterType::New();
    changeDetector->SetRadius((winSize - 1) / 2);
    changeDetector->SetInput1(img1);
    changeDetector->SetInput2(img2);

    // Once img1 and img2 are connected, it is time to connect imgRoi
    // to perform the parameters estimation of the non-changed area.

    changeDetector->SetTrainingArea(imgRoi);

    typedef otb::CommandProgressUpdate<FilterType> CommandType;
    CommandType::Pointer observer = CommandType::New();
    changeDetector->AddObserver(itk::ProgressEvent(), observer);

    typedef otb::ImageFileWriter<ImageType> WriterType;
    WriterType::Pointer writer = WriterType::New();
    writer->SetFileName(outputImageFileName);
    writer->SetInput(changeDetector->GetOutput());

    writer->Update();

    }
  catch (itk::ExceptionObject& err)
    {
    std::cerr << "ExceptionObject caught !" << std::endl;
    std::cerr << err << std::endl << std::endl;
    return EXIT_FAILURE;
    }

  return EXIT_SUCCESS;
}
