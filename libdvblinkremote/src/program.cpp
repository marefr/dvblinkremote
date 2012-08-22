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

Program::Program()
{
  m_id = "";
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

Program::Program(const std::string& id, const std::string& title, const long startTime, const long duration)
  : m_id(id), 
    m_title(title), 
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

Program::Program(Program& program) 
  : m_id(program.GetID()), m_title(program.GetTitle()), m_startTime(program.GetStartTime()), m_duration(program.GetDuration())
{
  ShortDescription = program.ShortDescription;
  SubTitle = program.SubTitle;
  Language = program.Language;
  Actors = program.Actors;
  Directors = program.Directors;
  Writers = program.Writers;
  Producers = program.Producers;
  Guests = program.Guests;
  Keywords = program.Keywords;
  Image = program.Image;
  Year = program.Year;
  EpisodeNumber = program.EpisodeNumber;
  SeasonNumber = program.SeasonNumber;
  Rating = program.Rating;
  MaximumRating = program.MaximumRating;
  IsHdtv = program.IsHdtv;
  IsPremiere = program.IsPremiere;
  IsRepeat = program.IsRepeat;
  IsSeries = program.IsSeries;
  IsRecord = program.IsRecord;
  IsRepeatRecord = program.IsRepeatRecord;
  IsCatAction = program.IsCatAction;
  IsCatComedy = program.IsCatComedy;
  IsCatDocumentary = program.IsCatDocumentary;
  IsCatDrama = program.IsCatDrama;
  IsCatEducational = program.IsCatEducational;
  IsCatHorror = program.IsCatHorror;
  IsCatKids = program.IsCatKids;
  IsCatMovie = program.IsCatMovie;
  IsCatMusic = program.IsCatMusic;
  IsCatNews = program.IsCatNews;
  IsCatReality = program.IsCatReality;
  IsCatRomance = program.IsCatRomance;
  IsCatScifi = program.IsCatScifi;
  IsCatSerial = program.IsCatSerial;
  IsCatSoap = program.IsCatSoap;
  IsCatSpecial = program.IsCatSpecial;
  IsCatSports = program.IsCatSports;
  IsCatThriller = program.IsCatThriller;
  IsCatAdult = program.IsCatAdult;
}

Program::~Program()
{

}

std::string& Program::GetID() 
{ 
  return m_id; 
}

void Program::SetID(const std::string& id) 
{ 
  m_id = id; 
}

std::string& Program::GetTitle() 
{ 
  return m_title; 
}

void Program::SetTitle(const std::string& title) 
{ 
  m_title = title; 
}

long Program::GetStartTime() 
{ 
  return m_startTime; 
}

void Program::SetStartTime(const long startTime) 
{ 
  m_startTime = startTime; 
}

long Program::GetDuration() 
{ 
  return m_duration; 
}

void Program::SetDuration(const long duration) 
{ 
  m_duration = duration; 
}

void ProgramSerializer::Deserialize(XmlObjectSerializer<Response>& objectSerializer, const tinyxml2::XMLElement& element, dvblinkremote::Program& program)
{
  program.SetID(Util::GetXmlFirstChildElementText(&element, "program_id"));
  program.SetTitle(Util::GetXmlFirstChildElementText(&element, "name"));
  program.SetStartTime(Util::GetXmlFirstChildElementTextAsLong(&element, "start_time"));
  program.SetDuration(Util::GetXmlFirstChildElementTextAsLong(&element, "duration"));

  program.ShortDescription = Util::GetXmlFirstChildElementText(&element, "short_desc");
  program.SubTitle = Util::GetXmlFirstChildElementText(&element, "subname");
  program.Language = Util::GetXmlFirstChildElementText(&element, "language");
  program.Actors = Util::GetXmlFirstChildElementText(&element, "actors");
  program.Directors = Util::GetXmlFirstChildElementText(&element, "directors");
  program.Writers = Util::GetXmlFirstChildElementText(&element, "writers");
  program.Producers = Util::GetXmlFirstChildElementText(&element, "producers");
  program.Guests = Util::GetXmlFirstChildElementText(&element, "guests");
  program.Keywords = Util::GetXmlFirstChildElementText(&element, "categories");
  program.Image = Util::GetXmlFirstChildElementText(&element, "image");
         
  program.Year = Util::GetXmlFirstChildElementTextAsLong(&element, "year");
  program.EpisodeNumber = Util::GetXmlFirstChildElementTextAsLong(&element, "episode_num");
  program.SeasonNumber = Util::GetXmlFirstChildElementTextAsLong(&element, "season_num");
  program.Rating = Util::GetXmlFirstChildElementTextAsLong(&element, "stars_num");
  program.MaximumRating = Util::GetXmlFirstChildElementTextAsLong(&element, "starsmax_num");
         
  program.IsHdtv = objectSerializer.HasChildElement(*&element, "hdtv");
  program.IsPremiere = objectSerializer.HasChildElement(*&element, "premiere");
  program.IsRepeat = objectSerializer.HasChildElement(*&element, "repeat");
  program.IsSeries = objectSerializer.HasChildElement(*&element, "is_series");
  program.IsRecord = objectSerializer.HasChildElement(*&element, "is_record");
  program.IsRepeatRecord = objectSerializer.HasChildElement(*&element, "is_repeat_record");
         
  program.IsCatAction = objectSerializer.HasChildElement(*&element, "cat_action");
  program.IsCatComedy = objectSerializer.HasChildElement(*&element, "cat_comedy");
  program.IsCatDocumentary = objectSerializer.HasChildElement(*&element, "cat_documentary");
  program.IsCatDrama = objectSerializer.HasChildElement(*&element, "cat_drama");
  program.IsCatEducational = objectSerializer.HasChildElement(*&element, "cat_educational");
  program.IsCatHorror = objectSerializer.HasChildElement(*&element, "cat_horror");
  program.IsCatKids = objectSerializer.HasChildElement(*&element, "cat_kids");
  program.IsCatMovie = objectSerializer.HasChildElement(*&element, "cat_movie");
  program.IsCatMusic = objectSerializer.HasChildElement(*&element, "cat_music");
  program.IsCatNews = objectSerializer.HasChildElement(*&element, "cat_news");
  program.IsCatReality = objectSerializer.HasChildElement(*&element, "cat_reality");
  program.IsCatRomance = objectSerializer.HasChildElement(*&element, "cat_romance");
  program.IsCatScifi = objectSerializer.HasChildElement(*&element, "cat_scifi");
  program.IsCatSerial = objectSerializer.HasChildElement(*&element, "cat_serial");
  program.IsCatSoap = objectSerializer.HasChildElement(*&element, "cat_soap");
  program.IsCatSpecial = objectSerializer.HasChildElement(*&element, "cat_special");
  program.IsCatSports = objectSerializer.HasChildElement(*&element, "cat_sports");
  program.IsCatThriller = objectSerializer.HasChildElement(*&element, "cat_thriller");
  program.IsCatAdult = objectSerializer.HasChildElement(*&element, "cat_adult");
}
