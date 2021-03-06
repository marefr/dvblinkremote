
#############################################################
# sources

SET(DVBLINKREMOTE_SOURCES
	command_interpreter.cpp
	program.cpp
	util.cpp
)

#############################################################
# headers

# public
SET(DVBLINKREMOTE_HEADERS
	command_interpreter.h
	util.h
)

INCLUDE_DIRECTORIES(
  ${CMAKE_CURRENT_SOURCE_DIR}
  "${PROJECT_SOURCE_DIR}/${DVBLINKREMOTE_LIBRARY_NAME}/src"
  ${CURL_INCLUDE_DIR}
  ${TINYXML2_INCLUDE_DIR}
)

#############################################################
# dvblinkremote command line tool

ADD_EXECUTABLE(${DVBLINKREMOTE_EXE_NAME} ${DVBLINKREMOTE_SOURCES} ${DVBLINKREMOTE_HEADERS} ${LIBDVBLINKREMOTE_PUBL_HEADERS})

SET_TARGET_PROPERTIES(${DVBLINKREMOTE_EXE_NAME} PROPERTIES
    VERSION ${LIBDVBLINKREMOTE_VERSION}
    SOVERSION ${LIBDVBLINKREMOTE_VERSION}
)

INSTALL(FILES ${CURL_DLL} DESTINATION ${DVBLINKREMOTE_BIN_DIR})

TARGET_LINK_LIBRARIES(${DVBLINKREMOTE_EXE_NAME} ${DVBLINKREMOTE_LIBRARY_NAME})

# install

INSTALL(TARGETS ${DVBLINKREMOTE_EXE_NAME}
  RUNTIME DESTINATION ${DVBLINKREMOTE_BIN_DIR}
  LIBRARY DESTINATION ${DVBLINKREMOTE_LIB_DIR}
  ARCHIVE DESTINATION ${DVBLINKREMOTE_LIB_DIR}
  FRAMEWORK DESTINATION ${DVBLINKREMOTE_FW_SUBDIR}
  PUBLIC_HEADER DESTINATION ${DVBLINKREMOTE_INCLUDE_DIR})