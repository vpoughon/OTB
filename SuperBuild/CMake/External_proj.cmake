#
# Copyright (C) 2005-2016 Centre National d'Etudes Spatiales (CNES)
#
# This file is part of Orfeo Toolbox
#
#     https://www.orfeo-toolbox.org/
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#     http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.
#

INCLUDE_ONCE_MACRO(PROJ)

SETUP_SUPERBUILD(PROJ)

if(MSVC)
  ExternalProject_Add(PROJ
    PREFIX PROJ
    URL "http://download.osgeo.org/proj/proj-4.8.0.tar.gz"
    URL_MD5 d815838c92a29179298c126effbb1537
    SOURCE_DIR ${PROJ_SB_SRC}
    BINARY_DIR ${PROJ_SB_SRC}
    INSTALL_DIR ${SB_INSTALL_PREFIX}
    DOWNLOAD_DIR ${DOWNLOAD_LOCATION}
    CONFIGURE_COMMAND ""
    BUILD_COMMAND nmake /f ${PROJ_SB_SRC}/makefile.vc
    INSTALL_COMMAND nmake /f ${PROJ_SB_SRC}/makefile.vc install-all INSTDIR=${SB_INSTALL_PREFIX_NATIVE}
    )

else()

  if(APPLE)
    set(PROJ_SB_ENV_CONFIGURE_CMD ${SB_ENV_CONFIGURE_CMD} LDFLAGS=-headerpad_max_install_names)
  else()
    set(PROJ_SB_ENV_CONFIGURE_CMD ${SB_ENV_CONFIGURE_CMD})
  endif()

  ExternalProject_Add(PROJ
    PREFIX PROJ
    URL "http://download.osgeo.org/proj/proj-4.8.0.tar.gz"
    URL_MD5 d815838c92a29179298c126effbb1537
    BINARY_DIR ${PROJ_SB_SRC}
    INSTALL_DIR ${SB_INSTALL_PREFIX}
    DOWNLOAD_DIR ${DOWNLOAD_LOCATION}
    CONFIGURE_COMMAND
    ${SB_ENV_CONFIGURE_CMD}
    ${PROJ_SB_SRC}/configure
    --prefix=${SB_INSTALL_PREFIX}
    --enable-static=no
    BUILD_COMMAND $(MAKE)
    INSTALL_COMMAND $(MAKE) install
    )

endif()

SUPERBUILD_PATCH_SOURCE(PROJ)

set(_SB_PROJ_INCLUDE_DIR ${SB_INSTALL_PREFIX}/include)
if(WIN32)
  set(_SB_PROJ_LIBRARY ${SB_INSTALL_PREFIX}/lib/proj_i.lib)
elseif(UNIX)
  set(_SB_PROJ_LIBRARY ${SB_INSTALL_PREFIX}/lib/libproj${CMAKE_SHARED_LIBRARY_SUFFIX})
endif()
