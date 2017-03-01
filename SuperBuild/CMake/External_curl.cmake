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

INCLUDE_ONCE_MACRO(CURL)

SETUP_SUPERBUILD(CURL)

# declare dependencies
ADDTO_DEPENDENCIES_IF_NOT_SYSTEM(CURL ZLIB)

if(NOT APPLE)
  ADDTO_DEPENDENCIES_IF_NOT_SYSTEM(OPENSSL)
endif()

if(MSVC)
  if(NOT BUILD_SHARED_LIBS)
    message(FATAL_ERROR "static build or curl not supported")
    return()
  endif()

  if(OTB_TARGET_SYSTEM_ARCH_IS_X64)
    set(CURL_INSTALL_DIR_PREFIX "libcurl-vc-x64")
  else()
    set(CURL_INSTALL_DIR_PREFIX "libcurl-vc-x86")
  endif()

  set(CURL_INSTALL_DIR_PREFIX "${CURL_INSTALL_DIR_PREFIX}-release-dll-zlib-dll-ipv6-sspi-winssl")

  ExternalProject_Add(CURL
  PREFIX CURL
  URL "http://curl.haxx.se/download/curl-7.40.0.tar.gz"
  URL_MD5 58943642ea0ed050ab0431ea1caf3a6f
  SOURCE_DIR ${CURL_SB_SRC}
  BINARY_DIR ${CURL_SB_SRC}/winbuild
  INSTALL_DIR ${SB_INSTALL_PREFIX}
  DOWNLOAD_DIR ${DOWNLOAD_LOCATION}
  DEPENDS ${CURL_DEPENDENCIES}
  CONFIGURE_COMMAND ""
  BUILD_COMMAND nmake /f ${CURL_SB_SRC}/winbuild/Makefile.vc mode=dll WITH_ZLIB=dll WITH_DEVEL=${SB_INSTALL_PREFIX}
  INSTALL_COMMAND ${CMAKE_COMMAND} -E copy_directory
  ${CURL_SB_SRC}/builds/${CURL_INSTALL_DIR_PREFIX}/ ${SB_INSTALL_PREFIX}
  )

else(UNIX)

  ExternalProject_Add(CURL
    PREFIX CURL
    URL "http://curl.haxx.se/download/curl-7.40.0.tar.gz"
    URL_MD5 58943642ea0ed050ab0431ea1caf3a6f
    BINARY_DIR ${CURL_SB_BUILD_DIR}
    INSTALL_DIR ${SB_INSTALL_PREFIX}
    DOWNLOAD_DIR ${DOWNLOAD_LOCATION}
    CMAKE_CACHE_ARGS
    ${SB_CMAKE_CACHE_ARGS}
    -DBUILD_CURL_TESTS:BOOL=OFF
    -DBUILD_CURL_EXE:BOOL=ON
    -DCMAKE_USE_OPENSSL:BOOL=${SB_ENABLE_OPENSSL_CURL}
    -DCMAKE_USE_LIBSSH2:BOOL=OFF
    -DCURL_DISABLE_LDAP:BOOL=ON
    -DCMAKE_USE_OPENLDAP:BOOL=OFF
    ${CURL_SB_CONFIG}
    DEPENDS ${CURL_DEPENDENCIES}
    CMAKE_COMMAND ${SB_CMAKE_COMMAND}
    LOG_CONFIGURE 1
    LOG_BUILD 1
    LOG_INSTALL 1
    )
endif()

SUPERBUILD_UPDATE_CMAKE_VARIABLES(CURL TRUE)
