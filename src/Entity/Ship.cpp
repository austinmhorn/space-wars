#include "Entity/Ship.hpp"
#include "Core/Resources.hpp"

Ship::Ship()
    : m_velocity{0.f, 0.f}
    , m_max_velocity{2.5f, 2.5f} 
    , m_acceleration{0.93f}
    , m_engine_effects_curr_state{Ship::State::IDLE}
    , m_engine_on{true}
    , m_can_fire_auto_cannon{true}
    , m_scale{1.f, 1.f}
{
    m_base_texture = Textures::__load_ship_base_pristine_texture();
    m_base_sprite.setTexture(m_base_texture);

    m_engine_texture = Textures::__load_ship_engine_texture();
    m_engine_sprite.setTexture(m_engine_texture);

    m_engine_effects_texture_sheet = Textures::__load_ship_engine_effects_texture_sheet();
    m_engine_effects_sprite.setTexture(m_engine_effects_texture_sheet);
    m_engine_effects_sprite.setTextureRect({0, 0, 48, 48});

    setScale(m_scale);

    updateSprites();

    __init_animations();
}

Ship::~Ship()
{
    
}

void Ship::setScale(const sf::Vector2f& scale)
{
    m_scale = scale;
    m_base_sprite.setScale(scale);
    m_engine_sprite.setScale(scale);
    m_engine_effects_sprite.setScale(scale);
    m_cannon.setScale(scale);
}

void Ship::setBounds(const sf::Vector2f& bounds)
{
    m_bounds = bounds;
}

void Ship::setPosition(const sf::Vector2f& position)
{
    m_base_sprite.setPosition(position);
    updateSprites();
}

void Ship::setMaxVelocity(const sf::Vector2f& max_velocity)
{
    m_max_velocity = max_velocity;
}

void Ship::updateCollisions()
{
    if (m_base_sprite.getPosition().x < 0.f) // Left window collision
        m_base_sprite.setPosition(0.f, m_base_sprite.getPosition().y);
    if (m_base_sprite.getPosition().x + m_base_sprite.getGlobalBounds().width > m_bounds.x) // Right window collision
        m_base_sprite.setPosition(m_bounds.x - m_base_sprite.getGlobalBounds().width, m_base_sprite.getPosition().y);
    if (m_base_sprite.getPosition().y < 0.f) // Top window collision
        m_base_sprite.setPosition(m_base_sprite.getPosition().x, 0.f);
    if (m_base_sprite.getPosition().y + m_base_sprite.getGlobalBounds().height > m_bounds.y) // Bottom window collision
        m_base_sprite.setPosition(m_base_sprite.getPosition().x, m_bounds.y - m_base_sprite.getGlobalBounds().height);
}

void Ship::updateMovement(float elapsed)
{    
      // X axis movement
    if ( sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left) )
        m_velocity.x += -1.f * m_acceleration;
    else if ( sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right) )
        m_velocity.x += 1.f * m_acceleration;
    else
        m_velocity.x = 0.f;

    // Y axis movement
    if ( sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up) )
        m_velocity.y += -1.f * m_acceleration;
    else if ( sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down) )
        m_velocity.y += 1.f * m_acceleration;
    else
        m_velocity.y = 0.f;   
}

void Ship::updatePhysics()
{    
    // Limit Y axis velocity
    if (std::abs(m_velocity.y) > m_max_velocity.y)
        m_velocity.y = m_max_velocity.y * ((m_velocity.y < 0) ? -1.f : 1.f);
    
    // Move character sprite
    m_base_sprite.move(m_velocity);
    
    // Limit X axis velocity
    if (std::abs(m_velocity.x) > m_max_velocity.x)
        m_velocity.x = m_max_velocity.x * ((m_velocity.x < 0) ? -1.f : 1.f);
}

void Ship::updateSprites()
{
    const sf::Vector2f origin = m_base_sprite.getPosition();
    const sf::FloatRect size = m_base_sprite.getGlobalBounds();

    m_engine_sprite.setPosition( origin.x, origin.y + (3.f * m_engine_sprite.getScale().y) );

    m_engine_effects_sprite.setPosition( {(origin.x + size.width/2.f) - m_engine_effects_sprite.getGlobalBounds().width/2.f, (origin.y + size.height/2.f) - m_engine_effects_sprite.getGlobalBounds().width/2.f} );
    m_engine_effects_sprite.setPosition( {m_engine_effects_sprite.getPosition().x, m_engine_effects_sprite.getPosition().y + (3.f * m_engine_effects_sprite.getScale().y)} );

    m_cannon.setPosition( origin );
}

void Ship::updateAnimations(float elapsed)
{
    if ( m_velocity.y < 0.f)
    {
        m_engine_effects_curr_state = Ship::State::POWERED;
        m_engine_on = true;
    }
    else if ( m_velocity.y > 0.f )
    {
        m_engine_on = false;
    }
    else
    {
        m_engine_effects_curr_state = Ship::State::IDLE;
        m_engine_on = true;
    }

    if ( m_engine_effects_last_state != m_engine_effects_curr_state )
    {
        switch ( m_engine_effects_curr_state ) 
        {
            case Ship::State::IDLE:     m_curr_engine_effects_anim = m_engine_effects_idle_anim;     break;
            case Ship::State::POWERED:  m_curr_engine_effects_anim = m_engine_effects_powered_anim;  break;
        }
    }
    
    // Track last state
    m_engine_effects_last_state = m_engine_effects_curr_state;

    // Update engine effects animation
    m_curr_engine_effects_anim.update(elapsed);

    // Fire AutoCannon if Space key is pressed
    if ( sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space) )
        fireAutoCannon();
}

void Ship::fireAutoCannon()
{
    m_cannon.fire();
}

void Ship::update(sf::Time delta_time) 
{
    updateCollisions();
    updateMovement( delta_time.asSeconds() );
    updatePhysics();
    updateSprites();
    updateAnimations( delta_time.asSeconds() );

    m_cannon.update(delta_time);
}

void Ship::__init_animations()
{
    m_engine_effects_idle_anim = Animation(m_engine_effects_sprite, true);
    m_engine_effects_powered_anim = Animation(m_engine_effects_sprite, true);
    
    // Load 3 engine effect idle frames
    for (unsigned int i = 0; i < 3; i++)
    {
        sf::IntRect rect = sf::IntRect((i * 48), 0, 48, 48); // Adjust texture rectangle
        m_engine_effects_idle_anim.addFrame({rect, 0.1}); // Add new frame to animation
    }

    // Load 4 engine powered frames
    for (unsigned int i = 0; i < 4; i++)
    {
        sf::IntRect rect = sf::IntRect((i * 48), 48, 48, 48); 
        m_engine_effects_powered_anim.addFrame({rect, 0.1});
    }

    m_curr_engine_effects_anim = m_engine_effects_idle_anim;
}

void Ship::draw(sf::RenderTarget& target, sf::RenderStates states) const 
{
    if ( m_engine_on )
        target.draw(m_engine_effects_sprite);
    target.draw(m_cannon);
    target.draw(m_engine_sprite);
    target.draw(m_base_sprite);
}