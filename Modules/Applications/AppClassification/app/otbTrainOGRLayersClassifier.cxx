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

#include "otbWrapperApplication.h"
#include "otbWrapperApplicationFactory.h"

#include "otbOGRDataSourceWrapper.h"
#include "otbOGRFeatureWrapper.h"
#include "otbStatisticsXMLFileWriter.h"

#include "itkVariableLengthVector.h"
#include "otbStatisticsXMLFileReader.h"

#include "itkListSample.h"
#include "otbShiftScaleSampleListFilter.h"

#ifdef OTB_USE_LIBSVM
#include "otbLibSVMMachineLearningModel.h"
#endif

#include <time.h>

namespace otb
{
namespace Wrapper
{
class TrainOGRLayersClassifier : public Application
{
public:
  typedef TrainOGRLayersClassifier Self;
  typedef Application Superclass;
  typedef itk::SmartPointer<Self> Pointer;
  typedef itk::SmartPointer<const Self> ConstPointer;
  itkNewMacro(Self)
;

  itkTypeMacro(TrainOGRLayersClassifier, otb::Application)
;

private:
  void DoInit() ITK_OVERRIDE
  {
    SetName("TrainOGRLayersClassifier");
    SetDescription("Train a SVM classifier based on labeled geometries and a list of features to consider.");

    SetDocName("TrainOGRLayersClassifier (DEPRECATED)");
    SetDocLongDescription("This application trains a SVM classifier based on "
      "labeled geometries and a list of features to consider for classification."
      " This application is deprecated, prefer using TrainVectorClassifier which"
      " offers access to all the classifiers.");
    SetDocLimitations("Experimental. For now only shapefiles are supported. Tuning of SVM classifier is not available.");
    SetDocAuthors("David Youssefi during internship at CNES");
    SetDocSeeAlso("OGRLayerClassifier,ComputeOGRLayersFeaturesStatistics");
    AddDocTag(Tags::Segmentation);
  
    AddParameter(ParameterType_InputVectorData, "inshp", "Name of the input shapefile");
    SetParameterDescription("inshp","Name of the input shapefile");

    AddParameter(ParameterType_InputFilename, "instats", "XML file containing mean and variance of each feature.");
    SetParameterDescription("instats", "XML file containing mean and variance of each feature.");

    AddParameter(ParameterType_OutputFilename, "outsvm", "Output model filename.");
    SetParameterDescription("outsvm", "Output model filename.");

    AddParameter(ParameterType_ListView,  "feat", "List of features to consider for classification.");
    SetParameterDescription("feat","List of features to consider for classification.");

    AddParameter(ParameterType_String,"cfield","Field containing the class id for supervision");
    SetParameterDescription("cfield","Field containing the class id for supervision. Only geometries with this field available will be taken into account.");
    SetParameterString("cfield","class", false);

    // Doc example parameter settings
    SetDocExampleParameterValue("inshp", "vectorData.shp");
    SetDocExampleParameterValue("instats", "meanVar.xml");
    SetDocExampleParameterValue("outsvm", "svmModel.svm");
    SetDocExampleParameterValue("feat", "perimeter");
    SetDocExampleParameterValue("cfield", "predicted");

  }

  void DoUpdateParameters() ITK_OVERRIDE
  {
    if ( HasValue("inshp") )
      {
      std::string shapefile = GetParameterString("inshp");

       otb::ogr::DataSource::Pointer ogrDS;
       otb::ogr::Layer layer(ITK_NULLPTR, false);

       OGRSpatialReference oSRS("");
       std::vector<std::string> options;
       
       ogrDS = otb::ogr::DataSource::New(shapefile, otb::ogr::DataSource::Modes::Read);
       std::string layername = itksys::SystemTools::GetFilenameName(shapefile);
       layername = layername.substr(0,layername.size()-4);
       layer = ogrDS->GetLayer(0);

       otb::ogr::Feature feature = layer.ogr().GetNextFeature();
       ClearChoices("feat");
       for(int iField=0; iField<feature.ogr().GetFieldCount(); iField++)
         {
           std::string key, item = feature.ogr().GetFieldDefnRef(iField)->GetNameRef();
           key = item;
           key.erase(std::remove(key.begin(), key.end(), ' '), key.end());
           std::transform(key.begin(), key.end(), key.begin(), tolower);
           key="feat."+key;
           AddChoice(key,item);
         }
      }
  }

  void DoExecute() ITK_OVERRIDE
  {
    #ifdef OTB_USE_LIBSVM 
    clock_t tic = clock();

    std::string shapefile = GetParameterString("inshp");
    std::string XMLfile = GetParameterString("instats");
    std::string modelfile = GetParameterString("outsvm");

    typedef double ValueType;
    typedef itk::VariableLengthVector<ValueType> MeasurementType;
    typedef itk::Statistics::ListSample <MeasurementType> ListSampleType;
    typedef otb::StatisticsXMLFileReader<MeasurementType> StatisticsReader;
  
    typedef unsigned int LabelPixelType;
    typedef itk::FixedArray<LabelPixelType,1> LabelSampleType;
    typedef itk::Statistics::ListSample <LabelSampleType> LabelListSampleType;
  
    typedef otb::Statistics::ShiftScaleSampleListFilter<ListSampleType, ListSampleType> ShiftScaleFilterType;

    StatisticsReader::Pointer statisticsReader = StatisticsReader::New();
    statisticsReader->SetFileName(XMLfile);

    MeasurementType meanMeasurementVector = statisticsReader->GetStatisticVectorByName("mean");
    MeasurementType stddevMeasurementVector = statisticsReader->GetStatisticVectorByName("stddev");
   
    otb::ogr::DataSource::Pointer source = otb::ogr::DataSource::New(shapefile, otb::ogr::DataSource::Modes::Read);
    otb::ogr::Layer layer = source->GetLayer(0);
    bool goesOn = true;
    otb::ogr::Feature feature = layer.ogr().GetNextFeature();

    ListSampleType::Pointer input = ListSampleType::New();
    LabelListSampleType::Pointer target = LabelListSampleType::New();
    const int nbFeatures = GetSelectedItems("feat").size();

    input->SetMeasurementVectorSize(nbFeatures);
   
    if(feature.addr())
      while(goesOn)
       {
        if(feature.ogr().IsFieldSet(feature.ogr().GetFieldIndex(GetParameterString("cfield").c_str())))
           {
             MeasurementType mv; mv.SetSize(nbFeatures);
             
             for(int idx=0; idx < nbFeatures; ++idx)
              mv[idx] = feature.ogr().GetFieldAsDouble(GetSelectedItems("feat")[idx]);
             
             input->PushBack(mv);
             target->PushBack(feature.ogr().GetFieldAsInteger(GetParameterString("cfield").c_str()));
           }
         feature = layer.ogr().GetNextFeature();
         goesOn = feature.addr() != ITK_NULLPTR;
       }

    ShiftScaleFilterType::Pointer trainingShiftScaleFilter = ShiftScaleFilterType::New();
    trainingShiftScaleFilter->SetInput(input);
    trainingShiftScaleFilter->SetShifts(meanMeasurementVector);
    trainingShiftScaleFilter->SetScales(stddevMeasurementVector);
    trainingShiftScaleFilter->Update();
  
    ListSampleType::Pointer listSample;
    LabelListSampleType::Pointer labelListSample;

    listSample = trainingShiftScaleFilter->GetOutput();
    labelListSample = target;

    ListSampleType::Pointer trainingListSample = listSample;
    LabelListSampleType::Pointer trainingLabeledListSample = labelListSample;

    typedef otb::LibSVMMachineLearningModel<ValueType,LabelPixelType> LibSVMType;
    LibSVMType::Pointer libSVMClassifier = LibSVMType::New();
    libSVMClassifier->SetInputListSample(trainingListSample);
    libSVMClassifier->SetTargetListSample(trainingLabeledListSample);
    libSVMClassifier->SetParameterOptimization(true);
    libSVMClassifier->SetC(1.0);
    libSVMClassifier->SetKernelType(LINEAR);
    libSVMClassifier->Train();
    libSVMClassifier->Save(modelfile);

    clock_t toc = clock();

    otbAppLogINFO( "Elapsed: "<< ((double)(toc - tic) / CLOCKS_PER_SEC)<<" seconds.");
    
    #else
    otbAppLogFATAL("Module LIBSVM is not installed. You should consider turning OTB_USE_LIBSVM on during cmake configuration.");
    #endif
    
    }

};
}
}

OTB_APPLICATION_EXPORT(otb::Wrapper::TrainOGRLayersClassifier)


