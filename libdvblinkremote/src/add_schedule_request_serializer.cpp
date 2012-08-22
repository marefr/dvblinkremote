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

#include "xml_object_serializer.h"

using namespace dvblinkremote;
using namespace dvblinkremoteserialization;

bool AddScheduleRequestSerializer::WriteObject(std::string& serializedData, AddScheduleRequest& objectGraph)
{
  tinyxml2::XMLElement* rootElement = PrepareXmlDocumentForObjectSerialization("schedule");

  if (!objectGraph.UserParameter.empty()) {
    rootElement->InsertEndChild(Util::CreateXmlElementWithText(&GetXmlDocument(), "user_param", objectGraph.UserParameter));
  }

  if (objectGraph.ForceAdd) {
    rootElement->InsertEndChild(Util::CreateXmlElementWithText(&GetXmlDocument(), "force_add", objectGraph.ForceAdd));
  }

  if (objectGraph.GetScheduleType() == objectGraph.SCHEDULE_TYPE_MANUAL) {
    AddManualScheduleRequest& addManualScheduleRequest = (AddManualScheduleRequest&)objectGraph;

    rootElement->InsertEndChild(Util::CreateXmlElementWithText(&GetXmlDocument(), "channel_id", addManualScheduleRequest.GetChannelID()));

    if (!addManualScheduleRequest.Title.empty()) {
      rootElement->InsertEndChild(Util::CreateXmlElementWithText(&GetXmlDocument(), "title", addManualScheduleRequest.Title));
    }

    rootElement->InsertEndChild(Util::CreateXmlElementWithText(&GetXmlDocument(), "start_time", addManualScheduleRequest.GetStartTime()));
    rootElement->InsertEndChild(Util::CreateXmlElementWithText(&GetXmlDocument(), "duration", addManualScheduleRequest.GetDuration()));
    rootElement->InsertEndChild(Util::CreateXmlElementWithText(&GetXmlDocument(), "day_mask", addManualScheduleRequest.GetDayMask()));
  }
    
  if (objectGraph.GetScheduleType() == objectGraph.SCHEDULE_TYPE_BY_EPG) {
    AddScheduleByEpgRequest& addScheduleByEpgRequest = (AddScheduleByEpgRequest&)objectGraph;

    rootElement->InsertEndChild(Util::CreateXmlElementWithText(&GetXmlDocument(), "channel_id", addScheduleByEpgRequest.GetChannelID()));
    rootElement->InsertEndChild(Util::CreateXmlElementWithText(&GetXmlDocument(), "program_id", addScheduleByEpgRequest.GetProgramID()));

    if (addScheduleByEpgRequest.Repeat) {
      rootElement->InsertEndChild(Util::CreateXmlElementWithText(&GetXmlDocument(), "repeat", addScheduleByEpgRequest.Repeat));
    }
  }    

  tinyxml2::XMLPrinter* printer = new tinyxml2::XMLPrinter();    
  GetXmlDocument().Accept(printer);
  serializedData = std::string(printer->CStr());
  
  return true;
}
