#include <SFML/Graphics.hpp>

#include <random>

#include "Fruit.h"

using namespace sfSnake;

const float Fruit::Radius = 10.f;

Fruit::Fruit(sf::Vector2f position)
{
	shape_.setPosition(position);
	shape_.setRadius(Fruit::Radius);
	// Color:: Black & Brown-- 0 point, Blue -- 1 point, Green -- 2 points,  Red -- 3 points;
	score_ = getValue();
	shape_.setFillColor(setFruitColor());
	shape_.setOutlineThickness(2);
	shape_.setOutlineColor(sf::Color::Black);
}

void Fruit::render(sf::RenderWindow &window)
{
	window.draw(shape_);
}

sf::FloatRect Fruit::getBounds() const
{
	return shape_.getGlobalBounds();
}

unsigned Fruit::getScore() const
{
	return score_;
}

sf::Color Fruit::setFruitColor()
{
	switch (score_)
	{
	case 0:
		return sf::Color::Black;
	case 10:
		Fruit::score_ = 0;
		return sf::Color(99, 56, 17); // Brown
	case 1:
		return sf::Color::Blue;
	case 2:
		return sf::Color::Green;
	case 3:
		return sf::Color::Red;
	default:
		return sf::Color::White;
	}
}

unsigned getValue()
{
	std::random_device rd;
	std::mt19937 gene(rd());
	std::uniform_int_distribution<> dis(0, 99);
	unsigned random = dis(gene);
	if (random < 10)
		return 0; // 10%
	else if (random < 25)
		return 10; // 15%
	else if (random < 70)
		return 1; // 45%
	else if (random < 90)
		return 2; // 20%
	else if (random < 100)
		return 3; // 10%
	return 0;
}