#pragma once
#include <SFML/Graphics.hpp>

class ParticleSystem : public sf::Drawable, public sf::Transformable {
public:

	ParticleSystem(unsigned int count) : m_particles{count},m_vertices{sf::Points, count}, m_lifeTime{sf::seconds(3)},m_emitter{0,0} {
		
	}

	void setEmitter(sf::Vector2f position) {
		m_emitter = position;
	}

	void update(sf::Time elapsed) {
		for(std::size_t i = 0; i < m_particles.size(); ++i) {
			// update the particle lifetime
			Particle& p = m_particles[i];
			p.lifetime -= elapsed;
			
			sf::Uint8 r = std::rand() % 255;
			sf::Uint8 g = std::rand() % 255;
			sf::Uint8 b = std::rand() % 255;
			p.color = sf::Color{r,g,b};
			// if the particle is dead, respawn it
			if (p.lifetime <= sf::Time::Zero)
				resetParticle(i);
			// update the position of the corresponding vertex
			m_vertices[i].position += p.velocity * elapsed.asSeconds();
			
			// update the alpha (transparency) of the particle according to its lifetime
			float ratio = p.lifetime.asSeconds() / m_lifeTime.asSeconds();
			m_vertices[i].color = p.color;
			m_vertices[i].color.a = static_cast<sf::Uint8>(255);
		}
	}

private:
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const {
		// apply the transform
		states.transform *= getTransform();
		// our particles don't use a texture
		states.texture = nullptr;
		// draw the vertex array
		target.draw(m_vertices, states);
	}

private:
	struct Particle {
		sf::Vector2f velocity;
		sf::Time lifetime;
		sf::Color color;
	};

	void resetParticle(std::size_t index) {
		// give a random velocity and lifetime to the particle
		float angle = (std::rand() % 360) * 3.14f / 180.f;
		float speed = (std::rand() % 50) + 50.f;
		m_particles[index].velocity = sf::Vector2f(std::cos(angle) * speed, std::sin(angle) * speed);
		m_particles[index].lifetime = sf::milliseconds((std::rand() % 2000) + 1000);
		// reset the position of the corresponding vertex
		m_vertices[index].position = m_emitter;
	}

	std::vector<Particle> m_particles;
	sf::VertexArray m_vertices;
	sf::Time m_lifeTime;
	sf::Vector2f m_emitter;
};
