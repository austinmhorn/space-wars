#include "Entity/Button.hpp"

#include <cmath>

#include "Core/Resources.hpp"

Button::Button(const std::string& text, const Resources& resources, unsigned int fontSize)
    : m_text{ text, resources.Zorque, fontSize }
{
    m_text.setFillColor(sf::Color{ 0xDDDDDDFF });
    m_text.setLetterSpacing(2.f);
}

void Button::update(sf::Time delta_time)
{
}

sf::FloatRect Button::getGlobalBounds() const
{
    return getTransform().transformRect(m_text.getGlobalBounds());
}

void Button::mouseOver()
{
    m_text.setOutlineColor(sf::Color{ sf::Color::Blue });
    m_text.setOutlineThickness(1.f);
}

void Button::mouseLeave()
{
    m_text.setFillColor(sf::Color{ 0xFFFFFFFF });
    m_text.setOutlineThickness(0.f);
}

bool Button::contains(const sf::Vector2f& point)
{
    return getGlobalBounds().contains(point);
}

void Button::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    states.transform *= getTransform();
    target.draw(m_text, states);
}
