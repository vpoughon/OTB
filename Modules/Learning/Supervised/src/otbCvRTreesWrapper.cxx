/*=========================================================================

  Program:   ORFEO Toolbox
  Language:  C++


  Copyright (c) Centre National d'Etudes Spatiales. All rights reserved.
  See OTBCopyright.txt for details.


     This software is distributed WITHOUT ANY WARRANTY; without even
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
     PURPOSE.  See the above copyright notices for more information.

=========================================================================*/
#include "otbCvRTreesWrapper.h"
#include <algorithm>
#include <functional>

namespace otb
{

CvRTreesWrapper::CvRTreesWrapper(){}

CvRTreesWrapper::~CvRTreesWrapper(){}

void CvRTreesWrapper::get_votes(const cv::Mat& sample, 
                                const cv::Mat& missing,
                                CvRTreesWrapper::VotesVectorType& vote_count) const
{
  vote_count.resize(nclasses);
  for( int k = 0; k < ntrees; k++ )
    {
    CvDTreeNode* predicted_node = trees[k]->predict( sample, missing );
    int class_idx = predicted_node->class_idx;
    CV_Assert( 0 <= class_idx && class_idx < nclasses );
    ++vote_count[class_idx];
    }
}

float CvRTreesWrapper::predict_margin(const cv::Mat& sample, 
                                      const cv::Mat& missing) const
{
  // Sanity check (division by ntrees later on)
  if(ntrees == 0)
    {
    return 0.;
    }
  std::vector<unsigned int> classVotes;
  this->get_votes(sample, missing, classVotes);
// We only sort the 2 greatest elements
  std::nth_element(classVotes.begin(), classVotes.begin()+1, 
                   classVotes.end(), std::greater<unsigned int>());
  float margin = static_cast<float>(classVotes[0]-classVotes[1])/ntrees;
  return margin;
}

float CvRTreesWrapper::predict_confidence(const cv::Mat& sample, 
                                  const cv::Mat& missing) const
{
  // Sanity check (division by ntrees later on)
  if(ntrees == 0)
    {
    return 0.;
    }
  std::vector<unsigned int> classVotes;
  this->get_votes(sample, missing, classVotes);
  unsigned int max_votes = *(std::max_element(classVotes.begin(), 
                                              classVotes.end()));
  float confidence = static_cast<float>(max_votes)/ntrees;
  return confidence;
}

}
