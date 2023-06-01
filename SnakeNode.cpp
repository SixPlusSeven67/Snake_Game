#include <SFML/Graphics.hpp>
#include <cmath>
#include <iostream>

#include "SnakeNode.h"

using namespace sfSnake;

const float SnakeNode::Width = 25.f;
const float SnakeNode::Height = 14.f;
const float SnakeNode::Radius = 15.f;

Rectangle::Rectangle(sf::Vector2f position)
	: position_(position)
{
	shape_.setPosition(position_);
	shape_.setOrigin(SnakeNode::Width / 2, SnakeNode::Height / 2);
	shape_.setFillColor(sf::Color(253, 220, 222));
	shape_.setSize(sf::Vector2f(SnakeNode::Width, SnakeNode::Height));
}

void Rectangle::setPosition(sf::Vector2f position)
{
	position_ = position;
	shape_.setPosition(position_);
}

void Rectangle::setPosition(float x, float y)
{
	position_.x = x;
	position_.y = y;
	shape_.setPosition(position_);
}

void Rectangle::setRotation(float x)
{
	shape_.setRotation(x);
}

void Rectangle::move(float xOffset, float yOffset)
{
	position_.x += xOffset;
	position_.y += yOffset;
	shape_.setPosition(position_);
	shape_.setRotation(-180 / 3.14 * atan2(xOffset, yOffset));
}

sf::FloatRect Rectangle::getBounds() const
{
	return shape_.getGlobalBounds();
}

sf::Vector2f Rectangle::getPosition() const
{
	return position_;
}

float Rectangle::getRotation() const
{
	return shape_.getRotation();
}

void Rectangle::render(sf::RenderWindow &window)
{
	window.draw(shape_);
}

Circle::Circle(sf::Vector2f position)
	: position_(position)
{
	shape_.setOrigin(SnakeNode::Radius, SnakeNode::Radius);
	shape_.setPosition(position_);
	shape_.setFillColor(sf::Color(253, 89, 92));
	shape_.setRadius(SnakeNode::Radius);
}

void Circle::setPosition(sf::Vector2f position)
{
	position_ = position;
	shape_.setPosition(position_);
}

void Circle::setPosition(float x, float y)
{
	position_.x = x;
	position_.y = y;
	shape_.setPosition(position_);
}

void Circle::setRotation(float x)
{
	shape_.setRotation(x);
}

void Circle::move(float xOffset, float yOffset)
{
	position_.x += xOffset;
	position_.y += yOffset;
	shape_.setPosition(position_);
	shape_.setRotation(-180 / 3.14 * atan2(xOffset, yOffset));
}

sf::FloatRect Circle::getBounds() const
{
	sf::FloatRect bounds(shape_.getPosition().x - SnakeNode::Radius / 1.414, shape_.getPosition().y - SnakeNode::Radius / 1.414, SnakeNode::Radius * 1.414, SnakeNode::Radius * 1.414);
	return bounds;
}

sf::Vector2f Circle::getPosition() const
{
	return position_;
}

float Circle::getRotation() const
{
	return shape_.getRotation();
}

void Circle::render(sf::RenderWindow &window)
{
	window.draw(shape_);
}
