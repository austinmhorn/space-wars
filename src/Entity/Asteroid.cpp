#include "Entity/Asteroid.hpp"
#include "Core/Resources.hpp"

#include <random>

const sf::Texture Asteroid::m_texture = Textures::__load_asteroid_texture_sheet();

Asteroid::Asteroid()
    : m_exploding{false}
    , m_finished_exploding{false}
    , m_velocity{0.f, 0.f}
    , m_max_velocity{5.f, 5.f} 
    , m_acceleration{0.93f}
{
    m_sprite.setTexture(m_texture);
    m_sprite.setTextureRect({0, 0, 96, 96});

    m_sprite.setOrigin({m_sprite.getGlobalBounds().left + m_sprite.getLocalBounds().width/2.f, m_sprite.getGlobalBounds().top + m_sprite.getLocalBounds().height/2.f});

    __init_animations();

    std::random_device rseed;
    std::mt19937 rng(rseed());
    std::uniform_int_distribution<int> dist(-3, 3);

    m_rotational_speed = dist(rng);
}

void Asteroid::setPosition(const sf::Vector2f& position)
{
    m_sprite.setPosition(position);
}

const sf::Vector2f& Asteroid::getPosition() const
{
    return m_sprite.getPosition();
}

void Asteroid::setVelocity(const sf::Vector2f& velocity)
{
    m_velocity = velocity;
}

const sf::Vector2f& Asteroid::getVelocity() const
{
    return m_velocity;
}

void Asteroid::setBounds(const sf::Vector2f& bounds)
{
    m_bounds = bounds;
}

bool Asteroid::explodeAnimationComplete() const
{
    return m_finished_exploding;
}


bool Asteroid::isExploding() const
{
    return m_exploding;
}

void Asteroid::update(sf::Time delta_time)
{
    updateCollisions();
    updateMovement( delta_time.asSeconds() );

}

void Asteroid::updateCollisions()
{
    if ( !isExploding()  &&  getPosition().y > m_bounds.y )
    {
        explode();
    }
    else if ( isExploding()  &&  getPosition().y > m_bounds.y )
    {
        
    }
    else
    {
        
    }
}

void Asteroid::updateMovement(float elapsed)
{
    if ( m_exploding )
    {
        m_explode_anim.update( elapsed );

        if ( m_explode_anim.complete() )
        {
            m_finished_exploding = true;
            m_exploding = false;
        }
    }
    else
    {
        m_sprite.rotate(m_rotational_speed);
    }

    // Move character sprite
    m_sprite.move(m_velocity);
}

void Asteroid::explode()
{
    m_exploding = true;
}

void Asteroid::__init_animations()
{
    m_explode_anim = Animation(m_sprite);
    
    for (unsigned int i = 0; i < 8; i++)
    {
        sf::IntRect rect = sf::IntRect((i * 96), 0, 96, 96); // Adjust texture rectangle
        m_explode_anim.addFrame({rect, 0.1}); // Add new frame to animation
    }
}

void Asteroid::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(m_sprite);
}