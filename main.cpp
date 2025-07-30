#include "render/renderer.hpp"
#include <SFML/Graphics.hpp>
#include <iostream>

int main() {

  // Create a fullscreen window
  sf::VideoMode fullscreen_mode = sf::VideoMode::getFullscreenModes()[0];
  sf::RenderWindow window(fullscreen_mode, "SFML 3 Fullscreen",
                          sf::Style::Default, sf::State::Fullscreen);

  const uint32_t frame_rate = 60;
  window.setFramerateLimit(frame_rate);

  Renderer renderer(window);

  Particle circle(window);

  sf::Clock clock;

  while (window.isOpen()) {
    float dt = clock.restart().asSeconds();

    while (const std::optional event = window.pollEvent()) {
      if (event->is<sf::Event::Closed>() ||
          sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Q)) {
        window.close();
      }
    }

    renderer.render(circle, dt);

    window.display();
  }
}
