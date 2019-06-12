#define _CRT_SECURE_NO_WARNINGS
#include "MessageLog.h"
#include <sstream>
#include <chrono>
#include <ctime>
#include <iostream>

// get current date/time, format is YYYY-MM-DD.HH:mm:ss
std::string currentDateTime() {
	time_t     now = time(nullptr);
	struct tm  tstruct;
	char       buf[80];
	tstruct = *localtime(&now);
	// Visit http://en.cppreference.com/w/cpp/chrono/c/strftime for more information about date/time format
	strftime(buf, sizeof(buf), "%r\t%D", &tstruct);

	return buf;
}

MessageLog::MessageLog(const int visible, 
					   const int charSize, 
					   const sf::Vector2f pos, 
					   const float width, 
					   const float height) 
{
	m_font.loadFromFile("arial.ttf");

	m_backdrop.setSize(sf::Vector2f{width,height});
	m_backdrop.setFillColor(sf::Color{90,90,90,90});
	m_backdrop.setPosition(pos);
	m_backdropPos = pos;

	m_visibleLines = visible;
	m_charSize = charSize;
	m_offset = sf::Vector2f{0.f, static_cast<float>(charSize)};

	if(m_bClearSave)
		m_file.open("Log.txt", std::ios::out | std::ios::trunc);
	else
		m_file.open("Log.txt", std::ios::out | std::ios::app | std::ios::ate);

	m_saveFile = m_bSave;
}

MessageLog::~MessageLog() {

	m_file << currentDateTime() << "\n";
	m_file.close();
	for(auto it : m_log) {
		delete it;
		it = nullptr;
	}
}

void MessageLog::addText(const std::string msg, 
						 const sf::Color fillColor, 
						 const sf::Text::Style style, 
						 const float thickness, 
						 const sf::Color outlineColor) 
{
	auto txt = new sf::Text;

	txt->setFont(m_font);
	txt->setString(msg);
	txt->setFillColor(fillColor);
	txt->setCharacterSize(m_charSize);
	txt->setOutlineColor(outlineColor);
	txt->setOutlineThickness(thickness);
	txt->setStyle(style);

	m_log.push_back(txt);
}

void MessageLog::update() {
	m_displayLog.clear();

	const auto logSize = m_log.size();
	
	if (logSize > m_visibleLines) {
		if (m_saveFile)
			saveLog();
		m_log.erase(m_log.begin());
	}

	for (auto it : m_log) {
		m_displayLog.push_back(*it);
	}

	std::reverse(m_displayLog.begin(), m_displayLog.end());
}

void MessageLog::draw(sf::RenderWindow& wind) {

	wind.draw(m_backdrop);
	auto visLines = m_visibleLines;
	for(auto it : m_displayLog) {
		it.setPosition(m_backdropPos.x - m_offset.x, m_backdropPos.y + (it.getCharacterSize() * visLines) - m_offset.y);
		wind.draw(it);
		--visLines;
	}
}

void MessageLog::saveLog()  {
	if (m_file.is_open()) {
		const auto sfText = m_log.front();
		const auto txt = sfText->getString();
		std::stringstream ss(static_cast<std::string>(txt));
		m_file << ss.str() << "\n";
	}
}

void MessageLog::setOffset(const sf::Vector2f offset) { m_offset = offset; }
void MessageLog::setOffset(const float x, const float y) { m_offset = sf::Vector2f{x,y}; }

void MessageLog::resetOffset() { m_offset = sf::Vector2f{0.f, static_cast<float>(m_charSize)}; }

sf::Vector2f MessageLog::getPos() const {
	if(m_displayLog.size() > 0) {
		auto p =  m_displayLog[0].getPosition();
		p.x += m_backdropPos.x - m_offset.x;
		p.y += m_backdropPos.y + (m_charSize * m_visibleLines) - m_offset.y;
		return p;
	}

	return sf::Vector2f{-1,-1};
}

