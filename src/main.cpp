#define HOT_RELOAD 1

#include <SFML/Graphics.hpp>
#include <cstdlib>
#include "window.hpp"
#include "camera.hpp"

int gfe::Window::m_map_index = 1;

int main() {
    gfe::Camera camera;

    gfe::Window spherical_map_window("shaders/ray_cast.glsl", sf::Vector2i(0.f, 720.f/1.5f), "3D view");
    gfe::Window flat_map_window("shaders/transform.glsl", sf::Vector2i(0.f, 0.f), "Flat view");

    sf::Clock clock;
    sf::Time elapsed;
    float delta_time;
    while (flat_map_window.isOpen()) {
	sf::Event event;
	while (flat_map_window.pollEvent(event)) {
	    if (event.type == sf::Event::Closed) {
		flat_map_window.close();
		spherical_map_window.close();
	    }
	}
	elapsed = clock.restart();
	delta_time = elapsed.asSeconds();

	camera.move(delta_time);
	flat_map_window.render(camera, delta_time);
	spherical_map_window.render(camera, delta_time);
    }
}
