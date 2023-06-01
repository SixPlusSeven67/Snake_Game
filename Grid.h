#ifndef GRID_H
#define GRID_H

#include <SFML/Graphics.hpp>

#include <vector>

#include "Game.h"

namespace sfSnake
{

    class Grid
    {
    public:
        Grid();

        void setFillColor();

        void render(sf::RenderWindow &window);

        static const unsigned Length = 4;
        static const unsigned Space = 60;

    private:
        std::vector<sf::RectangleShape> Grid_x;
        std::vector<sf::RectangleShape> Grid_y;
    };

}

#endif
