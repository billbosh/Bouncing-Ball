#pragma once
#include <SFML/Config.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/System/Utf.hpp>
#include <SFML/System/Vector2.hpp>
#include <algorithm>
#include <cmath>
#include "verlet-ball.cpp"

class VerletSolver {
    sf::Vector2f gravity;
    std::vector<VerletBall> balls;
    float radius;

public:
    VerletSolver(std::vector<VerletBall>& ballsVector,
                 float ballsRadius,
                 sf::Vector2f g = sf::Vector2f{0.f, 5.f}) {
        gravity = g;
        balls = ballsVector;
        radius = ballsRadius;
    }

    void render(sf::RenderWindow& window) {
        std::for_each(balls.begin(), balls.end(), ([&window](VerletBall& obj) {
            obj.render(window); 
        })); 
    }

    void update() {
        applyGravity();
        solveBallCollisions();
        updatePositions();
    }
    
    void updatePositions() {
        std::for_each(balls.begin(), balls.end(), ([](VerletBall& obj) {
            obj.update(); 
        })); 
    }

    void applyGravity() {
        std::for_each(balls.begin(), balls.end(), ([this](VerletBall& obj) {
            obj.accelerate(gravity); 
        })); 
    }

    void solveBallCollisions() {
        const sf::Uint32 ballCount = balls.size();
        for (unsigned int i = 0; i < ballCount; ++i) {
            VerletBall& obj1 = balls[i];
            for (unsigned int k = i + 1; k < ballCount; ++k) {
                VerletBall& obj2 = balls[k];
                sf::Vector2f collisionAxis = obj1.getPosition() - obj2.getPosition();
                float distance = std::sqrt(std::pow(collisionAxis.x, 2) + std::pow(collisionAxis.y, 2));
                if (distance < radius * 2) {
                    float delta = radius * 2 - distance;
                    obj1.setPosition(sf::Vector2f {obj1.getPosition().x + (0.5f * delta), obj1.getPosition().y + (0.5f * delta)});
                    obj2.setPosition(sf::Vector2f {obj2.getPosition().x - (0.5f * delta), obj2.getPosition().y + (0.5f * delta)});
                }
            }
        }
    }

    void addBall(VerletBall newBall) {
        balls.push_back(newBall);
    }
};

