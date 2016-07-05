# - Try to find OML2
#
# Once done this will define
#  OML2_FOUND        - System has liboml2
#  OML2_INCLUDE_DIRS - The liboml2 include directories
#  OML2_LIBRARIES    - The liboml2 libraries
#
# The following variables are used:
#  OML2_DIR          - Environment variable giving liboml2 install directory
#  OML2_SRCDIR       - Directory containing liboml2 sources
#  OML2_BUILDDIR     - Directory containing liboml2 build

find_package(PkgConfig)
pkg_check_modules(PC_OML2 QUIET oml2)

FIND_PATH(
    OML2_INCLUDE_DIRS
    NAMES   oml2/omlc.h
    HINTS   $ENV{OML2_DIR}/include
            ${PC_OML2_INCLUDEDIR}
            ${CMAKE_INSTALL_PREFIX}/include
    PATHS   /usr/local/include 
            /usr/include 
)

FIND_LIBRARY(
    OML2_LIBRARY
    NAMES   oml2
    HINTS   $ENV{OML2_DIR}/lib
            ${PC_OML2_LIBDIR}
            ${CMAKE_INSTALL_PREFIX}/lib
            ${CMAKE_INSTALL_PREFIX}/lib64
    PATHS   /usr/local/lib
            /usr/local/lib64
            /usr/lib
            /usr/lib64
)


SET(OML2_LIBRARIES    ${OML2_LIBRARY})

message(STATUS "OML2 LIBRARIES: " ${OML2_LIBRARIES})
message(STATUS "OML2 INCLUDE DIRS: " ${OML2_INCLUDE_DIRS})

INCLUDE(FindPackageHandleStandardArgs)
FIND_PACKAGE_HANDLE_STANDARD_ARGS(OML2 DEFAULT_MSG OML2_LIBRARIES OML2_INCLUDE_DIRS)
MARK_AS_ADVANCED(OML2_LIBRARIES OML2_INCLUDE_DIRS)
