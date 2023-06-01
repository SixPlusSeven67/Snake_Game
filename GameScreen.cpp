#include <SFML/Graphics.hpp>

#include <random>
#include <memory>
#include <string>

#include "GameScreen.h"
#include "GameOverScreen.h"
#include "Game.h"

using namespace sfSnake;

GameScreen::GameScreen() : snake_()
{
	sf::sleep(sf::milliseconds(300));
	font_.loadFromFile("Fonts/HYWenHei.ttf");
	text_.setFont(font_);
	text_.setString(L"得分：");
	text_.setFillColor(sf::Color::Red);

	sf::FloatRect textBounds = text_.getLocalBounds();
	text_.setOrigin(textBounds.left + textBounds.width / 2,
					textBounds.top + textBounds.height / 2);
	text_.setPosition(Game::Width / 2, textBounds.height / 2);
}

void GameScreen::handleInput(sf::RenderWindow &window)
{
	snake_.handleInput(window);
}

void GameScreen::update(sf::Time delta)
{
	static sf::Time timeSinceLastGenerate{sf::Time::Zero};
	timeSinceLastGenerate += delta;
	if (fruit_.size() == 0 || fruit_.size() < 12 && timeSinceLastGenerate.asSeconds() > 1)
	{
		timeSinceLastGenerate = delta;
		generateFruit();
	}
	snake_.update(delta);
	snake_.checkFruitCollisions(fruit_);
	text_.setString(L"得分：" + std::to_wstring(snake_.getScore()));

	if (snake_.hitSelf())
		Game::Screen_ = std::make_shared<GameOverScreen>(snake_.getScore());
}

void GameScreen::render(sf::RenderWindow &window)
{
	if (Game::isGridVisible)
		grid_.render(window);
	snake_.render(window);

	for (auto fruit : fruit_)
		fruit.render(window);
	window.draw(text_);
}

void GameScreen::generateFruit()
{
	static std::random_device rd;
	static std::mt19937 engine(rd());
	static std::uniform_int_distribution<int> xDistribution(Game::Width / 100, Game::Width * 99 / 100);
	static std::uniform_int_distribution<int> yDistribution(Game::Height / 100, Game::Height * 99 / 100);

	fruit_.push_back(Fruit(sf::Vector2f(xDistribution(engine), yDistribution(engine))));
}
