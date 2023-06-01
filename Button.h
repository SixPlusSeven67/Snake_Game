#ifndef BUTTON_H
#define BUTTON_H

#include <SFML/Graphics.hpp>

#include <string>

namespace sfSnake
{
    class Button
    {
    public:
        Button();
        Button(sf::Texture &, float, float);

        void Highlight();
        void deHighlight();
        void setPosition(sf::Vector2f &);

        sf::Vector2f getPosition() const;
        sf::FloatRect getBound() const;

        void render(sf::RenderWindow &window);

        static const float Radius;

    private:
        sf::Sprite shape_;
        sf::Vector2f position_;
    };
}

#endif