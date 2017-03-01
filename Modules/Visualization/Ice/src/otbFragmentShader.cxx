/*=========================================================================

  Program:   ORFEO Toolbox
  Language:  C++


  Copyright (c) Centre National d'Etudes Spatiales. All rights reserved.
  See OTBCopyright.txt for details.


     This software is distributed WITHOUT ANY WARRANTY; without even
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
     PURPOSE.  See the above copyright notices for more information.

=========================================================================*/
#include "otbFragmentShader.h"
#include "otbFragmentShaderRegistry.h"

namespace otb
{
FragmentShader::FragmentShader()
{}

FragmentShader::~FragmentShader()
{}

void FragmentShader::BuildShader()
{
  std::string source = this->GetSource();
  std::string name = this->GetName();
  
  try
    {
    // Assumption here is that each shader has its unique name
    if(!otb::FragmentShaderRegistry::Instance()->IsShaderRegistered(name))
      {
      otb::FragmentShaderRegistry::Instance()->RegisterShader(name,source);
      }
    }
  catch(itk::ExceptionObject& err)
    {
    // Log compilation errors if any
    std::cerr<<err<<std::endl;
    }
}

void FragmentShader::LoadShader()
{
  otb::FragmentShaderRegistry::Instance()->LoadShader(GetName());
}

void FragmentShader::UnloadShader()
{
  otb::FragmentShaderRegistry::Instance()->UnloadShader();
}

void FragmentShader::SetupShader()
{
  // // Default always report corners
  // GLint shader_ul = glGetUniformLocation(otb::FragmentShaderRegistry::Instance()->GetShaderProgram("StandardShader"), "shader_ul");

  // glUniform2f(shader_ul,m_UL[0],m_UL[1]);
  // GLint shader_ur = glGetUniformLocation(otb::FragmentShaderRegistry::Instance()->GetShaderProgram("StandardShader"), "shader_ur");
  // glUniform2f(shader_ur,m_UR[0],m_UR[1]);

  // GLint shader_ll = glGetUniformLocation(otb::FragmentShaderRegistry::Instance()->GetShaderProgram("StandardShader"), "shader_ll");
  // glUniform2f(shader_ll,m_LL[0],m_LL[1]);

  // GLint shader_lr = glGetUniformLocation(otb::FragmentShaderRegistry::Instance()->GetShaderProgram("StandardShader"), "shader_lr");
  // glUniform2f(shader_lr,m_LR[0],m_LR[1]);
}

}
