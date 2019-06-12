#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <string>
#include <fstream>

std::string currentDateTime();

using MessageContainer = std::vector<std::string>;

class MessageLog {
public:
	MessageLog(int visible, int charSize, sf::Vector2f pos, float width, float height);
	~MessageLog();
	void addText(std::string msg, 
				 sf::Color fillColor = sf::Color::White, 
				 sf::Text::Style style = sf::Text::Style::Regular,
				 float thickness = 0.f,
				 sf::Color outlineColor = sf::Color::Black);

	void update();
	void draw(sf::RenderWindow& wind);

	void saveLog();

	void setOffset(sf::Vector2f offset);
	void setOffset(float x, float y);
	void resetOffset();

	sf::Vector2f getPos() const;
private:
	std::vector<sf::Text*> m_log;
	std::vector<sf::Text> m_displayLog;
	sf::Font m_font;
	sf::RectangleShape m_backdrop;
private:
	int m_visibleLines;
	int m_charSize;
	sf::Vector2f m_offset;
	sf::Vector2f m_backdropPos;
private:
	std::ofstream m_file;
	bool m_saveFile;
	bool m_bSave = true;
	bool m_bClearSave = true;
};
