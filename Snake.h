#ifndef SNAKE_H
#define SNAKE_H

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include <list>
#include <vector>
#include <memory>

#include "SnakeNode.h"
#include "Fruit.h"

namespace sfSnake
{
	class Snake
	{
	public:
		Snake();

		void handleInput(sf::RenderWindow &window);
		void update(sf::Time delta);
		void render(sf::RenderWindow &window);

		void checkFruitCollisions(std::list<Fruit> &fruits);

		bool hitSelf() const;

		unsigned getSize() const;
		size_t getScore() const;

		sf::Vector2f tellVec(sf::Vector2i) const;

	private:
		void move();
		void grow();
		void checkEdgeCollisions();
		void checkSelfCollisions();
		void initNodes();

		bool hitSelf_;

		sf::Vector2f position_;
		sf::Vector2f direction_;

		sf::SoundBuffer pickupBuffer_;
		sf::Sound pickupSound_;

		sf::SoundBuffer dieBuffer_;
		sf::Sound dieSound_;

		sf::Texture headTexture;
		sf::Sprite headnode;
		std::vector<std::shared_ptr<SnakeNode>> nodes_;

		unsigned score_;

		static const int InitialSize;
	};
}

#endif