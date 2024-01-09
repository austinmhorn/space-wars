#ifndef Assets_hpp
#define Assets_hpp

#include <SFML/Graphics.hpp>

#include <iostream>   // std::cin, std::cout
#include <new>        // std::bad_alloc
#include <cmath>      // std::ceil, std::log
#include <map>        
#include <cassert>    // assert

#include "Core/Sansation.hpp"


// Images
static const std::string __filepath_ship_base_pristine = "assets/png/ship/base/pristine.png";

// Fonts
static const std::string __filepath_zorque = "assets/fonts/Zorque.otf";


static const sf::Font load_zorque()
{
    sf::Font font;
    try 
    {
        if ( !font.loadFromFile(__filepath_zorque) )
            throw std::runtime_error("Failed loading font: ");
        else
            std::cout << "Loaded font: " << __filepath_zorque << std::endl;
    }
    catch(const std::runtime_error &e) 
    {
        std::cerr << "std::runtime_error::what(): " << e.what() << __filepath_zorque << std::endl;
    }
    return font;
}

////////////////////////////////////////////////////////////
/// \namespace Textures
///
/// \brief
////////////////////////////////////////////////////////////
namespace Textures 
{
    static sf::Texture __load_ship_base_pristine_texture() 
    {
        static sf::Texture texture;
        try 
        {
            if ( !texture.loadFromFile(__filepath_ship_base_pristine) )
                throw std::runtime_error("Failed loading texture: ");
            else
                std::cout << "Loaded image: " << __filepath_ship_base_pristine << std::endl;
        }
        catch(const std::runtime_error &e) 
        {
            std::cerr << "std::runtime_error::what(): " << e.what() << __filepath_ship_base_pristine << std::endl;
        }
        return texture;
    }
} // MARK: End of namespace 'Textures'

struct Resources
{
    static const sf::Font Sansation;
    static const sf::Font Zorque;
    
    static const sf::Color Gray;
    static const sf::Color DarkGreen;
    static const sf::Color DarkRed;
    static const sf::Color DarkPurple;
    static const sf::Color LightBlue;
    static const sf::Color Seafoam;
    static const sf::Color LightGreen;
    static const sf::Color Peach;
    static const sf::Color Tan;
    static const sf::Color Pink;
    static const sf::Color LightPurple;
    static const sf::Color Orange;
    static const sf::Color DarkBlue;
};

#endif /* Assets_hpp */
