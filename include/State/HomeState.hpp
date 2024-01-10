#ifndef HomeState_hpp
#define HomeState_hpp

#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/Text.hpp>

#include "Core/State.hpp"
#include "Entity/StarAnimation.hpp"

#include "Entity/Button.hpp"

class HomeState final : public State
{
public:
    HomeState(StateMachine& machine, sf::RenderWindow& window, Resources& resources, const bool replace = true);

    void pause() override;
    void resume() override;
    void handleEvent() override;
    void update() override;
    void draw() override;
    
private:

    sf::RectangleShape m_background;
    sf::Vector2f       m_current_mouse_position;

    sf::Text           m_title;
    StarAnimation      m_star_anim;
    
    Button m_start;
    //Button m_inventory;
    //Button m_upgrades;
    Button m_controls;
    Button m_options;
    Button m_quit;
};

#endif /* HomeState_hpp */