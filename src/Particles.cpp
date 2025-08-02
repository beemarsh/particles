#include "render/Particles.hpp"
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Shader.hpp>
#include <random>

Particles::Particles(sf::RenderTarget &_window, sf::Shader &_shader,
                     float _radius)
    : window(_window), radius(_radius), shader(_shader) {
  // Set Position to the middle of the screen
  const auto &screen_size = window.getSize();
  window_size = {screen_size.x, screen_size.y};
  mid_screen = {screen_size.x / 2.f, screen_size.y / 2.f};
}

Particle *Particles::create(sf::Vector2f _pos) { // By default, render particle
                                                 // in the middle of the screen

  next_id++;
  auto new_particle = std::make_unique<Particle>(window, next_id, radius);
  new_particle->position = _pos;
  n_particles[next_id] = std::move(new_particle);
  return n_particles[next_id].get();
}

Particle *Particles::create() {
  auto created_particle = create(mid_screen);
  return created_particle;
}

void Particles::render_all() {
  for (const auto &curr_particle : n_particles) {
    curr_particle.second->render(shader);
  }
}

void Particles::drop_all(float &dt) {
  for (const auto &curr_particle : n_particles) {
    curr_particle.second->fall(dt);
  }
};

void Particles::generate(int N) {

  for (int i{0}; i < N; i++) {
    next_id++;
    auto new_particle = std::make_unique<Particle>(window, next_id, radius);
    new_particle->position = get_random_position();
    n_particles[next_id] = std::move(new_particle);
  }
}

sf::Vector2f Particles::get_random_position() {
  std::random_device rd;
  std::mt19937 gen(rd());

  std::uniform_int_distribution<> distrib_x(0, window_size.x - radius * 2);
  std::uniform_int_distribution<> distrib_y(0, window_size.y - radius * 2);

  float rand_num_x = static_cast<float>(distrib_x(gen));
  float rand_num_y = static_cast<float>(distrib_y(gen));

  return {rand_num_x, rand_num_y};
}
