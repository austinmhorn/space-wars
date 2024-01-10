#ifndef Ship_hpp
#define Ship_hpp

#include "Base/Entity.hpp"
#include "Base/Animation.hpp"

#include "Entity/AutoCannon.hpp"

struct Resources;

class Ship 
    : public Entity
{
    public:

        enum class State : unsigned
        {
            IDLE = 0,
            POWERED = 1
        };

        Ship();
        virtual ~Ship() = default;

        sf::Sprite& operator()() 
        {
            return m_base_sprite;
        }

        void setScale(const sf::Vector2f& scale);

        void setBounds(const sf::Vector2f& bounds);
        void setPosition(const sf::Vector2f& position);

        void updateCollisions();
        void updateMovement(float elapsed);
        void updatePhysics();
        void updateSprites();
        void updateAnimations(float elapsed);
        
        void fireAutoCannon();

        virtual void update(sf::Time delta_time) override;

    protected:

        void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

    private:

        void __init_animations();

        Animation  m_curr_engine_effects_anim;
        Animation  m_engine_effects_idle_anim;
        Animation  m_engine_effects_powered_anim;
        State      m_engine_effects_last_state;
        State      m_engine_effects_curr_state;

        sf::Vector2f m_bounds;

        sf::Vector2f m_velocity;
        sf::Vector2f m_max_velocity;
        float        m_acceleration;

        sf::Texture  m_base_texture; 
        sf::Sprite   m_base_sprite;
        sf::Texture  m_engine_texture;
        sf::Sprite   m_engine_sprite;
        sf::Texture  m_engine_effects_texture_sheet;
        sf::Sprite   m_engine_effects_sprite;
        bool         m_engine_on;

        AutoCannon  m_cannon;
        bool        m_can_fire_auto_cannon;

        sf::Vector2f  m_scale;
};

#endif /* Ship_hpp */