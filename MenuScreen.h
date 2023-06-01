#ifndef MENU_SCREEN_H
#define MENU_SCREEN_H

#include <SFML/Graphics.hpp>

#include "Screen.h"
#include "Button.h"
#include "Grid.h"

namespace sfSnake
{
	class MenuScreen : public Screen
	{
	public:
		MenuScreen();

		void handleInput(sf::RenderWindow &window) override;
		void update(sf::Time delta) override;
		void render(sf::RenderWindow &window) override;

	private:
		Button buttons_[3];
		sf::Texture texture_[3];
		Grid grid_;
		sf::Texture Title_Texture_;
		sf::Sprite Title_;
	};
}

#endif