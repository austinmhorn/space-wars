#include "Entity/AutoCannon.hpp"

#include "Core/Resources.hpp"



AutoCannon::AutoCannon()
    : m_shooting{false}
{
    m_texture = Textures::__load_auto_cannon_texture_sheet();
    m_sprite.setTexture(m_texture);
    m_sprite.setTextureRect(sf::IntRect{0, 0, 48, 48});
    
    __init_animations();

    m_bullet_texture_sheet = Textures::__load_auto_cannon_bullet_texture_sheet();
    
    for (std::size_t i = 0; i < AUTO_CANNON_AMMO_SIZE; i++)
    {
        m_bullets_loaded.push_back(new AutoCannon::Bullet{&m_bullet_texture_sheet});
    }

}

AutoCannon::~AutoCannon()
{
    for (std::size_t i = 0; i < AUTO_CANNON_AMMO_SIZE; i++)
    {
        delete m_bullets_loaded[i];
    }
    for (auto& bullet : m_bullets_active)
        bullet = nullptr;
}

void AutoCannon::setScale(const sf::Vector2f& scale)
{
    m_scale = scale;
    m_sprite.setScale(scale);
    
    for (std::size_t i = 0; i < AUTO_CANNON_AMMO_SIZE; i++)
    {
        m_bullets_loaded[i]->setScale(m_scale);
    }
}

void AutoCannon::setPosition(const sf::Vector2f& position)
{
    m_sprite.setPosition(position);
}

void AutoCannon::fire()
{
    m_shooting = true;
}

bool AutoCannon::canStopAnimation()
{
    return m_shoot_anim.complete();
}

void AutoCannon::fireLeftCannon()
{
    auto& bullet = m_bullets_loaded.back();
    bullet->setPosition( {m_sprite.getPosition().x - m_sprite.getScale().x, m_sprite.getPosition().y - (3.f * m_sprite.getScale().y)} );
    
    m_bullets_active.insert(m_bullets_active.begin(), std::move(bullet));
    m_bullets_loaded.pop_back();
    std::cout << "Fire LEFT cannon" << std::endl;
}

void AutoCannon::fireRightCannon()
{
    auto& bullet = m_bullets_loaded.back();
    bullet->setPosition( {m_sprite.getPosition().x + m_sprite.getGlobalBounds().width - bullet->getGlobalBounds().width + (3.f * bullet->getScale().x), m_sprite.getPosition().y - (3.f * m_sprite.getScale().y)} );
    
    m_bullets_active.insert(m_bullets_active.begin(), std::move(bullet));
    m_bullets_loaded.pop_back();
    std::cout << "Fire RIGHT cannon" << std::endl;
}

void AutoCannon::update(sf::Time delta_time)
{
    updateAnimations( delta_time.asSeconds() );

    for (std::size_t i = 0; i < m_bullets_active.size(); i++)
    {
        m_bullets_active[i]->update( delta_time );
        
    }

    if ( m_bullets_active.size()  &&  m_bullets_active.back()->getPosition().y + m_bullets_active.back()->getGlobalBounds().height < 0.f )
    {
        m_bullets_loaded.insert(m_bullets_loaded.begin(), std::move(m_bullets_active.back()));
        m_bullets_active.pop_back();
        std::cout << "Recycled off-screen bullet" << std::endl;
    }

}

void AutoCannon::updateAnimations(float elapsed)
{
    if ( m_shooting )
    {
        m_shoot_anim.update( elapsed );

        if ( m_shoot_anim.complete() )
        {
            m_shooting = false;
            m_left_cannon_fired = false;
            m_right_cannon_fired = false;
            m_shoot_anim.reset();
        }
        else if ( !m_left_cannon_fired  &&  m_shoot_anim.currentFrameTime() >= 0.2  &&  m_shoot_anim.currentFrameTime() <= 0.3 )
        {
            m_left_cannon_fired = true;
            fireLeftCannon();
        }
        else if ( !m_right_cannon_fired  &&  m_shoot_anim.currentFrameTime() >= 0.3  &&  m_shoot_anim.currentFrameTime() <= 0.4 )
        {
            m_right_cannon_fired = true;
            fireRightCannon();
        }
    }

}

void AutoCannon::__init_animations()
{
    m_shoot_anim = Animation(m_sprite);

    for (unsigned int i = 0; i < 7; i++)
    {
        sf::IntRect rect = sf::IntRect((i * 48), 0, 48, 48); // Adjust texture rectangle
        m_shoot_anim.addFrame({rect, 0.1}); // Add new frame to animation
    }
}

void AutoCannon::draw(sf::RenderTarget& target, sf::RenderStates states) const 
{
    target.draw(m_sprite);

    for (auto& bullet : m_bullets_active)
        target.draw(*bullet);
}








///< Auto Cannon Bullet
////////////////////////////////////////////////////////////////////////////////////////////////////
AutoCannon::Bullet::Bullet(const sf::Texture* texture)
    : m_velocity{0.f, 0.f}
    , m_max_velocity{8.5f, 8.5f} 
    , m_acceleration{0.93f}
{
    m_texture = texture;
    m_sprite.setTexture(*m_texture);
    m_sprite.setTextureRect(sf::IntRect{0, 0, 32, 32});

    __init_animations();
}

void AutoCannon::Bullet::update(sf::Time delta_time) 
{
    updateMovement( delta_time.asSeconds() );
    updatePhysics();
    updateAnimations( delta_time.asSeconds() );
}

void AutoCannon::Bullet::setScale(const sf::Vector2f& scale)
{
    m_sprite.setScale(scale);
}

void AutoCannon::Bullet::setPosition(const sf::Vector2f& position)
{
    m_sprite.setPosition(position);
}

const sf::Vector2f& AutoCannon::Bullet::getPosition() const
{
    return m_sprite.getPosition();
}

sf::FloatRect AutoCannon::Bullet::getGlobalBounds() const
{
    return m_sprite.getGlobalBounds();
}

void AutoCannon::Bullet::updateMovement(float elapsed)
{    
    m_velocity.y += -1.f * m_acceleration; 
}

void AutoCannon::Bullet::updatePhysics()
{    
    // Limit Y axis velocity
    if (std::abs(m_velocity.y) > m_max_velocity.y)
        m_velocity.y = m_max_velocity.y * ((m_velocity.y < 0) ? -1.f : 1.f);
    
    // Move character sprite
    m_sprite.move(m_velocity);
    
    // Limit X axis velocity
    if (std::abs(m_velocity.x) > m_max_velocity.x)
        m_velocity.x = m_max_velocity.x * ((m_velocity.x < 0) ? -1.f : 1.f);
}

void AutoCannon::Bullet::updateAnimations(float elapsed)
{
    m_anim.update(elapsed);
}

void AutoCannon::Bullet::reset()
{
    
}

void AutoCannon::Bullet::draw(sf::RenderTarget& target, sf::RenderStates states) const 
{
    target.draw(m_sprite);
}

void AutoCannon::Bullet::__init_animations()
{
    m_anim = Animation(m_sprite, true);

    for (unsigned int i = 0; i < 4; i++)
    {
        sf::IntRect rect = sf::IntRect((i * 32), 0, 32, 32); // Adjust texture rectangle
        m_anim.addFrame({rect, 0.1}); // Add new frame to animation
    }
}
