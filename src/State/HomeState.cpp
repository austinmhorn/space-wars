#include <SFML/Window/Window.hpp>
#include <SFML/Window/Event.hpp>

#include "State/HomeState.hpp"
#include "State/PlayState.hpp"
#include "Core/StateMachine.hpp"
#include "Core/Resources.hpp"

#include <iostream>
#include <memory>

HomeState::HomeState(StateMachine& machine, sf::RenderWindow& window, Resources& resources, const bool replace)
    : State{ machine, window, resources, replace }
    , m_start{ "Start", resources, 30 }
    , m_inventory{ "Inventory", resources, 30 }
    , m_market{ "Market", resources, 30 }
    , m_highscores{ "Highscores", resources, 30 }
    , m_options{ "Options", resources, 30 }
    , m_controls{ "Controls", resources, 30 }
    , m_quit{ "Quit", resources, 30 }  
{
    const auto window_size = sf::Vector2f{ window.getSize() };

    m_background.setFillColor(sf::Color::Black);
    m_background.setSize(window_size);

    m_title = sf::Text("Space  Wars", resources.Zorque, 36 + std::round(window_size.x / 20) );
    m_title.setLetterSpacing(4.f);
    m_title.setPosition( window_size.x/2.f - m_title.getGlobalBounds().width/2.f, window_size.y/6.f - m_title.getGlobalBounds().height/2.f );
    m_title.setFillColor(sf::Color::White);

    m_star_anim.setColor(sf::Color{255, 255, 255, 150});
    m_star_anim.setBounds(window_size);

    __init_buttons(window_size);

}

void HomeState::__init_buttons(const sf::Vector2f& window_size)
{
    float factor = 18;
    m_start.text().setCharacterSize( std::round(window_size.y / factor) );
    m_start.setOutlineThickness(4.f);
    m_inventory.text().setCharacterSize( std::round(window_size.y / factor) );
    m_inventory.setOutlineThickness(4.f);
    m_market.text().setCharacterSize( std::round(window_size.y / factor) );
    m_market.setOutlineThickness(4.f);
    m_highscores.text().setCharacterSize( std::round(window_size.y / factor) );
    m_highscores.setOutlineThickness(4.f);
    m_options.text().setCharacterSize( std::round(window_size.y / factor) );
    m_options.setOutlineThickness(4.f);
    m_controls.text().setCharacterSize( std::round(window_size.y / factor) );
    m_controls.setOutlineThickness(4.f);
    m_quit.text().setCharacterSize( std::round(window_size.y / factor) );
    m_quit.setOutlineThickness(4.f);

    m_start.setPosition({10.f, window_size.y/2.f});
    m_inventory.setPosition({10.f, m_start.getGlobalBounds().top + m_start.getGlobalBounds().height + m_inventory.text().getCharacterSize()/10.f });
    m_market.setPosition({ 10.f, m_inventory.getGlobalBounds().top + m_inventory.getGlobalBounds().height + m_market.text().getCharacterSize()/10.f });
    m_highscores.setPosition({ 10.f, m_market.getGlobalBounds().top + m_market.getGlobalBounds().height + m_highscores.text().getCharacterSize()/10.f });
    m_options.setPosition({ 10.f, m_highscores.getGlobalBounds().top + m_highscores.getGlobalBounds().height + m_options.text().getCharacterSize()/10.f });
    m_controls.setPosition({ 10.f, m_options.getGlobalBounds().top + m_options.getGlobalBounds().height + m_controls.text().getCharacterSize()/10.f });
    m_quit.setPosition({ 10.f, m_controls.getGlobalBounds().top + m_controls.getGlobalBounds().height + m_quit.text().getCharacterSize()/10.f });

    m_start.setOutlineColor(sf::Color::Green);
    m_quit.setOutlineColor(sf::Color::Red);
}

void HomeState::pause()
{
    //std::cout << "HomeState Pause" << std::endl;;
}

void HomeState::resume()
{
    //std::cout << "HomeState Resume" << std::endl;;
}

void HomeState::handleEvent()
{
    for (auto event = sf::Event{}; m_window.pollEvent(event);)
    {        
        switch (event.type)
        {
            case sf::Event::Closed:
                m_machine.quit();
                break;
                
            case sf::Event::MouseMoved:
                ///< Get new mouse position
                m_current_mouse_position = m_window.mapPixelToCoords({ event.mouseMove.x, event.mouseMove.y });               
                break;
                
            case sf::Event::MouseButtonPressed:
                ///< Get location for mouse button press event
                m_current_mouse_position = m_window.mapPixelToCoords({ event.mouseButton.x, event.mouseButton.y });
                break;
                
            case sf::Event::MouseButtonReleased:
                ///< Get location for mouse button release event
                m_current_mouse_position = m_window.mapPixelToCoords({ event.mouseButton.x, event.mouseButton.y });

                if ( m_quit.contains(m_current_mouse_position) )
                    m_machine.quit();
                else if ( m_start.contains(m_current_mouse_position) )
                    m_next = StateMachine::build<PlayState>(m_machine, m_window, m_resources, true);
                break;
                
            case sf::Event::KeyPressed:
                break;
                
            case sf::Event::TextEntered:
                break;
                
            default:
                break;
        }
        
        
    }
}

void HomeState::update()
{
    static const auto clock = sf::Clock{};
    static auto last_frame_time = sf::Time{};
    const auto delta_time = clock.getElapsedTime() - last_frame_time;
    last_frame_time = clock.getElapsedTime();
    
    handleEvent();

    ( m_start.contains(m_current_mouse_position) ) ? m_start.mouseOver() : m_start.mouseLeave();
    ( m_inventory.contains(m_current_mouse_position) ) ? m_inventory.mouseOver() : m_inventory.mouseLeave();
    ( m_market.contains(m_current_mouse_position) ) ? m_market.mouseOver() : m_market.mouseLeave();
    ( m_highscores.contains(m_current_mouse_position) ) ? m_highscores.mouseOver() : m_highscores.mouseLeave();
    ( m_options.contains(m_current_mouse_position) ) ? m_options.mouseOver() : m_options.mouseLeave();
    ( m_controls.contains(m_current_mouse_position) ) ? m_controls.mouseOver() : m_controls.mouseLeave();
    ( m_quit.contains(m_current_mouse_position) ) ? m_quit.mouseOver() : m_quit.mouseLeave();

    // Update star animation
    m_star_anim.update(delta_time);
}

void HomeState::draw()
{
    m_window.clear();
    
    m_window.draw(m_background);
    m_window.draw(m_star_anim);

    m_window.draw(m_title);

    m_window.draw(m_start);
    m_window.draw(m_inventory);
    m_window.draw(m_market);
    m_window.draw(m_highscores);
    m_window.draw(m_options);
    m_window.draw(m_controls);
    m_window.draw(m_quit);

    m_window.display();
}
