#pragma once
#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/Shader.hpp>
#include <cstdint>

using ParticleID = int;
struct Particle {

  ParticleID id;

  sf::Vector2f position;
  sf::Vector2f velocity;
  sf::Vector2f acceleration;
  float mass;
  int32_t point_count;

  sf::Color color;
  float radius;
  int32_t bounce_height;
  float smoothing_radius;

  sf::CircleShape shape;
  sf::RenderTarget &window;
  sf::Vector2u window_size;

  Particle(sf::RenderTarget &window_, ParticleID _id, float _radius = 1.f);

  void render(sf::Shader &_shader);

  void fall(float &dt);

  void set_x(const int &_x);

  void set_y(const int &_y);

  int32_t get_drop_height();

  static bool direction_change(float a, float b);
};
