/*=========================================================================

  Program:   ORFEO Toolbox
  Language:  C++


  Copyright (c) Centre National d'Etudes Spatiales. All rights reserved.
  See OTBCopyright.txt for details.


     This software is distributed WITHOUT ANY WARRANTY; without even
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
     PURPOSE.  See the above copyright notices for more information.

=========================================================================*/
#ifndef otbWrapperQtWidgetComplexOutputImageParameter_h
#define otbWrapperQtWidgetComplexOutputImageParameter_h

#include <QtGui>
#ifndef Q_MOC_RUN  // See: https://bugreports.qt-project.org/browse/QTBUG-22829  //tag=QT4-boost-compatibility
#include "otbWrapperComplexOutputImageParameter.h"
#include "otbWrapperQtWidgetParameterBase.h"
#endif //tag=QT4-boost-compatibility


namespace otb
{
namespace Wrapper
{

/** \class QtWidgetComplexOutputImageParameter
 * \brief
 *
 * \ingroup OTBQtWidget
 */
class OTBQtWidget_EXPORT QtWidgetComplexOutputImageParameter : public QtWidgetParameterBase
{
  Q_OBJECT
public:
  QtWidgetComplexOutputImageParameter(ComplexOutputImageParameter*, QtWidgetModel*);
  ~QtWidgetComplexOutputImageParameter() ITK_OVERRIDE;

  /** Get the PixelType*/
  //itkGetMacro(PixelType, int);

protected slots:
  void SetFileName( const QString& value );
  void SelectFile();
  void SetPixelType(int pixelType);

private:
  QtWidgetComplexOutputImageParameter(const QtWidgetComplexOutputImageParameter&); //purposely not implemented
  void operator=(const QtWidgetComplexOutputImageParameter&); //purposely not implemented

  void DoCreateWidget() ITK_OVERRIDE;

  void DoUpdateGUI() ITK_OVERRIDE;

  std::string m_FileName;
  ComplexOutputImageParameter::Pointer m_OutputImageParam;

  QHBoxLayout * m_HLayout;
  QLineEdit*    m_Input;
  QPushButton * m_Button;
  QComboBox*    m_ComboBox;
  int           m_ComplexPixelType;

};


}
}

#endif
