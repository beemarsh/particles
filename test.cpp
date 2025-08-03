#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Shader.hpp>
#include <SFML/System/Vector2.hpp>
#include <iostream>

int main() {
  sf::VideoMode fullscreen_mode = sf::VideoMode::getFullscreenModes()[0];
  sf::RenderWindow window(fullscreen_mode, "SFML 3 Fullscreen",
                          sf::Style::Default, sf::State::Fullscreen);
  window.setFramerateLimit(60);

  // Create circle shape

  // Load fragment shader
  sf::Shader shader;

  if (!shader.loadFromFile("./assets/shaders/particle.frag",
                           sf::Shader::Type::Fragment)) {
    std::cerr << "Error loading Shader" << '\n';
    return -1;
  }

  float particleRadius = 128.f;
  sf::Color particleColor = sf::Color::White;

  shader.setUniform("radius", particleRadius);
  shader.setUniform("baseColor", sf::Glsl::Vec4(particleColor));

  float posX = (window.getSize().x / 2.0f) - particleRadius;
  float posY = (window.getSize().y / 2.0f) - particleRadius;

  sf::CircleShape canvas;
  canvas.setPosition({200, 200});
  canvas.setRadius(particleRadius);

  shader.setUniform("radius", particleRadius);
  shader.setUniform("baseColor", sf::Glsl::Vec4(particleColor));

  while (window.isOpen()) {
    while (const std::optional event = window.pollEvent()) {
      if (event->is<sf::Event::Closed>() ||
          sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Q)) {
        window.close();
      }
    }

    sf::Vector2f center_world_pos =
        canvas.getPosition() + sf::Vector2f(particleRadius, particleRadius);
    sf::Vector2i center_pixel_pos = window.mapCoordsToPixel(center_world_pos);

    // +++ THE FINAL FIX IS HERE +++
    // Flip the Y-axis to match the shader's coordinate system.
    center_pixel_pos.y = window.getSize().y - center_pixel_pos.y;

    shader.setUniform("center", sf::Vector2f(center_pixel_pos));
    // sf::Vector2f particleCenter =
    //     circle.getPosition() + sf::Vector2f(particleRadius, particleRadius);

    // std::cout << particleCenter.x << ", " << particleCenter.y << '\n';

    // shader.setUniform("center",
    //                   sf::Glsl::Vec2(window.mapCoordsToPixel(particleCenter)));

    // 4. Draw everything.
    window.clear(sf::Color(10, 10, 10));
    window.draw(canvas, &shader);
    window.display();
  }

  return 0;
}
