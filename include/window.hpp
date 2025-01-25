#ifndef WINDOW_HPP
#define WINDOW_HPP

#include <SFML/Graphics.hpp>
#include <cstdlib>
#include <string>
#include <dirent.h>
#include "camera.hpp"

namespace gfe {
	class Window: public sf::RenderWindow {
	private:
		sf::Texture m_input_buffer;
		sf::Shader m_shader;
		std::string m_shader_path;
		sf::RectangleShape m_output;

		sf::Font m_font;
		sf::Text m_title;

		static int m_map_index;

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

			m_font.loadFromFile("bin/fonts/pixelmix.ttf");
			m_title.setFont(m_font);
			m_title.setString(title);
			m_title.setPosition(sf::Vector2f(10.f, 10.f));
			m_title.setCharacterSize(21);
			m_title.setFillColor(sf::Color(255, 100, 0));
		}
	private:
		void m_update_map() {
			static bool tab_pressed = false;

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Tab)) {
				if (!tab_pressed) {
					tab_pressed = true;

					int count = 0;
					DIR* dir = opendir("bin/maps/");
					if (dir) {
						struct dirent* entry;
						while ((entry = readdir(dir)) != nullptr) {
							if (entry->d_type == DT_REG) {
								++count;
							}
						}
						closedir(dir);
					}

					m_map_index += 1;
					if (m_map_index >= count) {
						m_map_index = 0;
					}
				}
			} else {
				tab_pressed = false;
			}
		}

	public:
		void render(const gfe::Camera& camera) {
#if HOT_RELOAD
			m_update_map();
			m_input_buffer.loadFromFile("bin/maps/map" + std::to_string(m_map_index) + ".jpg");
			m_shader.setUniform("texture", m_input_buffer);
#endif
			clear();

			m_shader.setUniform("camera_angle", camera.get_angle((sf::Vector2f)getSize()));
			m_shader.setUniform("FAR", camera.get_FAR());
			draw(m_output, &m_shader);

			draw(m_title);

			display();
		}
	};
}

#endif
