#pragma once

#include "Entity/Base/Entity.hpp"
#pragma once

struct Resources;

class Button final : public Entity
{
public:
    Button(const std::string& text, const Resources& resources, unsigned int fontSize = 30);

    void update(sf::Time delta_time) override;
    sf::FloatRect getGlobalBounds() const;

    void mouseOver();
    void mouseLeave();

    void setFillColor(const sf::Color& color);
    void setOutlineColor(const sf::Color& color);

    bool contains(const sf::Vector2f& point);

protected:
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

private:
    sf::Text m_text;
    sf::Color m_fillColor;
    sf::Color m_outlineColor;
};