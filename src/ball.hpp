#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Transformable.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/System/Time.hpp>
#include <SFML/System/Vector2.hpp>
#include <cstdlib>
#include <iostream>

class Ball {
    sf::Vector2f m_pos;
    sf::Vector2f m_vel;
    sf::CircleShape m_s;
    float m_radius;
    float m_gravity = 0.2f;
    sf::Clock m_clock;
    sf::Vector2f m_bounds;
    float m_collisionDamping;
    float m_dragCoefficient;
    float m_drag;

public:
    Ball (float pos_x, float pos_y, float vel_x, float vel_y, float radius, sf::Vector2f bounds, float collisionDamping = 0.8f, float dragCoefficient = 0.98f) {
        m_pos.x = pos_x;
        m_pos.y = pos_y;

        m_vel.x = vel_x;
        m_vel.y = vel_y;
        
        m_bounds = bounds;

        m_radius = radius;

        m_collisionDamping = collisionDamping;
        m_drag = dragCoefficient;

        m_s.setPosition(m_pos.x, m_pos.y);
        m_s.setFillColor(sf::Color::White);
        m_s.setRadius(radius);
        m_s.setOrigin(radius, radius);
    }

    void render(sf::RenderWindow& window) {
        window.draw(m_s);
    }

    void update() {
        sf::Time elapsed = m_clock.getElapsedTime();

        m_pos.x += m_vel.x * elapsed.asSeconds();
        m_pos.y += m_vel.y * elapsed.asSeconds();

        m_vel.y += m_gravity * elapsed.asSeconds();

        resolveCollisions();

        m_s.setPosition(m_pos.x, m_pos.y);
    }

    void resolveCollisions() {
        if (m_pos.x > m_bounds.x) {
            m_pos.x = m_bounds.x - m_radius;
            m_vel.x *= -1 * m_collisionDamping;
        }
        else if (m_pos.x < 0) {
            m_pos.x = m_radius;
            m_vel.x *= -1 * m_collisionDamping;
        }
        if (m_pos.y > m_bounds.y) {
            m_pos.y = m_bounds.y - m_radius;
            m_vel.y *= -1 * m_collisionDamping;
        }
        else if (m_pos.y < 0) {
            m_pos.y = m_radius;
            m_vel.y *= -1 * m_collisionDamping;
        }
    }

    int sign(float num) {
        if (num > 0) {
            return 1;
        }
        else if (num == 0) {
            return 0;
        }
        else {
            return -1;
        }
    }

    void onClick(sf::Vector2f newPos) {
        m_pos.x = newPos.x;
        m_pos.y = newPos.y;

        std::cout << "x: " << newPos.x << " y: " << newPos.y << std::endl;

        m_vel.x = 10;
        m_vel.y = -1;

        m_clock.restart();
    }
};
