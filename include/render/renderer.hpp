#include <SFML/Graphics.hpp>
#include <render/particle.hpp>
class Renderer {
private:
  sf::RenderTarget &target;

public:
  Renderer(sf::RenderTarget &target_) : target{target_} {}

  void render(Particle &particle, float &dt) {
    target.clear(sf::Color::Black);

    particle.velocity = particle.velocity + particle.acceleration * dt;

    particle.position = particle.position + particle.velocity * dt;

    particle.render();
  }
};
