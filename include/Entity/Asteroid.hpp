#ifndef Asteroid_hpp
#define Asteroid_hpp

#include "Entity/Base/Entity.hpp"
#include "Entity/Base/Animation.hpp"

class Asteroid
    : public Entity
{
    public:

        Asteroid();
        
        void setPosition(const sf::Vector2f& position);
        const sf::Vector2f& getPosition() const;

        void setVelocity(const sf::Vector2f& velocity);
        const sf::Vector2f& getVelocity() const;

        void setBounds(const sf::Vector2f& bounds);

        bool explodeAnimationComplete() const;


        void update(sf::Time delta_time) override;
        void updateCollisions();
        void updateMovement(float elapsed);


        void explode();
        bool isExploding() const;

    protected:

        void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

    private:

        void __init_animations();

        static const sf::Texture m_texture;
        sf::Sprite   m_sprite;

        Animation  m_explode_anim;
        bool       m_exploding : 1;
        bool       m_finished_exploding : 1;

        unsigned  m_rotational_speed;
        sf::Vector2f  m_velocity;
        sf::Vector2f  m_max_velocity;
        float         m_acceleration;
        
        sf::Vector2f  m_bounds;
};

#endif /* Asteroid_hpp */