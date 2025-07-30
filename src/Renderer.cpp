#include <SFML/Graphics.hpp>
#include <render/Renderer.hpp>

Renderer::Renderer(sf::RenderTarget &target_) : target{target_} {}

void Renderer::render(Particles &particles, float &dt) {
  target.clear(sf::Color::Black);

  particles.render_all();
  particles.drop_all(dt);
};
