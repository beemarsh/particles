#include <SFML/Graphics.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/System/Vector2.hpp>

struct Particle {
  sf::Vector2f position;
  sf::Vector2f velocity;
  sf::Vector2f acceleration;
  sf::Color color;
  sf::CircleShape shape;
  int32_t radius;
  sf::RenderTarget &window;

  Particle(sf::RenderTarget &window_)
      : radius(1.f), color(sf::Color::Blue), shape(sf::CircleShape(1.f)),
        velocity({0.f, 0.f}), acceleration({0.f, 500.f}), window(window_) {
    // Set Position to the middle of the screen
    const auto &screen_size = window.getSize();
    const float mid_x = static_cast<float>(screen_size.x) / 2;
    const float mid_y = static_cast<float>(screen_size.y) / 2;
    shape.setOrigin(position);
    position = {mid_x, mid_y};
  }

  void render() {
    shape.setPointCount(32);
    shape.setScale({10.0f, 10.0f});
    shape.setRadius(radius);
    shape.setFillColor(color);
    shape.setPosition(position);
    window.draw(shape);
  }

  void set_x(const int &_x) { position.x = _x; }

  void set_y(const int &_y) { position.y = _y; }
};
