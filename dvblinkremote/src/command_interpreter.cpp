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

#include "command_interpreter.h"
#include <iostream>
#include <sstream>
#include <cctype>
#include <ctime>
#include "util.h"

using namespace dvblinkremote;

CommandInterpreter::CommandInterpreter(IDVBLinkRemoteConnection& dvblinkRemoteCommunication, const std::string& hostAddress, const std::string& clientId)
  : m_dvblinkRemoteCommunication(dvblinkRemoteCommunication), 
    m_hostAddress(hostAddress), 
    m_clientId(clientId)
{

}

CommandInterpreter::~CommandInterpreter()
{

}

void CommandInterpreter::PrintCommands()
{
  std::cout << std::endl << "Available commands:" << std::endl;
  std::cout << "----------------------" << std::endl;
  std::cout << "[1]\tGet channels" << std::endl;
  std::cout << "[2]\tSearch the electronic program guide (EPG)" << std::endl;
  std::cout << "[3]\tPlay channel" << std::endl;
  std::cout << "[4]\tGet recordings" << std::endl;
  std::cout << "[exit]\tTerminate the program" << std::endl;
}

int CommandInterpreter::Evaluate(std::string& command)
{
  int ret = 1;

  if (command == "1") {
    GetChannels();
  }
  else if (command == "2") {
    SearchEpg();
  }
  else if (command == "3") {
    PlayChannel();
  }
  else if (command == "4") {
    GetRecordings();
  }
  else if (command == "exit") {
    ret = -1;
  }
  else {
    ret = 0;
  }

  return ret;
}

void CommandInterpreter::PrintError()
{
  std::string lastError;
  m_dvblinkRemoteCommunication.GetLastError(lastError);
  printf("%s\n", lastError.c_str());
}

void CommandInterpreter::GetChannels()
{
  DVBLinkRemoteStatusCode status;
  GetChannelsRequest* request = new GetChannelsRequest();
  ChannelList* response = new ChannelList();

  if ((status = m_dvblinkRemoteCommunication.GetChannels(*request, *response)) == DVBLINK_REMOTE_STATUS_OK) {
    std::cout << "Channels:" << std::endl;
    std::cout << "----------------------" << std::endl;

    for (std::vector<Channel*>::iterator it = response->begin(); it < response->end(); it++) 
    {
      printf("[%d]\t%s\n", (*it)->Number, (*it)->GetName().c_str());
    }
  }
  else {
    PrintError();
  }

  delete response;
  delete request;
}

void CommandInterpreter::SearchEpg()
{
  DVBLinkRemoteStatusCode status;

  while (true) {
    std::string channelName;
    std::string channelId = "";
    std::cout << "Enter channel name: ";
    getline(std::cin, channelName);
    ToLowerCase(channelName);

    GetChannelsRequest* request1 = new GetChannelsRequest();
    ChannelList* response1 = new ChannelList();

    if ((status = m_dvblinkRemoteCommunication.GetChannels(*request1, *response1)) == DVBLINK_REMOTE_STATUS_OK) {
      for (std::vector<Channel*>::iterator it = response1->begin(); it < response1->end(); it++) 
      {
        std::string cName = (*it)->GetName();
        ToLowerCase(cName);

        if (cName == channelName) {
          channelId = (*it)->GetID();
        }
      }

      if (!channelId.empty()) {
        EpgSearchRequest* epgSearchRequest = new EpgSearchRequest(channelId);
        EpgSearchResult* epgSearchResult = new EpgSearchResult();

        if ((status = m_dvblinkRemoteCommunication.SearchEpg(*epgSearchRequest, *epgSearchResult)) == DVBLINK_REMOTE_STATUS_OK) {
          for (std::vector<ChannelEpgData*>::iterator it = epgSearchResult->begin(); it < epgSearchResult->end(); it++) 
          {
            ChannelEpgData* channelEpgData = (ChannelEpgData*)*it;
            EpgData& epgData = channelEpgData->GetEpgData();

            printf("EPG data found for channel with id (%s)\n", channelEpgData->GetChannelID());

            for (std::vector<Program*>::iterator pIt = epgData.begin(); pIt < epgData.end(); pIt++) 
            {
              Program* p = (Program*)*pIt;
              struct tm * timeinfo;
              char startTimeBuffer[80];
              char endTimeBuffer[80];
              memset(startTimeBuffer, 0, 80);
              memset(endTimeBuffer, 0, 80);

              time_t startTime = (time_t)p->GetStartTime();
              timeinfo = localtime(&startTime);
              strftime(startTimeBuffer, 80, "%c", timeinfo);

              time_t endTime = (time_t)(p->GetStartTime() + p->GetDuration());        
              timeinfo = localtime(&endTime);
              strftime(endTimeBuffer, 80, "%c", timeinfo);

              printf("Title: %s\nDescription: %s\nKeywords: %s\nActors: %s\nDirectors: %s\nYear: %d\nStart Time: %s\nEnd Time: %s\n\n", 
                p->GetTitle().c_str(), 
                p->ShortDescription.c_str(), 
                p->Keywords.c_str(),
                p->Actors.c_str(),
                p->Directors.c_str(),
                p->Year,
                startTimeBuffer,
                endTimeBuffer
                );
            }
          }
        }
        else {
          PrintError();
        }

        delete epgSearchResult;
        delete epgSearchRequest;

        break;
      }
      else {
        std::cout << "Error! No channel with provided name was found..." << std::endl;
      }
    }
    else {
      PrintError();
    }

    delete response1;
    delete request1;
  }
}

void CommandInterpreter::PlayChannel()
{
  DVBLinkRemoteStatusCode status;

  while (true) {
    std::cout << "Play channel:" << std::endl;
    std::cout << "----------------------" << std::endl;
    std::string channelName;
    long dvbLinkChannelId = 0;
    std::cout << "Enter channel name: ";
    getline(std::cin, channelName);
    ToLowerCase(channelName);

    GetChannelsRequest* gcr = new GetChannelsRequest();
    ChannelList* channelList = new ChannelList();

    if ((status = m_dvblinkRemoteCommunication.GetChannels(*gcr, *channelList)) == dvblinkremote::DVBLINK_REMOTE_STATUS_OK) {
      for (std::vector<Channel*>::iterator it = channelList->begin(); it < channelList->end(); it++) 
      {
        std::string cName = (*it)->GetName();
        ToLowerCase(cName);

        if (cName == channelName) {
          dvbLinkChannelId = (*it)->GetDvbLinkID();
        }
      }

      if (dvbLinkChannelId > 0) {
        RawHttpStreamRequest* streamRequest = new RawHttpStreamRequest(m_hostAddress, dvbLinkChannelId, m_clientId);
        Stream* stream = new Stream();

        if ((status = m_dvblinkRemoteCommunication.PlayChannel(*streamRequest, *stream)) == DVBLINK_REMOTE_STATUS_OK) {
          printf("Use the following url to play the stream:\n%s\n\n", stream->GetUrl());
          std::cout << "Press any key to stop stream..." << std::endl;
          std::string s;
          getline(std::cin, s);

          dvblinkremote::StopStreamRequest* stopStreamRequest = new dvblinkremote::StopStreamRequest(stream->GetChannelHandle());

          if ((status = m_dvblinkRemoteCommunication.StopChannel(*stopStreamRequest)) == DVBLINK_REMOTE_STATUS_OK) {
            std::cout << "Stream has been stopped." << std::endl;
          }

          delete stopStreamRequest;
        }
        else {
          PrintError();
        }

        delete stream;
        delete streamRequest;
      }
      else {
        std::cout << "Error! No channel with provided name was found..." << std::endl;
      }
    }
    else {
      PrintError();
    }

    delete channelList;
    delete gcr;

    break;
  }
}

void CommandInterpreter::GetRecordings()
{
  DVBLinkRemoteStatusCode status;
  GetRecordingsRequest* getRecordingsRequest = new GetRecordingsRequest();
  RecordingList* recordingList = new RecordingList();

  if ((status = m_dvblinkRemoteCommunication.GetRecordings(*getRecordingsRequest, *recordingList)) == DVBLINK_REMOTE_STATUS_OK) {
    int n = 1;

    std::cout << "Scheduled recordings:" << std::endl;
    std::cout << "----------------------" << std::endl;

    for (std::vector<Recording*>::iterator it = recordingList->begin(); it < recordingList->end(); it++) 
    {
      Recording* recording = (Recording*)*it;
      Program& p = recording->GetProgram();

      struct tm * timeinfo;
      char startTimeBuffer[80];
      memset(startTimeBuffer, 0, 80);

      time_t startTime = (time_t)p.GetStartTime();
      timeinfo = localtime(&startTime);
      strftime(startTimeBuffer, 80, "%c", timeinfo);

      std::string strActive = "";

      if (recording->IsActive) {
        strActive = "*";
      }

      printf("[%d] %s%s (%s)\n", 
        n,
        strActive.c_str(),
        p.GetTitle().c_str(),
        startTimeBuffer
        );

      n++;
    }
  }
  else {
    PrintError();
  }

  delete recordingList;
  delete getRecordingsRequest;
}
