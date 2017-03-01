/*=========================================================================

  Program:   ORFEO Toolbox
  Language:  C++


  Copyright (c) Centre National d'Etudes Spatiales. All rights reserved.
  See OTBCopyright.txt for details.


     This software is distributed WITHOUT ANY WARRANTY; without even
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
     PURPOSE.  See the above copyright notices for more information.

=========================================================================*/
#ifndef otbCommandProgressUpdate_txx
#define otbCommandProgressUpdate_txx

#include "otbCommandProgressUpdate.h"

namespace otb
{

template <class TFilter>
void CommandProgressUpdate<TFilter>::Execute(itk::Object *caller, const itk::EventObject& event)
{
  Execute((const itk::Object *) caller, event);
}

template <class TFilter>
void CommandProgressUpdate<TFilter>::Execute(const itk::Object * object, const itk::EventObject& event)
{
  FilterPointer filter =
    dynamic_cast<FilterPointer>(object);
  if (typeid(event) != typeid(itk::ProgressEvent))
    {
    return;
    }

  int factor = 160;

  int val = int(filter->GetProgress() * factor);

  if ((val % 2) == 0)
    {
    std::cout << "|";
    std::cout.flush();
    }

  if (val == factor)
    {
    std::cout << ">";
    std::cout.flush();
    }
}

} // end namespace otb

#endif
