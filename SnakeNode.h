#ifndef SNAKE_NODE_H
#define SNAKE_NODE_H

#include <SFML/Graphics.hpp>

namespace sfSnake
{
	class SnakeNode
	{
	public:
		virtual void setPosition(sf::Vector2f position) = 0;
		virtual void setPosition(float x, float y) = 0;
		virtual void setRotation(float x) = 0;

		virtual void move(float xOffset, float yOffset) = 0;

		virtual void render(sf::RenderWindow &window) = 0;

		virtual sf::Vector2f getPosition() const = 0;
		virtual float getRotation() const = 0;
		virtual sf::FloatRect getBounds() const = 0;

		static const float Width;
		static const float Height;
		static const float Radius;
	};

	class Circle : public SnakeNode
	{
	public:
		Circle(sf::Vector2f position = sf::Vector2f(0, 0));

		void setPosition(sf::Vector2f position) override;
		void setPosition(float x, float y) override;
		void setRotation(float x) override;

		void move(float xOffset, float yOffset) override;
		void render(sf::RenderWindow &window) override;

		sf::Vector2f getPosition() const override;
		float getRotation() const override;
		sf::FloatRect getBounds() const override;

	private:
		sf::CircleShape shape_;
		sf::Vector2f position_;
	};

	class Rectangle : public SnakeNode
	{
	public:
		Rectangle(sf::Vector2f position = sf::Vector2f(0, 0));

		void setPosition(sf::Vector2f position) override;
		void setPosition(float x, float y) override;
		void setRotation(float x) override;

		void move(float xOffset, float yOffset) override;
		void render(sf::RenderWindow &window) override;

		sf::Vector2f getPosition() const override;
		float getRotation() const override;
		sf::FloatRect getBounds() const override;

	private:
		sf::RectangleShape shape_;
		sf::Vector2f position_;
	};

}

#endif