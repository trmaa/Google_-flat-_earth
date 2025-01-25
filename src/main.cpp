#include <SFML/Graphics.hpp>
#include "window.hpp"
#include "camera.hpp"

gfe::Camera camera;
gfe::Window window;

int main() {
	sf::Clock clock;
	sf::Time elapsed;
	float delta_time;
	while (window.isOpen()) {
		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed) {
				window.close();
			}
		}
		elapsed = clock.restart();
		delta_time = elapsed.asSeconds();

		camera.move(delta_time);
		window.render(camera);
	}
}
