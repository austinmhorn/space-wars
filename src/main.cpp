#include "Core/Application.hpp"
#include "Core/SystemInfo.hpp"

int main(int arc, const char **argv) 
{
    unsigned int window_width = 0;
    unsigned int window_height = 0;
    getScreenResolution(window_width, window_height);
    //std::cout << window_width << ", " << window_height << std::endl;

    

    auto app = Application{window_width, window_height, "SpaceWars", sf::Style::Close};
    app.run();


    return 0;
}