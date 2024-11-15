#include <malloc/_malloc_type.h>
#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/System/Vector2.hpp>
#include <cmath>
#include <ctime>

class VerletBall {
    sf::Vector2f posCurrent;
    sf::Vector2f posPrevious;
    sf::Vector2f acceleration;
    sf::Vector2f bounds;
    float collisionDamping;
    float radius;
    sf::Color color;
    sf::CircleShape s;
    sf::Clock clock;

public:
    VerletBall(sf::Vector2f posSpawn,
               sf::Vector2f velocitySpawn,
               sf::Vector2f accelerationSpawn,
               sf::Vector2f boundsSpawn,
               float collisionDampingSpawn,
               float radiusSpawn,
               sf::Color colorSpawn) {
        posCurrent = posSpawn;
        posPrevious = posSpawn - velocitySpawn;
        acceleration = accelerationSpawn;
        bounds = boundsSpawn;
        collisionDamping = collisionDampingSpawn;

        radius = radiusSpawn;
        color = colorSpawn;

        s.setPosition(posCurrent);
        s.setRadius(radius);
        s.setFillColor(color);
        s.setOrigin(radius, radius);

        clock.restart();
    }

    void render(sf::RenderWindow& window) {
        window.draw(s);
    }

    void update() {
        float elapsed = clock.getElapsedTime().asSeconds();

        sf::Vector2f velocity = posCurrent - posPrevious;
        velocity = resolveCollisions(velocity);

        posPrevious = posCurrent;

        float elapsedSquared = std::pow(elapsed, 2);
        posCurrent = posCurrent + velocity + acceleration * elapsedSquared;

        acceleration = (sf::Vector2f{0.f, 0.f});

        s.setPosition(posCurrent);
    }

    void accelerate(sf::Vector2f acc) {
        acceleration += acc;
    }

    void setPosition(sf::Vector2f pos) {
        posCurrent = pos;
    }

    sf::Vector2f resolveCollisions(sf::Vector2f velocity) {
        // if ball hits left side
        if (posCurrent.x < radius) {
            posCurrent = sf::Vector2f{radius, posCurrent.y};
            posPrevious = posCurrent;   
            return sf::Vector2f{velocity.x * -1.f, velocity.y};
        }
        // if ball hits right side
        if (posCurrent.x > bounds.x - radius) {
            posCurrent = sf::Vector2f{bounds.x - radius, posCurrent.y};
            posPrevious = posCurrent;
             return sf::Vector2f{velocity.x * -1.f, velocity.y};
        }
        // if ball hits top side
        if (posCurrent.y < radius) {
            posCurrent = sf::Vector2f{posCurrent.x, radius};
            posPrevious = posCurrent;
            return sf::Vector2f{velocity.x, velocity.y * -1.f};
        }
        // if ball hits bottom side
        if (posCurrent.y > bounds.y - radius) {
            posCurrent = sf::Vector2f{posCurrent.x, bounds.y - radius};
            posPrevious = posCurrent;
            return sf::Vector2f{velocity.x, velocity.y * -1.f};
        }
        return velocity;
    }
};
