#include "render/Particle.hpp"
#include <SFML/Graphics.hpp>

Particle::Particle(sf::RenderTarget &window_, ParticleID _id)
    : id(_id), radius(1.f), color(sf::Color::Blue), shape(sf::CircleShape(1.f)),
      velocity({200.f, 200.f}), acceleration({200.f, 100.f}), window(window_),
      scale({10.0f, 10.0f}) {

  // Set Position to the middle of the screen
  const auto &screen_size = window.getSize();
  window_size = {screen_size.x, screen_size.y};

  float mid_x = window_size.x / 2.f;
  float mid_y = window_size.y / 2.f;
  position = {mid_x, mid_y};
}

void Particle::render() {
  shape.setPointCount(32);
  shape.setScale(scale);
  shape.setRadius(radius);
  shape.setFillColor(color);
  shape.setPosition(position);
  window.draw(shape);
}

void Particle::fall(float &dt) {

  if (position.y >= (window_size.y - scale.y * 2)) {
    velocity.y = -200.f;
    acceleration.y = -100.f;
  }

  if (position.y <= (0 + scale.y * 2)) {
    velocity.y = 200.f;
    acceleration.y = 100.f;
  }

  if (position.x <= (0 + scale.x * 2)) {
    velocity.x = 200.f;
    acceleration.x = 200.f;
  }

  if (position.x >= (window_size.x - scale.x * 2)) {
    velocity.x = -200.f;
    acceleration.x = -200.f;
  }
  velocity += this->acceleration * dt;
  position += this->velocity * dt;
}

void Particle::set_x(const int &_x) { position.x = _x; }

void Particle::set_y(const int &_y) {
  position.y = _y;
}

;
