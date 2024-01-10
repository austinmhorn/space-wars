#ifndef AutoCannon_hpp
#define AutoCannon_hpp

#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/System/Clock.hpp>

#include "Entity/Base/Entity.hpp"
#include "Entity/Base/Animation.hpp"

#include <queue>

#define AUTO_CANNON_AMMO_SIZE 10

class AutoCannon
    : public Entity
{
    public:

        class Bullet;

        AutoCannon();
        virtual ~AutoCannon();

        void update(sf::Time delta_time) override;

        void setScale(const sf::Vector2f& scale);
        void setPosition(const sf::Vector2f& position);

        void fire();

        bool canStopAnimation();

    protected:

        void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

    private:

        void fireLeftCannon();
        void fireRightCannon();
        void updateAnimations(float elapsed);

        void __init_animations();

        sf::Texture  m_texture;
        sf::Sprite   m_sprite; 

        Animation  m_shoot_anim;
        bool       m_shooting;
        bool       m_left_cannon_fired : 1;
        bool       m_right_cannon_fired : 1;

        sf::Texture  m_bullet_texture_sheet;

        std::vector<Bullet*> m_bullets_loaded;
        std::vector<Bullet*> m_bullets_active;

        sf::Vector2f m_scale;

};





class AutoCannon::Bullet
    : public Entity
{
    public:

        Bullet(const sf::Texture* texture = nullptr);
        void update(sf::Time delta_time) override;

        void setScale(const sf::Vector2f& scale);
        void setPosition(const sf::Vector2f& position);
        const sf::Vector2f& getPosition() const;

        sf::FloatRect getGlobalBounds() const;
        void updateMovement(float elapsed);
        void updatePhysics();

        void reset();

    protected:

        void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

    private:

        void __init_animations();
        void updateAnimations(float elapsed);

        const sf::Texture*  m_texture;
        sf::Sprite          m_sprite;

        Animation  m_anim;

        sf::Vector2f  m_velocity;
        sf::Vector2f  m_max_velocity;
        float         m_acceleration;
};


#endif /* AutoCannon_hpp */