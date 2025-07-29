#include "render/renderer.hpp"
#include <SFML/Graphics.hpp>

int main() {

  // Create a fullscreen window
  sf::VideoMode fullscreen_mode = sf::VideoMode::getFullscreenModes()[0];
  sf::RenderWindow window(fullscreen_mode, "SFML 3 Fullscreen",
                          sf::Style::Default, sf::State::Fullscreen);

  const uint32_t frame_rate = 60;
  window.setFramerateLimit(frame_rate);

  Renderer renderer(window);

  while (window.isOpen()) {

    while (const std::optional event = window.pollEvent()) {
      if (event->is<sf::Event::Closed>() ||
          sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Q)) {
        window.close();
      }
    }


    renderer.render();

    window.display();
  }
}
