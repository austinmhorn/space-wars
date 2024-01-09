#ifndef Application_hpp
#define Application_hpp

#include <SFML/Graphics/RenderWindow.hpp>

#include "StateMachine.hpp"
#include "Resources.hpp"
#include "SystemInfo.hpp"
#include "State/HomeState.hpp"

class Application
{
public:
    
    Application(unsigned int window_width, unsigned int window_height, const std::string& title, sf::Uint32 style=sf::Style::Default, const sf::ContextSettings& settings=sf::ContextSettings());
    virtual ~Application() = default;
    
    Application(const Application&) = delete;
    Application& operator=(const Application&) = delete;
    
    Application(Application&&) noexcept = delete;
    Application& operator=(Application&&) noexcept = delete;

    virtual void init();
    virtual void run();
    
protected:
    
    virtual void loadResources();

private:

    StateMachine     m_machine;
    sf::RenderWindow m_window;
    Resources        m_resources;
};

#endif /* Application_hpp */