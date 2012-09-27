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
#include <vector>

namespace dvblinkremote {
  /** 
    * Base class for DVBLink Client requests.
    */
  class Request { };

  /**
    * Class for defining a get channels request. 
    * This is used as input parameter for the DVBLinkClient::GetChannels method.
    * @see Channel::Channel()
    * @see DVBLinkClient::GetChannels()
    */
  class GetChannelsRequest : public Request
  {
  public:
    /**
      * Initializes a new instance of the dvblinkremote::GetChannelsRequest class.
      */
    GetChannelsRequest();

    /**
      * Destructor for cleaning up allocated memory.
      */
    ~GetChannelsRequest();
  };

  /**
    * Represent a strongly typed list of channel identifiers.
    * @see Channel::GetID()
    */
  class ChannelIdentifierList : public std::vector<std::string>
  { 
  public:
    /**
      * Initializes a new instance of the dvblinkremote::ChannelIdentifierList class.
      */
    ChannelIdentifierList();

    /**
      * Destructor for cleaning up allocated memory.
      */
    ~ChannelIdentifierList();
  };

  //TODO: PAE: Add description
  class RemoveObjectRequest : public Request 
  {
  public:
    RemoveObjectRequest(const std::string& objectId);
    ~RemoveObjectRequest();
    std::string ObjectID;
  };


  enum OBJECT_TYPE{OBJECT_TYPE_UNKNOWN = -1,OBJECT_TYPE_CONTAINER = 0,OBJECT_TYPE_ITEM = 1};
  enum ITEM_TYPE{ITEM_TYPE_UNKNOWN = -1, ITEM_TYPE_RECORDED_TV = 0, ITEM_TYPE_VIDEO = 1, ITEM_TYPE_AUDIO = 2, ITEM_TYPE_IMAGE = 3};

  class GetObjectRequest : public Request
  {
  public:

	  GetObjectRequest(const std::string serverAddress,const std::string objectId = "", const OBJECT_TYPE objectType = OBJECT_TYPE_UNKNOWN, const ITEM_TYPE itemType = ITEM_TYPE_UNKNOWN, const int startPosition = 0, const int requestCount = -1, const bool childrenRequest = false);

    ~GetObjectRequest();

	OBJECT_TYPE ObjectType;
	ITEM_TYPE ItemType;

	int StartPosition;
	int RequestCount;
	bool ChildrenRequest;

	std::string GetServerAddress();
	std::string GetObjectID();

  private:
	  std::string m_serverAddress;
	  std::string m_objectId;


  };

 

  /**
    * Class for defining an electronic program guide (EPG) search request. 
    * This is used as input parameter for the DVBLinkClient::SearchEpg method.
    * @see DVBLinkClient::SearchEpg()
    */
  class EpgSearchRequest : public Request
  {
  public:
    /**
      * Constant long value which specifies that a time value not is bound.
      * Used for the <tt>start time</tt> and <tt>end time</tt>.
      * @see EpgSearchRequest::EpgSearchRequest
      * @see EpgSearchRequest::GetStartTime()
      * @see EpgSearchRequest::SetStartTime
      * @see EpgSearchRequest::GetEndTime()
      * @see EpgSearchRequest::SetEndTime
      */
    static const long EPG_SEARCH_TIME_NOT_BOUND;

    /**
      * Initializes a new instance of the dvblinkremote::EpgSearchRequest class.
      * @param channelId a constant string reference representing the channel identifier for searching the epg.
      * @param startTime an optional constant long representing the start time of programs for searching the epg.
      * @param endTime an optional constant long representing the end time of programs for searching the epg.
      * @param shortEpg an optional constant boolean representing a flag for the level of returned EPG information 
      * from the epg search.
      * \remark By setting a \p startTime or \p endTime the search will only return programs that fully or partially fall 
      * into a specified time span. One of the parameters \p startTime or \p endTime may be -1 
      * (EpgSearchRequest::EPG_SEARCH_TIME_NOT_BOUND), meaning that the search is not bound on the start time or end time side.
      * \remark \p startTime and \p endTime is the number of seconds, counted from UNIX epoc: 00:00:00 UTC on 1 January 1970.
      * \remark \p shortEpg specifies the level of returned EPG information and allows for faster EPG overview build up. 
      * Short EPG information includes only program id, name, start time, duration and genre info. Default value is false.
      */
    EpgSearchRequest(const std::string& channelId, const long startTime = EPG_SEARCH_TIME_NOT_BOUND, const long endTime = EPG_SEARCH_TIME_NOT_BOUND, const bool shortEpg = false);

    /**
      * Initializes a new instance of the dvblinkremote::EpgSearchRequest class.
      * @param channelIdentifierList a constant dvblinkremote::ChannelIdentifierList instance reference representing a 
      * list of channel identifiers for searching the epg.
      * @param startTime an optional constant long representing the start time of programs for searching the epg.
      * @param endTime an optional constant long representing the end time of programs for searching the epg.
      * @param shortEpg an optional constant boolean representing a flag for the level of returned EPG information 
      * from the epg search.
      * \remark By setting a \p startTime or \p endTime the search will only return programs that fully or partially fall 
      * into a specified time span. One of the parameters \p startTime or \p endTime may be -1 
      * (EpgSearchRequest::EPG_SEARCH_TIME_NOT_BOUND), meaning that the search is not bound on the start time or end time side.
      * \remark \p startTime and \p endTime is the number of seconds, counted from UNIX epoc: 00:00:00 UTC on 1 January 1970.
      * \remark \p shortEpg specifies the level of returned EPG information and allows for faster EPG overview build up. 
      * Short EPG information includes only program id, name, start time, duration and genre info. Default value is false.
      */
    EpgSearchRequest(const ChannelIdentifierList& channelIdentifierList, const long startTime = EPG_SEARCH_TIME_NOT_BOUND, const long endTime = EPG_SEARCH_TIME_NOT_BOUND, const bool shortEpg = false);

    /**
      * Destructor for cleaning up allocated memory.
      */
    ~EpgSearchRequest();

    /**
      * Gets a list of the channel identifiers of the epg search request.
      * @return Epg search request channel identifiers
      */
    ChannelIdentifierList& GetChannelIdentifiers();

    /**
      * Adds a channel identifier to be searched for.
      * @param channelId a constant strint reference representing the channel identifier to search for.
      */
    void AddChannelID(const std::string& channelId);

    /**
      * String representing the program identifier to search for.
      */
    std::string ProgramID;

    /**
      * String representing the keywords to search for.
      */
    std::string Keywords;

    /**
      * Gets the start time of the epg search request.
      * @return Epg search request start time
      * \remark Number of seconds, counted from UNIX epoc: 00:00:00 UTC on 1 January 1970.
      */
    long GetStartTime();

    /**
      * Sets the start time to be searched for.
      * @param startTime a constant long representing the start time to search for.
      */
    void SetStartTime(const long startTime);

    /**
      * Gets the end time of the epg search request.
      * @return Epg search request end time
      * \remark Number of seconds, counted from UNIX epoc: 00:00:00 UTC on 1 January 1970.
      */
    long GetEndTime();

    /**
      * Sets the end time to be searched for.
      * @param endTime a constant long representing the end time to search for.
      */
    void SetEndTime(const long endTime);

    /**
      * Gets if short epg flag is set for the epg search request.
      * @return if short epg flag is set or not
      */
    bool IsShortEpg();

    /**
      * Sets the short epg flag of the search request.
      * @param shortEpg a const boolean representing if short epg flag is set or not.
      */
    void SetShortEpg(const bool shortEpg);

  private:
    ChannelIdentifierList* m_channelIdList;
    long m_startTime;
    long m_endTime;
    bool m_shortEpg;
  };

  /**
    * Abstract base class for stream requests. 
    * This is used as input parameter for the DVBLinkClient::PlayChannel method.
    * @see DVBLinkClient::PlayChannel()
    */
  class StreamRequest : public Request
  {
  public:
    /**
      * Initializes a new instance of the dvblinkremote::StreamRequest class.
      * @param serverAddress a constant string reference representing the DVBLink server address.
      * @param dvbLinkChannelId a constant long representing the DVBLink channel identifier.
      * @param clientId a constant string reference representing the unique identification string of the client. 
      * @param streamType a constant string reference representing the stream type for the stream request. 
      * \remark \p serverAddress is the IP address/server network name of the DVBLink server. 
      * \remark \p clientId should be the same across all DVBLink Client API calls from a given client. 
      * It can be a uuid for example or id/mac of the client device.
      */
    StreamRequest(const std::string& serverAddress, const long dvbLinkChannelId, const std::string& clientId, const std::string& streamType);

    /**
      * Pure virtual destructor for cleaning up allocated memory.
      */
    virtual ~StreamRequest() = 0;

    /**
      * Gets the server address for the stream request.
      * @return Stream request server address
      * \remark Ip address/server network name of the DVBLink server. 
      */
    std::string& GetServerAddress();

    /**
      * Gets the DVBLink channel identifier for the stream request.
      * @return Stream request channel identifier
      */
    long GetDVBLinkChannelID();

    /**
      * Gets the unique identification string of the client for the stream request.
      * @return Stream request client identifier
      */
    std::string& GetClientID();

    /**
      * Gets the stream type for the stream request.
      * @return Stream request stream type
      */
    std::string& GetStreamType();

    /**
      * The timeout until channel playback is stopped by a server (indefinite if not specified).
      */
    long Duration;

  private:
    /**
      * Ip address/server network name of the DVBLink server. 
      */
    std::string m_serverAddress; 

    /**
      * DVBLink channel identifier.
      */
    long m_dvbLinkChannelId;

    /**
      * The unique identification string of the client.
      * This should be the same across all DVBLink Client API calls from a given client. 
      * Can be a uuid for example or id/mac of the client device.
    */
    std::string	m_clientId;

    /**
      * The type of requested stream.
      * @see StreamRequest::ANDROID_STREAM_TYPE
      * @see StreamRequest::IPHONE_STREAM_TYPE
      * @see StreamRequest::WINPHONE_STREAM_TYPE
      * @see StreamRequest::RAW_HTTP_STREAM_TYPE
      * @see StreamRequest::RAW_UDP_STREAM_TYPE
      */
    std::string	m_streamType;
  };

  /**
    * Class for transcoded video stream options. 
    */
  class TranscodingOptions 
  {
  public:
    /**
      * Initializes a new instance of the dvblinkremote::Transcoding class.
      * @param width a constant unsigned integer representing the width in pixels to use for a transcoded video stream.
      * @param height a constant unsigned integer representing the height in pixels to use for a transcoded video stream.
      */
    TranscodingOptions(const unsigned int width, const unsigned int height);

    /**
      * Destructor for cleaning up allocated memory.
      */
    ~TranscodingOptions();

    /**
      * Gets the width to be used for transcoding a video stream.
      * @return Width in pixels
      */
    unsigned int GetWidth();

    /**
      * Sets the width to be used for transcoding a video stream.
      * @param width a constant unsigned integer representing width in pixels to be used for transcoding a video stream.
      */
    void SetWidth(const unsigned int width);

    /**
      * Gets the height to be used for transcoding a video stream.
      * @return Height in pixels
      */
    unsigned int GetHeight();

    /**
      * Sets the height to be used for transcoding a video stream.
      * @param height a constant unsigned integer representing height in pixels to be used for transcoding a video stream.
      */
    void SetHeight(const unsigned int height);

    /**
      * Gets the bitrate to be used for transcoding a video stream.
      * @return Bitrate in kilobits/sec
      */
    unsigned int GetBitrate();

    /**
      * Sets the bitrate to be used for transcoding a video stream.
      * @param bitrate a constant unsigned integer representing height in pixels to be used for transcoding a video stream.
      */
    void SetBitrate(const unsigned int bitrate);

    /**
      * Gets the audio track to be used for transcoding a video stream.
      * @return Audio track in ISO-639 language code format.
      */
    std::string& GetAudioTrack();

    /**
      * Sets the audio track to be used for transcoding a video stream.
      * @param audioTrack a constant string reference representing an audio track in ISO-639 language code format to be used for transcoding a video stream.
      */
    void SetAudioTrack(const std::string& audioTrack);

  private:
    /**
      * The width in pixels to use for a transcoded video stream.
      */
    unsigned int m_width;

    /**
      * The height in pixels to use for a transcoded video stream.
      */
    unsigned int m_height;

    /**
      * The bitrate in kilobits/sec to use for a transcoded video stream.
      */
    unsigned int m_bitrate;

    /**
      * The ISO-639 language code to use particular audio track for transcoding.
      */
    std::string	m_audioTrack;	
  };

  /** 
    * Abstract base class for transcoded video stream requests.
    * This is used as input parameter for the DVBLinkClient::PlayChannel method.
    * @see DVBLinkClient::PlayChannel()
    */
  class TranscodedVideoStreamRequest : public StreamRequest
  {
  public:
    /**
      * Initializes a new instance of the dvblinkremote::TranscodedVideoStreamRequest class.
      * @param serverAddress a constant string reference representing the DVBLink server address.
      * @param dvbLinkChannelId a constant long representing the DVBLink channel identifier.
      * @param clientId a constant string reference representing the unique identification string of the client. 
      * @param transcodingOptions a dvblinkremote::TranscodingOptions instance reference representing the transcoding options
      * of the stream request. 
      * @param streamType a constant string reference representing the stream type for the stream request. 
      * \remark \p serverAddress is the IP address/server network name of the DVBLink server. 
      * \remark \p clientId should be the same across all DVBLink Client API calls from a given client. 
      * It can be a uuid for example or id/mac of the client device.
      */
    TranscodedVideoStreamRequest(const std::string& serverAddress, const long dvbLinkChannelId, const std::string& clientId, TranscodingOptions& transcodingOptions, const std::string& streamType);

    /**
      * Destructor for cleaning up allocated memory.
      */
    virtual ~TranscodedVideoStreamRequest() = 0;

    /**
      * Gets the transcoding options of the stream request.
      * @return dvblinkremote::TranscodingOptions instance reference.
      */
    TranscodingOptions& GetTranscodingOptions();

  private:
    /**
      * The transcoding options for the stream request.
      */
    TranscodingOptions&	m_transcodingOptions;
  };

  /** 
    * Class for Real-time Transport Protocol (RTP) stream requests.
    * This is used as input parameter for the DVBLinkClient::PlayChannel method.
    * @see DVBLinkClient::PlayChannel()
    */
  class RealTimeTransportProtocolStreamRequest : public TranscodedVideoStreamRequest
  {
  public:
    /**
      * Initializes a new instance of the dvblinkremote::RealTimeTransportProtocolStreamRequest class.
      * @param serverAddress a constant string reference representing the DVBLink server address.
      * @param dvbLinkChannelId a constant long representing the DVBLink channel identifier.
      * @param clientId a constant string reference representing the unique identification string of the client. 
      * @param transcodingOptions a dvblinkremote::TranscodingOptions instance reference representing the transcoding options
      * of the stream request. 
      * \remark \p serverAddress is the IP address/server network name of the DVBLink server. 
      * \remark \p clientId should be the same across all DVBLink Client API calls from a given client. 
      * It can be a uuid for example or id/mac of the client device.
      */
    RealTimeTransportProtocolStreamRequest(const std::string& serverAddress, const long dvbLinkChannelId, const std::string& clientId, TranscodingOptions& transcodingOptions);

    /**
      * Destructor for cleaning up allocated memory.
      */
    ~RealTimeTransportProtocolStreamRequest();
  };

  /** 
    * Class for HTTP Live %Stream (HLS) stream requests.
    * This is used as input parameter for the DVBLinkClient::PlayChannel method.
    * @see DVBLinkClient::PlayChannel()
    */
  class HttpLiveStreamRequest : public TranscodedVideoStreamRequest
  {
  public:
    /**
      * Initializes a new instance of the dvblinkremote::HttpLiveStreamRequest class.
      * @param serverAddress a constant string reference representing the DVBLink server address.
      * @param dvbLinkChannelId a constant long representing the DVBLink channel identifier.
      * @param clientId a constant string reference representing the unique identification string of the client. 
      * @param transcodingOptions a dvblinkremote::TranscodingOptions instance reference representing the transcoding options 
      * of the stream request. 
      * \remark \p serverAddress is the IP address/server network name of the DVBLink server. 
      * \remark \p clientId should be the same across all DVBLink Client API calls from a given client. 
      * It can be a uuid for example or id/mac of the client device.
      */
    HttpLiveStreamRequest(const std::string& serverAddress, const long dvbLinkChannelId, const std::string& clientId, TranscodingOptions& transcodingOptions);

    /**
      * Destructor for cleaning up allocated memory.
      */
    ~HttpLiveStreamRequest();
  };

  /** 
    * Class for Windows Media %Stream (ASF) stream requests.
    * This is used as input parameter for the DVBLinkClient::PlayChannel method.
    * @see DVBLinkClient::PlayChannel()
    */
  class WindowsMediaStreamRequest : public TranscodedVideoStreamRequest
  {
  public:
    /**
      * Initializes a new instance of the dvblinkremote::WindowsMediaStreamRequest class.
      * @param serverAddress a constant string reference representing the DVBLink server address.
      * @param dvbLinkChannelId a constant long representing the DVBLink channel identifier.
      * @param clientId a constant string reference representing the unique identification string of the client. 
      * @param transcodingOptions a dvblinkremote::TranscodingOptions instance reference representing the transcoding options
      * of the stream request. 
      * \remark \p serverAddress is the IP address/server network name of the DVBLink server. 
      * \remark \p clientId should be the same across all DVBLink Client API calls from a given client. 
      * It can be a uuid for example or id/mac of the client device.
      */
    WindowsMediaStreamRequest(const std::string& serverAddress, const long dvbLinkChannelId, const std::string& clientId, TranscodingOptions& transcodingOptions);

    /**
      * Destructor for cleaning up allocated memory.
      */
    ~WindowsMediaStreamRequest();
  };

  /** 
    * Class for Raw HTTP stream requests.
    * This is used as input parameter for the DVBLinkClient::PlayChannel method.
    * @see DVBLinkClient::PlayChannel()
    */
  class RawHttpStreamRequest : public StreamRequest
  {
  public:
    /**
      * Initializes a new instance of the dvblinkremote::RawHttpStreamRequest class.
      * @param serverAddress a constant string reference representing the DVBLink server address.
      * @param dvbLinkChannelId a constant long representing the DVBLink channel identifier.
      * @param clientId a constant string reference representing the unique identification string of the client. 
      * \remark \p serverAddress is the IP address/server network name of the DVBLink server. 
      * \remark \p clientId should be the same across all DVBLink Client API calls from a given client. 
      * It can be a uuid for example or id/mac of the client device.
      */
    RawHttpStreamRequest(const std::string& serverAddress, const long dvbLinkChannelId, const std::string& clientId);

    /**
      * Destructor for cleaning up allocated memory.
      */
    ~RawHttpStreamRequest();
  };

  /** 
    * Class for Raw UDP stream requests.
    * This is used as input parameter for the DVBLinkClient::PlayChannel method.
    * @see DVBLinkClient::PlayChannel()
    */
  class RawUdpStreamRequest : public StreamRequest
  {
  public:
    /**
      * Initializes a new instance of the dvblinkremote::RawUdpStreamRequest class.
      * @param serverAddress a constant string reference representing the DVBLink server address.
      * @param dvbLinkChannelId a constant long representing the DVBLink channel identifier.
      * @param clientId a constant string reference representing the unique identification string of the client. 
      * @param clientAddress a constant string reference representing the client address.
      * @param streamingPort a constant unsigned short representing the streaming port.
      * \remark \p serverAddress is the IP address/server network name of the DVBLink server. 
      * \remark \p clientId should be the same across all DVBLink Client API calls from a given client. 
      * It can be a uuid for example or id/mac of the client device.
      */
    RawUdpStreamRequest(const std::string& serverAddress, const long dvbLinkChannelId, const std::string& clientId, const std::string& clientAddress, const unsigned short int streamingPort);

    /**
      * Destructor for cleaning up allocated memory.
      */
    ~RawUdpStreamRequest();

    /**
      * Gets the client address of the stream request.
      * @return The client address for the stream request.
      */
    std::string& GetClientAddress();

    /**
      * Gets the streaming port of the stream request.
      * @return The streaming port for the stream request.
      */
    long GetStreamingPort();

  private:
    /**
      * The client address for the stream request.
      */
    std::string	m_clientAddress;

    /**
      * The streaming port for the stream request.
      */
    unsigned short int m_streamingPort;
  };

  /** 
    * Class for stop stream requests.
    * This is used as input parameter for the DVBLinkClient::StopChannel method.
    * @see DVBLinkClient::StopChannel()
    */
  class StopStreamRequest : public Request 
  {
  public:
    /**
      * Initializes a new instance of the dvblinkremote::StopStreamRequest class.
      * @param channelHandle a constant long representing the channel handle of an 
      * existing playing stream to stop.
      * @see dvblinkremote::StreamRequest() for information about the channel handle.
      */
    StopStreamRequest(long channelHandle);

    /**
      * Initializes a new instance of the dvblinkremote::StopStreamRequest class.
      * @param clientId a constant string reference representing the unique 
      * identification string of the client for stopping all playing streams 
      * from that specific client.
      */
    StopStreamRequest(const std::string& clientId);

    /**
      * Destructor for cleaning up allocated memory.
      */
    ~StopStreamRequest();

    /**
      * Gets the channel handle for the stop stream request.
      * @return Channel handle
      */
    long GetChannelHandle();

    /**
      * Gets the client identifier for the stop stream request.
      * @return Client identifier
      */
    std::string& GetClientID();

  private:
    /**
      * The channel handle for the stop stream request.
      */
    long m_channelHandle;

    /**
      * The unique identification string of the client.
    */
    std::string m_clientId;
  };

  /**
    * Class for get schedules requests. 
    * This is used as input parameter for the DVBLinkClient::GetSchedules method.
    * @see DVBLinkClient::GetSchedules()
    */
  class GetSchedulesRequest : public Request
  {
  public:
    /**
      * Initializes a new instance of the dvblinkremote::GetSchedulesRequest class.
      */
    GetSchedulesRequest();

    /**
      * Destructor for cleaning up allocated memory.
      */
    ~GetSchedulesRequest();
  };


  /**
    * Abstract base class for add schedule requests. 
    * This is used as input parameter for the DVBLinkClient::AddSchedule method.
    * @see DVBLinkClient::AddSchedule m()
    */
  class AddScheduleRequest : public Request
  {
  public:
    /**
      * An enum for schedule types.
      */
    enum DVBLinkScheduleType
    {
      SCHEDULE_TYPE_MANUAL = 0, /**< Used for adding manual schedules. */ 
      SCHEDULE_TYPE_BY_EPG = 1 /**< Used for adding schedules by electronic program guide (EPG). */ 
    };

    /**
      * Initializes a new instance of the dvblinkremote::AddScheduleRequest class.
      * @param scheduleType a const DVBLinkScheduleType instance representing the type of 
      * schedule to add.
      * @param channelId a constant string reference representing the channel identifier.
	  * @param recordingsToKeep an constant int representing how many recordings to keep when recording series
	  * Default value is <tt>0</tt> and means all recordings.
      */
    AddScheduleRequest(const DVBLinkScheduleType scheduleType, const std::string& channelId, const int recordingsToKeep = 0 );

    /**
      * Pure virtual destructor for cleaning up allocated memory.
      */
    virtual ~AddScheduleRequest() = 0;

    /**
      * Gets the channel identifier for the schedule request.
      * @return Channel identifier
      */
    std::string& GetChannelID();

    /**
      * The user parameter of the add schedule request.
      */
    std::string UserParameter;

    /**
      * A flag indicating that new schedule should be added even if there are other 
      * conflicting schedules present.
      */
    bool ForceAdd;

    /**
      * Indicate how many recordings to keep (Used for series) (1,2,3,4,5,6,7,10; 0 ? keep all)
      */
	int RecordingsToKeep;

    /**
      * Gets the schedule type for the add schedule request.
      * @return DVBLinkScheduleType instance reference
      */
    DVBLinkScheduleType& GetScheduleType();

  private:
    /**
      * The channel identifier of the manual schedule request.
      */
    std::string m_channelId;

    /**
      * The schedule type of the add schedule request.
      */
    DVBLinkScheduleType m_scheduleType;
  };
  
  /**
    * Class for add manual schedule requests. 
    * This is used as input parameter for the DVBLinkClient::AddSchedule method.
    * @see DVBLinkClient::AddSchedule()
    */
  class AddManualScheduleRequest : public AddScheduleRequest
  {
  public:
    /**
      * An enum to be used for constructing a bitflag for creating a manual schedule.
      */
    enum DVBLinkManualScheduleDayMask 
    {
      MANUAL_SCHEDULE_DAY_MASK_SUNDAY = 1, /**< Sunday schedule. */
      MANUAL_SCHEDULE_DAY_MASK_MONDAY = 2, /**< Monday schedule. */
      MANUAL_SCHEDULE_DAY_MASK_TUESDAY = 4, /**< Tuesday schedule. */
      MANUAL_SCHEDULE_DAY_MASK_WEDNESDAY = 8, /**< Wednesday schedule. */
      MANUAL_SCHEDULE_DAY_MASK_THURSDAY = 16, /**< Thursday schedule. */
      MANUAL_SCHEDULE_DAY_MASK_FRIDAY = 32, /**< Friday schedule. */
      MANUAL_SCHEDULE_DAY_MASK_SATURDAY = 64, /**< Saturday schedule. */
      MANUAL_SCHEDULE_DAY_MASK_DAILY = 255 /**< Daily schedule. */
    };

    /**
      * Initializes a new instance of the dvblinkremote::AddManualScheduleRequest class.
      * @param channelId a constant string reference representing the channel identifier.
      * @param startTime a constant long representing the start time of the schedule.
      * @param duration a constant long representing the duration of the schedule. 
      * @param dayMask a constant long representing the day bitflag of the schedule.
      * \remark Construct the \p dayMask parameter by using bitwize operations on the DVBLinkManualScheduleDayMask.
      * @see DVBLinkManualScheduleDayMask
	  * @param title of schedule
      */
    AddManualScheduleRequest(const std::string& channelId, const long startTime, const long duration, const long dayMask, const std::string& title = "");

    /**
      * Destructor for cleaning up allocated memory.
      */
    ~AddManualScheduleRequest();

    /**
      * The title of the add manual schedule request.
      */
    std::string Title;

    /**
      * Gets the start time for the add manual schedule request.
      * @return Start time
      */
    long GetStartTime();

    /**
      * Gets the duration for the add manual schedule request.
      * @return Duration
      */
    long GetDuration();
    
    /**
      * Gets the day bitmask for the add manual schedule request.
      * @return Day bitmask
      */
    long GetDayMask();

  private:
    /**
      * The start time of the add manual schedule request.
      */
    long m_startTime;

    /**
      * The duration of the add manual schedule request.
      */
    long m_duration;

    /**
      * The day bitmask of the add manual schedule request.
      */
    long m_dayMask;
  };

  /**
    * Class for add schedule by electronic program guide (EPG) requests. 
    * This is used as input parameter for the DVBLinkClient::AddSchedule method.
    * @see DVBLinkClient::AddSchedule m()
    */
  class AddScheduleByEpgRequest : public AddScheduleRequest
  {
  public:
    /**
      * Initializes a new instance of the dvblinkremote::AddScheduleByEpgRequest class.
      * @param channelId a constant string reference representing the channel identifier.
      * @param programId a constant string reference representing the program identifier.
      * @param repeat an optional constant boolean representing if the schedule should be repeated or not. 
      * Default value is <tt>false</tt>.
	  * @param newOnly an optional constant boolean representing if only new programs should be recorded 
	  * Default value is <tt>false</tt>.
	  * @param recordSeriesAnytime an optional constant boolean representing if only series starting around original program start time or any of them 
	  * Default value is <tt>false</tt>.
	  */
    AddScheduleByEpgRequest(const std::string& channelId, const std::string& programId, const bool repeat = false, const bool newOnly = false,const bool recordSeriesAnytime = false);

    /**
      * Destructor for cleaning up allocated memory.
      */
    ~AddScheduleByEpgRequest();

    /**
      * Gets the program identifier for the add schedule request.
      * @return Program identifier
      */
    std::string& GetProgramID();

    /**
      * The repeat flag for the add schedule request.
      */
    bool Repeat;

	/**
    * The NewOnly flag for the add schedule request.
    */
	bool NewOnly;

	/**
      * The RecordSeriesAnytime flag for the add schedule request.
      */
	bool RecordSeriesAnytime;

  private:
    /**
      * The program identifier for the add schedule request.
      */
    std::string m_programId;
  };

  /**
    * Class for get recordings requests. 
    * This is used as input parameter for the DVBLinkClient::GetRecordings method.
    * @see DVBLinkClient::GetRecordings()
    */
  class GetRecordingsRequest : public Request
  {
  public:
    /**
      * Initializes a new instance of the dvblinkremote::GetRecordingsRequest class.
      */
    GetRecordingsRequest();

    /**
      * Destructor for cleaning up allocated memory.
      */
    ~GetRecordingsRequest();
  };

  /**
    * Class for remove schedule requests. 
    * This is used as input parameter for the DVBLinkClient::RemoveSchedule method.
    * @see DVBLinkClient::RemoveSchedule()
    */
  class RemoveScheduleRequest : public Request 
  {
  public:
    /**
      * Initializes a new instance of the dvblinkremote::GetRecordingsRequest class.
      * @param scheduleId a constant string reference representing the identifier of the 
      * schedule to be removed.
      */
    RemoveScheduleRequest(const std::string& scheduleId);
    
    /**
      * Destructor for cleaning up allocated memory.
      */
    ~RemoveScheduleRequest();

    /**
      * Gets the identifier for the schedule to be removed.
      * @return Schedule identifier
      */
    std::string& GetScheduleID();

  private:
    /**
      * The identifier of the schedule to be removed.
      */
    std::string m_scheduleId;
  };

  /**
    * Class for remove recording requests. 
    * This is used as input parameter for the DVBLinkClient::RemoveRecording method.
    * @see DVBLinkClient::RemoveRecording()
    */
  class RemoveRecordingRequest : public Request 
  {
  public:
    /**
      * Initializes a new instance of the dvblinkremote::GetRecordingsRequest class.
      * @param recordingId a constant string reference representing the identifier of the 
      * recording to be removed.
      */
    RemoveRecordingRequest(const std::string& recordingId);

    /**
      * Destructor for cleaning up allocated memory.
      */
    ~RemoveRecordingRequest();

    /**
      * Gets the identifier for the recording to be removed.
      * @return Recording identifier
      */
    std::string& GetRecordingID();

  private:
    /**
      * The identifier of the recording to be removed.
      */
    std::string m_recordingId;
  };

  /**
    * Class for get parental status requests. 
    * This is used as input parameter for the DVBLinkClient::GetParentalStatus method.
    * @see DVBLinkClient::GetParentalStatus()
    */
  class GetParentalStatusRequest : public Request
  {
  public:
    /**
      * Initializes a new instance of the dvblinkremote::GetParentalStatusRequest class.
      * @param clientId a constant string reference representing the unique identification string of the client. 
      * \remark \p clientId should be the same across all DVBLink Client API calls from a given client. 
      * It can be a uuid for example or id/mac of the client device.
      */
    GetParentalStatusRequest(const std::string& clientId);

    /**
      * Destructor for cleaning up allocated memory.
      */
    ~GetParentalStatusRequest();

    /**
      * Gets the unique identification string of the client.
      * @return Client identifier
      */
    std::string& GetClientID();

  private:
    /**
      * The unique identification string of the client.
      * This should be the same across all DVBLink Client API calls from a given client. 
      * Can be a uuid for example or id/mac of the client device.
      */
    std::string m_clientId;
  };

  /**
    * Class for set parental lock requests. 
    * This is used as input parameter for the DVBLinkClient::SetParentalLock method.
    * @see DVBLinkClient::SetParentalLock()
    */
  class SetParentalLockRequest : public Request
  {
  public:
    /**
      * Initializes a new instance of the dvblinkremote::SetParentalLockRequest class for disabling a parental lock.
      * @param clientId a constant string reference representing the unique identification string of the client. 
      * \remark \p clientId should be the same across all DVBLink Client API calls from a given client. 
      * It can be a uuid for example or id/mac of the client device.
      */
    SetParentalLockRequest(const std::string& clientId);
    
    /**
      * Initializes a new instance of the dvblinkremote::SetParentalLockRequest class for enabling a parental lock.
      * @param clientId a constant string reference representing the unique identification string of the client. 
      * @param code a constant string reference representing the parental lock code. 
      * \remark \p clientId should be the same across all DVBLink Client API calls from a given client. 
      * It can be a uuid for example or id/mac of the client device.
      */
    SetParentalLockRequest(const std::string& clientId, const std::string& code);

    /**
      * Destructor for cleaning up allocated memory.
      */
    ~SetParentalLockRequest();

    /**
      * Gets the unique identification string of the client.
      * @return Client identifier
      */
    std::string& GetClientID();

    /**
      * Gets if the parental lock should be enabled or not for the set parental lock request.
      * @return Enabled flag
      */
    bool IsEnabled();
    
    /**
      * Gets the parental lock code for the set parental lock request.
      * @return Parental lock code
      */
    std::string& GetCode();

  private:
    /**
      * The unique identification string of the client.
      * This should be the same across all DVBLink Client API calls from a given client. 
      * Can be a uuid for example or id/mac of the client device.
      */
    std::string m_clientId;

    /**
      * The flag which tells if parental lock should be enabled or disabled.
      */
    bool m_enabled;

    /**
      * The parental lock code if \p m_enabled is \p true.
      */
    std::string m_code;
  };
}
