#ifndef OPTION_SCREEN_H
#define OPTION_SCREEN_H

#include <SFML/Graphics.hpp>

#include "Screen.h"
#include "Grid.h"
#include "Button.h"

namespace sfSnake
{
    class OptionScreen : public Screen
    {
    public:
        OptionScreen();

        void handleInput(sf::RenderWindow &window) override;
        void update(sf::Time delta) override;
        void render(sf::RenderWindow &window) override;

    private:
        sf::Font font_;
        sf::Text texts_[12];
        sf::Texture button_texture;
        Button button_;
        Grid grid_;
    };
}

#endif