#include "Core/Application.hpp"

int main(int arc, const char **argv) 
{
    auto app = Application{800, 600, "SpaceWars"};
    app.run();


    return 0;
}