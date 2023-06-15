#ifndef GAME_H
#define GAME_H

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include <vector>
#include <memory>

#include "Screen.h"

namespace sfSnake
{
	class Game
	{
	public:
		Game();

		void run();

		void handleInput();
		void update(sf::Time delta);
		void render(std::shared_ptr<Screen>);

		static const int Width = 1920;
		static const int Height = 1080;

		static bool isGridVisible;
		static sf::Color Grid_Color;
		static sf::Color Back_Color;

		static std::shared_ptr<Screen> Screen_;
		static std::shared_ptr<Screen> Temp_Screen;
		static std::shared_ptr<Screen> Paused_Screen;

		static sf::Time TimePerFrame;

	private:
		sf::RenderWindow window_;
		sf::Music bgMusic_;
	};
}

#endif