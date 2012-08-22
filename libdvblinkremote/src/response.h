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
    * Base class for DVBLink Client responses.
    */
  class Response { };

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
      * @param number an optional constant integer representing the number of the channel.
      * @param subNumber an optional constant integer representing the sub-number of the channel.
      */
    Channel(const std::string& id, const long dvbLinkId, const std::string& name, const int number = -1, const int subNumber = -1);

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
