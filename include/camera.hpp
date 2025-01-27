#ifndef CAMERA_H
#define CAMERA_H

#include <SFML/Graphics.hpp>
#include <cmath>
#include <glm/glm.hpp>

namespace gfe {
	class Camera {
	private:
		glm::vec2 m_position;
		float m_speed;
		float m_FAR = 1.f;

	public:
		sf::Vector2f get_angle(sf::Vector2f viewport) const {
			glm::vec2 uv = m_position/glm::vec2(viewport.x, viewport.y);
			uv *= 2.f * 3.14159f;
			return sf::Vector2f(uv.x, uv.y);
		}

		const float& get_FAR() const { return m_FAR; }

		Camera(): m_position(0.f), m_speed(-100.f) {}

	public:
		void move(const float& dt) {
			float fixed_speed = m_speed * dt;

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
				m_position.y += fixed_speed/m_FAR;
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
				m_position.y -= fixed_speed/m_FAR;
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
				m_position.x -= fixed_speed/m_FAR;
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
				m_position.x += fixed_speed/m_FAR;
			}

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
				m_FAR -= 0.01f;
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift)) {
				m_FAR += 0.01f;
			}

			if (m_FAR < 1.f) {
				m_FAR = 1.f;
			}
			if (m_FAR > 10.f) {
				m_FAR = 10.f;
			}
		}
	};
}

#endif
