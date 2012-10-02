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

#include "request.h"

using namespace dvblinkremote;

AddScheduleByEpgRequest::AddScheduleByEpgRequest(const std::string& channelId, const std::string& programId, const bool repeat, const bool newOnly, const bool recordSeriesAnytime)
  : AddScheduleRequest(SCHEDULE_TYPE_BY_EPG, channelId), 
    m_programId(programId), 
    Repeat(repeat), 
    NewOnly(newOnly), 
    RecordSeriesAnytime(recordSeriesAnytime)
{

}

AddScheduleByEpgRequest::~AddScheduleByEpgRequest()
{

}

std::string& AddScheduleByEpgRequest::GetProgramID() 
{ 
  return m_programId; 
}
