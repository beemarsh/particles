#pragma once

#include "render/Particle.hpp"
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/Shader.hpp>
#include <unordered_map>
using ParticleID = int;

class Particles {

private:
  ParticleID next_id = 0;
  sf::RenderTarget &window;
  sf::Vector2u window_size;
  sf::Vector2f mid_screen;

  float radius;
  sf::Shader &shader;

public:
  std::unordered_map<ParticleID, std::unique_ptr<Particle>> n_particles;

  Particles(sf::RenderTarget &_window, sf::Shader &_shader,
            float _radius = 1.f);

  Particle *create(sf::Vector2f);

  Particle *create();

  void generate(int N = 100);

  void render_all();

  void drop_all(float &dt);

  sf::Vector2f get_random_position();
};
