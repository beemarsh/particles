#include "render/Renderer.hpp"
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Shader.hpp>
#include <iostream>

int main() {

  // Create a fullscreen window
  sf::VideoMode fullscreen_mode = sf::VideoMode::getFullscreenModes()[0];
  sf::RenderWindow window(fullscreen_mode, "SFML 3 Fullscreen",
                          sf::Style::Default, sf::State::Fullscreen);

  const uint32_t frame_rate = 60;
  window.setFramerateLimit(frame_rate);

  Renderer renderer(window);

  sf::Shader shader;
  if (!shader.loadFromFile("assets/shaders/particle.frag",
                           sf::Shader::Type::Fragment)) {
    std::cerr << "Error loading Shader" << '\n';

    return -1;
  }

  Particles particles = Particles(window, shader, 80.f);
  particles.generate(1000);

  sf::Clock clock;

  while (window.isOpen()) {
    float dt = clock.restart().asSeconds();

    while (const std::optional event = window.pollEvent()) {
      if (event->is<sf::Event::Closed>() ||
          sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Q)) {
        window.close();
      }
    }

    renderer.render(particles, dt);

    window.display();
  }
}
