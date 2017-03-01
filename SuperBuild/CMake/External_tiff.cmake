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

INCLUDE_ONCE_MACRO(TIFF)

SETUP_SUPERBUILD(TIFF)

# declare dependencies
ADDTO_DEPENDENCIES_IF_NOT_SYSTEM(TIFF ZLIB JPEG)

ADD_SUPERBUILD_CMAKE_VAR(TIFF ZLIB_INCLUDE_DIR)
ADD_SUPERBUILD_CMAKE_VAR(TIFF ZLIB_LIBRARY)
ADD_SUPERBUILD_CMAKE_VAR(TIFF JPEG_INCLUDE_DIR)
ADD_SUPERBUILD_CMAKE_VAR(TIFF JPEG_LIBRARY)

if(MSVC)
  STRING(REGEX REPLACE "/$" "" CMAKE_WIN_INSTALL_PREFIX ${SB_INSTALL_PREFIX})
  STRING(REGEX REPLACE "/" "\\\\" CMAKE_WIN_INSTALL_PREFIX ${CMAKE_WIN_INSTALL_PREFIX})
  configure_file(${CMAKE_SOURCE_DIR}/patches/TIFF/nmake.opt ${CMAKE_BINARY_DIR}/nmake_libtiff_extra.opt)
  ExternalProject_Add(TIFF_build
    PREFIX TIFF
    URL "http://download.osgeo.org/libtiff/tiff-4.0.6.tar.gz"
    URL_MD5 d1d2e940dea0b5ad435f21f03d96dd72
    SOURCE_DIR ${TIFF_SB_SRC}
    BINARY_DIR ${TIFF_SB_SRC}
    INSTALL_DIR ${SB_INSTALL_PREFIX}
    DOWNLOAD_DIR ${DOWNLOAD_LOCATION}
    DEPENDS ${TIFF_DEPENDENCIES}
    PATCH_COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_BINARY_DIR}/nmake_libtiff_extra.opt ${TIFF_SB_SRC}/nmake.opt
    CONFIGURE_COMMAND ""
    BUILD_COMMAND nmake /f ${TIFF_SB_SRC}/Makefile.vc
    INSTALL_COMMAND ${CMAKE_COMMAND} -E copy  ${CMAKE_SOURCE_DIR}/patches/TIFF/CMakeLists.txt
    ${CMAKE_BINARY_DIR}/TIFF/_install
    )

  ExternalProject_Add(TIFF
    PREFIX TIFF/_install
    DOWNLOAD_COMMAND ""
    SOURCE_DIR TIFF/_install
    BINARY_DIR ${TIFF_SB_BUILD_DIR}
    INSTALL_DIR ${SB_INSTALL_PREFIX}
    DOWNLOAD_DIR ${DOWNLOAD_LOCATION}
    CMAKE_CACHE_ARGS
    -DCMAKE_INSTALL_PREFIX:STRING=${SB_INSTALL_PREFIX}
    -DCMAKE_BUILD_TYPE:STRING=Release
    -DTIFF_BUILD_DIR:STRING=${TIFF_SB_SRC}/libtiff
    DEPENDS TIFF_build
    CMAKE_COMMAND
    )

else()
  ExternalProject_Add(TIFF
    PREFIX TIFF
    URL "http://download.osgeo.org/libtiff/tiff-4.0.6.tar.gz"
    URL_MD5 d1d2e940dea0b5ad435f21f03d96dd72
    SOURCE_DIR ${TIFF_SB_SRC}
    BINARY_DIR ${TIFF_SB_BUILD_DIR}
    INSTALL_DIR ${SB_INSTALL_PREFIX}
    DOWNLOAD_DIR ${DOWNLOAD_LOCATION}
    DEPENDS ${TIFF_DEPENDENCIES}
    CMAKE_CACHE_ARGS
    ${SB_CMAKE_CACHE_ARGS}
    -DCMAKE_INSTALL_LIBDIR:PATH=lib
    -DCMAKE_INSTALL_BINDIR:PATH=bin
    -DBUILD_TESTING:BOOL=OFF
    -Djpeg:BOOL=TRUE
    -Dlzma:BOOL=FALSE
    -Djbig:BOOL=FALSE
    -Dzlib:BOOL=TRUE
    -DWITH_OPENGL:BOOL=FALSE
    -Dpixarlog:BOOL=TRUE
    ${TIFF_SB_CONFIG}
    CMAKE_COMMAND ${SB_CMAKE_COMMAND}
    )
endif()

SUPERBUILD_PATCH_SOURCE(TIFF)

set(_SB_TIFF_INCLUDE_DIR ${SB_INSTALL_PREFIX}/include)
if(WIN32)
  set(_SB_TIFF_LIBRARY ${SB_INSTALL_PREFIX}/lib/libtiff_i.lib)
elseif(UNIX)
  set(_SB_TIFF_LIBRARY ${SB_INSTALL_PREFIX}/lib/libtiff${CMAKE_SHARED_LIBRARY_SUFFIX})
endif()
