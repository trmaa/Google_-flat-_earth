#include <SFML/Graphics.hpp>

int main() {
	sf::RenderWindow window;
	window.create(sf::VideoMode(800, 600), "Flat Earth", sf::Style::None);

	sf::Text text;
	text.setString("Hello world");
	sf::Font font;
	font.loadFromFile("bin/fonts/pixelmix.ttf");
	text.setFont(font);
	text.setPosition(100, 100);

	while (window.isOpen()) {
		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed) {
				window.close();
			}
		}

		window.clear();
		window.draw(text);
		window.display();
	}
}
