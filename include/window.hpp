#ifndef WINDOW_HPP
#define WINDOW_HPP

#include <SFML/Graphics.hpp>
#include <cstdlib>
#include <string>
#include "camera.hpp"

namespace gfe {
	class Window: public sf::RenderWindow {
	private:
		sf::Texture m_input_buffer;
		sf::Shader m_shader;
		std::string m_shader_path;
		sf::RectangleShape m_output;

		sf::Font m_font;  // Store font as a member variable
		sf::Text m_title;

	public:
		Window(const std::string& path, sf::Vector2i position, const std::string& title = "")
			: m_shader_path(path) {
			const int width = 1280 / 1.5f;
			const int height = 720 / 1.5f;
			create(sf::VideoMode(width, height), "Google flat earth", sf::Style::Close);
			setPosition(position);

			m_input_buffer.loadFromFile("bin/maps/map1.jpg");
			m_output.setSize(sf::Vector2f(width, height));

			m_shader.loadFromFile(m_shader_path, sf::Shader::Fragment);
			m_shader.setUniform("resolution", sf::Vector2f(width, height));
			m_shader.setUniform("texture", m_input_buffer);

			m_font.loadFromFile("bin/fonts/pixelmix.ttf");  // Font loading moved here
			m_title.setFont(m_font);
			m_title.setString(title);
			m_title.setPosition(sf::Vector2f(10.f, 10.f));
			m_title.setCharacterSize(21);
			m_title.setFillColor(sf::Color(255, 100, 0));
		}

		void render(const gfe::Camera& camera) {
			clear();

			m_shader.setUniform("camera_angle", camera.get_angle((sf::Vector2f)getSize()));
			draw(m_output, &m_shader);

			draw(m_title);

			display();
		}
	};
}

#endif
