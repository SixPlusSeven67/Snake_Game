#include <SFML/Graphics.hpp>

#include <memory>

#include "MenuScreen.h"
#include "Game.h"

using namespace sfSnake;

sf::Time Game::TimePerFrame = sf::seconds(1.f / 10.f);
sf::Color Game::Grid_Color = sf::Color(200, 200, 200);
sf::Color Game::Back_Color = sf::Color(250, 250, 250);
bool Game::isGridVisible = true;

std::shared_ptr<Screen> Game::Screen_ = std::make_shared<MenuScreen>();
std::shared_ptr<Screen> Game::Temp_Screen = nullptr;

Game::Game() : window_(sf::VideoMode(Game::Width, Game::Height), "sfSnake", sf::Style::Close)

{
	window_.setVerticalSyncEnabled(true);
	bgMusic_.openFromFile("Music/bg_music.wav");
	bgMusic_.setLoop(true);
	bgMusic_.play();
}

void Game::handleInput()
{
	sf::Event event;

	while (window_.pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
			window_.close();
	}
	if (window_.hasFocus() && sf::FloatRect(sf::Vector2f(0, 0), sf::Vector2f(Game::Width, Game::Height))
								  .contains(static_cast<sf::Vector2f>(sf::Mouse::getPosition(window_))))
		Game::Screen_->handleInput(window_);
}

void Game::update(sf::Time delta)
{
	Game::Screen_->update(delta);
}

void Game::render(std::shared_ptr<Screen> in_Screen_)
{
	window_.clear(Game::Back_Color);
	in_Screen_->render(window_);
	window_.display();
}

void Game::run()
{
	sf::Clock clock;
	sf::Time timeSinceLastUpdate = sf::Time::Zero;

	while (window_.isOpen())
	{
		sf::Time delta = clock.restart();
		timeSinceLastUpdate += delta;
		Temp_Screen = Screen_;
		while (timeSinceLastUpdate > Game::TimePerFrame)
		{
			timeSinceLastUpdate -= TimePerFrame;
			handleInput();
			update(TimePerFrame);
		}
		if (Temp_Screen != Screen_)
		{
			render(Temp_Screen);
			sf::sleep(sf::milliseconds(200));
		}
		else
			render(Screen_);
	}
}
