#include <SFML/Graphics.hpp>

#include "HelpScreen.h"
#include "MenuScreen.h"

using namespace sfSnake;

HelpScreen::HelpScreen()
{
    font_.loadFromFile("Fonts/msyh.ttc");
    text_.setFont(font_);
    text_.setPosition(Game::Width / 5, Game::Height / 5);
    text_.setString(
        L"                                帮助文档\n"
        L"本游戏为贪吃蛇小游戏:\n"
        L"目标为在不碰触到蛇身的情况下尽量得到高分。\n"
        L"游戏可使用方向键“↑↓←→”进行经典操作，\n"
        L"使用wasd进行类似摇杆操作，\n"
        L"同时也可以用鼠标点击，\n"
        L"贪吃蛇将向鼠标位置移动。\n"
        L"按Q键可加快移动速度，按E键可减慢移动速度。\n"
        L"在游戏中可随时按ESC键暂停游戏，\n"
        L"暂停界面可以继续游戏、返回主菜单及重开游戏。\n"
        L"黑色、棕色球不计分，不增加长度，生成概率共25%，\n"
        L"蓝色球一分，增加一节长度，生成概率45%，\n"
        L"绿色球两分，增加两节长度，生成概率20%，\n"
        L"黄色球三分，增加三节长度，生成概率10%。\n");
    text_.setFillColor(sf::Color::Black);
    text_.setScale(1.5, 1.5);
    texture_.loadFromFile("Image/exit.png");
    button_ = Button(texture_, Game::Width / 10, Game::Height / 10);
}

void HelpScreen::handleInput(sf::RenderWindow &window)
{
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

void HelpScreen::update(sf::Time delta)
{
}

void HelpScreen::render(sf::RenderWindow &window)
{
    window.draw(text_);
    button_.render(window);
}