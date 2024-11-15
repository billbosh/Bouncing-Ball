/* Original ball class, since updated to verlet integration based class */

#include <SFML/Graphics.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/System/Time.hpp>
#include <SFML/System/Vector2.hpp>

class Ball {
    sf::Vector2f m_pos;
    sf::Vector2f m_vel;
    sf::CircleShape m_s;
    float m_radius;
    float m_gravity;
    sf::Clock m_clock;
    sf::Vector2f m_bounds;
    float m_collisionDamping;
    float m_dragCoefficient;

public:
    Ball (sf::Vector2f pos, 
          sf::Vector2f vel, 
          float radius, 
          sf::Vector2f bounds, 
          float gravity,
          float collisionDamping, 
          float dragCoefficient) {
        m_pos.x = pos.x;
        m_pos.y = pos.y;

        m_vel.x = vel.x;
        m_vel.y = vel.y;
        
        m_radius = radius;
        
        m_bounds = bounds;
        m_gravity = gravity;
        m_collisionDamping = collisionDamping;
        m_dragCoefficient = dragCoefficient;

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
        
        // m_vel.x *= m_dragCoefficient;
        m_vel.y += m_gravity * elapsed.asSeconds();

        resolveCollisions();

        m_s.setPosition(m_pos.x, m_pos.y);
    }

    void resolveCollisions() {
        if (m_pos.x > m_bounds.x) {
            m_pos.x = m_bounds.x - m_radius;
            m_vel.x *= -1.f * m_collisionDamping;
        }
        else if (m_pos.x < 0) {
            m_pos.x = m_radius;
            m_vel.x *= -1.f * m_collisionDamping;
        }
        if (m_pos.y > m_bounds.y) {
            m_pos.y = m_bounds.y - m_radius;
            m_vel.y *= -1.f * m_collisionDamping;
        }
        else if (m_pos.y < 0) {
            m_pos.y = m_radius;
            m_vel.y *= -1.f * m_collisionDamping;
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

        m_vel.x = 10;
        m_vel.y = 0;

        m_clock.restart();
    }
};
