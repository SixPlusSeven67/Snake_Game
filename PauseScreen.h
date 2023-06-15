#ifndef PAUSESCREEN_H
#define PAUSESCREEN_H

#include <SFML/Graphics.hpp>

#include "GameScreen.h"
#include "Button.h"

namespace sfSnake
{
	class PauseScreen : public Screen
	{
	public:
		PauseScreen();
		void handleInput(sf::RenderWindow &window) override;
		void update(sf::Time delta) override;
		void render(sf::RenderWindow &window) override;

	private:
		sf::Texture continue_texture_;
		sf::Texture home_texture_;
		sf::Texture retry_texture_;

		Button continue_button_;
		Button home_button_;
		Button retry_button_;

		sf::Font font_;
		sf::Text text_;
	};

}

#endif