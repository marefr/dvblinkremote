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

GetRecordingsRequest::GetRecordingsRequest()
{

}

GetRecordingsRequest::~GetRecordingsRequest()
{

}

bool GetRecordingsRequestSerializer::WriteObject(std::string& serializedData, GetRecordingsRequest& objectGraph)
{
  PrepareXmlDocumentForObjectSerialization("recordings");    
  tinyxml2::XMLPrinter* printer = new tinyxml2::XMLPrinter();    
  GetXmlDocument().Accept(printer);
  serializedData = std::string(printer->CStr());
  
  return true;
}

bool GetRecordingsResponseSerializer::ReadObject(RecordingList& object, const std::string& xml)
{
  tinyxml2::XMLDocument& doc = GetXmlDocument();
    
  if (doc.Parse(xml.c_str()) == tinyxml2::XML_NO_ERROR) {
    tinyxml2::XMLElement* elRoot = doc.FirstChildElement("recordings");
    GetRecordingsResponseXmlDataDeserializer* xmlDataDeserializer = new GetRecordingsResponseXmlDataDeserializer(*this, object);
    elRoot->Accept(xmlDataDeserializer);
    delete xmlDataDeserializer;
    
    return true;
  }

  return false;
}

GetRecordingsResponseSerializer::GetRecordingsResponseXmlDataDeserializer::GetRecordingsResponseXmlDataDeserializer(GetRecordingsResponseSerializer& parent, RecordingList& recordingList) 
  : m_parent(parent), 
    m_recordingList(recordingList) 
{ }

GetRecordingsResponseSerializer::GetRecordingsResponseXmlDataDeserializer::~GetRecordingsResponseXmlDataDeserializer()
{ }

bool GetRecordingsResponseSerializer::GetRecordingsResponseXmlDataDeserializer::VisitEnter(const tinyxml2::XMLElement& element, const tinyxml2::XMLAttribute* attribute)
{
  if (strcmp(element.Name(), "recording") == 0) 
  {    
    std::string recordingId = Util::GetXmlFirstChildElementText(&element, "recording_id");
    std::string scheduleId = Util::GetXmlFirstChildElementText(&element, "schedule_id");
    std::string channelId = Util::GetXmlFirstChildElementText(&element, "channel_id");
    
    tinyxml2::XMLElement* pEl = (tinyxml2::XMLElement*)(&element)->FirstChildElement("program");
    
    Program* p = new Program();
    ProgramSerializer::Deserialize((XmlObjectSerializer<Response>&)m_parent, *pEl, *p);

    Recording* r = new Recording(recordingId, scheduleId, channelId, p);
      
    if (m_parent.HasChildElement(element, "is_active")) {
      r->IsActive = Util::GetXmlFirstChildElementTextAsBoolean(&element, "is_active");
    }

    m_recordingList.push_back(r);

    return false;
  }

  return true;
}
