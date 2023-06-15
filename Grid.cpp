#include <SFML/Graphics.hpp>

#include "Grid.h"

using namespace sfSnake;

Grid::Grid()
{
    for (int i = 0; i < Game::Height / Grid::Space; ++i)
    {
        Grid_x.emplace_back(sf::RectangleShape(sf::Vector2f(Game::Width, Grid::Length)));
        Grid_x[i].setPosition(0, Grid::Space * (i + 1));
        Grid_x[i].setFillColor(Game::Grid_Color);
    }

    for (int i = 0; i < Game::Width / Grid::Space; ++i)
    {
        Grid_y.emplace_back(sf::RectangleShape(sf::Vector2f(Grid::Length, Game::Height)));
        Grid_y[i].setPosition(Grid::Space * (i + 1), 0);
        Grid_y[i].setFillColor(Game::Grid_Color);
    }
}

void Grid::setFillColor()
{
    for (auto &grid : Grid_x)
        grid.setFillColor(Game::Grid_Color);
    for (auto &grid : Grid_y)
        grid.setFillColor(Game::Grid_Color);
}

void Grid::render(sf::RenderWindow &window)
{
    for (auto &grid : Grid_x)
        window.draw(grid);

    for (auto &grid : Grid_y)
        window.draw(grid);
}
