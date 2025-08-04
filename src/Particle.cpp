#include "render/Particle.hpp"
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/BlendMode.hpp>
#include <SFML/Graphics/PrimitiveType.hpp>
#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/Shader.hpp>
#include <cmath>
#include <iostream>
#include <string>

bool Particle::direction_change(float a, float b) {
  if (a > 0 && b > 0)
    return false;

  if (a < 0 && b < 0)
    return false;

  if (a == 0 && b == 0)
    return false;
  return true;
}
Particle::Particle(sf::RenderTarget &window_, ParticleID _id, float _radius)
    : id(_id), radius(_radius), smoothing_radius(_radius), mass(1.f),
      velocity({0.f, 0.f}), acceleration({0.f, 500.f}), point_count{32},
      window(window_), bounce_height(-1.f) {

  // Set Position to the middle of the screen
  const auto &screen_size = window.getSize();
  window_size = {screen_size.x, screen_size.y};

  // float mid_x = window_size.x / 2.f;
  // float mid_y = window_size.y / 2.f;
  // position = {mid_x, mid_y};

  // sf::Color bluish(30, 144, 255);
  sf::Color bluish(0x3989e8);

  color = bluish;

  shape = sf::CircleShape(smoothing_radius);
  shape.setPointCount(point_count);
  shape.setFillColor(bluish);
}

void Particle::render(sf::Shader &shader) {
  shape.setPointCount(point_count);
  shape.setRadius(smoothing_radius);
  shape.setFillColor(color);

  shader.setUniform(
      "radius",
      smoothing_radius); // Or whatever your radius variable is called

  // Set the color uniform
  shader.setUniform("baseColor", sf::Glsl::Vec4(color));

  sf::Vector2f center_world_pos =
      position + sf::Vector2f(smoothing_radius, smoothing_radius);
  sf::Vector2i center_pixel_pos = window.mapCoordsToPixel(center_world_pos);

  // +++ THE FINAL FIX IS HERE +++
  // Flip the Y-axis to match the shader's coordinate system.
  center_pixel_pos.y = window.getSize().y - center_pixel_pos.y;

  shader.setUniform("center", sf::Vector2f(center_pixel_pos));
  shape.setPosition(position);

  sf::RenderStates states;
  states.shader = &shader;
  states.blendMode = sf::BlendAdd;

  window.draw(shape, states);
}

void Particle::fall(float &dt) {

  auto new_velocity = velocity + acceleration * dt;
  auto new_position = position + velocity * dt;

  if (direction_change(new_velocity.y, velocity.y)) {
    bounce_height = (window_size.y - position.y - smoothing_radius * 2);
  }

  if (bounce_height <= 0.1f) {
    return;
  } else {

    if (new_position.y >= (window_size.y - smoothing_radius * 2)) {
      velocity.y = -0.8 * std::fabs(velocity.y);
      acceleration.y = std::fabs(acceleration.y);
    }

    if (new_position.y <= (0 + smoothing_radius * 2)) {
      velocity.y = std::fabs(velocity.y);
      acceleration.y = std::fabs(acceleration.y);
    }

    if (new_position.x <= (0 + smoothing_radius * 2)) {
      velocity.x = std::fabs(velocity.x);
      acceleration.x = std::fabs(velocity.x);
    }

    if (new_position.x >= (window_size.x - smoothing_radius * 2)) {
      velocity.x = -1 * std::fabs(velocity.x);
      acceleration.x = -1 * std::fabs(velocity.x);
    }
    velocity += acceleration * dt;
    position += velocity * dt;
  }
}

void Particle::set_x(const int &_x) { position.x = _x; }

void Particle::set_y(const int &_y) { position.y = _y; }
