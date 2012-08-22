/***************************************************************************
 * Copyright (C) 2012 Marcus Efraimsson.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a 
 * copy of this software and associated documentation files (the "Software"), 
 * to deal in the Software without restriction, including without limitation 
 * the rights to use, copy, modify, merge, publish, distribute, sublicense, 
 * and/or sell copies of the Software, and to permit persons to whom the 
 * Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included 
 * in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS 
 * OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, 
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL 
 * THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER 
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING 
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER 
 * DEALINGS IN THE SOFTWARE.
 *
 ***************************************************************************/

#pragma once

#include <string>
#include "dvblinkremotehttp.h"
#include "response.h"
#include "request.h"
#include "version.h"

/**
  * Default namespace for DVBLink Remote API library.
  */
namespace dvblinkremote 
{
  /**
    * A constant integer representing the default buffer size.
    */
  const int DVBLINK_REMOTE_DEFAULT_BUFFER_SIZE = 1024;

  /**
    * A constant char representing the EOF string.
    */
  const char DVBLINK_REMOTE_EOF = '\0';

  /**
    * A constant char representing the newline string.
    */
  const char DVBLINK_REMOTE_NEWLINE = '\n';

  /**
    * A constant string for the scheme used to communicate with DVBLink server.
    */
  const std::string DVBLINK_REMOTE_SERVER_URL_SCHEME = "http";

  /**
    * A constant string for the path specifying how to find the resource where DVBLink Remote API requests should be sent to.
    */
  const std::string DVBLINK_REMOTE_SERVER_URL_PATH = "cs/";

  /**
    * A constant string used to format a DVBLink server URL.
    * The default format is &lt;scheme&gt;://&lt;domain&gt;:&lt;port&gt;/&lt;path&gt;.
    * \remark Parameters will be interpreted in the following order:
    * 1. The value of <tt>DVBLINK_REMOTE_SERVER_URL_SCHEME</tt>.
    * 2. The domain/host address of DVBLink server.
    * 3. The port number specifies the base streaming port of DVBLink server.
    * 4. The value of <tt>DVBLINK_REMOTE_SERVER_URL_PATH</tt>.
    */
  const std::string DVBLINK_REMOTE_SERVER_URL_FORMAT = "%s://%s:%ld/%s";

  /**
    * A constant string representing the HTTP method used to communicate with the DVBLink Remote API.
    */
  const std::string DVBLINK_REMOTE_HTTP_METHOD = dvblinkremotehttp::DVBLINK_REMOTE_HTTP_POST_METHOD;
  
  /**
    * A constant string representing the MIME type of the data sent via DVBLink Remote API requests.
    */
  const std::string DVBLINK_REMOTE_HTTP_CONTENT_TYPE = "application/x-www-form-urlencoded; charset=utf-8";

  /**
   * A constant string representing the name of the DVBLink command querystring used for data to be sent in a DVBLink Remote API request.
   */
  const std::string DVBLINK_REMOTE_HTTP_COMMAND_QUERYSTRING = "command";
  
  /**
   * A constant string representing the name of the DVBLink xml data querystring used for data to be sent in a DVBLink Remote API request.
   */
  const std::string DVBLINK_REMOTE_HTTP_XML_PARAM_QUERYSTRING = "xml_param";

  /**
    * A constant string representing the DVBLink command for retrieving channels. 
    */
  const std::string DVBLINK_REMOTE_GET_CHANNELS_CMD = "get_channels";

  /**
    * A constant string representing the DVBLink command for playing a channel. 
    */
  const std::string DVBLINK_REMOTE_PLAY_CHANNEL_CMD = "play_channel";

  /**
    * A constant string representing the DVBLink command for stopping one or several playing channels. 
    */
  const std::string DVBLINK_REMOTE_STOP_CHANNEL_CMD = "stop_channel";

   /**
    * A constant string representing the DVBLink command for searching the electronic program guide (EPG). 
    */
  const std::string DVBLINK_REMOTE_SEARCH_EPG_CMD = "search_epg";

  /**
    * A constant string representing the DVBLink command for retrieving recordings. 
    */
  const std::string DVBLINK_REMOTE_GET_RECORDINGS_CMD = "get_recordings";

  /**
    * A constant string representing the DVBLink command for adding a recording schedule. 
    */
  const std::string DVBLINK_REMOTE_ADD_SCHEDULE_CMD = "add_schedule";

  /**
    * A constant string representing the DVBLink command for removing a recording schedule. 
    */
  const std::string DVBLINK_REMOTE_REMOVE_SCHEDULE_CMD = "remove_schedule";

  /**
    * A constant string representing the DVBLink command for removing a recording. 
    */
  const std::string DVBLINK_REMOTE_REMOVE_RECORDING_CMD = "remove_recording";

  /**
    * A constant string representing the DVBLink command for setting a parental lock. 
    */
  const std::string DVBLINK_REMOTE_SET_PARENTAL_LOCK_CMD = "set_parental_lock";

  /**
    * A constant string representing the DVBLink command for retrieving parental lock status. 
    */
  const std::string DVBLINK_REMOTE_GET_PARENTAL_STATUS_CMD = "get_parental_status";

  /**
    * A constant string representing a Real Time Transport Protocol stream type for Android devices.
    */
  const std::string DVBLINK_REMOTE_STREAM_TYPE_ANDROID = "rtp";

  /**
    * A constant string representing a Http Live stream type for IOS devices.
    */
  const std::string DVBLINK_REMOTE_STREAM_TYPE_IPHONE = "hls";

  /**
    * A constant string representing a Windows Media stream type for Windows phone devices.
    */
  const std::string DVBLINK_REMOTE_STREAM_TYPE_WINPHONE = "asf";

  /**
    * A constant string representing a Raw HTTP stream type.
    */
  const std::string DVBLINK_REMOTE_STREAM_TYPE_RAW_HTTP = "raw_http";

  /**
    * A constant string representing a Raw UDP stream type.
    */
  const std::string DVBLINK_REMOTE_STREAM_TYPE_RAW_UDP = "raw_udp";

  /**
    * An enum representing the different status codes that DVBLink Remote API request could return.
    */
  enum DVBLinkRemoteStatusCode
  {
    DVBLINK_REMOTE_STATUS_OK = 0, /**< DVBLink Remote API command was successful. */ 
    DVBLINK_REMOTE_STATUS_ERROR = 1000, /**< An unspecified error occurred. */ 
    DVBLINK_REMOTE_STATUS_INVALID_DATA = 1001, /**< Invalid request data provided. */ 
    DVBLINK_REMOTE_STATUS_INVALID_PARAM = 1002, /**< Invalid request parameter provided. */ 
    DVBLINK_REMOTE_STATUS_NOT_IMPLEMENTED = 1003, /**< An invalid command was provied to the DVBLink Remote API. */
    DVBLINK_REMOTE_STATUS_MC_NOT_RUNNING = 1005, /**< Windows Media Center is not running. */
    DVBLINK_REMOTE_STATUS_NO_DEFAULT_RECORDER = 1006, /**< No default recorder is configured. */
    DVBLINK_REMOTE_STATUS_MCE_CONNECTION_ERROR = 1008, /**< An error occurred when trying to establish a connection to Windows Media Center. */
    DVBLINK_REMOTE_STATUS_CONNECTION_ERROR = 2000,  /**< An error occurred when trying to connect to the DVBLink Connect! Server. */
    DVBLINK_REMOTE_STATUS_UNAUTHORISED = 2001 /**< An authentication error occurred when trying to establish a connection to the DVBLink Connect! Server. */
  };

  /**
    * A constant string representing a description of the DVBLink Remote API status code <tt>DVBLINK_REMOTE_STATUS_OK</tt>.
    * @see DVBLinkRemoteStatusCode
    */
  const std::string DVBLINK_REMOTE_STATUS_DESC_OK = "DVBLink Remote API command was successful";

  /**
    * A constant string representing a description of the DVBLink Remote API status code <tt>DVBLINK_REMOTE_STATUS_ERROR</tt>.
    * @see DVBLinkRemoteStatusCode
    */
  const std::string DVBLINK_REMOTE_STATUS_DESC_ERROR = "An unspecified error occurred";

  /**
    * A constant string representing a description of the DVBLink Remote API status code <tt>DVBLINK_REMOTE_STATUS_INVALID_DATA</tt>.
    * @see DVBLinkRemoteStatusCode
    */
  const std::string DVBLINK_REMOTE_STATUS_DESC_INVALID_DATA = "Invalid request data provided";

  /**
    * A constant string representing a description of the DVBLink Remote API status code <tt>DVBLINK_REMOTE_STATUS_INVALID_PARAM</tt>.
    * @see DVBLinkRemoteStatusCode
    */
  const std::string DVBLINK_REMOTE_STATUS_DESC_INVALID_PARAM = "Invalid request parameter provided";

  /**
    * A constant string representing a description of the DVBLink Remote API status code <tt>DVBLINK_REMOTE_STATUS_NOT_IMPLEMENTED</tt>.
    * @see DVBLinkRemoteStatusCode
    */
  const std::string DVBLINK_REMOTE_STATUS_DESC_NOT_IMPLEMENTED = "An invalid command was provided to the DVBLink Remote API";

  /**
    * A constant string representing a description of the DVBLink Remote API status code <tt>DVBLINK_REMOTE_STATUS_MC_NOT_RUNNING</tt>.
    * @see DVBLinkRemoteStatusCode
    */
  const std::string DVBLINK_REMOTE_STATUS_DESC_MC_NOT_RUNNING = "Windows Media Center is not running";

  /**
    * A constant string representing a description of the DVBLink Remote API status code <tt>DVBLINK_REMOTE_STATUS_NO_DEFAULT_RECORDER</tt>.
    * @see DVBLinkRemoteStatusCode
    */
  const std::string DVBLINK_REMOTE_STATUS_DESC_NO_DEFAULT_RECORDER = "No default recorder is configured";

  /**
    * A constant string representing a description of the DVBLink Remote API status code <tt>DVBLINK_REMOTE_STATUS_MCE_CONNECTION_ERROR</tt>.
    * @see DVBLinkRemoteStatusCode
    */
  const std::string DVBLINK_REMOTE_STATUS_DESC_MCE_CONNECTION_ERROR = "An error occurred when trying to establish a connection to Windows Media Center";

  /**
    * A constant string representing a description of the DVBLink Remote API status code <tt>DVBLINK_REMOTE_STATUS_CONNECTION_ERROR</tt>.
    * @see DVBLinkRemoteStatusCode
    */
  const std::string DVBLINK_REMOTE_STATUS_DESC_CONNECTION_ERROR = "An error occurred when trying to establish a connection to the DVBLink Connect! Server";

  /**
    * A constant string representing a description of the DVBLink Remote API status code <tt>DVBLINK_REMOTE_STATUS_UNAUTHORISED</tt>.
    * @see DVBLinkRemoteStatusCode
    */
  const std::string DVBLINK_REMOTE_STATUS_DESC_UNAUTHORIZED = "An authentication error occurred when trying to establish a connection to the DVBLink Connect! Server";

  /**
    * Interface representing the available DVBLink Remote API methods. 
    * This is the interface for communicating with a DVBLink Connect! server. This 
    * class is abstract.
    */
  class IDVBLinkRemoteConnection
  {
  public:
    /**
      * Gets a list of all available channels.
      * @param[in]      request   A constant GetChannelsRequest reference representing the get channel request criterias.
      * @param[in,out]  response  A ChannelList reference that will be populated with channels.
      * @return                   A DVBLinkRemoteStatusCode representing the status of the executed method.
      */
    virtual DVBLinkRemoteStatusCode GetChannels(const GetChannelsRequest& request, ChannelList& response) = 0;

    /**
      * Search the electronic program guide (EPG).
      * @param[in]      request   A constant GetChannelsRequest reference representing the EPG search request criterias.
      * @param[in,out]  response  A EpgSearchResult reference that will be populated with ChannelEPGData objects.
      * @return                   A DVBLinkRemoteStatusCode representing the status of the executed method.
      */
    virtual DVBLinkRemoteStatusCode SearchEpg(const EpgSearchRequest& request, EpgSearchResult& response) = 0;

    /**
      * Start stream of a channel.
      * @param[in]      request   A constant StreamRequest reference representing the stream request criterias.
      * @param[in,out]  response  A Stream reference that will be populated with details of a playing stream.
      * @return                   A DVBLinkRemoteStatusCode representing the status of the executed method.
      */
    virtual DVBLinkRemoteStatusCode PlayChannel(const StreamRequest& request, Stream& response) = 0;

    /**
      * Stop a streaming channel or channels.
      * @param[in] request A constant StopStreamRequest reference representing the stop stream request criterias.
      * @return            A DVBLinkRemoteStatusCode representing the status of the executed method.
      */
    virtual DVBLinkRemoteStatusCode StopChannel(const StopStreamRequest& request) = 0;

    /**
      * Gets a list of all recordings.
      * @param[in]      request   A constant GetRecordingsRequest reference representing the get recordings request criterias.
      * @param[in,out]  response  A RecordingList reference that will be populated with Recording objects.
      * @return                   A DVBLinkRemoteStatusCode representing the status of the executed method.
      */
    virtual DVBLinkRemoteStatusCode GetRecordings(const GetRecordingsRequest& request, RecordingList& response) = 0;

    /**
      * Removes a recording.
      * @param[in] request A constant RemoveRecordingRequest reference representing the remove recording request criterias.
      * @return            A DVBLinkRemoteStatusCode representing the status of the executed method.
      */
    virtual DVBLinkRemoteStatusCode RemoveRecording(const RemoveRecordingRequest& request) = 0;

    /**
      * Add a schedule.
      * @param[in] request A constant AddScheduleRequest reference representing the add schedule request criterias.
      * @return            A DVBLinkRemoteStatusCode representing the status of the executed method.
      */
    virtual DVBLinkRemoteStatusCode AddSchedule(const AddScheduleRequest& request) = 0;

    /**
      * Remove a schedule.
      * @param[in] request A constant RemoveScheduleRequest reference representing the remove schedule request criterias.
      * @return            A DVBLinkRemoteStatusCode representing the status of the executed method.
      */
    virtual DVBLinkRemoteStatusCode RemoveSchedule(const RemoveScheduleRequest& request) = 0;

    /**
      * Get parental status.
      * @param[in]      request   A constant GetParentalStatusRequest reference representing the get parental status request criterias.
      * @param[in,out]  response  A ParentalStatus reference that will be populated with parental status details.
      * @return                   A DVBLinkRemoteStatusCode representing the status of the executed method.
      */
    virtual DVBLinkRemoteStatusCode GetParentalStatus(const GetParentalStatusRequest& request, ParentalStatus& response) = 0;

    /**
      * Sets the parental lock.
      * @param[in]      request   A constant SetParentalLockRequest reference representing the set parental lock request criterias.
      * @param[in,out]  response  A ParentalStatus reference that will be populated with parental status details.
      * @return                   A DVBLinkRemoteStatusCode representing the status of the executed method.
      */
    virtual DVBLinkRemoteStatusCode SetParentalLock(const SetParentalLockRequest& request, ParentalStatus& response) = 0;

    /**
      * Gets a description of the last occured error.
      * @param[in,out] err A string reference representing the string where the description of the last error will be provided.
      */
    virtual void GetLastError(std::string& err) = 0;
  };

  /**
    * Class used for connecting to a DVBLink Connect! server.
    */
  class DVBLinkRemote
  {
  public:
    /**
      * Connect to a DVBLink Connect! server and recieve a IDVBLinkRemoteConnection instance for executing DVBLink Remote API methods against it.
      * @param[in] httpClient   A dvblinkremotehttp::HttpClient reference to be used for sending and recieving HTTP requests/responses to/from the DVBLink Connect! server.
      * @param[in] hostAddress  A constanst string reference representing the host address of the DVBLink Connect! server.
      * @param[in] port         A constanst long representing the base streaming port of the DVBLink Connect! server.
      */
    static IDVBLinkRemoteConnection* Connect(dvblinkremotehttp::HttpClient& httpClient, const std::string& hostAddress, const long port);

    /**
      * Connect to a DVBLink Connect! server and recieve a IDVBLinkRemoteConnection instance for executing DVBLink Remote API methods against it.
      * @param[in] httpClient   A dvblinkremotehttp::HttpClient reference to be used for sending and recieving HTTP requests/responses to/from the DVBLink Connect! server.
      * @param[in] hostAddress  A constanst string reference representing the host address of the DVBLink Connect! server.
      * @param[in] port         A constanst long representing the base streaming port of the DVBLink Connect! server.
      * @param[in] username     A constanst string reference representing the user name to be used for authentication towards the DVBLink Connect! server.
      * @param[in] password     A constanst string reference representing the password to be used for authentication towards the DVBLink Connect! server.
      */
    static IDVBLinkRemoteConnection* Connect(dvblinkremotehttp::HttpClient& httpClient, const std::string& hostAddress, const long port, const std::string& username, const std::string& password);

    /**
      * Gets the copyright notice of the DVBLink Remote API library.
      * @param[in,out] copyright A string reference representing the string where the copyright notice will be provided.
      */
    static void GetCopyrightNotice(std::string& copyright);

    /**
      * Gets the version information of the DVBLink Remote API library.
      * @param[in,out] version A string reference representing the string where the version information will be provided.
      */
    static void GetVersion(std::string& version);

    /**
      * Gets the version numbers of the DVBLink Remote API library.
      * @param[in,out] major An integer reference representing the integer where the major version information will be provided.
      * @param[in,out] minor An integer reference representing the integer where the minor version information will be provided.
      * @param[in,out] patch An integer reference representing the integer where the patch version information will be provided.
      */
    static void GetVersion(int& major, int& minor, int& patch);
  };
};
