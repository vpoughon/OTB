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

#ifndef otbImageClassificationFilter_h
#define otbImageClassificationFilter_h

#include "itkImageToImageFilter.h"
#include "otbMachineLearningModel.h"
#include "otbImage.h"

namespace otb
{
/** \class ImageClassificationFilter
 *  \brief This filter performs the classification of a VectorImage using a Model.
 *
 *  This filter is streamed and threaded, allowing to classify huge images
 *  while fully using several core.
 *
 * \sa Classifier
 * \ingroup Streamed
 * \ingroup Threaded
 *
 * \ingroup OTBSupervised
 */
template <class TInputImage, class TOutputImage, class TMaskImage = TOutputImage>
class ITK_EXPORT ImageClassificationFilter
  : public itk::ImageToImageFilter<TInputImage, TOutputImage>
{
public:
  /** Standard typedefs */
  typedef ImageClassificationFilter                       Self;
  typedef itk::ImageToImageFilter<TInputImage, TOutputImage> Superclass;
  typedef itk::SmartPointer<Self>                            Pointer;
  typedef itk::SmartPointer<const Self>                      ConstPointer;

  /** Type macro */
  itkNewMacro(Self);

  /** Creation through object factory macro */
  itkTypeMacro(ImageClassificationFilter, ImageToImageFilter);

  typedef TInputImage                                InputImageType;
  typedef typename InputImageType::ConstPointer      InputImageConstPointerType;
  typedef typename InputImageType::InternalPixelType ValueType;

  typedef TMaskImage                           MaskImageType;
  typedef typename MaskImageType::ConstPointer MaskImageConstPointerType;
  typedef typename MaskImageType::Pointer      MaskImagePointerType;

  typedef TOutputImage                         OutputImageType;
  typedef typename OutputImageType::Pointer    OutputImagePointerType;
  typedef typename OutputImageType::RegionType OutputImageRegionType;
  typedef typename OutputImageType::PixelType  LabelType;

  typedef MachineLearningModel<ValueType, LabelType> ModelType;
  typedef typename ModelType::Pointer                ModelPointerType;

  typedef otb::Image<double>                    ConfidenceImageType;
  typedef typename ConfidenceImageType::Pointer ConfidenceImagePointerType;

  /** Set/Get the model */
  itkSetObjectMacro(Model, ModelType);
  itkGetObjectMacro(Model, ModelType);

  /** Set/Get the default label */
  itkSetMacro(DefaultLabel, LabelType);
  itkGetMacro(DefaultLabel, LabelType);

  /** Set/Get the confidence map flag */
  itkSetMacro(UseConfidenceMap, bool);
  itkGetMacro(UseConfidenceMap, bool);

  itkSetMacro(BatchMode, bool);
  itkGetMacro(BatchMode, bool);
  itkBooleanMacro(BatchMode);
  
  /**
   * If set, only pixels within the mask will be classified.
   * All pixels with a value greater than 0 in the mask, will be classified.
   * \param mask The input mask.
   */
  void SetInputMask(const MaskImageType * mask);

  /**
   * Get the input mask.
   * \return The mask.
   */
  const MaskImageType * GetInputMask(void);

  /**
   * Get the output confidence map
   */
  ConfidenceImageType * GetOutputConfidence(void);

protected:
  /** Constructor */
  ImageClassificationFilter();
  /** Destructor */
  ~ImageClassificationFilter() ITK_OVERRIDE {}

  /** Threaded generate data */
  void ThreadedGenerateData(const OutputImageRegionType& outputRegionForThread, itk::ThreadIdType threadId) ITK_OVERRIDE;
  void ClassicThreadedGenerateData(const OutputImageRegionType& outputRegionForThread, itk::ThreadIdType threadId);
  void BatchThreadedGenerateData(const OutputImageRegionType& outputRegionForThread, itk::ThreadIdType threadId);
  /** Before threaded generate data */
  void BeforeThreadedGenerateData() ITK_OVERRIDE;
  /**PrintSelf method */
  void PrintSelf(std::ostream& os, itk::Indent indent) const ITK_OVERRIDE;

private:
  ImageClassificationFilter(const Self &); //purposely not implemented
  void operator =(const Self&); //purposely not implemented

  /** The model used for classification */
  ModelPointerType m_Model;
  /** Default label for invalid pixels (when using a mask) */
  LabelType m_DefaultLabel;
  /** Flag to produce the confidence map (if the model supports it) */
  bool m_UseConfidenceMap;
  bool m_BatchMode;
};
} // End namespace otb
#ifndef OTB_MANUAL_INSTANTIATION
#include "otbImageClassificationFilter.txx"
#endif

#endif
