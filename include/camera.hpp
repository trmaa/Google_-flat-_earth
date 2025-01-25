#ifndef CAMERA_H
#define CAMERA_H

#include <SFML/Graphics.hpp>
#include <glm/glm.hpp>

namespace gfe {
	class Camera {
	private:
		glm::vec2 m_position;
		float m_speed;

	public:
		sf::Vector2f get_angle(sf::Vector2f viewport) const {
			glm::vec2 uv = m_position/glm::vec2(viewport.x, viewport.y);
			uv *= 2.f * 3.14159f;
			return sf::Vector2f(uv.x, uv.y);
		}

		Camera(): m_position(0.f), m_speed(-100.f) {}

	public:
		void move(const float& dt) {
			float fixed_speed = m_speed * dt;

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
				m_position.y += fixed_speed;
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
				m_position.y -= fixed_speed;
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
				m_position.x -= fixed_speed;
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
				m_position.x += fixed_speed;
			}

		}
	};
}

#endif
