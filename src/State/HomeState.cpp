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
    , m_options{ "Options", resources, 30 }
    , m_controls{ "Controls", resources, 30 }
    , m_quit{ "Quit", resources, 30 }  
{
    const auto window_size = sf::Vector2f{ window.getSize() };

    m_background.setFillColor(sf::Color::Black);
    m_background.setSize(window_size);

    m_title = sf::Text("Space  Wars", resources.Zorque, 48);
    m_title.setLetterSpacing(4.f);
    m_title.setPosition( window_size.x/2.f - m_title.getGlobalBounds().width/2.f, window_size.y/6.f - m_title.getGlobalBounds().height/2.f );
    m_title.setFillColor(sf::Color::White);

    m_star_anim.setColor(sf::Color{255, 255, 255, 150});
    m_star_anim.setBounds(window_size);

    m_start.setPosition({window_size.x/2.f - m_start.getGlobalBounds().width/2.f, window_size.y/2.f - m_start.getGlobalBounds().height - 50.f});
    m_options.setPosition({window_size.x/2.f - m_options.getGlobalBounds().width/2.f, window_size.y/2.f - m_options.getGlobalBounds().height/2.f});
    m_controls.setPosition({window_size.x/2.f - m_controls.getGlobalBounds().width/2.f, window_size.y/2.f + 50.f});
    m_quit.setPosition({window_size.x/2.f - m_quit.getGlobalBounds().width/2.f, m_controls.getGlobalBounds().top + 50.f});
    
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
    m_window.draw(m_options);
    m_window.draw(m_controls);
    m_window.draw(m_quit);

    m_window.display();
}
