#ifndef FRUIT_H
#define FRUIT_H

#include <SFML/Graphics.hpp>

namespace sfSnake
{
	class Fruit
	{
	public:
		Fruit(sf::Vector2f position = sf::Vector2f(0, 0));

		sf::Color setFruitColor();

		sf::FloatRect getBounds() const;
		unsigned getScore() const;

		void render(sf::RenderWindow &window);

	private:
		sf::CircleShape shape_;
		unsigned score_;

		static const float Radius;
	};
}

unsigned getValue();

#endif