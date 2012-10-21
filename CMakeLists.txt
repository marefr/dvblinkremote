SET(LIBDVBLINKREMOTE_COPYRIGHT "2012 Marcus Efraimsson")
SET(LIBDVBLINKREMOTE_VERSION_MAJOR 0)
SET(LIBDVBLINKREMOTE_VERSION_MINOR 2)
SET(LIBDVBLINKREMOTE_VERSION_PATCH 0)
SET(LIBDVBLINKREMOTE_VERSION ${LIBDVBLINKREMOTE_VERSION_MAJOR}.${LIBDVBLINKREMOTE_VERSION_MINOR}.${LIBDVBLINKREMOTE_VERSION_PATCH})
SET(LIBDVBLINKREMOTE_RELEASE_NAME "Master")
SET(DVBLINKREMOTE_LIBRARY_NAME "libdvblinkremote")
SET(DVBLINKREMOTE_EXE_NAME "dvblinkremote")
PROJECT(dvblinkremote)

MATH(EXPR DVBLINKREMOTE_VERSION_INT "${LIBDVBLINKREMOTE_VERSION_MAJOR}*10000+${LIBDVBLINKREMOTE_VERSION_MINOR}*100+${LIBDVBLINKREMOTE_VERSION_PATCH}")
MESSAGE(STATUS "DVBLink Remote API Library version: ${LIBDVBLINKREMOTE_VERSION} ${LIBDVBLINKREMOTE_RELEASE_NAME} (${DVBLINKREMOTE_VERSION_INT})")

#############################################################
# CMake settings

# 2.8.8 minumum required version of CMake
CMAKE_MINIMUM_REQUIRED(VERSION 2.8.8)

SET (WITH_COMMAND_LINE_TOOL TRUE CACHE BOOL "Determines whether DVBLink Remote command line tool should be built")

# set path to additional CMake modules
SET(CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake ${CMAKE_MODULE_PATH})

#############################################################
# search for dependencies

SET (WITH_CURL TRUE CACHE BOOL "Determines whether cURL support should be included or not")

IF(NOT WITH_CURL)
	SET(WITH_COMMAND_LINE_TOOL false)
ENDIF()

IF(WITH_COMMAND_LINE_TOOL)
	SET(WITH_CURL true)
ENDIF()

IF(WITH_CURL)
  FIND_LIBRARY(CURL_LIBRARY NAMES libcurld REQUIRED)
  FIND_FILE(CURL_DLL NAMES libcurld.dll REQUIRED)
  FIND_PACKAGE(CURL REQUIRED)
  ADD_LIBRARY(CURL SHARED IMPORTED)
  SET_PROPERTY(TARGET CURL PROPERTY IMPORTED_LOCATION "${CURL_DLL}")
  SET_PROPERTY(TARGET CURL PROPERTY IMPORTED_IMPLIB "${CURL_LIBRARY}")
ENDIF()

FIND_PACKAGE(TINYXML2 REQUIRED)
ADD_LIBRARY(TINYXML2 STATIC IMPORTED)
SET_PROPERTY(TARGET TINYXML2 PROPERTY IMPORTED_LOCATION "${TINYXML2_LIBRARY}")

#############################################################
# platform specific stuff

IF(WIN32)
  SET (DEFAULT_LIB_SUBDIR lib)
  SET (DEFAULT_INCLUDE_SUBDIR "include/libdvblinkremote")
  SET (DEFAULT_DOC_SUBDIR "doc")

  IF(MSVC)
    SET (DEFAULT_BIN_SUBDIR bin)
    # put all the build products into a single directory
    # under build (doesnt affect install target) to make for
    # easier debugging.

    # Turn on defines for non standard maths stuff
    ADD_DEFINITIONS(-D_USE_MATH_DEFINES)

    # Turn off deprecation warnings
    ADD_DEFINITIONS(-D_CRT_SECURE_NO_WARNINGS)
    ADD_DEFINITIONS(-D_CRT_NONSTDC_NO_WARNINGS)

    IF(CMAKE_BUILD_TYPE MATCHES Debug OR CMAKE_BUILD_TYPE MATCHES RelWithDebInfo)
      MESSAGE (STATUS "Generating browse files")
      ADD_DEFINITIONS( /FR )
    ENDIF()

    IF(INSTALL_DEPS)
      INSTALL(DIRECTORY ${INSTALL_DEPS} DESTINATION .)
    ENDIF()
  ELSE()
    SET (DEFAULT_BIN_SUBDIR .)
  ENDIF(MSVC)
ENDIF()

#############################################################
# user-changeable settings which can be used to customize
# layout of DVBLink Remote API library installation
# (default values are platform-specific)

SET (DVBLINKREMOTE_BIN_SUBDIR ${DEFAULT_BIN_SUBDIR} CACHE STRING "Subdirectory where executables will be installed")
SET (DVBLINKREMOTE_LIB_SUBDIR ${DEFAULT_LIB_SUBDIR} CACHE STRING "Subdirectory where libraries will be installed")
SET (DVBLINKREMOTE_INCLUDE_SUBDIR ${DEFAULT_INCLUDE_SUBDIR} CACHE STRING "Subdirectory where header files will be installed")
SET (DVBLINKREMOTE_DOC_SUBDIR ${DEFAULT_DOC_SUBDIR} CACHE STRING "Subdirectory where documentation files will be installed")

# mark *_SUBDIR variables as advanced as this is not something
# that an average user would use
MARK_AS_ADVANCED (
	DVBLINKREMOTE_BIN_SUBDIR 
	DVBLINKREMOTE_LIB_SUBDIR 
	DVBLINKREMOTE_INCLUDE_SUBDIR
	DVBLINKREMOTE_DOC_SUBDIR
)

# full paths for the installation
SET (DVBLINKREMOTE_BIN_DIR ${DVBLINKREMOTE_BIN_SUBDIR})
SET (DVBLINKREMOTE_LIB_DIR ${DVBLINKREMOTE_LIB_SUBDIR})
SET (DVBLINKREMOTE_INCLUDE_DIR ${DVBLINKREMOTE_INCLUDE_SUBDIR})
SET (DVBLINKREMOTE_DOC_DIR ${DVBLINKREMOTE_DOC_SUBDIR})

# set the default locations where the targets (executables, libraries) will land when compiled
# this is to allow running DVBLinkRemote from the source tree without having to actually do a "make install"
SET (DVBLINKREMOTE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/output)
SET (CMAKE_RUNTIME_OUTPUT_DIRECTORY ${DVBLINKREMOTE_OUTPUT_DIRECTORY}/${DVBLINKREMOTE_BIN_SUBDIR})
SET (CMAKE_LIBRARY_OUTPUT_DIRECTORY ${DVBLINKREMOTE_OUTPUT_DIRECTORY}/${DVBLINKREMOTE_LIB_SUBDIR})

# write a marker with source directory path into the output's bin directory
# if run from the build directory DVBLink Remote will detect it and alter the paths
FILE(WRITE ${DVBLINKREMOTE_OUTPUT_DIRECTORY}/${DVBLINKREMOTE_BIN_SUBDIR}/path.txt "${CMAKE_SOURCE_DIR}\n${DVBLINKREMOTE_OUTPUT_DIRECTORY}")

#############################################################
# process subdirs

ADD_SUBDIRECTORY(dvblinkremote)
ADD_SUBDIRECTORY(libdvblinkremote)
ADD_SUBDIRECTORY(doc)

#############################################################
# install license file
INSTALL(FILES "${CMAKE_CURRENT_SOURCE_DIR}/COPYING" DESTINATION .)

#############################################################
# Enable packaging

SET(CPACK_GENERATOR "ZIP")
SET(CPACK_PACKAGE_NAME "dvblinkremote")
SET(CPACK_PACKAGE_VERSION_MAJOR "${LIBDVBLINKREMOTE_VERSION_MAJOR}")
SET(CPACK_PACKAGE_VERSION_MINOR "${LIBDVBLINKREMOTE_VERSION_MINOR}")
SET(CPACK_PACKAGE_VERSION_PATCH "${LIBDVBLINKREMOTE_VERSION_PATCH}")

INCLUDE(CPack)

#############################################################
# Print all variables

#get_cmake_property(_variableNames VARIABLES)
#foreach (_variableName ${_variableNames})
#    message(STATUS "${_variableName}=${${_variableName}}")
#endforeach()
