#include <SFML/Graphics.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Mouse.hpp>
#include "ball.hpp"

int main()
{
    sf::Vector2f windowSize(1000.f, 1000.f);
    auto window = sf::RenderWindow({1000u, 1000u}, "Bouncing Ball");
    window.setFramerateLimit(144);

    Ball ball(10, 10, 10, 0, 10.0f, windowSize, 0.6f);

    sf::Clock clock;
    sf::Vector2i mouse; 

    while (window.isOpen())
    {
        for (auto event = sf::Event(); window.pollEvent(event);)
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }
            if (event.type == sf::Event::MouseButtonPressed) {
                sf::Vector2i mouse = sf::Mouse::getPosition(window);
                ball.onClick(static_cast<sf::Vector2f>(mouse)); 
            }
        }
        
        ball.update();

        window.clear();
        ball.render(window);
        window.display();
    }
}
