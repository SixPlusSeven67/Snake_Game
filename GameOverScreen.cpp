#include <SFML/Graphics.hpp>

#include <iostream>
#include <memory>

#include "Game.h"
#include "MenuScreen.h"
#include "GameScreen.h"
#include "GameOverScreen.h"

using namespace sfSnake;

GameOverScreen::GameOverScreen(std::size_t score) : score_(score)
{
	font_.loadFromFile("Fonts/HYWenHei.ttf");
	text_.setFont(font_);
	text_.setString(L"你的最终得分：" + std::to_wstring(score) + L"\n\n\n按[ESC]退出游戏");
	text_.setScale(2.5, 2.5);
	text_.setFillColor(sf::Color::Red);

	sf::FloatRect textBounds = text_.getLocalBounds();
	text_.setOrigin(textBounds.left + textBounds.width / 2,
					textBounds.top + textBounds.height / 2);
	text_.setPosition(Game::Width / 2, Game::Height / 3);

	RetryTexture_.loadFromFile("Image/retry.png");
	RetryButton_ = Button(RetryTexture_, Game::Width * 2 / 5 - RetryTexture_.getSize().x / 2, Game::Height * 2 / 3 - RetryTexture_.getSize().y / 2);
	HomeTexture_.loadFromFile("Image/home.png");
	HomeButton_ = Button(HomeTexture_, Game::Width * 3 / 5 - HomeTexture_.getSize().x / 2, Game::Height * 2 / 3 - HomeTexture_.getSize().y / 2);
}

void GameOverScreen::handleInput(sf::RenderWindow &window)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
		window.close();
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		if (RetryButton_.getBound().contains(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y))
			Game::Screen_ = std::make_shared<GameScreen>();
	}
	if (RetryButton_.getBound().contains(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y))
		RetryButton_.Highlight();
	else
		RetryButton_.deHighlight();

	if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		if (HomeButton_.getBound().contains(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y))
			Game::Screen_ = std::make_shared<MenuScreen>();
	}
	if (HomeButton_.getBound().contains(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y))
		HomeButton_.Highlight();
	else
		HomeButton_.deHighlight();
}

void GameOverScreen::update(sf::Time delta)
{
}

void GameOverScreen::render(sf::RenderWindow &window)
{
	window.draw(text_);
	RetryButton_.render(window);
	HomeButton_.render(window);
}