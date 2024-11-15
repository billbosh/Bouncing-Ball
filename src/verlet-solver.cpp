#pragma once
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/System/Vector2.hpp>
#include <algorithm>
#include "verlet-ball.cpp"

class VerletSolver {
    sf::Vector2f gravity;
    std::vector<VerletBall> balls;

public:
    VerletSolver(std::vector<VerletBall>& ballsVector,
                 sf::Vector2f g = sf::Vector2f{0.f, 0.5f}) {
        gravity = g;
        balls = ballsVector;
    }

    void render(sf::RenderWindow& window) {
        std::for_each(balls.begin(), balls.end(), ([&window](VerletBall& obj) {
            obj.render(window); 
        })); 
    }

    void update() {
        applyGravity();
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

    void addBall(VerletBall newBall) {
        balls.push_back(newBall);
    }
};

