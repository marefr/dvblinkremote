# - Find the tinyxml2 includes and library
# This module defines
#  TINYXML2_INCLUDE_DIR, where to find tinyxml.h, etc.
#  TINYXML2_LIBRARY, the libraries required to use tinyxml2.
#  TINYXML2_FOUND, If false, do not try to use tinyxml2.

FIND_PATH(TINYXML2_INCLUDE_DIR tinyxml2/tinyxml2.h)
FIND_LIBRARY(TINYXML2_LIBRARY NAMES tinyxml2)

# handle the QUIETLY and REQUIRED arguments and set TINYXML2_FOUND to TRUE if 
# all listed variables are TRUE
INCLUDE(${CMAKE_ROOT}/Modules/FindPackageHandleStandardArgs.cmake)
FIND_PACKAGE_HANDLE_STANDARD_ARGS(TINYXML2 DEFAULT_MSG TINYXML2_LIBRARY TINYXML2_INCLUDE_DIR)

MARK_AS_ADVANCED(TINYXML2_INCLUDE_DIR TINYXML2_LIBRARY)
