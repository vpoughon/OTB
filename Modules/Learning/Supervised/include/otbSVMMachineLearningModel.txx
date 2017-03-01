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

#ifndef otbSVMMachineLearningModel_txx
#define otbSVMMachineLearningModel_txx

#include <fstream>
#include "itkMacro.h"
#include "otbSVMMachineLearningModel.h"
#include "otbOpenCVUtils.h"

namespace otb
{

template <class TInputValue, class TOutputValue>
SVMMachineLearningModel<TInputValue,TOutputValue>
::SVMMachineLearningModel() :
 m_SVMModel (new CvSVM),
 m_SVMType(CvSVM::C_SVC),
 m_KernelType(CvSVM::RBF),
 m_Degree(0),
 m_Gamma(1),
 m_Coef0(0),
 m_C(1),
 m_Nu(0),
 m_P(0),
 m_TermCriteriaType(CV_TERMCRIT_ITER),
 m_MaxIter(1000),
 m_Epsilon(FLT_EPSILON),
 m_ParameterOptimization(false),
 m_OutputDegree(0),
 m_OutputGamma(1),
 m_OutputCoef0(0),
 m_OutputC(1),
 m_OutputNu(0),
 m_OutputP(0)
{
  this->m_ConfidenceIndex = true;
  this->m_IsRegressionSupported = true;
}


template <class TInputValue, class TOutputValue>
SVMMachineLearningModel<TInputValue,TOutputValue>
::~SVMMachineLearningModel()
{
  delete m_SVMModel;
}

/** Train the machine learning model */
template <class TInputValue, class TOutputValue>
void
SVMMachineLearningModel<TInputValue,TOutputValue>
::Train()
{
  // Check that the SVM type is compatible with the chosen mode (classif/regression)
  if ( bool(m_SVMType == CvSVM::NU_SVR || m_SVMType == CvSVM::EPS_SVR) != this->m_RegressionMode)
    {
    itkGenericExceptionMacro("SVM type incompatible with chosen mode (classification or regression."
                             "SVM types for classification are C_SVC, NU_SVC, ONE_CLASS. "
                             "SVM types for regression are NU_SVR, EPS_SVR");
    }

  //convert listsample to opencv matrix
  cv::Mat samples;
  otb::ListSampleToMat<InputListSampleType>(this->GetInputListSample(), samples);

  cv::Mat labels;
  otb::ListSampleToMat<TargetListSampleType>(this->GetTargetListSample(),labels);

  // Set up SVM's parameters
  CvTermCriteria term_crit   = cvTermCriteria(m_TermCriteriaType, m_MaxIter, m_Epsilon);
  CvSVMParams params( m_SVMType, m_KernelType, m_Degree, m_Gamma, m_Coef0, m_C, m_Nu, m_P, ITK_NULLPTR , term_crit );

  // Train the SVM
  if (!m_ParameterOptimization)
    {
    m_SVMModel->train(samples, labels, cv::Mat(), cv::Mat(), params);
    }
  else
    {
    //Trains SVM with optimal parameters.
    //train_auto(const Mat& trainData, const Mat& responses, const Mat& varIdx, const Mat& sampleIdx,
    //CvSVMParams params, int k_fold=10, CvParamGrid Cgrid=CvSVM::get_default_grid(CvSVM::C),
    //CvParamGrid gammaGrid=CvSVM::get_default_grid(CvSVM::GAMMA),
    //CvParamGrid pGrid=CvSVM::get_default_grid(CvSVM::P), CvParamGrid nuGrid=CvSVM::get_default_grid(CvSVM::NU),
    //CvParamGrid coeffGrid=CvSVM::get_default_grid(CvSVM::COEF), CvParamGrid degreeGrid=CvSVM::get_default_grid(CvSVM::DEGREE),
    //bool balanced=false)
    //We used default parameters grid. If not enough, those grids should be expose to the user.
    m_SVMModel->train_auto(samples, labels, cv::Mat(), cv::Mat(), params);
    }

  // Export of the SVM parameters into the class SVMMachineLearningModel
  m_OutputDegree = m_SVMModel->get_params().degree;
  m_OutputGamma = m_SVMModel->get_params().gamma;
  m_OutputCoef0 = m_SVMModel->get_params().coef0;
  m_OutputC = m_SVMModel->get_params().C;
  m_OutputNu = m_SVMModel->get_params().nu;
  m_OutputP = m_SVMModel->get_params().p;

}

template <class TInputValue, class TOutputValue>
typename SVMMachineLearningModel<TInputValue,TOutputValue>
::TargetSampleType
SVMMachineLearningModel<TInputValue,TOutputValue>
::DoPredict(const InputSampleType & input, ConfidenceValueType *quality) const
{
  //convert listsample to Mat
  cv::Mat sample;

  otb::SampleToMat<InputSampleType>(input,sample);

  double result = m_SVMModel->predict(sample,false);

  TargetSampleType target;

  target[0] = static_cast<TOutputValue>(result);

  if (quality != ITK_NULLPTR)
    {
    (*quality) = m_SVMModel->predict(sample,true);
    }

  return target;
}

template <class TInputValue, class TOutputValue>
void
SVMMachineLearningModel<TInputValue,TOutputValue>
::Save(const std::string & filename, const std::string & name)
{
  if (name == "")
    m_SVMModel->save(filename.c_str(), ITK_NULLPTR);
  else
    m_SVMModel->save(filename.c_str(), name.c_str());
}

template <class TInputValue, class TOutputValue>
void
SVMMachineLearningModel<TInputValue,TOutputValue>
::Load(const std::string & filename, const std::string & name)
{
  if (name == "")
    m_SVMModel->load(filename.c_str(), ITK_NULLPTR);
  else
    m_SVMModel->load(filename.c_str(), name.c_str());
}

template <class TInputValue, class TOutputValue>
bool
SVMMachineLearningModel<TInputValue,TOutputValue>
::CanReadFile(const std::string & file)
{
  std::ifstream ifs;
  ifs.open(file.c_str());

  if(!ifs)
    {
    std::cerr<<"Could not read file "<<file<<std::endl;
    return false;
    }

  while (!ifs.eof())
    {
    std::string line;
    std::getline(ifs, line);

    //if (line.find(m_SVMModel->getName()) != std::string::npos)
    if (line.find(CV_TYPE_NAME_ML_SVM) != std::string::npos)
      {
      //std::cout<<"Reading a "<<CV_TYPE_NAME_ML_SVM<<" model"<<std::endl;
      return true;
      }
    }
  ifs.close();
  return false;
}

template <class TInputValue, class TOutputValue>
bool
SVMMachineLearningModel<TInputValue,TOutputValue>
::CanWriteFile(const std::string & itkNotUsed(file))
{
  return false;
}

template <class TInputValue, class TOutputValue>
void
SVMMachineLearningModel<TInputValue,TOutputValue>
::PrintSelf(std::ostream& os, itk::Indent indent) const
{
  // Call superclass implementation
  Superclass::PrintSelf(os,indent);
}

} //end namespace otb

#endif
