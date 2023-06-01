#include <SFML/Graphics.hpp>

#include "Button.h"

using namespace sfSnake;

const float Button::Radius = 200.f;
Button::Button(sf::Texture &texture, float x, float y) : position_{x, y}
{
    shape_.setTexture(texture);
    shape_.setOrigin(texture.getSize().x / 2, texture.getSize().y / 2);
    shape_.setPosition(x, y);
    shape_.setScale(Button::Radius / texture.getSize().x, Button::Radius / texture.getSize().y);
}

void Button::Highlight()
{
    shape_.setColor(sf::Color(255, 254, 145));
}

void Button::deHighlight()
{
    shape_.setColor(sf::Color::White);
}

void Button::setPosition(sf::Vector2f &position)
{
    shape_.setPosition(position);
}

sf::Vector2f Button::getPosition() const
{
    return position_;
}

sf::FloatRect Button::getBound() const
{
    return shape_.getGlobalBounds();
}

Button::Button() : position_{0, 0}
{
}

void Button::render(sf::RenderWindow &window)
{
    window.draw(shape_);
}