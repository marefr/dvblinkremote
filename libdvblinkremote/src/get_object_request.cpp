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


GetObjectRequest::GetObjectRequest(const std::string serverAddress,const std::string objectId, const OBJECT_TYPE objectType, const ITEM_TYPE itemType, const int startPosition, const int requestCount, const bool childrenRequest)
	:m_serverAddress(serverAddress), m_objectId(objectId), ObjectType(objectType), ItemType(itemType),StartPosition(startPosition), RequestCount(requestCount), ChildrenRequest(childrenRequest)
{

}

GetObjectRequest::~GetObjectRequest()
{


}

std::string GetObjectRequest::GetObjectID()
{
	return m_objectId;
}

std::string GetObjectRequest::GetServerAddress()
{
	return m_serverAddress;
}

GetObjectResult::GetObjectResult()
{

}

GetObjectResult::~GetObjectResult()
{

}

ItemList::ItemList()
{

}
ItemList::~ItemList()
{
	for (std::vector<Item*>::iterator it = begin(); it < end(); it++) 
	{
		delete (*it);
	}
}

ContainerList::ContainerList()
{

}

ContainerList::~ContainerList()
{
	for (std::vector<Container*>::iterator it = begin(); it < end(); it++) 
	{
		delete (*it);
	}
}

bool GetObjectRequestSerializer::WriteObject(std::string& serializedData, GetObjectRequest& objectGraph)
{
  tinyxml2::XMLElement* rootElement = PrepareXmlDocumentForObjectSerialization("object_requester"); 

  rootElement->InsertEndChild(Util::CreateXmlElementWithText(&GetXmlDocument(), "object_id", objectGraph.GetObjectID()));

  if ( objectGraph.ObjectType != OBJECT_TYPE_UNKNOWN)
  {
	  rootElement->InsertEndChild(Util::CreateXmlElementWithText(&GetXmlDocument(), "object_type", objectGraph.ObjectType));
  }
  if (objectGraph.ItemType != ITEM_TYPE_UNKNOWN)
  {
	  rootElement->InsertEndChild(Util::CreateXmlElementWithText(&GetXmlDocument(), "item_type", objectGraph.ItemType));
  }
  if (objectGraph.StartPosition != 0)
  {
	  rootElement->InsertEndChild(Util::CreateXmlElementWithText(&GetXmlDocument(), "start_position", objectGraph.StartPosition));
  }
  if ( objectGraph.RequestCount != -1)
  {
	  rootElement->InsertEndChild(Util::CreateXmlElementWithText(&GetXmlDocument(), "requested_count", objectGraph.RequestCount));
  }

  if (objectGraph.ChildrenRequest)
  {
	  rootElement->InsertEndChild(Util::CreateXmlElementWithText(&GetXmlDocument(), "children_request", objectGraph.ChildrenRequest));

  }
rootElement->InsertEndChild(Util::CreateXmlElementWithText(&GetXmlDocument(), "server_address", objectGraph.GetServerAddress()));
  tinyxml2::XMLPrinter* printer = new tinyxml2::XMLPrinter();    
  GetXmlDocument().Accept(printer);
  serializedData = std::string(printer->CStr());
  
  return true;
}

bool GetObjectResponseSerializer::ReadObject(GetObjectResult& object, const std::string& xml)
{

  tinyxml2::XMLDocument& doc = GetXmlDocument();
    
  if (doc.Parse(xml.c_str()) == tinyxml2::XML_NO_ERROR) {

	  tinyxml2::XMLElement* elRoot = doc.FirstChildElement("object");
	 tinyxml2::XMLElement* containers = elRoot->FirstChildElement("containers");
	 tinyxml2::XMLElement* items =elRoot->FirstChildElement("items");

    ContainerXmlDataDeserializer* xmlContainerDataDeserializer = new ContainerXmlDataDeserializer(*this, object.Containers);
    containers->Accept(xmlContainerDataDeserializer);
	delete xmlContainerDataDeserializer;

	ItemXmlDataDeserializer* xmlItemDataDeserializer = new ItemXmlDataDeserializer(*this, object.Items);
	items->Accept(xmlItemDataDeserializer);
	delete xmlItemDataDeserializer;

    return true;
  }

  return false;
}


Container::Container(const std::string& objectId, const std::string& parentId, const std::string& name, const std::string& description, const std::string& logo, const std::string& sourceId, const CONTAINER_TYPE containerType, const CONTENT_TYPE contentType, const int totalCount)
: ObjectID(objectId), ParentID(parentId), Name(name),Description(description), Logo(logo), SourceId(sourceId), ContainerType(containerType), ContentType(contentType), TotalCount(totalCount)
{

}

Item::Item(const ITEM_TYPE type)
	: Type(type)
{

}

Video::Video(const std::string& objectId, const std::string& parentId, const std::string& url, const std::string& thumbnail, const bool canBeDeleted, const long size, const long creationTime)
	: Item(ITEM_TYPE_VIDEO),ObjectID(objectId), ParentID(parentId), Url(url), Thumbnail(thumbnail),CanBeDeleted(canBeDeleted), Size(size), CreationTime(creationTime)
{

}

RecordedTV::RecordedTV(const std::string& objectId, const std::string& parentId, const std::string& url, const std::string& thumbnail, const std::string& channelName, const bool canBeDeleted, const long size, const long creationTime, const int channelNumber, const int channelSubnumber, const RECORDEDTV_STATE state)
	:Video(objectId,parentId,url,thumbnail,canBeDeleted,size,creationTime), ChannelName(channelName), ChannelNumber(channelNumber), ChannelSubnumber(channelSubnumber), State(state)
{
	Type = ITEM_TYPE_RECORDED_TV;
}

Audio::Audio()
	: Item(ITEM_TYPE_AUDIO)
{

}

Image::Image()
	: Item(ITEM_TYPE_IMAGE)
{

}

GetObjectResponseSerializer::ContainerXmlDataDeserializer::ContainerXmlDataDeserializer(GetObjectResponseSerializer& parent, ContainerList& containers)
	: m_parent(parent), m_containers(containers)
{

}

GetObjectResponseSerializer::ContainerXmlDataDeserializer::~ContainerXmlDataDeserializer()
{

}

bool GetObjectResponseSerializer::ContainerXmlDataDeserializer::VisitEnter(const tinyxml2::XMLElement& element, const tinyxml2::XMLAttribute* attribute)
{

	if (strcmp(element.Name(), "container") == 0) 
	{     
	 std::string objectId = Util::GetXmlFirstChildElementText(&element, "object_id");
	 std::string parentId = Util::GetXmlFirstChildElementText(&element, "parent_id");
	 std::string name = Util::GetXmlFirstChildElementText(&element, "name");
	 std::string description = Util::GetXmlFirstChildElementText(&element, "description");
	 std::string logo = Util::GetXmlFirstChildElementText(&element, "logo");
	 dvblinkremote::CONTAINER_TYPE containerType = (dvblinkremote::CONTAINER_TYPE) Util::GetXmlFirstChildElementTextAsInt(&element, "container_type");
	 CONTENT_TYPE contentType = (CONTENT_TYPE) Util::GetXmlFirstChildElementTextAsInt(&element, "content_type");
	 int totalcount = Util::GetXmlFirstChildElementTextAsInt(&element, "total_count");
	 std::string sourceId = Util::GetXmlFirstChildElementText(&element, "source_id");
	 Container * container = new Container(objectId,parentId,name,description,logo,sourceId,containerType,contentType,totalcount);
	 m_containers.push_back(container);

	return false;
	}
	return true;
}



GetObjectResponseSerializer::ItemXmlDataDeserializer::ItemXmlDataDeserializer(GetObjectResponseSerializer& parent, ItemList& items)
	: m_parent(parent), m_items(items)
{

}

GetObjectResponseSerializer::ItemXmlDataDeserializer::~ItemXmlDataDeserializer()
{

}

bool GetObjectResponseSerializer::ItemXmlDataDeserializer::VisitEnter(const tinyxml2::XMLElement& element, const tinyxml2::XMLAttribute* attribute)
{
	Item * item;
	if (strcmp(element.Name(), "recorded_tv") == 0) 
	{     
		std::string objectId = Util::GetXmlFirstChildElementText(&element, "object_id");
		std::string parentId = Util::GetXmlFirstChildElementText(&element, "parent_id");
		std::string url = Util::GetXmlFirstChildElementText(&element, "url");
		std::string thumbnail = Util::GetXmlFirstChildElementText(&element, "thumbnail");
		std::string channelName = Util::GetXmlFirstChildElementText(&element, "channel_name");
		bool canBeDeleted = Util::GetXmlFirstChildElementTextAsBoolean(&element, "can_be_deleted");
		long size = Util::GetXmlFirstChildElementTextAsLong(&element, "size");
		long creationTime = Util::GetXmlFirstChildElementTextAsLong(&element, "creation_time");
		int channelNumber = Util::GetXmlFirstChildElementTextAsInt(&element, "channel_number");
		int channelSubnumber = Util::GetXmlFirstChildElementTextAsInt(&element, "channel_subnumber");
		RECORDEDTV_STATE state = (RECORDEDTV_STATE)  Util::GetXmlFirstChildElementTextAsInt(&element, "state");

		item = new RecordedTV(objectId, parentId, url,thumbnail,channelName,canBeDeleted,size,creationTime,channelNumber,channelSubnumber, state);

		tinyxml2::XMLElement * vElement = (tinyxml2::XMLElement*)(&element)->FirstChildElement("video_info");

		VideoInfoSerializer::Deserialize((XmlObjectSerializer<Response>&)m_parent, *vElement, ((RecordedTV*) item)->VInfo);
		
		m_items.push_back(item);
		return false;
	}

	if (strcmp(element.Name(), "video") == 0) 
	{     
		std::string objectId = Util::GetXmlFirstChildElementText(&element, "object_id");
		std::string parentId = Util::GetXmlFirstChildElementText(&element, "parent_id");
		std::string url = Util::GetXmlFirstChildElementText(&element, "url");
		std::string thumbnail = Util::GetXmlFirstChildElementText(&element, "thumbnail");
		std::string channelName = Util::GetXmlFirstChildElementText(&element, "channel_name");
		bool canBeDeleted = Util::GetXmlFirstChildElementTextAsBoolean(&element, "can_be_deleted");
		long size = Util::GetXmlFirstChildElementTextAsLong(&element, "size");
		long creationTime = Util::GetXmlFirstChildElementTextAsLong(&element, "creation_time");

		item = new Video(objectId, parentId, url,thumbnail,canBeDeleted,size,creationTime);
		m_items.push_back(item);
		return false;
	}

	if (strcmp(element.Name(), "audio") == 0) 
	{     
		item = new Audio();
		m_items.push_back(item);
		return false;
	}

	if (strcmp(element.Name(), "image") == 0) 
	{     
		item = new Image();
		m_items.push_back(item);
		return false;
	}

	return true;

}

void VideoInfoSerializer::Deserialize(XmlObjectSerializer<Response>& objectSerializer, const tinyxml2::XMLElement& element, dvblinkremote::VideoInfo& videoinfo)
{

	videoinfo.Title = Util::GetXmlFirstChildElementText(&element, "name");
	videoinfo.StartTime = Util::GetXmlFirstChildElementTextAsLong(&element, "start_time");
	videoinfo.Duration = Util::GetXmlFirstChildElementTextAsLong(&element, "duration");

	videoinfo.ShortDescription = Util::GetXmlFirstChildElementText(&element, "short_desc");
	videoinfo.SubTitle = Util::GetXmlFirstChildElementText(&element, "subname");
	videoinfo.Language = Util::GetXmlFirstChildElementText(&element, "language");
	videoinfo.Actors = Util::GetXmlFirstChildElementText(&element, "actors");
	videoinfo.Directors = Util::GetXmlFirstChildElementText(&element, "directors");
	videoinfo.Writers = Util::GetXmlFirstChildElementText(&element, "writers");
	videoinfo.Producers = Util::GetXmlFirstChildElementText(&element, "producers");
	videoinfo.Guests = Util::GetXmlFirstChildElementText(&element, "guests");
	videoinfo.Keywords = Util::GetXmlFirstChildElementText(&element, "categories");
	videoinfo.Image = Util::GetXmlFirstChildElementText(&element, "image");

	videoinfo.Year = Util::GetXmlFirstChildElementTextAsLong(&element, "year");
	videoinfo.EpisodeNumber = Util::GetXmlFirstChildElementTextAsLong(&element, "episode_num");
	videoinfo.SeasonNumber = Util::GetXmlFirstChildElementTextAsLong(&element, "season_num");
	videoinfo.Rating = Util::GetXmlFirstChildElementTextAsLong(&element, "stars_num");
	videoinfo.MaximumRating = Util::GetXmlFirstChildElementTextAsLong(&element, "starsmax_num");

	videoinfo.IsHdtv = objectSerializer.HasChildElement(*&element, "hdtv");
	videoinfo.IsPremiere = objectSerializer.HasChildElement(*&element, "premiere");
	videoinfo.IsRepeat = objectSerializer.HasChildElement(*&element, "repeat");

	videoinfo.IsCatAction = objectSerializer.HasChildElement(*&element, "cat_action");
	videoinfo.IsCatComedy = objectSerializer.HasChildElement(*&element, "cat_comedy");
	videoinfo.IsCatDocumentary = objectSerializer.HasChildElement(*&element, "cat_documentary");
	videoinfo.IsCatDrama = objectSerializer.HasChildElement(*&element, "cat_drama");
	videoinfo.IsCatEducational = objectSerializer.HasChildElement(*&element, "cat_educational");
	videoinfo.IsCatHorror = objectSerializer.HasChildElement(*&element, "cat_horror");
	videoinfo.IsCatKids = objectSerializer.HasChildElement(*&element, "cat_kids");
	videoinfo.IsCatMovie = objectSerializer.HasChildElement(*&element, "cat_movie");
	videoinfo.IsCatMusic = objectSerializer.HasChildElement(*&element, "cat_music");
	videoinfo.IsCatNews = objectSerializer.HasChildElement(*&element, "cat_news");
	videoinfo.IsCatReality = objectSerializer.HasChildElement(*&element, "cat_reality");
	videoinfo.IsCatRomance = objectSerializer.HasChildElement(*&element, "cat_romance");
	videoinfo.IsCatScifi = objectSerializer.HasChildElement(*&element, "cat_scifi");
	videoinfo.IsCatSerial = objectSerializer.HasChildElement(*&element, "cat_serial");
	videoinfo.IsCatSoap = objectSerializer.HasChildElement(*&element, "cat_soap");
	videoinfo.IsCatSpecial = objectSerializer.HasChildElement(*&element, "cat_special");
	videoinfo.IsCatSports = objectSerializer.HasChildElement(*&element, "cat_sports");
	videoinfo.IsCatThriller = objectSerializer.HasChildElement(*&element, "cat_thriller");
	videoinfo.IsCatAdult = objectSerializer.HasChildElement(*&element, "cat_adult");

}