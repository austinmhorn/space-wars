#ifndef Ship_hpp
#define Ship_hpp

#include "Base/Entity.hpp"

struct Resources;

class Ship 
    : public Entity
{
    public:
        Ship();
        virtual ~Ship() = default;

        sf::Sprite& operator()() 
        {
            return m_base_sprite;
        }

        void handleEvent(sf::RenderWindow &window, sf::Event event);

        virtual void update(sf::Time delta_time) override;

    protected:

        void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

    private:

        struct Movement
        {
            
        };

        sf::Texture  m_base_texture; 
        sf::Sprite   m_base_sprite;
};

#endif /* Ship_hpp */