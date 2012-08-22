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

Recording::Recording(const std::string& id, const std::string& scheduleId, const std::string& channelId, const Program* program)
  : m_id(id), 
    m_scheduleId(scheduleId), 
    m_channelId(channelId), 
    m_program((Program*)program)
{
  IsActive = false;
}

Recording::Recording(Recording& recording)
{
  m_id = recording.GetID();
  m_scheduleId = recording.GetScheduleID();
  m_channelId = recording.GetChannelID();
  m_program = new Program(recording.GetProgram());
  IsActive = false;
}

Recording::~Recording()
{
  if (m_program) {
    delete m_program;
  }
}

std::string& Recording::GetID() 
{ 
  return m_id; 
}

std::string& Recording::GetScheduleID() 
{ 
  return m_scheduleId; 
}

std::string& Recording::GetChannelID() 
{ 
  return m_channelId; 
}

Program& Recording::GetProgram() 
{ 
  return *m_program; 
}

RecordingList::~RecordingList()
{
  for (std::vector<Recording*>::const_iterator it = begin(); it < end(); it++) 
  {
    delete (*it);
  }
}
