#include <SFML/Window/Window.hpp>
#include <SFML/Window/Event.hpp>

#include "State/PlayState.hpp"
#include "State/PauseState.hpp"
#include "Core/StateMachine.hpp"
#include "Core/Resources.hpp"

#include <iostream>
#include <memory>
#include <random>

PlayState::PlayState(StateMachine& machine, sf::RenderWindow& window, Resources& resources, const bool replace)
    : State{ machine, window, resources, replace }
{
    const auto window_size = sf::Vector2f{ window.getSize() };

    m_background.setFillColor(sf::Color::Black);
    m_background.setSize(window_size);

    m_star_anim.setColor(sf::Color{255, 255, 255, 150});
    m_star_anim.setBounds(window_size);

    m_player.setScale({window_size.y/400.f, window_size.y/400.f});
    m_player.setMaxVelocity({window_size.x/576.f, window_size.x/576.f});
    m_player.setBounds(window_size);
    m_player.setPosition({window_size.x/2.f - m_player().getGlobalBounds().width/2.f, window_size.y});
}

PlayState::~PlayState()
{
    for (auto& asteroid : m_asteroids)
        delete asteroid;
}

void PlayState::pause()
{
    //std::cout << "PlayState Pause" << std::endl;;
}

void PlayState::resume()
{
    //std::cout << "PlayState Resume" << std::endl;;
}

void PlayState::handleEvent()
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
                break;
                
            case sf::Event::KeyPressed:
                if (event.key.code == sf::Keyboard::Key::Escape) 
                    m_next = StateMachine::build<PauseState>(m_machine, m_window, m_resources, false); // Move to PauseState
                else if (event.key.code == sf::Keyboard::Key::Space) 
                    m_space_key_pressed = true;

                ///< MARK: Asteroid test code
                ///< Press 'A' key to spawn asteroid
                if (event.key.code == sf::Keyboard::Key::A)
                {
                    Asteroid* asteroid = new Asteroid;

                    const auto window_size = sf::Vector2f{ m_window.getSize() };
                    std::random_device rseed; std::mt19937 rng(rseed());
                    std::uniform_int_distribution<int> dist_x_pos(0, m_window.getSize().x - 92.f);
                    std::uniform_int_distribution<int> dist_y_pos(0, m_window.getSize().y - 92.f);
                    std::uniform_real_distribution<double> dist_x_vel(-1.25f, 1.25f);
                    std::uniform_real_distribution<double> dist_y_vel(2.25f, 9.5f);

                    asteroid->setPosition( {static_cast<float>(dist_x_pos(rng)), -50.f} );
                    asteroid->setVelocity( {static_cast<float>(dist_x_vel(rng)), static_cast<float>(dist_y_vel(rng))} );
                    asteroid->setBounds( {window_size.x, window_size.y - 300.f} );        
            
                    m_asteroids.push_back(asteroid);
                }
                break;
                
            case sf::Event::KeyReleased:
                if (event.key.code == sf::Keyboard::Key::Space)
                    m_space_key_pressed = false;
                break;

            case sf::Event::TextEntered:
                break;
                
            default:
                break;
        }
    }
}

void PlayState::update()
{
    static const auto clock = sf::Clock{};
    static auto last_frame_time = sf::Time{};
    const auto delta_time = clock.getElapsedTime() - last_frame_time;
    last_frame_time = clock.getElapsedTime();
    
    handleEvent();

    // Update background star animation
    m_star_anim.update(delta_time);

    // Update player
    m_player.update(delta_time);

    // Update asteroids and sort for priority
    for (std::size_t i = 0; i < m_asteroids.size(); i++)
    {
        if ( m_asteroids[i] )
        {
            m_asteroids[i]->update(delta_time);

            if ( m_asteroids[i]->explodeAnimationComplete() )
            {
                std::swap(m_asteroids[i], m_asteroids.back());
                m_asteroids.pop_back();
            }
        }
    }
}

void PlayState::draw()
{
    m_window.clear();
    
    m_window.draw(m_background);

    m_window.draw(m_star_anim);

    for (std::size_t i = 0; i < m_asteroids.size(); i++)
        if ( m_asteroids[i] )
            m_window.draw( *m_asteroids[i] );

    m_window.draw(m_player);

    m_window.display();
}
