#ifndef StarAnimation_hpp
#define StarAnimation_hpp

#include <SFML/Graphics/Transformable.hpp>
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/System/Time.hpp>
#include <SFML/Graphics/CircleShape.hpp>

#include <cmath>
#include <iostream>

#define _USE_MATH_DEFINES

static const int STARS_COUNT = 100;

class StarAnimation : public sf::Drawable, public sf::Transformable
{
public:

    StarAnimation() 
        : m_particles(STARS_COUNT)
        , m_bounds(0.f, 0.f)
    {
        for (std::size_t i = 0; i < m_particles.size(); ++i)
        {
            m_shapes[i].setRadius(static_cast<float>(std::rand() % 2 + 1));
            float angle = 90 * M_PI / 180.f;
            float speed = (std::rand() % 50) + 50.f;
            m_particles[i].velocity = sf::Vector2f(std::cos(angle) * speed, std::sin(angle) * speed);
        }
    }
    
    void setColor(sf::Color color)
    {
        for (std::size_t i = 0; i < m_particles.size(); ++i)
            m_shapes[i].setFillColor(color);
    }
    
    void setColor(sf::Uint8 r, sf::Uint8 g, sf::Uint8 b, sf::Uint8 a)
    {
        for (std::size_t i = 0; i < m_particles.size(); ++i)
            m_shapes[i].setFillColor(sf::Color{r, g, b, a});
    }
    
    void setBounds(const sf::Vector2f& bounds)
    {
        m_bounds = bounds;

        for (auto &shape : m_shapes)
            shape.setPosition({static_cast<float>(std::rand() % static_cast<int>(m_bounds.x) + 1), 
                               static_cast<float>(std::rand() % static_cast<int>(m_bounds.y) + 1)});
    }
    
    void update(sf::Time elapsed)
    {
        for (std::size_t i = 0; i < m_particles.size(); ++i)
        {
            // update the particle lifetime
            Particle& p = m_particles[i];

            // if the particle is dead, respawn it
            if (m_shapes[i].getPosition().y >= m_bounds.y + m_shapes[i].getRadius()*2.f)
                resetParticle(i);

            // update the position of the corresponding vertex
            m_shapes[i].setPosition(m_shapes[i].getPosition() + p.velocity * elapsed.asSeconds());
        }
    }

private:

    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const
    {
        // apply the transform
        states.transform *= getTransform();

        // our particles don't use a texture
        states.texture = nullptr;

        // draw the vertex array
        for (auto &shape : m_shapes)
            target.draw(shape, states);
    }

private:

    struct Particle
    {
        sf::Vector2f velocity;
    };

    void resetParticle(std::size_t index)
    {
        // give a random velocity and lifetime to the particle
        float angle = 90 * M_PI / 180.f;
        float speed = (std::rand() % 50) + 50.f;
        m_particles[index].velocity = sf::Vector2f(std::cos(angle) * speed, std::sin(angle) * speed);

        // reset the position of the corresponding vertex
        m_shapes[index].setPosition({static_cast<float>(std::rand() % static_cast<int>(m_bounds.x) + 1), -5.f});
    }

    std::vector<Particle> m_particles;
    sf::CircleShape m_shapes[STARS_COUNT];
    sf::Vector2f m_bounds;
};

#undef _USE_MATH_DEFINES

#endif /* StarAnimation_hpp */