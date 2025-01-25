#ifndef WINDOW_HPP
#define WINDOW_HPP

#include <SFML/Graphics.hpp>
#include <cstdlib>
#include "camera.hpp"

namespace gfe {
	class Window: public sf::RenderWindow {
	private:
		sf::Texture m_input_buffer;
		sf::Shader m_transform;
		sf::RectangleShape m_output;

	public:
		Window() {
			const int width = 1280;
			const int height = 720;
			create(sf::VideoMode(width, height), "Google flat earth", sf::Style::None);

			m_input_buffer.loadFromFile("bin/maps/map1.jpg");
			m_output.setSize(sf::Vector2f(width, height));

			sf::Shader& shader = m_transform;
			shader.loadFromFile("shaders/compiled_shader.glsl", sf::Shader::Fragment);
			shader.setUniform("resolution", sf::Vector2f(width, height));
			shader.setUniform("texture", m_input_buffer);
		}

		void render(const gfe::Camera& camera) {
			clear();

			m_transform.setUniform("camera_angle", camera.get_angle((sf::Vector2f)getSize()));
			draw(m_output, &m_transform);

			display();
		}
	};
}

#endif
