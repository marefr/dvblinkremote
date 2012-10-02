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
#include "xml_object_serializer.h"

using namespace dvblinkremote;
using namespace dvblinkremoteserialization;

MultimediaInfo::MultimediaInfo() 
{
  m_title = "";
  m_startTime = 0;
  m_duration = 0;
  ShortDescription = "";
  SubTitle = "";
  Language = "";
  Actors = "";
  Directors = "";
  Writers = "";
  Producers = "";
  Guests = "";
  Keywords = "";
  Image = "";
  Year = 0;
  EpisodeNumber = 0;
  SeasonNumber = 0;
  Rating = 0;
  MaximumRating = 0;
  IsHdtv = false;
  IsPremiere = false;
  IsRepeat = false;
  IsSeries = false;
  IsRecord = false;
  IsRepeatRecord = false;
  IsCatAction = false;
  IsCatComedy = false;
  IsCatDocumentary = false;
  IsCatDrama = false;
  IsCatEducational = false;
  IsCatHorror = false;
  IsCatKids = false;
  IsCatMovie = false;
  IsCatMusic = false;
  IsCatNews = false;
  IsCatReality = false;
  IsCatRomance = false;
  IsCatScifi = false;
  IsCatSerial = false;
  IsCatSoap = false;
  IsCatSpecial = false;
  IsCatSports = false;
  IsCatThriller = false;
  IsCatAdult = false;
}

MultimediaInfo::MultimediaInfo(const std::string& title, const long startTime, const long duration)
  : m_title(title), 
    m_startTime(startTime), 
    m_duration(duration)
{
  ShortDescription = "";
  SubTitle = "";
  Language = "";
  Actors = "";
  Directors = "";
  Writers = "";
  Producers = "";
  Guests = "";
  Keywords = "";
  Image = "";
  Year = 0;
  EpisodeNumber = 0;
  SeasonNumber = 0;
  Rating = 0;
  MaximumRating = 0;
  IsHdtv = false;
  IsPremiere = false;
  IsRepeat = false;
  IsSeries = false;
  IsRecord = false;
  IsRepeatRecord = false;
  IsCatAction = false;
  IsCatComedy = false;
  IsCatDocumentary = false;
  IsCatDrama = false;
  IsCatEducational = false;
  IsCatHorror = false;
  IsCatKids = false;
  IsCatMovie = false;
  IsCatMusic = false;
  IsCatNews = false;
  IsCatReality = false;
  IsCatRomance = false;
  IsCatScifi = false;
  IsCatSerial = false;
  IsCatSoap = false;
  IsCatSpecial = false;
  IsCatSports = false;
  IsCatThriller = false;
  IsCatAdult = false;
}

MultimediaInfo::MultimediaInfo(MultimediaInfo& multimediaInfo) 
  : m_title(multimediaInfo.GetTitle()),
    m_startTime(multimediaInfo.GetStartTime()),
    m_duration(multimediaInfo.GetDuration())
{
  ShortDescription = multimediaInfo.ShortDescription;
  SubTitle = multimediaInfo.SubTitle;
  Language = multimediaInfo.Language;
  Actors = multimediaInfo.Actors;
  Directors = multimediaInfo.Directors;
  Writers = multimediaInfo.Writers;
  Producers = multimediaInfo.Producers;
  Guests = multimediaInfo.Guests;
  Keywords = multimediaInfo.Keywords;
  Image = multimediaInfo.Image;
  Year = multimediaInfo.Year;
  EpisodeNumber = multimediaInfo.EpisodeNumber;
  SeasonNumber = multimediaInfo.SeasonNumber;
  Rating = multimediaInfo.Rating;
  MaximumRating = multimediaInfo.MaximumRating;
  IsHdtv = multimediaInfo.IsHdtv;
  IsPremiere = multimediaInfo.IsPremiere;
  IsRepeat = multimediaInfo.IsRepeat;
  IsSeries = multimediaInfo.IsSeries;
  IsRecord = multimediaInfo.IsRecord;
  IsRepeatRecord = multimediaInfo.IsRepeatRecord;
  IsCatAction = multimediaInfo.IsCatAction;
  IsCatComedy = multimediaInfo.IsCatComedy;
  IsCatDocumentary = multimediaInfo.IsCatDocumentary;
  IsCatDrama = multimediaInfo.IsCatDrama;
  IsCatEducational = multimediaInfo.IsCatEducational;
  IsCatHorror = multimediaInfo.IsCatHorror;
  IsCatKids = multimediaInfo.IsCatKids;
  IsCatMovie = multimediaInfo.IsCatMovie;
  IsCatMusic = multimediaInfo.IsCatMusic;
  IsCatNews = multimediaInfo.IsCatNews;
  IsCatReality = multimediaInfo.IsCatReality;
  IsCatRomance = multimediaInfo.IsCatRomance;
  IsCatScifi = multimediaInfo.IsCatScifi;
  IsCatSerial = multimediaInfo.IsCatSerial;
  IsCatSoap = multimediaInfo.IsCatSoap;
  IsCatSpecial = multimediaInfo.IsCatSpecial;
  IsCatSports = multimediaInfo.IsCatSports;
  IsCatThriller = multimediaInfo.IsCatThriller;
  IsCatAdult = multimediaInfo.IsCatAdult;
}

std::string& MultimediaInfo::GetTitle() 
{ 
  return m_title; 
}

void MultimediaInfo::SetTitle(const std::string& title) 
{ 
  m_title = title; 
}

long MultimediaInfo::GetStartTime() 
{ 
  return m_startTime; 
}

void MultimediaInfo::SetStartTime(const long startTime) 
{ 
  m_startTime = startTime; 
}

long MultimediaInfo::GetDuration() 
{ 
  return m_duration; 
}

void MultimediaInfo::SetDuration(const long duration) 
{ 
  m_duration = duration; 
}

void MultimediaInfoSerializer::Deserialize(XmlObjectSerializer<Response>& objectSerializer, const tinyxml2::XMLElement& element, dvblinkremote::MultimediaInfo& multimediaInfo)
{
  multimediaInfo.SetTitle(Util::GetXmlFirstChildElementText(&element, "name"));
  multimediaInfo.SetStartTime(Util::GetXmlFirstChildElementTextAsLong(&element, "start_time"));
  multimediaInfo.SetDuration(Util::GetXmlFirstChildElementTextAsLong(&element, "duration"));

  multimediaInfo.ShortDescription = Util::GetXmlFirstChildElementText(&element, "short_desc");
  multimediaInfo.SubTitle = Util::GetXmlFirstChildElementText(&element, "subname");
  multimediaInfo.Language = Util::GetXmlFirstChildElementText(&element, "language");
  multimediaInfo.Actors = Util::GetXmlFirstChildElementText(&element, "actors");
  multimediaInfo.Directors = Util::GetXmlFirstChildElementText(&element, "directors");
  multimediaInfo.Writers = Util::GetXmlFirstChildElementText(&element, "writers");
  multimediaInfo.Producers = Util::GetXmlFirstChildElementText(&element, "producers");
  multimediaInfo.Guests = Util::GetXmlFirstChildElementText(&element, "guests");
  multimediaInfo.Keywords = Util::GetXmlFirstChildElementText(&element, "categories");
  multimediaInfo.Image = Util::GetXmlFirstChildElementText(&element, "image");
         
  multimediaInfo.Year = Util::GetXmlFirstChildElementTextAsLong(&element, "year");
  multimediaInfo.EpisodeNumber = Util::GetXmlFirstChildElementTextAsLong(&element, "episode_num");
  multimediaInfo.SeasonNumber = Util::GetXmlFirstChildElementTextAsLong(&element, "season_num");
  multimediaInfo.Rating = Util::GetXmlFirstChildElementTextAsLong(&element, "stars_num");
  multimediaInfo.MaximumRating = Util::GetXmlFirstChildElementTextAsLong(&element, "starsmax_num");
         
  multimediaInfo.IsHdtv = objectSerializer.HasChildElement(*&element, "hdtv");
  multimediaInfo.IsPremiere = objectSerializer.HasChildElement(*&element, "premiere");
  multimediaInfo.IsRepeat = objectSerializer.HasChildElement(*&element, "repeat");
  multimediaInfo.IsSeries = objectSerializer.HasChildElement(*&element, "is_series");
  multimediaInfo.IsRecord = objectSerializer.HasChildElement(*&element, "is_record");
  multimediaInfo.IsRepeatRecord = objectSerializer.HasChildElement(*&element, "is_repeat_record");
         
  multimediaInfo.IsCatAction = objectSerializer.HasChildElement(*&element, "cat_action");
  multimediaInfo.IsCatComedy = objectSerializer.HasChildElement(*&element, "cat_comedy");
  multimediaInfo.IsCatDocumentary = objectSerializer.HasChildElement(*&element, "cat_documentary");
  multimediaInfo.IsCatDrama = objectSerializer.HasChildElement(*&element, "cat_drama");
  multimediaInfo.IsCatEducational = objectSerializer.HasChildElement(*&element, "cat_educational");
  multimediaInfo.IsCatHorror = objectSerializer.HasChildElement(*&element, "cat_horror");
  multimediaInfo.IsCatKids = objectSerializer.HasChildElement(*&element, "cat_kids");
  multimediaInfo.IsCatMovie = objectSerializer.HasChildElement(*&element, "cat_movie");
  multimediaInfo.IsCatMusic = objectSerializer.HasChildElement(*&element, "cat_music");
  multimediaInfo.IsCatNews = objectSerializer.HasChildElement(*&element, "cat_news");
  multimediaInfo.IsCatReality = objectSerializer.HasChildElement(*&element, "cat_reality");
  multimediaInfo.IsCatRomance = objectSerializer.HasChildElement(*&element, "cat_romance");
  multimediaInfo.IsCatScifi = objectSerializer.HasChildElement(*&element, "cat_scifi");
  multimediaInfo.IsCatSerial = objectSerializer.HasChildElement(*&element, "cat_serial");
  multimediaInfo.IsCatSoap = objectSerializer.HasChildElement(*&element, "cat_soap");
  multimediaInfo.IsCatSpecial = objectSerializer.HasChildElement(*&element, "cat_special");
  multimediaInfo.IsCatSports = objectSerializer.HasChildElement(*&element, "cat_sports");
  multimediaInfo.IsCatThriller = objectSerializer.HasChildElement(*&element, "cat_thriller");
  multimediaInfo.IsCatAdult = objectSerializer.HasChildElement(*&element, "cat_adult");
}
