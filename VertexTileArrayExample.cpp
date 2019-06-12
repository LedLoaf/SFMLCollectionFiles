
#include <SFML/Graphics.hpp>
#include <iostream>

unsigned int WindowWidth = 1400;
unsigned int WindowHeight = 900;

const sf::Vector2i tileSize{32,32};
const int Scale = 128;

int main() {
	
	sf::RenderWindow window{sf::VideoMode{WindowWidth,WindowHeight},"VertexArray"};
	window.setFramerateLimit(120);

	sf::Texture m_tileset;
	// load the tileset texture
	if (!m_tileset.loadFromFile("data/tileset.png")) {
		std::cout << "No Tileset\n";
	}

	sf::VertexArray m_vertices;

	const int tiles[] = {
		1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
		1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
		1,0,0,2,0,2,3,3,3,3,3,3,3,3,2,0,2,0,0,1,
		1,0,0,0,0,2,3,3,0,0,0,0,3,3,0,0,0,0,0,1,
		1,0,0,0,0,0,3,3,0,2,2,0,3,3,0,0,2,0,0,1,
		1,0,0,0,0,0,0,3,0,0,0,0,3,0,2,0,0,0,0,1,
		1,0,0,0,0,0,0,3,3,3,0,3,3,0,0,0,0,0,0,1,
		1,0,0,0,2,0,0,2,0,2,0,2,0,0,0,2,0,0,0,1,
		1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
		1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
	};

	// resize the vertex array to fit the level size
	m_vertices.setPrimitiveType(sf::Quads);
	m_vertices.resize(20 * 10 * 4);

	sf::Vertex* quad = &m_vertices[(1 * 32) * 4];
	sf::View mainView{sf::FloatRect{0.f,0.f,32.f*WindowWidth,32.f*WindowHeight}};
	//mainView.zoom(WindowWidth/128);

	while(window.isOpen()) {
		sf::Event event;
		while(window.pollEvent(event)) {
			if (event.type == sf::Event::Closed || event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)
				window.close();
		}

		if(sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
			mainView.move(0, -20);
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
			mainView.move(0, 20);
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
			mainView.move(-20, 0);
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
			mainView.move(20, 0);
		}



		window.clear();
		window.setView(mainView);
		for(auto i = 0; i < 20; i++) {
			for(auto j = 0; j < 10; j++) {

				int tileNum = tiles[i + j * 20];

				int tu = tileNum % (m_tileset.getSize().x / tileSize.x);
				int tv = tileNum / (m_tileset.getSize().x / tileSize.x);

					// define it as a rectangle, located at (10, 10) and with size 100x100
				quad[0].position = sf::Vector2f(i * tileSize.x * Scale, j * tileSize.y * Scale);
				quad[1].position = sf::Vector2f((i + 1) * tileSize.x * Scale, j * tileSize.y * Scale);
				quad[2].position = sf::Vector2f((i + 1) * tileSize.x * Scale, (j + 1) * tileSize.y * Scale);
				quad[3].position = sf::Vector2f(i* tileSize.x * Scale, (j + 1)*tileSize.y * Scale);

				// define its texture area to be a 25x50 rectangle starting at (0, 0)
				quad[0].texCoords = sf::Vector2f(tu * tileSize.x,tv*tileSize.y);
				quad[1].texCoords = sf::Vector2f((tu + 1) * tileSize.x, tv * tileSize.y);
				quad[2].texCoords = sf::Vector2f((tu+1) * tileSize.x, (tv+1) * tileSize.y);
				quad[3].texCoords = sf::Vector2f(tu * tileSize.x, (tv + 1) * tileSize.y);
				window.draw(m_vertices, &m_tileset);
			}
		}

		window.display();

	}


	return 0;
}
