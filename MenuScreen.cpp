#include <SFML/Graphics.hpp>

#include <memory>

#include "GameScreen.h"
#include "MenuScreen.h"
#include "HelpScreen.h"
#include "OptionScreen.h"
#include "Game.h"

using namespace sfSnake;

MenuScreen::MenuScreen()
{
	// Head Title : Welcome! Initialize
	Title_Texture_.loadFromFile("Image/Welcome.png");
	Title_.setTexture(Title_Texture_);
	Title_.setScale(3, 3);
	Title_.setOrigin(Title_Texture_.getSize().x / 2, Title_Texture_.getSize().y / 2);
	Title_.setPosition(Game::Width / 2, Game::Height / 5);

	// Button Initialize

	texture_[0].loadFromFile("Image/settings.png");
	texture_[1].loadFromFile("Image/launch.png");
	texture_[2].loadFromFile("Image/helps.png");

	buttons_[0] = Button(texture_[0], Game::Width * 2 / 6, Game::Height * 3 / 5);
	buttons_[1] = Button(texture_[1], Game::Width * 3 / 6, Game::Height * 3 / 5);
	buttons_[2] = Button(texture_[2], Game::Width * 4 / 6, Game::Height * 3 / 5);

	// Grid Initialize
}

void MenuScreen::handleInput(sf::RenderWindow &window)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
		window.close();
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		if (buttons_[0].getBound().contains(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y))
			Game::Screen_ = std::make_shared<OptionScreen>();
		else if (buttons_[1].getBound().contains(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y))
			Game::Screen_ = std::make_shared<GameScreen>();
		else if (buttons_[2].getBound().contains(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y))
			Game::Screen_ = std::make_shared<HelpScreen>();
	}
	if (buttons_[0].getBound().contains(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y))
		buttons_[0].Highlight();
	else
		buttons_[0].deHighlight();
	if (buttons_[1].getBound().contains(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y))
		buttons_[1].Highlight();
	else
		buttons_[1].deHighlight();
	if (buttons_[2].getBound().contains(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y))
		buttons_[2].Highlight();
	else
		buttons_[2].deHighlight();
}

void MenuScreen::update(sf::Time delta)
{
}
void MenuScreen::render(sf::RenderWindow &window)
{
	if (Game::isGridVisible)
		grid_.render(window);
	window.draw(Title_);
	for (auto &button : buttons_)
		button.render(window);
}