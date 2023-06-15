#include <SFML/Graphics.hpp>

#include "PauseScreen.h"
#include "MenuScreen.h"

using namespace sfSnake;
PauseScreen::PauseScreen()
{
    continue_texture_.loadFromFile("Image/Launch.png");
    home_texture_.loadFromFile("Image/Home.png");
    retry_texture_.loadFromFile("Image/Retry.png");
    continue_button_ = Button(continue_texture_, Game::Width * 2 / 7, Game::Height * 4 / 7);
    home_button_ = Button(home_texture_, Game::Width * 3.5 / 7, Game::Height * 4 / 7);
    retry_button_ = Button(retry_texture_, Game::Width * 5 / 7, Game::Height * 4 / 7);
    // text initial
    font_.loadFromFile("Fonts/HYHuaMuLanW.ttf");
    text_.setFont(font_);
    text_.setString(L"暂 停");
    text_.setScale(6, 6);
    text_.setFillColor(sf::Color::White);
    text_.setOutlineColor(sf::Color::Black);
    text_.setOutlineThickness(2);
    text_.setPosition(Game::Width / 2 - text_.getGlobalBounds().width / 2, Game::Height / 7);
}
void PauseScreen::handleInput(sf::RenderWindow &window)
{
    // Highlight
    if (continue_button_.getBound().contains(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y))
        continue_button_.Highlight();
    else
        continue_button_.deHighlight();

    if (home_button_.getBound().contains(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y))
        home_button_.Highlight();
    else
        home_button_.deHighlight();

    if (retry_button_.getBound().contains(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y))
        retry_button_.Highlight();
    else
        retry_button_.deHighlight();

    // Pressed
    if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && continue_button_.getBound().contains(
                                                           sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y))
    {
        Game::Screen_ = Game::Paused_Screen;
        Game::Paused_Screen = nullptr;
    }

    if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && home_button_.getBound().contains(
                                                           sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y))
    {
        Game::Screen_ = std::make_shared<MenuScreen>();
        Game::Paused_Screen = nullptr;
    }

    if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && retry_button_.getBound().contains(
                                                           sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y))
    {
        Game::Screen_ = std::make_shared<GameScreen>();
        Game::Paused_Screen = nullptr;
    }
}
void PauseScreen::update(sf::Time delta)
{
}
void PauseScreen::render(sf::RenderWindow &window)
{
    if (Game::Paused_Screen)
        Game::Paused_Screen->render(window);
    else
    {
        Game::Screen_->render(window);
        return;
    }
    window.draw(text_);
    continue_button_.render(window);
    home_button_.render(window);
    retry_button_.render(window);
}