/*=========================================================================

  Program:   ORFEO Toolbox
  Language:  C++
  Date:      $Date$
  Version:   $Revision$


  Copyright (c) Centre National d'Etudes Spatiales. All rights reserved.
  See OTBCopyright.txt for details.


     This software is distributed WITHOUT ANY WARRANTY; without even 
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR 
     PURPOSE.  See the above copyright notices for more information.

=========================================================================*/

#ifndef otbPrincipalImageViewAS_h
#define otbPrincipalImageViewAS_h

#include <FL/gl.h>
#include <FL/Fl.H>
#include <FL/fl_draw.H>
#include <FL/Fl_Gl_Window.H>

#include "otbGLVectorImageViewClick.h"
#include "otbSVMPointSetModelEstimator.h"
#include "itkPointSet.h"

namespace otb
{
  
/**
* \class PrincipalImageViewAS
* \brief Class for viewing an image in entier resolution
* 
* See GLVectorImageViewClick.h for details...
  **/
template <class TPixel, class TPixelOverlay>
class ITK_EXPORT PrincipalImageViewAS :  public
GLVectorImageViewClick<TPixel, TPixelOverlay>
                                
{
public:
    
    float _x,_y,_z;   
    typedef PrincipalImageViewAS                                Self;
    typedef GLVectorImageViewClick<TPixel, TPixelOverlay>       Superclass;
    typedef itk::SmartPointer<Self>                             Pointer;
    typedef itk::SmartPointer<const Self>                       ConstPointer;
	
    /* typdef for the image*/
    typedef typename Superclass::ImageType              ImageType;
    typedef typename Superclass::ImagePointer           ImagePointer;
    typedef typename Superclass::ImageConstPointer      ImageConstPointer;
    typedef typename Superclass::RegionType             RegionType;
    typedef typename Superclass::SizeType               SizeType;
    typedef typename Superclass::IndexType              IndexType;
    typedef typename Superclass::PixelType              PixelType;
	
    /* typedef for learning and classification */
    typedef float                                       InputPixelType;
    typedef std::vector<InputPixelType>                 InputVectorType;
    typedef int                                         LabelPixelType;
    typedef itk::PointSet< InputVectorType, 2>          MeasurePointSetType;
    typedef itk::PointSet< LabelPixelType,  2>          LabelPointSetType;
	
    typedef otb::SVMPointSetModelEstimator< MeasurePointSetType,
  						LabelPointSetType >   EstimatorType;
	

    /*! Method for creation through the object factory. */
    itkNewMacro(Self);

    /*! Run-time type information (and related methods). */
    itkTypeMacro(PrincipalImageViewAS,GLVectorImageViewClick);

  

  virtual int  handle(int event);

  /*! Show the image (display the window) */
  virtual void Show(void);
  
  /*! Erase the last clicked point */
  virtual void UndoPt();
  
  /*! Erase all clicked points */
  virtual void ResetPts();
  
  /*! Learn Step */
  void LearnStep();
  
  /*! Classification Step */
  void ClassificationStep();
  
  /*! If b is false, it is not possible to click on the image */
  void SetClickable(bool b);
  
  /*! Selected point correct */
  bool cMem;
  
  /*! Box color */
  ColorType cRectColor;
  
  /*! To know if click or box */
  int nbDrag;

  /*! Image clickable */
  bool cClickable;  
  
  /*! Estimator after learning */
  EstimatorType::Pointer cEstimator;
  
protected:
  
  /*! Standard constructor */
  PrincipalImageViewAS();
  /*! Standard destructor */
  virtual ~PrincipalImageViewAS(void);
  

};

} //namespace

#ifndef OTB_MANUAL_INSTANTIATION
#include "otbPrincipalImageViewAS.txx"
#endif

#endif

