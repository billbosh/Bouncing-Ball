#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Vertex.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Mouse.hpp>
#include <vector>
#include "ball.cpp"
#include "verlet-solver.cpp"
#include "helper-functions.cpp"

int main()
{
    sf::Vector2f bounds(1000.f, 1000.f);
    auto window = sf::RenderWindow({1000u, 1000u}, "Bouncing Ball");
    window.setFramerateLimit(60);

    /*
    Ball ball(sf::Vector2f{10.f, 10.f}, 
              sf::Vector2f{10.f, 0.f}, 
              10.0f, 
              bounds,
              0.2f,
              0.6f,
              0.985f);
    */
    
    std::vector<VerletBall> balls;
    VerletSolver solver(balls); 
    
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
                /*
                ball.onClick(static_cast<sf::Vector2f>(mouse)); 
                */

                // on click spawn ball at mouse location with random velocity vector
                sf::Vector2i mouse = sf::Mouse::getPosition(window);
                sf::Vector2f randomVel{randomFloatInRange(-10.f, 10.f), randomFloatInRange(-5.f, 5.f)};
                solver.addBall(VerletBall(static_cast<sf::Vector2f>(mouse),
                                             randomVel,
                                             sf::Vector2f{0.f, 0.f},
                                             bounds,
                                             0.8f,
                                             30.0f,
                                             sf::Color::Blue));
            }
        }
        solver.update();
        window.clear();
        solver.render(window);
        window.display();
    }
}
