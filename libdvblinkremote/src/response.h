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
#include "request.h"

namespace dvblinkremote {
  /** 
    * Base class for DVBLink Client responses.
    */
  class Response { };

  enum ChannelType {RD_CHANNEL_TV = 0, RD_CHANNEL_RADIO = 1, RD_CHANNEL_OTHER = 2};

  /**
    * Represent a DVBLink channel.
    */
  class Channel
  {
  public:
    /**
      * Initializes a new instance of the dvblinkremote::Channel class.
      * @param id a constant string reference representing the generic identifier of the channel.
      * @param dvbLinkId a constant long representing the DVBLink identifier of the channel.
      * @param name a constant string reference representing the name of the channel.
	  * @param type of channel TV = 0, RADIO = 1, OTHER = 2
      * @param number an optional constant integer representing the number of the channel.
      * @param subNumber an optional constant integer representing the sub-number of the channel.
      */
    Channel(const std::string& id, const long dvbLinkId, const std::string& name, const ChannelType type, const int number = -1, const int subNumber = -1);

    /**
      * Initializes a new instance of the dvblinkremote::Channel class by coping another 
      * dvblinkremote::Channel instance.
      * @param channel a dvblinkremote::Channel reference.
      */
    Channel(Channel& channel);
    
    /**
      * Destructor for cleaning up allocated memory.
      */
    ~Channel();

    /**
      * Gets the identifier of the channel.
      * @return Channel identifier
      */
    std::string& GetID();

    /**
      * Gets the DVBLink identifier of the channel. 
      * @return DVBLink channel identifier
      */
    long GetDvbLinkID();
    
    /**
      * Gets the name of the channel.
      * @return Channel name
      */
    std::string& GetName();

    /**
      * Represents the number of the channel.
      */
    int Number;

    /**
      * Represents the sub-number of the channel.
      */
    int SubNumber;

	/**
	  * Represents the type of channel
	  */
	ChannelType Type;
    
  private:
    std::string m_id;
    long m_dvbLinkId;
    std::string m_name;
  };

  /**
    * Represent a strongly typed list of DVBLink channels which is used as output 
    * parameter for the DVBLinkClient::GetChannels method.
    * @see Channel::Channel()
    * @see DVBLinkClient::GetChannels()
    */
  class ChannelList : public Response, public std::vector<Channel*> {
  public:
    /**
      * Initializes a new instance of the dvblinkremote::ChannelList class.
      */
    ChannelList();

    /**
      * Destructor for cleaning up allocated memory.
      */
    ~ChannelList();
  };

  /**
    * Represent a program in an electronic program guide (EPG).
    */
  class Program
  {
  public:
    /**
      * Initializes a new instance of the dvblinkremote::Program class.
      */
    Program();

    /**
      * Initializes a new instance of the dvblinkremote::Program class.
      * @param id a constant string reference representing the identifier of the program.
      * @param title a constant string reference representing the title of the program.
      * @param startTime a constant long representing the start time of the program.
      * @param duration a constant long representing the duration of the program.
      * \remark startTime and duration is the number of seconds, counted from 
      * UNIX epoc: 00:00:00 UTC on 1 January 1970.
      */
    Program(const std::string& id, const std::string& title, const long startTime, const long duration);

    /**
      * Initializes a new instance of the dvblinkremote::Program class by coping another 
      * dvblinkremote::Program instance.
      * @param program a dvblinkremote::Program reference.
      */
    Program(Program& program);
    
    /**
      * Destructor for cleaning up allocated memory.
      */
    ~Program();

    /**
      * Gets the identifier of the program.
      * @return Program identifier
      */
    std::string& GetID();

    /**
      * Sets the identifier of the program.
      * @param id a constant string reference representing the identifier of the program.
      */
    void SetID(const std::string& id);

    /**
      * Gets the title of the program.
      * @return Program title
      */
    std::string& GetTitle();
    
    /**
      * Sets the title of the program.
      * @param title a constant string reference representing the title of the program.
      */
    void SetTitle(const std::string& title);

    /**
      * Gets the start time of the program.
      * @return Program start time
      * \remark Number of seconds, counted from UNIX epoc: 00:00:00 UTC on 1 January 1970.
      */
    long GetStartTime();

    /**
      * Sets the start time of the program.
      * @param startTime a constant long representing the start time of the program.
      */
    void SetStartTime(const long startTime);

    /**
      * Gets the duration of the program.
      * @return program duration
      * \remark Number of seconds, counted from UNIX epoc: 00:00:00 UTC on 1 January 1970.
      */
    long GetDuration();

    /**
      * Sets the duration of the program.
      * @param duration a constant long representing the duration of the program.
      */
    void SetDuration(const long duration);

    std::string ShortDescription;
    std::string SubTitle;
    std::string Language;
    std::string Actors;
    std::string Directors;
    std::string Writers;
    std::string Producers;
    std::string Guests;
    std::string Keywords;
    std::string Image;
    int Year;
    int EpisodeNumber;
    int SeasonNumber;
    int Rating;
    int MaximumRating;
    bool IsHdtv;
    bool IsPremiere;
    bool IsRepeat;
    bool IsSeries;
    bool IsRecord;
    bool IsRepeatRecord;
    bool IsCatAction;
    bool IsCatComedy;
    bool IsCatDocumentary;
    bool IsCatDrama;
    bool IsCatEducational;
    bool IsCatHorror;
    bool IsCatKids;
    bool IsCatMovie;
    bool IsCatMusic;
    bool IsCatNews;
    bool IsCatReality;
    bool IsCatRomance;
    bool IsCatScifi;
    bool IsCatSerial;
    bool IsCatSoap;
    bool IsCatSpecial;
    bool IsCatSports;
    bool IsCatThriller;
    bool IsCatAdult;

  private:
    std::string m_id;
    std::string m_title;
    long m_startTime;
    long m_duration;
  };

  /**
    * Represent a strongly typed list of programs in an electronic 
    * program guide (EPG).
    * @see Program::Program()
    */
  class EpgData : public std::vector<Program*> {
  public:
    /**
      * Initializes a new instance of the dvblinkremote::EpgData class.
      */
    EpgData();

    /**
      * Initializes a new instance of the dvblinkremote::EpgData class by coping another 
      * dvblinkremote::EpgData instance.
      * @param epgData a dvblinkremote::EpgData reference.
      */
    EpgData(EpgData& epgData);
    
    /**
      * Destructor for cleaning up allocated memory.
      */
    ~EpgData();
  };

  /**
    * Represent electronic program guide (EPG) data for a channel.
    */
  class ChannelEpgData
  {
  public:
    /**
      * Initializes a new instance of the dvblinkremote::ChannelEpgData class.
      * @param channelId a constant string reference representing the channel identifier for the corresponding electronic program guide (EPG) data.
      */
    ChannelEpgData(const std::string& channelId);

    /**
      * Initializes a new instance of the dvblinkremote::ChannelEpgData class by coping another 
      * dvblinkremote::ChannelEpgData instance.
      * @param channelEpgData a dvblinkremote::ChannelEpgData reference.
      */
    ChannelEpgData(ChannelEpgData& channelEpgData);

    /**
      * Destructor for cleaning up allocated memory.
      */
    ~ChannelEpgData();

    /**
      * Get the channel identifier of the electronic program guide (EPG) data.
      * @return Channel identifier.
      */
    std::string& GetChannelID();

    /**
      * Get the electronic program guide (EPG) data.
      * @return Electronic program guide (EPG) data.
      */
    EpgData& GetEpgData();

    /**
      * Adds a program to the electronic program guide (EPG).
      * @param program A constant dvblinkremote::Program pointer.
      */
    void AddProgram(const Program* program);

  private:
    std::string m_channelId;
    EpgData* m_epgData;
  };

  /**
    * Represent a strongly typed list of electronic program guide (EPG) data 
    * for channels which is used as output parameter for the 
    * DVBLinkClient::SearchEpg method.
    * @see ChannelEpgData::ChannelEpgData()
    * @see DVBLinkClient::SearchEpg()
    */
  class EpgSearchResult : public Response, public std::vector<ChannelEpgData*> {
  public:
    /**
      * Initializes a new instance of the dvblinkremote::EpgSearchResult class.
      */
    EpgSearchResult();

    /**
      * Destructor for cleaning up allocated memory.
      */
    ~EpgSearchResult();
  };

  /**
  * Represent a DVBLink playing channel which is used as output parameter 
  * for the DVBLinkClient::PlayChannel method.
  * @see DVBLinkClient::PlayChannel()
  */
  class Stream : public Response
  {
  public:
    /**
      * Initializes a new instance of the dvblinkremote::Stream class.
      */
    Stream();

    /**
      * Initializes a new instance of the dvblinkremote::Stream class.
      * @param channelHandle a constant long representing the channel handle of the stream.
      * @param url a constant string reference representing the url of the stream.
      */
    Stream(const long channelHandle, const std::string& url);
    
    /**
      * Initializes a new instance of the dvblinkremote::Stream class by coping another 
      * dvblinkremote::Stream instance.
      * @param stream a dvblinkremote::Stream reference.
      */
    Stream(Stream& stream);

    /**
      * Destructor for cleaning up allocated memory.
      */
    ~Stream();
    
    /**
      * Gets the channel handle of the stream.
      * @return Stream channel handle
      */
    long GetChannelHandle();
    
    /**
      * Sets the channel handle of the stream.
      * @param channelHandle a constant long representing the channel handle of the stram.
      */
    void SetChannelHandle(const long channelHandle);
    
    /**
      * Gets the url of the stream.
      * @return Stream url
      */
    std::string& GetUrl();
    
    /**
      * Sets the url of the stream.
      * @param url a constant string reference representing the url of the stram.
      */
    void SetUrl(const std::string& url);

  private:
    long m_channelHandle;
    std::string m_url;
  };

  /**
    * Represent a recording.
    */
  class Recording
  {
  public:
    /**
      * Initializes a new instance of the dvblinkremote::Recording class.
      * @param id a constant string reference representing the identifier of the recording.
      * @param scheduleId a constant string reference representing the schedule identifier of the recording.
      * @param channelId a constant string reference representing the channel identifier of the recording.
      * @param program a constant dvblinkremote::Program instance pointer representing the program of the recording.
      */
    Recording(const std::string& id, const std::string& scheduleId, const std::string& channelId, const Program* program);
    
    /**
      * Initializes a new instance of the dvblinkremote::Recording class by coping another 
      * dvblinkremote::Recording instance.
      * @param recording a dvblinkremote::Recording reference.
      */
    Recording(Recording& recording);

    /**
      * Destructor for cleaning up allocated memory.
      */
    ~Recording();

    /**
      * Gets the identifier of the recording.
      * @return Recording identifier
      */
    std::string& GetID();
    
    /**
      * Gets the schedule identifier of the recording.
      * @return Recording schedule identifier
      */
    std::string& GetScheduleID();
    
    /**
      * Gets the channel identifier of the recording.
      * @return Recording channel identifier
      */
    std::string& GetChannelID();

    /**
      * Represents if the recording is in active state or not.
      */
    bool IsActive;

    /**
      * Gets the program of the recording.
      * @return Recording program
      */
    Program& GetProgram();

  private:
    std::string m_id;
    std::string m_scheduleId;
    std::string m_channelId;
    Program* m_program;
  };

  /**
    * Represent a strongly typed list of recordings which is used as output 
    * parameter for the DVBLinkClient::GetRecordings method.
    * @see Recording::Recording()
    * @see DVBLinkClient::GetRecordings()
    */
  class RecordingList : public Response, public std::vector<Recording*>
  {
  public:
    /**
      * Destructor for cleaning up allocated memory.
      */
    ~RecordingList();
  };


  enum DayMask{SUN = 1, MON = 2, TUE = 4, WED = 8, THU = 16, FRI = 32, SAT = 64, DAILY = 255};
  enum ScheduleType{Manual=0, EPG = 1};


  //TODO: PAE: Use inheritance instead
/**
    * Represent a schedule.
    */
  class Schedule
  {
  public:
	  //TODO: PAE Add description
    /**
      * Initializes a new instance of the dvblinkremote::Schedule class, by epg
      * @param id a constant string reference representing the identifier of the schedule.
      */  
    Schedule(const std::string& id, const std::string& channelId, const std::string& programId,const Program* program,  const int recordingsToKeep, const std::string& userParam = "", const bool forceAdd = false, const bool repeat = false, const bool newOnly = false,const bool recordSeriesAnyTime = false);
    
	//TODO: PAE Add description
	Schedule(const std::string& id, const std::string& channelId, const std::string& title,const long startTime, const int duration, const  DayMask dayMask,  const int recordingsToKeep, const std::string& userParam = "", const bool forceAdd = false);


    /**
      * Initializes a new instance of the dvblinkremote::Recording class by coping another 
      * dvblinkremote::Recording instance.
      * @param recording a dvblinkremote::Schedule reference.
      */
    Schedule(Schedule& schedule);

    /**
      * Destructor for cleaning up allocated memory.
      */
    ~Schedule();

    /**
      * Gets the identifier of the schedule.
      * @return Schedule identifier
      */
    std::string& GetID();
    
    /**
      * Gets the userparam identifier of the schedule.
      * @return userparam
      */
    std::string& GetUserParam();
    
    /**
      * Gets the channel identifier of the schedule.
      * @return Schedule channel identifier
      */
    std::string& GetChannelID();

    /**
      * Gets the program identifier of the schedule.
      * @return Program identifier
      */
    std::string& GetProgramID();

    /**
      * Gets the title of the schedule.
      * @return Title
      */
    std::string& GetTitle();


    /**
      * Represents if the schedule is defined using Manual information or EPG
      */
    ScheduleType Type;

	/**
	  * If true this flag indicates that schedule has to be added even if there are timer conflicts
	  */
	bool ForcedAdd;

	/**
	  * Indicates whether to record program series
	  */
	bool Repeat;

	/**
	  * Indicates that only new programs have to be recorded
	  */
	bool NewOnly;

	/**
	  * Indicates whether to record only series starting around original program start time or any of them
	  */
	bool RecordSeriesAnytime;

	/**
	  * Indicates the start time of the schedule
	  */
	long StartTime;

	/**
	  * Indicates the duration of the schedule
	  */
	int Duration;

	/**
	  * Indicates which days the schedule takes effect
	  */
	DayMask Mask;

	/**
	  * Indicatates for series recording how many recordings to keep (1,2,3,4,5,6,7,10; 0 ? keep all)
	  */
	bool RecordingsToKeep;

	
    /**
      * Gets the program of the recording.
      * @return Recording program
      */
    Program& GetProgram();

  private:
    std::string m_id;
    std::string m_userParam;
    std::string m_channelId;
    std::string m_programId;
    std::string m_title;
	Program* m_program;
  };



   /**
    * Represent a strongly typed list of schedules which is used as output 
    * parameter for the DVBLinkClient::GetSchedules method.
    * @see Schedule::Schedule()
    * @see DVBLinkClient::GetSchedules()
    */
  class ScheduleList : public Response, public std::vector<Schedule*>
  {
  public:
    /**
      * Destructor for cleaning up allocated memory.
      */
    ~ScheduleList();
  };



   //TODO: PAE: Missing description
  class Item
  {
  public:
	  Item(const ITEM_TYPE type);
	  ITEM_TYPE Type;

  };

  class VideoInfo
  {
  public :
	  std::string Title;
	  long StartTime;
	  long Duration;
	  std::string ShortDescription;
	  std::string SubTitle;
	  std::string Language;
	  std::string Actors;
	  std::string Directors;
	  std::string Writers;
	  std::string Producers;
	  std::string Guests;
	  std::string Keywords;
	  std::string Image;
	  int Year;
	  int EpisodeNumber;
	  int SeasonNumber;
	  int Rating;
	  int MaximumRating;
	  bool IsHdtv;
	  bool IsPremiere;
	  bool IsRepeat;
	  bool IsSeries;
	  bool IsCatAction;
	  bool IsCatComedy;
	  bool IsCatDocumentary;
	  bool IsCatDrama;
	  bool IsCatEducational;
	  bool IsCatHorror;
	  bool IsCatKids;
	  bool IsCatMovie;
	  bool IsCatMusic;
	  bool IsCatNews;
	  bool IsCatReality;
	  bool IsCatRomance;
	  bool IsCatScifi;
	  bool IsCatSerial;
	  bool IsCatSoap;
	  bool IsCatSpecial;
	  bool IsCatSports;
	  bool IsCatThriller;
	  bool IsCatAdult;
  
  };




  enum RECORDEDTV_STATE {RECORDEDTV_STATE_IN_PROGRESS = 0, RECORDEDTV_STATE_ERROR = 1, RECORDEDTV_STATE_FORCED_TO_COMPLETION = 2, RECORDEDTV_STATE_COMPLETED = 3};


   //TODO: PAE: Missing description
  class Video : public Item {
  public :
	  Video(const std::string& objectId, const std::string& parentId, const std::string& url, const std::string& thumbnail, const bool canBeDeleted, const long size, const long creationTime);

	  std::string ObjectID;
	  std::string ParentID;
	  std::string Url;
	  std::string Thumbnail;
	  bool CanBeDeleted;
	  long Size;
	  long CreationTime;
	  VideoInfo VInfo;

  };

  //TODO: PAE: Missing description
  class RecordedTV : public Video
  {
  public :
	  RecordedTV(const std::string& objectId, const std::string& parentId, const std::string& url, const std::string& thumbnail, const std::string& channelName, const bool canBeDeleted, const long size, const long creationTime, const int channelNumber, const int channelSubnumber, const RECORDEDTV_STATE state);

	  std::string ChannelName;
	  int ChannelNumber;
	  int ChannelSubnumber;
	  RECORDEDTV_STATE State;
  };

   //TODO: PAE: Missing description
  class Audio : public Item
  {
  public:
	  Audio();

  };

   //TODO: PAE: Missing description
  class Image : public Item
  {
  public :
	  Image();
  };

  enum CONTAINER_TYPE {CONTAINER_TYPE_CONTAINER_UNKNOWN = -1,CONTAINER_TYPE_CONTAINER_SOURCE = 0, CONTAINER_TYPE_CONTAINER_TYPE = 1, CONTAINER_TYPE_CONTAINER_CATEGORY = 2, CONTAINER_TYPE_CONTAINER_GROUP = 3};

  enum CONTENT_TYPE{CONTENT_TYPE_ITEM_UNKNOWN = -1, CONTENT_TYPE_ITEM_RECORDED_TV = 0, CONTENT_TYPE_ITEM_VIDEO = 1, CONTENT_TYPE_ITEM_AUDIO = 2, CONTENT_TYPE_ITEM_IMAGE = 3};


   //TODO: PAE: Missing description
  class Container
  {

  public :
	  Container(const std::string& objectId, const std::string& parentId, const std::string& name, const std::string& description, const std::string& logo, const std::string& sourceId, const CONTAINER_TYPE containerType, const CONTENT_TYPE contentType, const int totalCount);

	  std::string ObjectID;
	  std::string ParentID;
	  std::string Name;
	  std::string Description;
	  std::string Logo;
	  std::string SourceId;
	  CONTAINER_TYPE ContainerType;
	  CONTENT_TYPE ContentType;
	  int TotalCount;
  };
   //TODO: PAE: Missing description
  class ContainerList :  public std::vector<Container*>
  {
  public:
	  ContainerList();
	 ~ContainerList(); 
  };
   //TODO: PAE: Missing description
  class ItemList :  public std::vector<Item*>
  {
  public:
	  ItemList();
	  ~ItemList(); 
  };

  //TODO: PAE: Missing description
  class GetObjectResult : public Response
  {
  public :
	  GetObjectResult();
     ~GetObjectResult();
	 ContainerList Containers;
	 ItemList Items;
  };

  
  

  /**
  * Represent parental status which is used as output parameter for the 
  * DVBLinkClient::SetParentalLock and DVBLinkClient::GetParentalStatus 
  * methods.
  * @see DVBLinkClient::SetParentalLock()
  * @see DVBLinkClient::GetParentalStatus()
  */
  class ParentalStatus : public Response
  {
  public:
    /**
      * Initializes a new instance of the dvblinkremote::ParentalStatus class.
      */
    ParentalStatus();
    
    /**
      * Initializes a new instance of the dvblinkremote::ParentalStatus class by coping another 
      * dvblinkremote::ParentalStatus instance.
      * @param parentalStatus a dvblinkremote::ParentalStatus reference.
      */
    ParentalStatus(ParentalStatus& parentalStatus);

    /**
      * Destructor.
      */
    ~ParentalStatus();

    /**
      * Represents if the parental lock is enabled or not. 
      */
    bool IsEnabled;
  };
}
