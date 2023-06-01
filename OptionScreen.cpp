#include <SFML/Graphics.hpp>

#include <memory>

#include "OptionScreen.h"
#include "MenuScreen.h"
#include "Game.h"

using namespace sfSnake;

OptionScreen::OptionScreen()
{
    // 文本初始化
    font_.loadFromFile("Fonts/SmileySans-Oblique.ttf");
    texts_[0] = sf::Text(L"网格：", font_, 50U);
    texts_[1] = sf::Text(L"开启", font_, 50U);
    texts_[2] = sf::Text(L"关闭", font_, 50U);
    texts_[4] = sf::Text(L"网格颜色：", font_, 50U);
    texts_[5] = sf::Text(L"黑", font_, 50U);
    texts_[6] = sf::Text(L"棕", font_, 50U);
    texts_[7] = sf::Text(L"白", font_, 50U);
    texts_[8] = sf::Text(L"背景颜色：", font_, 50U);
    texts_[9] = sf::Text(L"黑", font_, 50U);
    texts_[10] = sf::Text(L"棕", font_, 50U);
    texts_[11] = sf::Text(L"白", font_, 50U);
    for (int i = 0; i < 3; ++i)
        for (int j = 0; j < 4; ++j)
        {
            texts_[i * 4 + j].setPosition(Game::Width * (j + 1) / 5, Game::Height * (i + 1) / 4);
            texts_[i * 4 + j].setFillColor(sf::Color::White);
            texts_[i * 4 + j].setOutlineColor(sf::Color::Black);
            texts_[i * 4 + j].setOutlineThickness(2);
        }
    // 默认网格开启
    if (Game::isGridVisible) // if Open
    {
        texts_[1].setStyle(sf::Text::Underlined);
        texts_[1].setFillColor(sf::Color::Yellow);
    }
    else // if Close
    {
        texts_[2].setStyle(sf::Text::Underlined);
        texts_[2].setFillColor(sf::Color::Yellow);
    }

    // 默认网格颜色：白
    if (Game::Grid_Color == sf::Color(128, 128, 128)) // if Black
    {
        texts_[5].setStyle(sf::Text::Underlined);
        texts_[5].setFillColor(sf::Color::Yellow);
    }
    else if (Game::Grid_Color == sf::Color(120, 65, 20)) // if Brown
    {
        texts_[6].setStyle(sf::Text::Underlined);
        texts_[6].setFillColor(sf::Color::Yellow);
    }
    else if (Game::Grid_Color == sf::Color(200, 200, 200)) // if White
    {
        texts_[7].setStyle(sf::Text::Underlined);
        texts_[7].setFillColor(sf::Color::Yellow);
    }

    // 默认背景颜色：白

    if (Game::Back_Color == sf::Color(64, 64, 64)) // if Black
    {
        texts_[9].setStyle(sf::Text::Underlined);
        texts_[9].setFillColor(sf::Color::Yellow);
    }
    else if (Game::Back_Color == sf::Color(150, 85, 30)) // if Brown
    {
        texts_[10].setStyle(sf::Text::Underlined);
        texts_[10].setFillColor(sf::Color::Yellow);
    }
    else if (Game::Back_Color == sf::Color(250, 250, 250)) // if White
    {
        texts_[11].setStyle(sf::Text::Underlined);
        texts_[11].setFillColor(sf::Color::Yellow);
    }

    // 返回按钮初始化
    button_texture.loadFromFile("Image/exit.png");
    button_ = Button(button_texture, Game::Width / 10, Game::Height / 10);
}

void OptionScreen::handleInput(sf::RenderWindow &window)
{
    // 文本输出处理

    // Highlight
    for (int i = 0; i < 12; ++i)
        if (texts_[i].getGlobalBounds().contains(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y))
            texts_[i].setOutlineColor(sf::Color::Magenta);
        else
            texts_[i].setOutlineColor(sf::Color::Black);
    // Selected
    if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
    {
        for (int i = 1; i < 3; ++i)
            if (texts_[i].getGlobalBounds().contains(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y))
            {
                for (int j = 1; j < 3; ++j)
                {
                    texts_[j].setStyle(sf::Text::Regular);
                    texts_[j].setFillColor(sf::Color::White);
                }

                texts_[i].setStyle(sf::Text::Underlined);
                texts_[i].setFillColor(sf::Color::Yellow);
            }
        for (int i = 5; i < 8; ++i)
            if (texts_[i].getGlobalBounds().contains(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y))
            {
                for (int j = 5; j < 8; ++j)
                {
                    texts_[j].setStyle(sf::Text::Regular);
                    texts_[j].setFillColor(sf::Color::White);
                }

                texts_[i].setStyle(sf::Text::Underlined);
                texts_[i].setFillColor(sf::Color::Yellow);
            }
        for (int i = 9; i < 12; ++i)
            if (texts_[i].getGlobalBounds().contains(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y))
            {
                for (int j = 9; j < 12; ++j)
                {
                    texts_[j].setStyle(sf::Text::Regular);
                    texts_[j].setFillColor(sf::Color::White);
                }

                texts_[i].setStyle(sf::Text::Underlined);
                texts_[i].setFillColor(sf::Color::Yellow);
            }
    }

    // 按钮输入处理
    // Highlight
    if (button_.getBound().contains(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y))
        button_.Highlight();
    else
        button_.deHighlight();

    // Pressed
    if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && button_.getBound().contains(
                                                           sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y))
        Game::Screen_ = std::make_shared<MenuScreen>();
}

void OptionScreen::update(sf::Time delta)
{
    if (texts_[1].getFillColor() == sf::Color::Yellow) // 开启
        Game::isGridVisible = true;
    if (texts_[2].getFillColor() == sf::Color::Yellow) // 关闭
        Game::isGridVisible = false;

    if (texts_[5].getFillColor() == sf::Color::Yellow) // 黑
        Game::Grid_Color = sf::Color(128, 128, 128);
    if (texts_[6].getFillColor() == sf::Color::Yellow) // 棕
        Game::Grid_Color = sf::Color(120, 65, 20);
    if (texts_[7].getFillColor() == sf::Color::Yellow) // 白
        Game::Grid_Color = sf::Color(200, 200, 200);
    grid_.setFillColor();

    if (texts_[9].getFillColor() == sf::Color::Yellow) // 黑
        Game::Back_Color = sf::Color(64, 64, 64);
    if (texts_[10].getFillColor() == sf::Color::Yellow) // 棕
        Game::Back_Color = sf::Color(150, 85, 30);
    if (texts_[11].getFillColor() == sf::Color::Yellow) // 白
        Game::Back_Color = sf::Color(250, 250, 250);
}

void OptionScreen::render(sf::RenderWindow &window)
{
    if (Game::isGridVisible)
        grid_.render(window);
    for (auto text : texts_)
        window.draw(text);
    button_.render(window);
}