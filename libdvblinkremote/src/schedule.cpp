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

#include "response.h"

using namespace dvblinkremote;


Schedule::Schedule(const std::string& id, const std::string& channelId, const std::string& title,const long startTime, const int duration, const DayMask dayMask, const int recordingsToKeep, const std::string& userParam, const bool forceAdd)
	: m_id(id),
	m_channelId(channelId),
	m_title(title),
	StartTime(startTime),
	Duration(duration),
	Mask(dayMask),
	RecordingsToKeep(recordingsToKeep),
	m_userParam(userParam),
	ForcedAdd(forceAdd),
	Type(Manual)
{

}

Schedule::Schedule(const std::string& id, const std::string& channelId, const std::string& programId,const Program* program, const int recordingsToKeep, const std::string& userParam, const bool forceAdd, const bool repeat, const bool newOnly,const bool recordSeriesAnyTime)
	: m_id(id),
	m_channelId(channelId),
	m_programId(programId),
	m_program((Program*)program),
	RecordingsToKeep(recordingsToKeep),
	m_userParam(userParam),
	ForcedAdd(forceAdd),
	Repeat(repeat),
	NewOnly(newOnly),
	RecordSeriesAnytime(recordSeriesAnyTime),
	Type(EPG)
{

}
Schedule::Schedule(Schedule& schedule)
{
	m_id = schedule.GetID();
	m_channelId = schedule.GetChannelID();
	m_programId = schedule.GetProgramID();
	m_program = new Program(schedule.GetProgram());
	RecordingsToKeep = schedule.RecordingsToKeep;
	m_userParam = schedule.GetUserParam();
	ForcedAdd = schedule.ForcedAdd;
	if (schedule.Type == EPG)
	{
		Repeat = schedule.Repeat;
		NewOnly = schedule.NewOnly;
		RecordSeriesAnytime = schedule.RecordSeriesAnytime;
	}else{
		m_title = schedule.GetTitle();
		StartTime = schedule.StartTime;
		Duration = schedule.Duration;
		Mask = schedule.Mask;
	}
	Type = schedule.Type;

}

Schedule::~Schedule()
{
	if (m_program) {
		delete m_program;
	}
}

std::string& Schedule::GetID() 
{ 
	return m_id; 
}

std::string& Schedule::GetUserParam() 
{ 
	return m_userParam; 
}

std::string& Schedule::GetChannelID() 
{ 
	return m_channelId; 
}

std::string& Schedule::GetProgramID() 
{ 
	return m_programId; 
}

Program& Schedule::GetProgram() 
{ 
	return *m_program; 
}


std::string& Schedule::GetTitle() 
{ 
	return m_title; 
}

ScheduleList::~ScheduleList()
{
	for (std::vector<Schedule*>::const_iterator it = begin(); it < end(); it++) 
	{
		delete (*it);
	}
}
