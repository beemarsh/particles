#include <SFML/Graphics.hpp>
#include <SFML/Window/WindowBase.hpp>
#include <iostream>
class Renderer {
private:
  sf::RenderTarget &target;

public:
  Renderer(sf::RenderTarget &target_) : target{target_} {}

  void render() {
    target.clear(sf::Color::Black);

    const auto &screen_size = target.getSize();
    const float mid_x = static_cast<float>(screen_size.x) / 2;
    const float mid_y = static_cast<float>(screen_size.y) / 2;

    sf::CircleShape circle(1.f);
    circle.setPointCount(32);
    circle.setPosition({mid_x, mid_y});

    circle.setScale({10.0f, 10.0f});
    circle.setFillColor(sf::Color::Blue);
    target.draw(circle);
  }
};
