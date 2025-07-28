#include <SFML/Graphics.hpp>
#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Window/VideoMode.hpp>
#include <optional>

int main(){
  sf::RenderWindow window(sf::VideoMode({200,200}), "SFML Works!");

  sf::CircleShape circle(100.f); //Circle of radius 100
  circle.setFillColor(sf::Color::Green);

  while(window.isOpen()){
    while(const std::optional event = window.pollEvent()){
      if(event->is<sf::Event::Closed>())
        window.close();
    }

    window.clear();

    window.draw(circle);

    window.display();
  }
}
