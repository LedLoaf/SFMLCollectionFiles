#pragma once
#include <string>
#include "Globals.h"

// FUNCTIONS
void drawString(std::string text, sf::Vector2f position, unsigned int size, sf::Color color = sf::Color::White, sf::Text::Style style = sf::Text::Style::Regular);
	// Clear the old data.
	sstream.str(std::string());
	sstream.clear();

	sstream << text;
	std::string str = sstream.str();

	sfText.setString(str);
	sfText.setFont(sfFont);
	sfText.setCharacterSize(size);
	sfText.setStyle(style);
	sfText.setFillColor(color);
	sfText.setPosition(position.x - (sfText.getLocalBounds().width / 2.f), position.y - (sfText.getLocalBounds().height / 2.f));

	window.draw(sfText);
};

bool checkCollision(sf::IntRect& a, sf::IntRect& b) {
	// the sides of the rectangle
	int leftA, leftB;
	int rightA, rightB;
	int topA, topB;
	int bottomA, bottomB;
	// calculate the sides of rect a
	leftA = a.left;
	rightA = a.left + a.width;
	topA = a.top;
	bottomA = a.top + a.height;
	// calcuate the sides of rect b
	leftB = b.left;
	rightB = b.left + b.width;
	topB = b.top;
	bottomB = b.top + b.height;

	// if any of the side from A are outside of B
	if (bottomA <= topB) { return false; }
	if (topA >= bottomB) { return false; }
	if (rightA <= leftB) { return false; }
	if (leftA >= rightB) { return false; }

	// if none of the sides from A are outside B
	return true;

}