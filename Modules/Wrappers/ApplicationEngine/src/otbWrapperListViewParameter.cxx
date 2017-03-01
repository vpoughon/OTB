/*=========================================================================

  Program:   ORFEO Toolbox
  Language:  C++


  Copyright (c) Centre National d'Etudes Spatiales. All rights reserved.
  See OTBCopyright.txt for details.


     This software is distributed WITHOUT ANY WARRANTY; without even
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
     PURPOSE.  See the above copyright notices for more information.

=========================================================================*/
#include "otbWrapperListViewParameter.h"

namespace otb
{
namespace Wrapper
{

ListViewParameter::ListViewParameter()
  : m_ChoiceList(),
    m_CurrentChoice(0),
    m_SelectedItems(),
    m_SelectedKeys(),
    m_SelectedNames(),
    m_SingleSelection(false)
{
}

ListViewParameter::~ListViewParameter()
{
}


void
ListViewParameter::AddChoice( std::string choicekey, std::string choiceName )
{
  ListViewChoice choice;
  choice.m_Key = choicekey;
  choice.m_Name = choiceName;
  m_ChoiceList.push_back(choice);
}

std::string
ListViewParameter::GetChoiceKey( int i )
{
  if (m_ChoiceList.empty())
  {
    return "";
  }
  else
  {
    return m_ChoiceList[i].m_Key;
  }
}


std::vector<std::string>
ListViewParameter::GetChoiceKeys( )
{
  std::vector<std::string> ret;
  ChoiceList::iterator it = m_ChoiceList.begin();

  for (it = m_ChoiceList.begin(); it != m_ChoiceList.end(); ++it)
    {
    ret.push_back(it->m_Key);
    }

  return ret;
}


std::string
ListViewParameter::GetChoiceName( int i )
{
  if (m_ChoiceList.empty())
  {
    return "";
  }
  else
  {
    return m_ChoiceList[i].m_Name;
  }
}


std::vector<std::string>
ListViewParameter::GetChoiceNames( )
{
  std::vector<std::string> ret;
  ChoiceList::iterator it = m_ChoiceList.begin();

  for (it = m_ChoiceList.begin(); it != m_ChoiceList.end(); ++it)
    {
    ret.push_back(it->m_Name);
    }
  return ret;
}

unsigned int
ListViewParameter::GetNbChoices( void )
{
  return m_ChoiceList.size();
}

void
ListViewParameter::SetValue(unsigned int v)
{
  std::vector<int> selectedItems(1,v);
  m_CurrentChoice = v;
  this->SetSelectedItems(selectedItems);
  SetActive(true);
  // Call Modified();
  this->Modified();
}

void
ListViewParameter::SetValue(std::string choiceKey)
{
  ChoiceList::iterator it = m_ChoiceList.begin();

  unsigned int i = 0;
  for (it = m_ChoiceList.begin(); it != m_ChoiceList.end(); ++it)
    {
    if ( it->m_Key == choiceKey )
      {
      SetValue(i);
      return;
      }
    ++i;
    }

  itkExceptionMacro(<< "Cannot find " << choiceKey);
}

unsigned int
ListViewParameter::GetValue()
{
  return m_CurrentChoice;
}


/** Clear choices */
void
ListViewParameter::ClearChoices()
{
  m_ChoiceList.clear();
}


void
ListViewParameter::SetSelectedNames(std::vector<std::string> selectedNames)
{
  std::vector<int> selectedItems;
  std::vector<std::string> names = this->GetChoiceNames();

  if(m_SingleSelection && selectedNames.size() > 1)
    {
    itkExceptionMacro(<<"Single selection mode is on, but there are "<<selectedNames.size()<<" selected items");
    }
  
  for(unsigned int i=0; i<selectedNames.size(); i++)
    {
    const std::string selectedName = selectedNames[i];
    unsigned int j(0);
      for(; j<names.size(); j++)
      {
      if( names[j] == selectedName )
            {
        selectedItems.push_back(j);
        break;
        }
      }
    // If not found
    if( j==names.size() )
      {
      std::ostringstream oss;
      for( j=0; j<names.size(); j++)
        {
        oss<<names[j];
        if( j < names.size()-1 )
          {
          oss<<", ";
          }
        }
      itkExceptionMacro("Value "<<selectedName<<" not found in the list of choices: "<<oss.str()<<".");
      }
    }
  this->SetSelectedItems(selectedItems);
}


void
ListViewParameter::SetSelectedKeys(std::vector<std::string> selectedKeys)
{
  std::vector<int> selectedItems;
  std::vector<std::string> keys = this->GetChoiceKeys();

if(m_SingleSelection && m_SelectedKeys.size() > 1)
    {
    itkExceptionMacro(<<"Single selection mode is on, but there are "<<m_SelectedKeys.size()<<" selected items");
    }
  
  for(unsigned int i=0; i<m_SelectedKeys.size(); i++)
    {
    const std::string selectedKey = selectedKeys[i];
    unsigned int j(0);
    std::ostringstream oss;
      for(; j<keys.size(); j++)
      {
      if( keys[j] == selectedKey )
            {
        selectedItems.push_back(j);
        break;
        }
      }
    // If not found
    if( j==keys.size() )
      {
      for( j=0; j<keys.size(); j++)
        {
        oss<<keys[j];
        if( j < keys.size()-1 )
          {
          oss<<", ";
          }
        }
      itkExceptionMacro("Value "<<selectedKey<<" not found in the list of choices: "<<oss.str()<<".");
      }
    }
  this->SetSelectedItems(selectedItems);
}
}
}
