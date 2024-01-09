#include "Entity/Ship.hpp"
#include "Core/Resources.hpp"


Ship::Ship()
{
    m_base_texture = Textures::__load_ship_base_pristine_texture();
    m_base_sprite.setTexture(m_base_texture);
}

void Ship::handleEvent(sf::RenderWindow &window, sf::Event event)
{
    if ( event.type == sf::Event::KeyPressed  &&  event.key.code == sf::Keyboard::Key::Up )
    {
        
    }
}

void Ship::update(sf::Time delta_time) 
{

}

void Ship::draw(sf::RenderTarget& target, sf::RenderStates states) const 
{
    target.draw(m_base_sprite, &m_base_texture);
}