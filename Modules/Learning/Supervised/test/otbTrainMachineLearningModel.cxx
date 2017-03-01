/*=========================================================================

 Program:   ORFEO Toolbox
 Language:  C++


 Copyright (c) Centre National d'Etudes Spatiales. All rights reserved.
 See OTBCopyright.txt for details.


 This software is distributed WITHOUT ANY WARRANTY; without even
 the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
 PURPOSE.  See the above copyright notices for more information.

 =========================================================================*/

#include <fstream>
#include <string>
#include <algorithm>

#include <otbMachineLearningModel.h>
#include "otbConfusionMatrixCalculator.h"

#include "otb_boost_string_header.h"

typedef otb::MachineLearningModel<float,short>         MachineLearningModelType;
typedef MachineLearningModelType::InputValueType       InputValueType;
typedef MachineLearningModelType::InputSampleType      InputSampleType;
typedef MachineLearningModelType::InputListSampleType  InputListSampleType;
typedef MachineLearningModelType::TargetValueType      TargetValueType;
typedef MachineLearningModelType::TargetSampleType     TargetSampleType;
typedef MachineLearningModelType::TargetListSampleType TargetListSampleType;

typedef otb::MachineLearningModel<float,float>                   MachineLearningModelRegressionType;
typedef MachineLearningModelRegressionType::InputValueType       InputValueRegressionType;
typedef MachineLearningModelRegressionType::InputSampleType      InputSampleRegressionType;
typedef MachineLearningModelRegressionType::InputListSampleType  InputListSampleRegressionType;
typedef MachineLearningModelRegressionType::TargetValueType      TargetValueRegressionType;
typedef MachineLearningModelRegressionType::TargetSampleType     TargetSampleRegressionType;
typedef MachineLearningModelRegressionType::TargetListSampleType TargetListSampleRegressionType;

typedef otb::ConfusionMatrixCalculator<TargetListSampleType, TargetListSampleType> ConfusionMatrixCalculatorType;

bool ReadDataFile(const std::string & infname, InputListSampleType * samples, TargetListSampleType * labels)
{
  std::ifstream ifs;
  ifs.open(infname.c_str());

  if(!ifs)
    {
    std::cout<<"Could not read file "<<infname<<std::endl;
    return false;
    }

  unsigned int nbfeatures = 0;

  while (!ifs.eof())
    {
    std::string line;
    std::getline(ifs, line);
    boost::algorithm::trim(line);

    if(nbfeatures == 0)
      {
      nbfeatures = std::count(line.begin(),line.end(),' ');
      }

    if(line.size()>1)
      {
      InputSampleType sample(nbfeatures);
      sample.Fill(0);

      std::string::size_type pos = line.find_first_of(" ", 0);

      // Parse label
      TargetSampleType label;
      label[0] = atoi(line.substr(0, pos).c_str());

      bool endOfLine = false;
      unsigned int id = 0;

      while(!endOfLine)
        {
        std::string::size_type nextpos = line.find_first_of(" ", pos+1);

        if(pos == std::string::npos)
          {
          endOfLine = true;
          nextpos = line.size()-1;
          }
        else
          {
          std::string feature = line.substr(pos,nextpos-pos);
          std::string::size_type semicolonpos = feature.find_first_of(":");
          id = atoi(feature.substr(0,semicolonpos).c_str());
          sample[id - 1] = atof(feature.substr(semicolonpos+1,feature.size()-semicolonpos).c_str());
          pos = nextpos;
          }

        }
      samples->SetMeasurementVectorSize(itk::NumericTraits<InputSampleType>::GetLength(sample));
      samples->PushBack(sample);
      labels->PushBack(label);
      }
    }

  //std::cout<<"Retrieved "<<samples->Size()<<" samples"<<std::endl;
  ifs.close();
  return true;
}

bool ReadDataRegressionFile(const std::string & infname, InputListSampleRegressionType * samples, TargetListSampleRegressionType * labels)
{
  std::ifstream ifs;
  ifs.open(infname.c_str());

  if(!ifs)
    {
    std::cout<<"Could not read file "<<infname<<std::endl;
    return false;
    }

  unsigned int nbfeatures = 0;

  while (!ifs.eof())
    {
    std::string line;
    std::getline(ifs, line);

    if(nbfeatures == 0)
      {
      nbfeatures = std::count(line.begin(),line.end(),' ')-1;
      //std::cout<<"Found "<<nbfeatures<<" features per samples"<<std::endl;
      }

    if(line.size()>1)
      {
      InputSampleRegressionType sample(nbfeatures);
      sample.Fill(0);

      std::string::size_type pos = line.find_first_of(" ", 0);

      // Parse label
      TargetSampleRegressionType label;
      label[0] = atof(line.substr(0, pos).c_str());

      bool endOfLine = false;
      unsigned int id = 0;

      while(!endOfLine)
        {
        std::string::size_type nextpos = line.find_first_of(" ", pos+1);

        if(nextpos == std::string::npos)
          {
          endOfLine = true;
          nextpos = line.size()-1;
          }
        else
          {
          std::string feature = line.substr(pos,nextpos-pos);
          std::string::size_type semicolonpos = feature.find_first_of(":");
          id = atoi(feature.substr(0,semicolonpos).c_str());
          sample[id - 1] = atof(feature.substr(semicolonpos+1,feature.size()-semicolonpos).c_str());
          pos = nextpos;
          }

        }
      samples->SetMeasurementVectorSize(itk::NumericTraits<InputSampleRegressionType>::GetLength(sample));
      samples->PushBack(sample);
      labels->PushBack(label);
      }
    }

  //std::cout<<"Retrieved "<<samples->Size()<<" samples"<<std::endl;
  ifs.close();
  return true;
}

#ifdef OTB_USE_LIBSVM
#include "otbLibSVMMachineLearningModel.h"
int otbLibSVMMachineLearningModelNew(int itkNotUsed(argc), char * itkNotUsed(argv) [])
{
  typedef otb::LibSVMMachineLearningModel<InputValueType, TargetValueType> SVMType;
  SVMType::Pointer svmclassifier = SVMType::New();
  return EXIT_SUCCESS;
}

int otbLibSVMMachineLearningModel(int argc, char * argv[])
{
  if (argc != 3)
    {
      std::cout<<"Wrong number of arguments "<<std::endl;
      std::cout<<"Usage : sample file, output file "<<std::endl;
      return EXIT_FAILURE;
    }


  typedef otb::LibSVMMachineLearningModel<InputValueType, TargetValueType> SVMType;
  InputListSampleType::Pointer samples = InputListSampleType::New();
  TargetListSampleType::Pointer labels = TargetListSampleType::New();
  TargetListSampleType::Pointer predicted = TargetListSampleType::New();

  if (!ReadDataFile(argv[1], samples, labels))
    {
    std::cout << "Failed to read samples file " << argv[1] << std::endl;
    return EXIT_FAILURE;
    }

  SVMType::Pointer classifier = SVMType::New();
  classifier->SetInputListSample(samples);
  classifier->SetTargetListSample(labels);
  classifier->Train();

  classifier->SetTargetListSample(predicted);
  classifier->PredictAll();

  ConfusionMatrixCalculatorType::Pointer cmCalculator = ConfusionMatrixCalculatorType::New();

  cmCalculator->SetProducedLabels(predicted);
  cmCalculator->SetReferenceLabels(labels);
  cmCalculator->Compute();

  std::cout << "Confusion matrix: " << std::endl;
  std::cout << cmCalculator->GetConfusionMatrix() << std::endl;
  const float kappaIdx = cmCalculator->GetKappaIndex();
  std::cout<<"Kappa: "<<kappaIdx<<std::endl;
  std::cout << "Overall Accuracy: " << cmCalculator->GetOverallAccuracy() << std::endl;

  classifier->Save(argv[2]);

  //Load Model to new LibSVM
  TargetListSampleType::Pointer predictedLoad = TargetListSampleType::New();
  SVMType::Pointer classifierLoad = SVMType::New();

  classifierLoad->Load(argv[2]);
  classifierLoad->SetInputListSample(samples);
  classifierLoad->SetTargetListSample(predictedLoad);
  classifierLoad->PredictAll();

  ConfusionMatrixCalculatorType::Pointer cmCalculatorLoad = ConfusionMatrixCalculatorType::New();

  cmCalculatorLoad->SetProducedLabels(predictedLoad);
  cmCalculatorLoad->SetReferenceLabels(labels);
  cmCalculatorLoad->Compute();

  std::cout<<"Confusion matrix: "<<std::endl;
  std::cout<<cmCalculatorLoad->GetConfusionMatrix()<<std::endl;
  const float kappaIdxLoad = cmCalculatorLoad->GetKappaIndex();
  std::cout<<"Kappa: "<<kappaIdxLoad<<std::endl;
  std::cout<<"Overall Accuracy: "<<cmCalculatorLoad->GetOverallAccuracy()<<std::endl;


  if ( vcl_abs(kappaIdxLoad - kappaIdx) < 0.00000001)
    {
    return EXIT_SUCCESS;
    }
  else
    {
    return EXIT_FAILURE;
    }
}
#endif

#ifdef OTB_USE_OPENCV
#include "otbSVMMachineLearningModel.h"
#include "otbKNearestNeighborsMachineLearningModel.h"
#include "otbRandomForestsMachineLearningModel.h"
#include "otbBoostMachineLearningModel.h"
#include "otbNeuralNetworkMachineLearningModel.h"
#include "otbNormalBayesMachineLearningModel.h"
#include "otbDecisionTreeMachineLearningModel.h"
#include "otbGradientBoostedTreeMachineLearningModel.h"
#include "otbKNearestNeighborsMachineLearningModel.h"

int otbSVMMachineLearningModelNew(int itkNotUsed(argc), char * itkNotUsed(argv) [])
{
  typedef otb::SVMMachineLearningModel<InputValueType,TargetValueType> SVMType;
  SVMType::Pointer svmclassifier = SVMType::New();
  return EXIT_SUCCESS;
}

int otbSVMMachineLearningModel(int argc, char * argv[])
{
  if (argc != 3 )
    {
      std::cout<<"Wrong number of arguments "<<std::endl;
      std::cout<<"Usage : sample file, output file "<<std::endl;
      return EXIT_FAILURE;
    }

  typedef otb::SVMMachineLearningModel<InputValueType, TargetValueType> SVMType;

  InputListSampleType::Pointer samples = InputListSampleType::New();
  TargetListSampleType::Pointer labels = TargetListSampleType::New();
  TargetListSampleType::Pointer predicted = TargetListSampleType::New();

  if(!ReadDataFile(argv[1],samples,labels))
    {
    std::cout<<"Failed to read samples file "<<argv[1]<<std::endl;
    return EXIT_FAILURE;
    }

  SVMType::Pointer classifier = SVMType::New();
  classifier->SetInputListSample(samples);
  classifier->SetTargetListSample(labels);
  classifier->Train();

  classifier->SetTargetListSample(predicted);
  classifier->PredictAll();

  classifier->Save(argv[2]);

  ConfusionMatrixCalculatorType::Pointer cmCalculator = ConfusionMatrixCalculatorType::New();

  cmCalculator->SetProducedLabels(predicted);
  cmCalculator->SetReferenceLabels(labels);
  cmCalculator->Compute();

  std::cout<<"Confusion matrix: "<<std::endl;
  std::cout<<cmCalculator->GetConfusionMatrix()<<std::endl;
  const float kappaIdx = cmCalculator->GetKappaIndex();
  std::cout<<"Kappa: "<<kappaIdx<<std::endl;
  std::cout<<"Overall Accuracy: "<<cmCalculator->GetOverallAccuracy()<<std::endl;

  //Load Model to new SVM
  TargetListSampleType::Pointer predictedLoad = TargetListSampleType::New();
  SVMType::Pointer classifierLoad = SVMType::New();

  classifierLoad->Load(argv[2]);
  classifierLoad->SetInputListSample(samples);
  classifierLoad->SetTargetListSample(predictedLoad);
  classifierLoad->PredictAll();

  ConfusionMatrixCalculatorType::Pointer cmCalculatorLoad = ConfusionMatrixCalculatorType::New();

  cmCalculatorLoad->SetProducedLabels(predictedLoad);
  cmCalculatorLoad->SetReferenceLabels(labels);
  cmCalculatorLoad->Compute();

  std::cout<<"Confusion matrix: "<<std::endl;
  std::cout<<cmCalculatorLoad->GetConfusionMatrix()<<std::endl;
  const float kappaIdxLoad = cmCalculatorLoad->GetKappaIndex();
  std::cout<<"Kappa: "<<kappaIdxLoad<<std::endl;
  std::cout<<"Overall Accuracy: "<<cmCalculatorLoad->GetOverallAccuracy()<<std::endl;


  if ( vcl_abs(kappaIdxLoad - kappaIdx) < 0.00000001)
    {
    return EXIT_SUCCESS;
    }
  else
    {
    return EXIT_FAILURE;
    }
}

int otbSVMMachineLearningRegressionModel(int argc, char * argv[])
{
  if (argc != 3 )
    {
      std::cout<<"Wrong number of arguments "<<std::endl;
      std::cout<<"Usage : sample file, output file "<<std::endl;
      return EXIT_FAILURE;
    }

  typedef otb::SVMMachineLearningModel<InputValueRegressionType, TargetValueRegressionType> SVMType;

  InputListSampleRegressionType::Pointer samples = InputListSampleRegressionType::New();
  TargetListSampleRegressionType::Pointer labels = TargetListSampleRegressionType::New();
  TargetListSampleRegressionType::Pointer predicted = TargetListSampleRegressionType::New();

  if(!ReadDataRegressionFile(argv[1],samples,labels))
    {
    std::cout<<"Failed to read samples file "<<argv[1]<<std::endl;
    return EXIT_FAILURE;
    }

  SVMType::Pointer classifier = SVMType::New();

  //Init SVM type in regression mode
  classifier->SetRegressionMode(1);
  classifier->SetSVMType(CvSVM::EPS_SVR);
  classifier->SetP(10);
  classifier->SetKernelType(CvSVM::RBF);


  classifier->SetInputListSample(samples);
  classifier->SetTargetListSample(labels);
  classifier->Train();

  //Predict age using first line of abalone dataset
  //1:-1 2:0.027027 3:0.0420168 4:-0.831858 5:-0.63733 6:-0.699395 7:-0.735352
  //8:-0.704036
  // Input value is 15.
  InputListSampleRegressionType::Pointer samplesT = InputListSampleRegressionType::New();

  //Init sample list to 8 (size of abalone dataset)
  InputSampleRegressionType sample(8);
  sample.Fill(0);
  sample[0] = -1;
  sample[1] = 0.027027;
  sample[2] = 0.0420168;
  sample[3] = -0.831858;
  sample[4] = -0.63733;
  sample[5] = -0.699395;
  sample[6] = -0.735352;
  sample[7] = -0.704036;

  samplesT->SetMeasurementVectorSize(itk::NumericTraits<InputSampleRegressionType>::GetLength(sample));
  samplesT->PushBack(sample);

  classifier->SetInputListSample(samplesT);
  classifier->SetTargetListSample(predicted);
  classifier->PredictAll();

  const float age = 15;

  if ( vcl_abs(age - predicted->GetMeasurementVector(0)[0]) <= 0.3 )
    {
    return EXIT_SUCCESS;
    }
  else
    {
    std::cout << age << "\t" << predicted->GetMeasurementVector(0)[0] << "\n";
    return EXIT_FAILURE;
    }
}

int otbKNearestNeighborsMachineLearningModelNew(int itkNotUsed(argc), char * itkNotUsed(argv) [])
{
  typedef otb::KNearestNeighborsMachineLearningModel<InputValueType,TargetValueType> KNearestNeighborsType;
  KNearestNeighborsType::Pointer knnclassifier = KNearestNeighborsType::New();
  return EXIT_SUCCESS;
}

int otbKNearestNeighborsMachineLearningModel(int argc, char * argv[])
{
  if (argc != 3 )
    {
    std::cout<<"Wrong number of arguments "<<std::endl;
    std::cout<<"Usage : sample file, output file"<<std::endl;
    return EXIT_FAILURE;
    }

  typedef otb::KNearestNeighborsMachineLearningModel<InputValueType,TargetValueType> KNearestNeighborsType;
  InputListSampleType::Pointer samples = InputListSampleType::New();
  TargetListSampleType::Pointer labels = TargetListSampleType::New();
  TargetListSampleType::Pointer predicted = TargetListSampleType::New();

  if(!ReadDataFile(argv[1],samples,labels))
    {
    std::cout<<"Failed to read samples file "<<argv[1]<<std::endl;
    return EXIT_FAILURE;
    }

  KNearestNeighborsType::Pointer classifier = KNearestNeighborsType::New();
  classifier->SetInputListSample(samples);
  classifier->SetTargetListSample(labels);
  classifier->Train();
  //write the model
  classifier->Save(argv[2]);

  classifier->SetTargetListSample(predicted);
  classifier->PredictAll();

  ConfusionMatrixCalculatorType::Pointer cmCalculator = ConfusionMatrixCalculatorType::New();

  cmCalculator->SetProducedLabels(predicted);
  cmCalculator->SetReferenceLabels(labels);
  cmCalculator->Compute();

  std::cout<<"Confusion matrix: "<<std::endl;
  std::cout<<cmCalculator->GetConfusionMatrix()<<std::endl;
  const float kappaIdx = cmCalculator->GetKappaIndex();
  std::cout<<"Kappa: "<<kappaIdx<<std::endl;
  std::cout<<"Overall Accuracy: "<<cmCalculator->GetOverallAccuracy()<<std::endl;


  //Load Model to new KNN
  TargetListSampleType::Pointer predictedLoad = TargetListSampleType::New();
  KNearestNeighborsType::Pointer classifierLoad = KNearestNeighborsType::New();

  classifierLoad->Load(argv[2]);
  classifierLoad->SetInputListSample(samples);
  classifierLoad->SetTargetListSample(predictedLoad);
  classifierLoad->PredictAll();

  ConfusionMatrixCalculatorType::Pointer cmCalculatorLoad = ConfusionMatrixCalculatorType::New();

  cmCalculatorLoad->SetProducedLabels(predictedLoad);
  cmCalculatorLoad->SetReferenceLabels(labels);
  cmCalculatorLoad->Compute();

  std::cout<<"Confusion matrix: "<<std::endl;
  std::cout<<cmCalculatorLoad->GetConfusionMatrix()<<std::endl;
  const float kappaIdxLoad = cmCalculatorLoad->GetKappaIndex();
  std::cout<<"Kappa: "<<kappaIdxLoad<<std::endl;
  std::cout<<"Overall Accuracy: "<<cmCalculatorLoad->GetOverallAccuracy()<<std::endl;


  if ( vcl_abs(kappaIdxLoad - kappaIdx) < 0.00000001)
    {
    return EXIT_SUCCESS;
    }
  else
    {
    return EXIT_FAILURE;
    }
}

int otbRandomForestsMachineLearningModelNew(int itkNotUsed(argc), char * itkNotUsed(argv) [])
{
  typedef otb::RandomForestsMachineLearningModel<InputValueType,TargetValueType> RandomForestType;
  RandomForestType::Pointer rfclassifier = RandomForestType::New();
  return EXIT_SUCCESS;
}

int otbRandomForestsMachineLearningModel(int argc, char * argv[])
{
  if (argc != 3 )
    {
    std::cout<<"Wrong number of arguments "<<std::endl;
    std::cout<<"Usage : sample file, output file "<<std::endl;
    return EXIT_FAILURE;
    }

  typedef otb::RandomForestsMachineLearningModel<InputValueType,TargetValueType> RandomForestType;
  InputListSampleType::Pointer samples = InputListSampleType::New();
  TargetListSampleType::Pointer labels = TargetListSampleType::New();
  TargetListSampleType::Pointer predicted = TargetListSampleType::New();

  if(!ReadDataFile(argv[1],samples,labels))
    {
    std::cout<<"Failed to read samples file "<<argv[1]<<std::endl;
    return EXIT_FAILURE;
    }

  std::vector<float> priors(26,1.);


  RandomForestType::Pointer classifier = RandomForestType::New();
  classifier->SetInputListSample(samples);
  classifier->SetTargetListSample(labels);

  //set parameters
  classifier->SetPriors(priors);
  // classifier->SetMaxNumberOfTrees(30);
  // classifier->SetMaxDepth(30);
  // classifier->SetMaxNumberOfCategories(30);
  // classifier->SetMaxNumberOfVariables(4);

  classifier->Train();
  classifier->Save(argv[2]);

  classifier->SetTargetListSample(predicted);
  classifier->PredictAll();

  ConfusionMatrixCalculatorType::Pointer cmCalculator = ConfusionMatrixCalculatorType::New();

  cmCalculator->SetProducedLabels(predicted);
  cmCalculator->SetReferenceLabels(labels);
  cmCalculator->Compute();

  std::cout<<"Confusion matrix: "<<std::endl;
  std::cout<<cmCalculator->GetConfusionMatrix()<<std::endl;
  const float kappaIdx = cmCalculator->GetKappaIndex();
  std::cout<<"Kappa: "<<kappaIdx<<std::endl;
  std::cout<<"Overall Accuracy: "<<cmCalculator->GetOverallAccuracy()<<std::endl;

  //Load Model to new RF
  TargetListSampleType::Pointer predictedLoad = TargetListSampleType::New();
  RandomForestType::Pointer classifierLoad = RandomForestType::New();

  classifierLoad->Load(argv[2]);
  classifierLoad->SetInputListSample(samples);
  classifierLoad->SetTargetListSample(predictedLoad);
  classifierLoad->PredictAll();

  ConfusionMatrixCalculatorType::Pointer cmCalculatorLoad = ConfusionMatrixCalculatorType::New();

  cmCalculatorLoad->SetProducedLabels(predictedLoad);
  cmCalculatorLoad->SetReferenceLabels(labels);
  cmCalculatorLoad->Compute();

  std::cout<<"Confusion matrix: "<<std::endl;
  std::cout<<cmCalculatorLoad->GetConfusionMatrix()<<std::endl;
  const float kappaIdxLoad = cmCalculatorLoad->GetKappaIndex();
  std::cout<<"Kappa: "<<kappaIdxLoad<<std::endl;
  std::cout<<"Overall Accuracy: "<<cmCalculatorLoad->GetOverallAccuracy()<<std::endl;


  if ( vcl_abs(kappaIdxLoad - kappaIdx) < 0.00000001)
    {
    return EXIT_SUCCESS;
    }
  else
    {
    return EXIT_FAILURE;
    }
}

int otbBoostMachineLearningModelNew(int itkNotUsed(argc), char * itkNotUsed(argv) [])
{
  typedef otb::BoostMachineLearningModel<InputValueType,TargetValueType> BoostType;
  BoostType::Pointer classifier = BoostType::New();
  return EXIT_SUCCESS;
}

int otbBoostMachineLearningModel(int argc, char * argv[])
{
  if (argc != 3 )
    {
    std::cout<<"Wrong number of arguments "<<std::endl;
    std::cout<<"Usage : sample file, output file "<<std::endl;
    return EXIT_FAILURE;
    }

  typedef otb::BoostMachineLearningModel<InputValueType, TargetValueType> BoostType;

  InputListSampleType::Pointer samples = InputListSampleType::New();
  TargetListSampleType::Pointer labels = TargetListSampleType::New();
  TargetListSampleType::Pointer predicted = TargetListSampleType::New();

  if(!ReadDataFile(argv[1],samples,labels))
    {
    std::cout<<"Failed to read samples file "<<argv[1]<<std::endl;
    return EXIT_FAILURE;
    }

  // Since otb::BoostMachineLearningModel ONLY handles 2-class classifications, then the
  // labels are split into 2 subsets: even (label = 1) and odd (label = 3) labels
  TargetSampleType currentLabel;
  for (unsigned itLabel = 0; itLabel < labels->Size(); ++itLabel)
    {
    currentLabel = labels->GetMeasurementVector(itLabel);
    labels->SetMeasurementVector(itLabel, (2 * (currentLabel[0] % 2)) + 1);
    }

  BoostType::Pointer classifier = BoostType::New();
  classifier->SetInputListSample(samples);
  classifier->SetTargetListSample(labels);
  classifier->Train();

  classifier->SetTargetListSample(predicted);
  classifier->PredictAll();

  classifier->Save(argv[2]);

  ConfusionMatrixCalculatorType::Pointer cmCalculator = ConfusionMatrixCalculatorType::New();

  cmCalculator->SetProducedLabels(predicted);
  cmCalculator->SetReferenceLabels(labels);
  cmCalculator->Compute();

  std::cout<<"Confusion matrix: "<<std::endl;
  std::cout<<cmCalculator->GetConfusionMatrix()<<std::endl;
  const float kappaIdx = cmCalculator->GetKappaIndex();
  std::cout<<"Kappa: "<<kappaIdx<<std::endl;
  std::cout<<"Overall Accuracy: "<<cmCalculator->GetOverallAccuracy()<<std::endl;

  //Load Model to new Boost model
  TargetListSampleType::Pointer predictedLoad = TargetListSampleType::New();
  BoostType::Pointer classifierLoad = BoostType::New();

  classifierLoad->Load(argv[2]);
  classifierLoad->SetInputListSample(samples);
  classifierLoad->SetTargetListSample(predictedLoad);
  classifierLoad->PredictAll();

  ConfusionMatrixCalculatorType::Pointer cmCalculatorLoad = ConfusionMatrixCalculatorType::New();

  cmCalculatorLoad->SetProducedLabels(predictedLoad);
  cmCalculatorLoad->SetReferenceLabels(labels);
  cmCalculatorLoad->Compute();

  std::cout<<"Confusion matrix: "<<std::endl;
  std::cout<<cmCalculatorLoad->GetConfusionMatrix()<<std::endl;
  const float kappaIdxLoad = cmCalculatorLoad->GetKappaIndex();
  std::cout<<"Kappa: "<<kappaIdxLoad<<std::endl;
  std::cout<<"Overall Accuracy: "<<cmCalculatorLoad->GetOverallAccuracy()<<std::endl;


  if ( vcl_abs(kappaIdxLoad - kappaIdx) < 0.00000001)
    {
    return EXIT_SUCCESS;
    }
  else
    {
    return EXIT_FAILURE;
    }
}

int otbANNMachineLearningModelNew(int itkNotUsed(argc), char * itkNotUsed(argv) [])
{
  typedef otb::NeuralNetworkMachineLearningModel<InputValueType, TargetValueType> ANNType;
  ANNType::Pointer classifier = ANNType::New();
  return EXIT_SUCCESS;
}

int otbANNMachineLearningModel(int argc, char * argv[])
{
  if (argc != 3)
    {
      std::cout<<"Wrong number of arguments "<<std::endl;
      std::cout<<"Usage : sample file, output file "<<std::endl;
      return EXIT_FAILURE;
    }


  typedef otb::NeuralNetworkMachineLearningModel<InputValueType, TargetValueType> ANNType;
  InputListSampleType::Pointer samples = InputListSampleType::New();
  TargetListSampleType::Pointer labels = TargetListSampleType::New();
  TargetListSampleType::Pointer predicted = TargetListSampleType::New();

  if (!ReadDataFile(argv[1], samples, labels))
    {
    std::cout << "Failed to read samples file " << argv[1] << std::endl;
    return EXIT_FAILURE;
    }

  std::vector<unsigned int> layerSizes;
  layerSizes.push_back(16);
  layerSizes.push_back(100);
  layerSizes.push_back(100);
  layerSizes.push_back(26);

  ANNType::Pointer classifier = ANNType::New();
  classifier->SetInputListSample(samples);
  classifier->SetTargetListSample(labels);
  classifier->SetLayerSizes(layerSizes);
  /*classifier->SetTrainMethod(CvANN_MLP_TrainParams::RPROP);
  classifier->SetRegPropDW0(0.1);
  classifier->SetRegPropDWMin(0.1);
  classifier->SetTermCriteriaType(CV_TERMCRIT_ITER);
  classifier->SetMaxIter(300);
  classifier->SetEpsilon(0.01); */
  classifier->Train();

  classifier->SetTargetListSample(predicted);
  classifier->PredictAll();

  ConfusionMatrixCalculatorType::Pointer cmCalculator = ConfusionMatrixCalculatorType::New();

  cmCalculator->SetProducedLabels(predicted);
  cmCalculator->SetReferenceLabels(labels);
  cmCalculator->Compute();

  std::cout << "Confusion matrix: " << std::endl;
  std::cout << cmCalculator->GetConfusionMatrix() << std::endl;
  const float kappaIdx = cmCalculator->GetKappaIndex();
  std::cout<<"Kappa: "<<kappaIdx<<std::endl;
  std::cout << "Overall Accuracy: " << cmCalculator->GetOverallAccuracy() << std::endl;

  classifier->Save(argv[2]);

  //Load Model to new ANN
  TargetListSampleType::Pointer predictedLoad = TargetListSampleType::New();
  ANNType::Pointer classifierLoad = ANNType::New();

  classifierLoad->Load(argv[2]);
  classifierLoad->SetInputListSample(samples);
  classifierLoad->SetTargetListSample(predictedLoad);
  classifierLoad->PredictAll();

  ConfusionMatrixCalculatorType::Pointer cmCalculatorLoad = ConfusionMatrixCalculatorType::New();

  cmCalculatorLoad->SetProducedLabels(predictedLoad);
  cmCalculatorLoad->SetReferenceLabels(labels);
  cmCalculatorLoad->Compute();

  std::cout<<"Confusion matrix: "<<std::endl;
  std::cout<<cmCalculatorLoad->GetConfusionMatrix()<<std::endl;
  const float kappaIdxLoad = cmCalculatorLoad->GetKappaIndex();
  std::cout<<"Kappa: "<<kappaIdxLoad<<std::endl;
  std::cout<<"Overall Accuracy: "<<cmCalculatorLoad->GetOverallAccuracy()<<std::endl;


  if ( vcl_abs(kappaIdxLoad - kappaIdx) < 0.00000001)
    {
    return EXIT_SUCCESS;
    }
  else
    {
    return EXIT_FAILURE;
    }
}

int otbNormalBayesMachineLearningModelNew(int itkNotUsed(argc), char * itkNotUsed(argv) [])
{
  typedef otb::NormalBayesMachineLearningModel<InputValueType,TargetValueType> NormalBayesType;
  NormalBayesType::Pointer classifier = NormalBayesType::New();
  return EXIT_SUCCESS;
}

int otbNormalBayesMachineLearningModel(int argc, char * argv[])
{
  if (argc != 3 )
    {
      std::cout<<"Wrong number of arguments "<<std::endl;
      std::cout<<"Usage : sample file, output file "<<std::endl;
      return EXIT_FAILURE;
    }

  typedef otb::NormalBayesMachineLearningModel<InputValueType, TargetValueType> NormalBayesType;

  InputListSampleType::Pointer samples = InputListSampleType::New();
  TargetListSampleType::Pointer labels = TargetListSampleType::New();
  TargetListSampleType::Pointer predicted = TargetListSampleType::New();

  if(!ReadDataFile(argv[1],samples,labels))
    {
    std::cout<<"Failed to read samples file "<<argv[1]<<std::endl;
    return EXIT_FAILURE;
    }

  NormalBayesType::Pointer classifier = NormalBayesType::New();
  classifier->SetInputListSample(samples);
  classifier->SetTargetListSample(labels);
  classifier->Train();

  classifier->SetTargetListSample(predicted);
  classifier->PredictAll();

  classifier->Save(argv[2]);

  ConfusionMatrixCalculatorType::Pointer cmCalculator = ConfusionMatrixCalculatorType::New();

  cmCalculator->SetProducedLabels(predicted);
  cmCalculator->SetReferenceLabels(labels);
  cmCalculator->Compute();

  std::cout<<"Confusion matrix: "<<std::endl;
  std::cout<<cmCalculator->GetConfusionMatrix()<<std::endl;
  const float kappaIdx = cmCalculator->GetKappaIndex();
  std::cout<<"Kappa: "<<kappaIdx<<std::endl;
  std::cout<<"Overall Accuracy: "<<cmCalculator->GetOverallAccuracy()<<std::endl;

  //Load Model to new Normal Bayes
  TargetListSampleType::Pointer predictedLoad = TargetListSampleType::New();
  NormalBayesType::Pointer classifierLoad = NormalBayesType::New();

  classifierLoad->Load(argv[2]);
  classifierLoad->SetInputListSample(samples);
  classifierLoad->SetTargetListSample(predictedLoad);
  classifierLoad->PredictAll();

  ConfusionMatrixCalculatorType::Pointer cmCalculatorLoad = ConfusionMatrixCalculatorType::New();

  cmCalculatorLoad->SetProducedLabels(predictedLoad);
  cmCalculatorLoad->SetReferenceLabels(labels);
  cmCalculatorLoad->Compute();

  std::cout<<"Confusion matrix: "<<std::endl;
  std::cout<<cmCalculatorLoad->GetConfusionMatrix()<<std::endl;
  const float kappaIdxLoad = cmCalculatorLoad->GetKappaIndex();
  std::cout<<"Kappa: "<<kappaIdxLoad<<std::endl;
  std::cout<<"Overall Accuracy: "<<cmCalculatorLoad->GetOverallAccuracy()<<std::endl;


  if ( vcl_abs(kappaIdxLoad - kappaIdx) < 0.00000001)
    {
    return EXIT_SUCCESS;
    }
  else
    {
    return EXIT_FAILURE;
    }
}

int otbDecisionTreeMachineLearningModelNew(int itkNotUsed(argc), char * itkNotUsed(argv) [])
{
  typedef otb::DecisionTreeMachineLearningModel<InputValueType,TargetValueType> DecisionTreeType;
  DecisionTreeType::Pointer classifier = DecisionTreeType::New();
  return EXIT_SUCCESS;
}

int otbDecisionTreeMachineLearningModel(int argc, char * argv[])
{
  if (argc != 3 )
    {
      std::cout<<"Wrong number of arguments "<<std::endl;
      std::cout<<"Usage : sample file, output file "<<std::endl;
      return EXIT_FAILURE;
    }

  typedef otb::DecisionTreeMachineLearningModel<InputValueType, TargetValueType> DecisionTreeType;

  InputListSampleType::Pointer samples = InputListSampleType::New();
  TargetListSampleType::Pointer labels = TargetListSampleType::New();
  TargetListSampleType::Pointer predicted = TargetListSampleType::New();

  if(!ReadDataFile(argv[1],samples,labels))
    {
    std::cout<<"Failed to read samples file "<<argv[1]<<std::endl;
    return EXIT_FAILURE;
    }

  DecisionTreeType::Pointer classifier = DecisionTreeType::New();
  classifier->SetInputListSample(samples);
  classifier->SetTargetListSample(labels);
  classifier->Train();

  classifier->SetTargetListSample(predicted);
  classifier->PredictAll();

  classifier->Save(argv[2]);

  ConfusionMatrixCalculatorType::Pointer cmCalculator = ConfusionMatrixCalculatorType::New();

  cmCalculator->SetProducedLabels(predicted);
  cmCalculator->SetReferenceLabels(labels);
  cmCalculator->Compute();

  std::cout<<"Confusion matrix: "<<std::endl;
  std::cout<<cmCalculator->GetConfusionMatrix()<<std::endl;
  const float kappaIdx = cmCalculator->GetKappaIndex();
  std::cout<<"Kappa: "<<kappaIdx<<std::endl;
  std::cout<<"Overall Accuracy: "<<cmCalculator->GetOverallAccuracy()<<std::endl;

  //Load Model to new Decision Tree
  TargetListSampleType::Pointer predictedLoad = TargetListSampleType::New();
  DecisionTreeType::Pointer classifierLoad = DecisionTreeType::New();

  classifierLoad->Load(argv[2]);
  classifierLoad->SetInputListSample(samples);
  classifierLoad->SetTargetListSample(predictedLoad);
  classifierLoad->PredictAll();

  ConfusionMatrixCalculatorType::Pointer cmCalculatorLoad = ConfusionMatrixCalculatorType::New();

  cmCalculatorLoad->SetProducedLabels(predictedLoad);
  cmCalculatorLoad->SetReferenceLabels(labels);
  cmCalculatorLoad->Compute();

  std::cout<<"Confusion matrix: "<<std::endl;
  std::cout<<cmCalculatorLoad->GetConfusionMatrix()<<std::endl;
  const float kappaIdxLoad = cmCalculatorLoad->GetKappaIndex();
  std::cout<<"Kappa: "<<kappaIdxLoad<<std::endl;
  std::cout<<"Overall Accuracy: "<<cmCalculatorLoad->GetOverallAccuracy()<<std::endl;


  if ( vcl_abs(kappaIdxLoad - kappaIdx) < 0.00000001)
    {
    return EXIT_SUCCESS;
    }
  else
    {
    return EXIT_FAILURE;
    }
}


int otbGradientBoostedTreeMachineLearningModelNew(int itkNotUsed(argc), char * itkNotUsed(argv) [])
{
  typedef otb::GradientBoostedTreeMachineLearningModel<InputValueType,TargetValueType> GBTreeType;
  GBTreeType::Pointer classifier = GBTreeType::New();
  return EXIT_SUCCESS;
}

int otbGradientBoostedTreeMachineLearningModel(int argc, char * argv[])
{
  if (argc != 3 )
    {
      std::cout<<"Wrong number of arguments "<<std::endl;
      std::cout<<"Usage : sample file, output file "<<std::endl;
      return EXIT_FAILURE;
    }

  typedef otb::GradientBoostedTreeMachineLearningModel<InputValueType, TargetValueType> GBTreeType;

  InputListSampleType::Pointer samples = InputListSampleType::New();
  TargetListSampleType::Pointer labels = TargetListSampleType::New();
  TargetListSampleType::Pointer predicted = TargetListSampleType::New();

  if(!ReadDataFile(argv[1],samples,labels))
    {
    std::cout<<"Failed to read samples file "<<argv[1]<<std::endl;
    return EXIT_FAILURE;
    }

  GBTreeType::Pointer classifier = GBTreeType::New();
  classifier->SetInputListSample(samples);
  classifier->SetTargetListSample(labels);
  classifier->Train();

  classifier->SetTargetListSample(predicted);
  classifier->PredictAll();

  classifier->Save(argv[2]);

  ConfusionMatrixCalculatorType::Pointer cmCalculator = ConfusionMatrixCalculatorType::New();

  cmCalculator->SetProducedLabels(predicted);
  cmCalculator->SetReferenceLabels(labels);
  cmCalculator->Compute();

  std::cout<<"Confusion matrix: "<<std::endl;
  std::cout<<cmCalculator->GetConfusionMatrix()<<std::endl;
  const float kappaIdx = cmCalculator->GetKappaIndex();
  std::cout<<"Kappa: "<<kappaIdx<<std::endl;
  std::cout<<"Overall Accuracy: "<<cmCalculator->GetOverallAccuracy()<<std::endl;

  //Load Model to new GBT
  TargetListSampleType::Pointer predictedLoad = TargetListSampleType::New();
  GBTreeType::Pointer classifierLoad = GBTreeType::New();

  classifierLoad->Load(argv[2]);
  classifierLoad->SetInputListSample(samples);
  classifierLoad->SetTargetListSample(predictedLoad);
  classifierLoad->PredictAll();

  ConfusionMatrixCalculatorType::Pointer cmCalculatorLoad = ConfusionMatrixCalculatorType::New();

  cmCalculatorLoad->SetProducedLabels(predictedLoad);
  cmCalculatorLoad->SetReferenceLabels(labels);
  cmCalculatorLoad->Compute();

  std::cout<<"Confusion matrix: "<<std::endl;
  std::cout<<cmCalculatorLoad->GetConfusionMatrix()<<std::endl;
  const float kappaIdxLoad = cmCalculatorLoad->GetKappaIndex();
  std::cout<<"Kappa: "<<kappaIdxLoad<<std::endl;
  std::cout<<"Overall Accuracy: "<<cmCalculatorLoad->GetOverallAccuracy()<<std::endl;


  if ( vcl_abs(kappaIdxLoad - kappaIdx) < 0.00000001)
    {
    return EXIT_SUCCESS;
    }
  else
    {
    return EXIT_FAILURE;
    }
}
#endif

#ifdef OTB_USE_SHARK
#include <chrono> // If shark is on, then we are using c++11

bool SharkReadDataFile(const std::string & infname, InputListSampleType * samples, TargetListSampleType * labels)
{
  std::ifstream ifs(infname.c_str());

  if(!ifs)
    {
    std::cout<<"Could not read file "<<infname<<std::endl;
    return false;
    }

  unsigned int nbfeatures = 0;

  std::string line;
  while (std::getline(ifs, line))
    {
    boost::algorithm::trim(line);

    if(nbfeatures == 0)
      {
      nbfeatures = std::count(line.begin(),line.end(),' ');
      }

    if(line.size()>1)
      {
      InputSampleType sample(nbfeatures);
      sample.Fill(0);

      std::string::size_type pos = line.find_first_of(" ", 0);

      // Parse label
      TargetSampleType label;
      label[0] = std::stoi(line.substr(0, pos).c_str());

      bool endOfLine = false;
      unsigned int id = 0;

      while(!endOfLine)
        {
        std::string::size_type nextpos = line.find_first_of(" ", pos+1);

        if(pos == std::string::npos)
          {
          endOfLine = true;
          nextpos = line.size()-1;
          }
        else
          {
          std::string feature = line.substr(pos,nextpos-pos);
          std::string::size_type semicolonpos = feature.find_first_of(":");
          id = std::stoi(feature.substr(0,semicolonpos).c_str());
          sample[id - 1] = atof(feature.substr(semicolonpos+1,feature.size()-semicolonpos).c_str());
          pos = nextpos;
          }

        }
      samples->SetMeasurementVectorSize(itk::NumericTraits<InputSampleType>::GetLength(sample));
      samples->PushBack(sample);
      labels->PushBack(label);
      }
    }

  //std::cout<<"Retrieved "<<samples->Size()<<" samples"<<std::endl;
  ifs.close();
  return true;
}

bool SharkReadDataRegressionFile(const std::string & infname, InputListSampleRegressionType * samples, TargetListSampleRegressionType * labels)
{
  std::ifstream ifs(infname.c_str());
  if(!ifs)
    {
    std::cout<<"Could not read file "<<infname<<std::endl;
    return false;
    }

  unsigned int nbfeatures = 0;

  while (!ifs.eof())
    {
    std::string line;
    std::getline(ifs, line);

    if(nbfeatures == 0)
      {
      nbfeatures = std::count(line.begin(),line.end(),' ')-1;
      //std::cout<<"Found "<<nbfeatures<<" features per samples"<<std::endl;
      }

    if(line.size()>1)
      {
      InputSampleRegressionType sample(nbfeatures);
      sample.Fill(0);

      std::string::size_type pos = line.find_first_of(" ", 0);

      // Parse label
      TargetSampleRegressionType label;
      label[0] = atof(line.substr(0, pos).c_str());

      bool endOfLine = false;
      unsigned int id = 0;

      while(!endOfLine)
        {
        std::string::size_type nextpos = line.find_first_of(" ", pos+1);

        if(nextpos == std::string::npos)
          {
          endOfLine = true;
          nextpos = line.size()-1;
          }
        else
          {
          std::string feature = line.substr(pos,nextpos-pos);
          std::string::size_type semicolonpos = feature.find_first_of(":");
          id = std::stoi(feature.substr(0,semicolonpos).c_str());
          sample[id - 1] = atof(feature.substr(semicolonpos+1,feature.size()-semicolonpos).c_str());
          pos = nextpos;
          }

        }
      samples->SetMeasurementVectorSize(itk::NumericTraits<InputSampleRegressionType>::GetLength(sample));
      samples->PushBack(sample);
      labels->PushBack(label);
      }
    }

  //std::cout<<"Retrieved "<<samples->Size()<<" samples"<<std::endl;
  ifs.close();
  return true;
}


#include "otbSharkRandomForestsMachineLearningModel.h"
int otbSharkRFMachineLearningModelNew(int itkNotUsed(argc), char * itkNotUsed(argv) [])
{
  typedef otb::SharkRandomForestsMachineLearningModel<InputValueType,TargetValueType> SharkRFType;
  SharkRFType::Pointer classifier = SharkRFType::New();
  return EXIT_SUCCESS;
}

int otbSharkRFMachineLearningModel(int argc, char * argv[])
{
  if (argc != 3 )
    {
    std::cout<<"Wrong number of arguments "<<std::endl;
    std::cout<<"Usage : sample file, output file "<<std::endl;
    return EXIT_FAILURE;
    }

  typedef otb::SharkRandomForestsMachineLearningModel<InputValueType,TargetValueType> RandomForestType;
  InputListSampleType::Pointer samples = InputListSampleType::New();
  TargetListSampleType::Pointer labels = TargetListSampleType::New();
  TargetListSampleType::Pointer predicted = TargetListSampleType::New();

  if(!SharkReadDataFile(argv[1],samples,labels))
    {
    std::cout<<"Failed to read samples file "<<argv[1]<<std::endl;
    return EXIT_FAILURE;
    }


  RandomForestType::Pointer classifier = RandomForestType::New();
  classifier->SetInputListSample(samples);
  classifier->SetTargetListSample(labels);
  classifier->SetRegressionMode(false);
  classifier->SetNumberOfTrees(100);
  classifier->SetMTry(0);
  classifier->SetNodeSize(25);
  classifier->SetOobRatio(0.3);
  std::cout << "Train\n";
  classifier->Train();
  std::cout << "Save\n";
  classifier->Save(argv[2]); 
  
  std::cout << "Predict\n";
  classifier->SetTargetListSample(predicted);
  classifier->PredictAll();

  ConfusionMatrixCalculatorType::Pointer cmCalculator = ConfusionMatrixCalculatorType::New();

  cmCalculator->SetProducedLabels(predicted);
  cmCalculator->SetReferenceLabels(labels);
  cmCalculator->Compute();

  std::cout<<"Confusion matrix: "<<std::endl;
  std::cout<<cmCalculator->GetConfusionMatrix()<<std::endl;
  const float kappaIdx = cmCalculator->GetKappaIndex();
  std::cout<<"Kappa: "<<kappaIdx<<std::endl;
  std::cout<<"Overall Accuracy: "<<cmCalculator->GetOverallAccuracy()<<std::endl;
  
  // //Predict single samples. Written for benchmarking purposes, but
  // too long for regression testing
  // std::cout << "Predict single samples\n";
  // auto sIt = samples->Begin();
  // auto lIt = labels->Begin();
  // auto start = std::chrono::system_clock::now();
  // for(; sIt != samples->End(); ++sIt, ++lIt)
  //   {
  //   classifier->Predict(sIt.GetMeasurementVector())[0];
  //   }
  // auto duration = std::chrono::duration_cast< TimeT> 
  //   (std::chrono::system_clock::now() - start);
  // auto elapsed = duration.count();
  // std::cout << "Predict took " << elapsed << " ms\n";
  //  std::cout << "Single sample OA = " << oa << '\n';
//Load Model to new RF
  TargetListSampleType::Pointer predictedLoad = TargetListSampleType::New();
  RandomForestType::Pointer classifierLoad = RandomForestType::New();

  std::cout << "Load\n";
  classifierLoad->Load(argv[2]);
  auto start = std::chrono::system_clock::now();
  classifierLoad->SetInputListSample(samples);
  classifierLoad->SetTargetListSample(predictedLoad);
  std::cout << "Predict loaded\n";
  classifierLoad->PredictAll();
  using TimeT = std::chrono::milliseconds;
  auto duration = std::chrono::duration_cast< TimeT> 
    (std::chrono::system_clock::now() - start);
  auto elapsed = duration.count();
  std::cout << "PredictAll took " << elapsed << " ms\n";
  ConfusionMatrixCalculatorType::Pointer cmCalculatorLoad = ConfusionMatrixCalculatorType::New();

   cmCalculatorLoad->SetProducedLabels(predictedLoad);
   cmCalculatorLoad->SetReferenceLabels(labels);
   cmCalculatorLoad->Compute();

   std::cout<<"Confusion matrix: "<<std::endl;
   std::cout<<cmCalculatorLoad->GetConfusionMatrix()<<std::endl;
   const float kappaIdxLoad = cmCalculatorLoad->GetKappaIndex();
   std::cout<<"Kappa: "<<kappaIdxLoad<<std::endl;
   std::cout<<"Overall Accuracy: "<<cmCalculatorLoad->GetOverallAccuracy()<<std::endl;


   if ( vcl_abs(kappaIdxLoad - kappaIdx) < 0.00000001)
     {
     return EXIT_SUCCESS;
     }
   else
     {
     return EXIT_FAILURE;
     }
  
   return EXIT_SUCCESS;
}

#endif
