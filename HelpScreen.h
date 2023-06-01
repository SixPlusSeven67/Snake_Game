#ifndef HELP_SCREEN_H
#define HELP_SCREEN_H

#include <SFML/Graphics.hpp>

#include "Screen.h"
#include "Button.h"

namespace sfSnake
{
    class HelpScreen : public Screen
    {
    public:
        HelpScreen();

        void handleInput(sf::RenderWindow &window) override;
        void update(sf::Time delta) override;
        void render(sf::RenderWindow &window) override;

    private:
        sf::Font font_;
        sf::Text text_;
        sf::Texture texture_;
        Button button_;
    };
}

#endif