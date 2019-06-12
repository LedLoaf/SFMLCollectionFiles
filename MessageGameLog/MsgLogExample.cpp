#include <SFML/Graphics.hpp>
#include <iostream>
#include <fstream>
#include <iomanip>
#include "MessageLog.h"

sf::Vector2u WINDOW_SIZE{1400,900};

int main() {

	sf::RenderWindow window{sf::VideoMode{WINDOW_SIZE.x,WINDOW_SIZE.y},"VertexArray"};
	window.setFramerateLimit(120);

	MessageLog log(9, 12, sf::Vector2f{100,300}, 255, 125);

	sf::Vector2f offset{0,0};
	while (window.isOpen()) {
		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed || event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)
				window.close();
			if(event.type == sf::Event::KeyPressed) {
				switch(event.key.code) {
					case sf::Keyboard::Num1: log.addText("Attacking", sf::Color::Green,sf::Text::Bold, 1.f); break;
					case sf::Keyboard::Num2: log.addText("Defending", sf::Color::Red,sf::Text::Bold,1.f); break;
					case sf::Keyboard::Num3: log.addText("Evading", sf::Color::Magenta,sf::Text::Style(sf::Text::Bold|sf::Text::Italic),1.f); break;
					case sf::Keyboard::G:
						{
							auto pos = log.getPos();
							std::cout << pos.x << ", " << pos.y << "\n";

						}; break;
					case sf::Keyboard::Num6: log.setOffset(--offset.x,offset.y); break;
					case sf::Keyboard::Num7: log.setOffset(++offset.x, offset.y); break;
					case sf::Keyboard::Num8: log.setOffset(offset.x, --offset.y); break;
					case sf::Keyboard::Num9: log.setOffset(offset.x, ++offset.y); break;
					case sf::Keyboard::Num0: log.resetOffset(); break;
				}
			}
		}

		log.update();

		window.clear();

		log.draw(window);

		window.display();

	}


	return 0;
}