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
#include "response.h"
#include "xml_object_serializer.h"

using namespace dvblinkremote;
using namespace dvblinkremoteserialization;

GetSchedulesRequest::GetSchedulesRequest()
{

}

GetSchedulesRequest::~GetSchedulesRequest()
{

}

bool GetSchedulesRequestSerializer::WriteObject(std::string& serializedData, GetSchedulesRequest& objectGraph)
{
  PrepareXmlDocumentForObjectSerialization("schedules");    
  tinyxml2::XMLPrinter* printer = new tinyxml2::XMLPrinter();    
  GetXmlDocument().Accept(printer);
  serializedData = std::string(printer->CStr());
  
  return true;
}

bool GetSchedulesResponseSerializer::ReadObject(ScheduleList& object, const std::string& xml)
{
  tinyxml2::XMLDocument& doc = GetXmlDocument();
    
  if (doc.Parse(xml.c_str()) == tinyxml2::XML_NO_ERROR) {
    tinyxml2::XMLElement* elRoot = doc.FirstChildElement("schedules");
    GetSchedulesResponseXmlDataDeserializer* xmlDataDeserializer = new GetSchedulesResponseXmlDataDeserializer(*this, object);
    elRoot->Accept(xmlDataDeserializer);
    delete xmlDataDeserializer;
    
    return true;
  }

  return false;
}

GetSchedulesResponseSerializer::GetSchedulesResponseXmlDataDeserializer::GetSchedulesResponseXmlDataDeserializer(GetSchedulesResponseSerializer& parent, ScheduleList& scheduleList) 
  : m_parent(parent), 
    m_scheduleList(scheduleList) 
{ }

GetSchedulesResponseSerializer::GetSchedulesResponseXmlDataDeserializer::~GetSchedulesResponseXmlDataDeserializer()
{ }

bool GetSchedulesResponseSerializer::GetSchedulesResponseXmlDataDeserializer::VisitEnter(const tinyxml2::XMLElement& element, const tinyxml2::XMLAttribute* attribute)
{

  if (strcmp(element.Name(), "schedule") == 0) 
  {    
	
    std::string scheduleId = Util::GetXmlFirstChildElementText(&element, "schedule_id");
    std::string userParam = Util::GetXmlFirstChildElementText(&element, "user_param");
    bool forceadd = Util::GetXmlFirstChildElementTextAsBoolean(&element, "force_add");

	tinyxml2::XMLElement* epg = (tinyxml2::XMLElement*)(&element)->FirstChildElement("by_epg");
	tinyxml2::XMLElement* manual = (tinyxml2::XMLElement*)(&element)->FirstChildElement("manual");

	 Schedule* s = NULL;
		
	if (epg->FirstChildElement("program_id") != NULL) //byEPG
	{
	
		std::string channelid = Util::GetXmlFirstChildElementText(epg, "channel_id");
		std::string programid = Util::GetXmlFirstChildElementText(epg, "program_id");

		bool repeat = Util::GetXmlFirstChildElementTextAsBoolean(epg, "repeat");
		bool newonly = Util::GetXmlFirstChildElementTextAsBoolean(epg, "new_only");
		bool recordseriesanytime = Util::GetXmlFirstChildElementTextAsBoolean(epg, "record_series_anytime");
		bool recordings_to_keep = Util::GetXmlFirstChildElementTextAsBoolean(epg, "recordings_to_keep");
		tinyxml2::XMLElement* pEl = (tinyxml2::XMLElement*)(epg)->FirstChildElement("program");
		Program* p = new Program();
		ProgramSerializer::Deserialize((XmlObjectSerializer<Response>&)m_parent, *pEl, *p);
		s = new Schedule(scheduleId,channelid,programid, p, recordings_to_keep,userParam,forceadd,repeat,newonly,recordings_to_keep);

	}else{

		std::string channelid = Util::GetXmlFirstChildElementText(epg, "channel_id");
		std::string title = Util::GetXmlFirstChildElementText(epg, "title");

		long starttime = Util::GetXmlFirstChildElementTextAsLong(epg, "start_time");
		int duration = Util::GetXmlFirstChildElementTextAsLong(epg, "duration");
		DayMask daymask = (DayMask)Util::GetXmlFirstChildElementTextAsInt(epg, "day_mask");
		bool recordings_to_keep = Util::GetXmlFirstChildElementTextAsBoolean(epg, "recordings_to_keep");
		s= new Schedule(scheduleId,channelid,title,starttime,duration,daymask,recordings_to_keep,userParam,forceadd);

	}
	
	if (s != NULL)
	m_scheduleList.push_back(s);

    return false;
  }

  return true;
}
