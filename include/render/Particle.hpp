#pragma once
#include <SFML/Graphics.hpp>

using ParticleID = int;
struct Particle {

  ParticleID id;

  sf::Vector2f position;
  sf::Vector2f velocity;
  sf::Vector2f acceleration;

  sf::Color color;
  int32_t radius;
  sf::CircleShape shape;
  sf::RenderTarget &window;
  sf::Vector2u window_size;
  sf::Vector2f scale;

  Particle(sf::RenderTarget &window_, ParticleID _id);

  void render();

  void fall(float &dt);

  void set_x(const int &_x);

  void set_y(const int &_y);
};
