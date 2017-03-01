/*=========================================================================

  Program:   ORFEO Toolbox
  Language:  C++


  Copyright (c) Centre National d'Etudes Spatiales. All rights reserved.
  See OTBCopyright.txt for details.


     This software is distributed WITHOUT ANY WARRANTY; without even
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
     PURPOSE.  See the above copyright notices for more information.

=========================================================================*/
#ifndef otbWrapperQtWidgetChoiceParameter_h
#define otbWrapperQtWidgetChoiceParameter_h

#include <QtGui>
#ifndef Q_MOC_RUN  // See: https://bugreports.qt-project.org/browse/QTBUG-22829  //tag=QT4-boost-compatibility
#include "otbWrapperChoiceParameter.h"
#include "otbWrapperQtWidgetParameterBase.h"
#endif //tag=QT4-boost-compatibility

namespace otb
{
namespace Wrapper
{

/** \class QtWidgetChoiceParameter
 * \brief
 *
 * \ingroup OTBQtWidget
 */
class OTBQtWidget_EXPORT QtWidgetChoiceParameter : public QtWidgetParameterBase
{
  Q_OBJECT
public:
  QtWidgetChoiceParameter(ChoiceParameter*, QtWidgetModel*);
  ~QtWidgetChoiceParameter() ITK_OVERRIDE;

protected slots:
  void SetValue( int value );

private:
  QtWidgetChoiceParameter(const QtWidgetChoiceParameter&); //purposely not implemented
  void operator=(const QtWidgetChoiceParameter&); //purposely not implemented

  void DoCreateWidget() ITK_OVERRIDE;

  void DoUpdateGUI() ITK_OVERRIDE;

  ChoiceParameter::Pointer m_ChoiceParam;

  QHBoxLayout*    m_MainHLayout;

  QComboBox*      m_ComboBox;
  QStackedWidget* m_StackWidget;

  QVBoxLayout*    m_VLayout;
  QGroupBox*      m_VLayoutGroup;

  typedef std::vector<QtWidgetParameterBase*> WidgetListType;
  typedef WidgetListType::iterator WidgetListIteratorType;
  WidgetListType m_WidgetList;
};

}
}

#endif
