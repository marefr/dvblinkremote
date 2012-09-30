
#############################################################
# sources

SET(LIBDVBLINKREMOTE_SOURCES
	add_manual_schedule_request.cpp 
	add_schedule_by_epg_request.cpp 
	add_schedule_request.cpp 
	add_schedule_request_serializer.cpp 
	channel.cpp 
	dvblinkremote.cpp 
	dvblinkremotecommunication.cpp 
	dvblinkremotehttp.cpp 
	epg.cpp 
	generic_response.cpp 
	get_recordings_request.cpp 
	http_live_stream_request.cpp 
	parental_lock.cpp 
	program.cpp 
	raw_http_stream_request.cpp 
	raw_udp_stream_request.cpp 
	recording.cpp 
	remove_recording_request.cpp 
	remove_schedule_request.cpp 
	rtp_stream_request.cpp 
	stop_stream_request.cpp 
	stream.cpp stream_request.cpp 
	stream_request_serializer.cpp 
	transcoded_video_stream_request.cpp 
	transcoding_options.cpp 
	util.cpp 
	windows_media_stream_request.cpp 
	xml_object_serializer.cpp
)

#############################################################
# headers

# public
SET(LIBDVBLINKREMOTE_PUBL_HEADERS
	dvblinkremote.h 
	dvblinkremotehttp.h 
	request.h 
	response.h 
	${CMAKE_BINARY_DIR}/version.h 
)

IF(WITH_CURL AND CURL_FOUND)
  SET(LIBDVBLINKREMOTE_SOURCES
    ${LIBDVBLINKREMOTE_SOURCES}
    curlhttpclient.cpp
  )
  
  SET(LIBDVBLINKREMOTE_PUBL_HEADERS
    ${LIBDVBLINKREMOTE_PUBL_HEADERS}
    curlhttpclient.h
  )
  
  INCLUDE_DIRECTORIES(
    ${CURL_INCLUDE_DIR}
  )
ENDIF()

# internal

SET(LIBDVBLINKREMOTE_INT_HEADERS
	dvblinkremoteconnection.h 
	generic_response.h 
	util.h
)

INCLUDE_DIRECTORIES(
  ${CMAKE_CURRENT_SOURCE_DIR}
  ${TINYXML2_INCLUDE_DIR}
)

#############################################################
# dvblinkremote library

ADD_LIBRARY(${DVBLINKREMOTE_LIBRARY_NAME} STATIC ${LIBDVBLINKREMOTE_SOURCES} ${LIBDVBLINKREMOTE_PUBL_HEADERS} ${LIBDVBLINKREMOTE_INT_HEADERS})

IF(WITH_CURL AND CURL_FOUND)
  SET_TARGET_PROPERTIES(${DVBLINKREMOTE_LIBRARY_NAME} PROPERTIES
    VERSION ${LIBDVBLINKREMOTE_VERSION}
    SOVERSION ${LIBDVBLINKREMOTE_VERSION}
    IMPORTED_LINK_INTERFACE_LIBRARIES ${CURL_LIBRARY}
    IMPORTED_LINK_DEPENDENT_LIBRARIES ${CURL_LIBRARY}
    IMPORTED_IMPLIB ${CURL_LIBRARY}
    LINK_INTERFACE_LIBRARIES ${CURL_LIBRARY}
 )
ELSE()
  SET_TARGET_PROPERTIES(${DVBLINKREMOTE_LIBRARY_NAME} PROPERTIES
    VERSION ${LIBDVBLINKREMOTE_VERSION}
    SOVERSION ${LIBDVBLINKREMOTE_VERSION}
  )
ENDIF()

INSTALL(FILES ${LIBDVBLINKREMOTE_PUBL_HEADERS} DESTINATION ${DVBLINKREMOTE_INCLUDE_DIR})

IF(WITH_CURL AND CURL_FOUND)
  TARGET_LINK_LIBRARIES(${DVBLINKREMOTE_LIBRARY_NAME} CURL TINYXML2)
ELSEIF()
  TARGET_LINK_LIBRARIES(${DVBLINKREMOTE_LIBRARY_NAME} TINYXML2)
ENDIF()

# install

INSTALL(TARGETS ${DVBLINKREMOTE_LIBRARY_NAME} DESTINATION ${DVBLINKREMOTE_LIB_DIR} EXPORT libdvblinkremote-targets)
install(EXPORT libdvblinkremote-targets DESTINATION ${DVBLINKREMOTE_LIB_DIR})