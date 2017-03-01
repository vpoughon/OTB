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

#include "otbWrapperInputFilenameListParameter.h"
#include "itksys/SystemTools.hxx"

namespace otb
{
namespace Wrapper
{

InputFilenameListParameter::InputFilenameListParameter()
{
  this->SetName("Input Filename List");
  this->SetKey("inList");
  m_FilenameList = StringParameterListType::New();
}

InputFilenameListParameter::~InputFilenameListParameter()
{
}

bool
InputFilenameListParameter::SetListFromFileName(const std::vector<std::string> & filenames)
{
  // First clear previous file chosen
  this->ClearValue();

  bool isOk = true;
  for(unsigned int i=0; i<filenames.size(); i++)
    {
    std::string filename = filenames[i];
    // TODO : when the logger will be available, redirect the exception
    // in the logger (like what is done in MsgReporter)
    // File existence checked by the reader
    if (!filename.empty())
      {
      StringParameter::Pointer strParameter = StringParameter::New();
      strParameter->SetValue(filename);
      try
        {
        strParameter->HasValue();
        }
      catch(itk::ExceptionObject & /*err*/)
        {
        this->ClearValue();
        isOk = false;
        break;
        }

      // everything went fine, store the object reference
      m_FilenameList->PushBack(strParameter);
      }
    }

  if( !isOk )
    {
    return false;
    }

  SetActive(true);
  this->Modified();
  return true;
}


void
InputFilenameListParameter::AddNullElement()
{
  m_FilenameList->PushBack(ITK_NULLPTR);
  SetActive(false);
  this->Modified();
}

bool
InputFilenameListParameter::AddFromFileName(const std::string & filename)
{
  // TODO : when the logger will be available, redirect the exception
  // in the logger (like what is done in MsgReporter)
  // File existence checked by the reader
  if (!filename.empty())
    {
    StringParameter::Pointer strParameter = StringParameter::New();
    strParameter->SetValue(filename);
    try
      {
      strParameter->HasValue();
      }
    catch(itk::ExceptionObject & /*err*/)
      {
      this->ClearValue();
      return false;
      }

    // everything went fine, store the object references
    m_FilenameList->PushBack(strParameter);
    SetActive(true);
    this->Modified();
    return true;
    }

  return false;
}

bool
InputFilenameListParameter::SetNthFileName( const unsigned int id, const std::string & filename )
{
  if( m_FilenameList->Size()<id )
    {
    itkExceptionMacro(<< "No file "<<id<<". Only "<<m_FilenameList->Size()<<" filenames available.");
    }

  // TODO : when the logger will be available, redirect the exception
  // in the logger (like what is done in MsgReporter)
  // File existence checked by the reader
  if (!filename.empty())
    {
    StringParameter::Pointer strParameter = StringParameter::New();
    strParameter->SetValue(filename);
    try
      {
      strParameter->HasValue();
      }
    catch(itk::ExceptionObject &)
      {
      this->ClearValue();
      return false;
      }

    m_FilenameList->SetNthElement(id, strParameter);

    this->Modified();
    return true;
    }

  return false;
}


std::vector<std::string>
InputFilenameListParameter::GetFileNameList() const
{
  if (m_FilenameList)
    {
    std::vector<std::string> filenames;
    for(unsigned int i=0; i<m_FilenameList->Size(); i++)
      {
      if( m_FilenameList->GetNthElement(i) )
        filenames.push_back( m_FilenameList->GetNthElement(i)->GetValue() );
      }

    return filenames;
    }

  itkExceptionMacro(<< "No filename value");
}


std::string
InputFilenameListParameter::GetNthFileName( unsigned int i ) const
{
  if (m_FilenameList)
    {
    if(m_FilenameList->Size()<i)
      {
      itkExceptionMacro(<< "No file "<<i<<". Only "<<m_FilenameList->Size()<<" filenames available.");
      }

    return m_FilenameList->GetNthElement(i)->GetValue();
    }

  itkExceptionMacro(<< "No filename value");
}


InputFilenameListParameter::StringParameterListPointerType
InputFilenameListParameter::GetFileList() const
{
  return m_FilenameList;
}

bool
InputFilenameListParameter::HasValue() const
{
  if(m_FilenameList->Size() == 0)
    {
    return false;
    }

  bool res(true);
  unsigned int i(0);
  while(i < m_FilenameList->Size() && res == true)
    {
    res = m_FilenameList->GetNthElement(i).IsNotNull();
    i++;
    }

  return res;
}


void
InputFilenameListParameter::Erase( unsigned int id )
{
  if(m_FilenameList->Size()<id)
    {
    itkExceptionMacro(<< "No file "<<id<<". Only "<<m_FilenameList->Size()<<" filenames available.");
    }

  m_FilenameList->Erase( id );

  this->Modified();
}

void
InputFilenameListParameter::ClearValue()
{
  m_FilenameList->Clear();

  SetActive(false);
  this->Modified();
}


}
}

