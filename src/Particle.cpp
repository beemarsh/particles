#include "render/Particle.hpp"
#include <SFML/Graphics.hpp>
#include <cmath>
#include <iostream>

bool Particle::direction_change(float a, float b) {
  if (a > 0 && b > 0)
    return false;

  if (a < 0 && b < 0)
    return false;

  if (a == 0 && b == 0)
    return false;

  return true;
}

Particle::Particle(sf::RenderTarget &window_, ParticleID _id)
    : id(_id), radius(1.f), color(sf::Color::Blue), shape(sf::CircleShape(1.f)),
      velocity({0.f, 0.f}), acceleration({0.f, 500.f}), window(window_),
      bounce_height(-1.f), scale({10.0f, 10.0f}) {

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

  auto new_velocity = velocity + acceleration * dt;
  auto new_position = position + velocity * dt;

  if (direction_change(new_velocity.y, velocity.y)) {
    bounce_height = (window_size.y - position.y - scale.y * 2);
  }

  if (bounce_height <= 0.1f) {
    return;
  } else {
    std::cout << bounce_height << '\n';

    if (new_position.y >= (window_size.y - scale.y * 2)) {
      velocity.y = -0.8 * std::fabs(velocity.y);
      acceleration.y = std::fabs(acceleration.y);
    }

    if (new_position.y <= (0 + scale.y * 2)) {
      velocity.y = std::fabs(velocity.y);
      acceleration.y = std::fabs(acceleration.y);
    }

    if (new_position.x <= (0 + scale.x * 2)) {
      velocity.x = std::fabs(velocity.x);
      acceleration.x = std::fabs(velocity.x);
    }

    if (new_position.x >= (window_size.x - scale.x * 2)) {
      velocity.x = -1 * std::fabs(velocity.x);
      acceleration.x = -1 * std::fabs(velocity.x);
    }
    velocity += acceleration * dt;
    position += velocity * dt;
  }
}

void Particle::set_x(const int &_x) { position.x = _x; }

void Particle::set_y(const int &_y) { position.y = _y; }
