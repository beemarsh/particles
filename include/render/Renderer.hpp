#pragma once
#include "render/Particles.hpp"
#include <SFML/Graphics.hpp>

class Renderer {
private:
  sf::RenderTarget &target;

public:
  Renderer(sf::RenderTarget &target_);

  void render(Particles &particles, float &dt);
};
