#
# This function will prevent in-source builds
function(AssureOutOfSourceBuilds)
  if (${CMAKE_MAJOR_VERSION}.${CMAKE_MINOR_VERSION} GREATER 2.6)
    # make sure the user doesn't play dirty with symlinks
    get_filename_component(srcdir "${CMAKE_SOURCE_DIR}" REALPATH)
    get_filename_component(bindir "${CMAKE_BINARY_DIR}" REALPATH)
  else()
    get_filename_component(srcdir "${CMAKE_SOURCE_DIR}" ABSOLUTE)
    get_filename_component(bindir "${CMAKE_BINARY_DIR}" ABSOLUTE)
  endif()

  # disallow in-source builds
  if("${srcdir}" STREQUAL "${bindir}")
    message("######################################################")
    message("# OTB should not be configured & built in the OTB source directory")
    message("# You must run cmake in a build directory.")
    message("# For example:")
    message("# mkdir OTB-Sandbox ; cd OTB-Sandbox")
    message("# hg clone http://hg.orfeo-toolbox.org/OTB # or download & unpack the source tarball")
    message("# mkdir OTB-Binary ")
    message("# this will create the following directory structure ")
    message("#  ")
    message("# OTB-Sandbox")
    message("#  +--OTB ")
    message("#  +--OTB-Binary ")
    message("#  ")
    message("# Then you can proceed to configure and build ")
    message("# by using the following commands ")
    message("#  ")
    message("# cd OTB-Binary")
    message("# ccmake ../OTB")
    message("# make ")
    message("#  ")
    message("# NOTE: Given that you already tried to make an in-source build")
    message("#       CMake have already created several files & directories")
    message("#       in your source tree. run 'hg status' to find them and")
    message("#       remove them by doing:")
    message("#  ")
    message("#       cd OTB-Sandbox/OTB")
    message("#       hg purge ")
    message("#  ")
    message("######################################################")
    message(FATAL_ERROR "Quitting configuration")
  endif()
endfunction()

AssureOutOfSourceBuilds()