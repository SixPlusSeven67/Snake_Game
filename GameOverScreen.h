#ifndef GAME_OVER_SCREEN_H
#define GAME_OVER_SCREEN_H

#include <SFML/Graphics.hpp>

#include "Screen.h"
#include "Button.h"

namespace sfSnake
{
	class GameOverScreen : public Screen
	{
	public:
		GameOverScreen(std::size_t score);

		void handleInput(sf::RenderWindow &window) override;
		void update(sf::Time delta) override;
		void render(sf::RenderWindow &window) override;

	private:
		sf::Font font_;
		sf::Text text_;

		sf::Texture RetryTexture_;
		Button RetryButton_;
		sf::Texture HomeTexture_;
		Button HomeButton_;

		unsigned score_;
	};
}

#endif