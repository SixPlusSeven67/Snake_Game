#include <SFML/Graphics.hpp>

#include <iostream>
#include <cmath>

#include "Snake.h"
#include "Game.h"
#include "Fruit.h"
#include "SnakeNode.h"
#include "GameOverScreen.h"

using namespace sfSnake;

const int Snake::InitialSize = 20;

Snake::Snake() : direction_(sf::Vector2f(0.f, -1.f)), hitSelf_(false), score_{0}
{
	initNodes();

	pickupBuffer_.loadFromFile("Sounds/pickup.wav");
	pickupSound_.setBuffer(pickupBuffer_);
	pickupSound_.setVolume(30);

	dieBuffer_.loadFromFile("Sounds/die.wav");
	dieSound_.setBuffer(dieBuffer_);
	dieSound_.setVolume(50);
}

void Snake::initNodes()
{
	if (!headTexture.loadFromFile("Image/snake.png"))
		std::cout << "Unable to find headImage" << '\n';
	headTexture.setSmooth(true);
	headnode.setTexture(headTexture);
	headnode.setPosition(sf::Vector2f(Game::Width / 2, Game::Height / 2));
	headnode.setOrigin(headTexture.getSize().x / 2, headTexture.getSize().y / 2);
	headnode.setScale(2.1 * SnakeNode::Radius / headTexture.getSize().x, 2.1 * SnakeNode::Radius / headTexture.getSize().y);
	nodes_.reserve(5000);

	for (int i = 0; i < Snake::InitialSize; ++i)
	{
		if (i % 2)
			nodes_.push_back(std::make_shared<Rectangle>(nodes_[i - 1]->getPosition() + sf::Vector2f(0, -SnakeNode::Radius)));
		else
			nodes_.push_back(std::make_shared<Circle>(sf::Vector2f(
				Game::Width / 2,
				Game::Height / 2 + headTexture.getSize().y / 3 + (SnakeNode::Radius * (i + 1)))));
	}
}

void Snake::handleInput(sf::RenderWindow &window)
{
	// 键盘wasd模拟摇杆
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
		direction_ += sf::Vector2f(0.f, -1.f);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
		direction_ += sf::Vector2f(0.f, 1.f);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
		direction_ += sf::Vector2f(-1.f, 0.f);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		direction_ += sf::Vector2f(1.f, 0.f);
	// 箭头经典操作
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
		direction_ = sf::Vector2f(0.f, -1.f);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
		direction_ = sf::Vector2f(0.f, 1.f);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
		direction_ = sf::Vector2f(-1.f, 0.f);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		direction_ = sf::Vector2f(1.f, 0.f);
	// 按z加速,按c减速
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q))
		if (Game::TimePerFrame.asSeconds() >= 0.03)
			Game::TimePerFrame -= sf::seconds(0.005);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::E))
		if (Game::TimePerFrame.asSeconds() <= 0.2)
			Game::TimePerFrame += sf::seconds(0.005);
	// 鼠标指定方向
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		direction_ = tellVec(sf::Mouse::getPosition(window));
	float distance = sqrt(direction_.x * direction_.x + direction_.y * direction_.y);
	if (distance)
		direction_ = sf::Vector2f(direction_.x / distance, direction_.y / distance);
}

void Snake::update(sf::Time delta)
{
	move();
	position_ = headnode.getPosition();
	checkEdgeCollisions();
	checkSelfCollisions();
}

void Snake::checkFruitCollisions(std::list<Fruit> &fruits)
{
	decltype(fruits.begin()) toRemove = fruits.end();

	for (auto it = fruits.begin(); it != fruits.end(); ++it)
	{
		if (it->getBounds().intersects(nodes_[0]->getBounds()))
			toRemove = it;
	}

	if (toRemove != fruits.end())
	{
		pickupSound_.play();
		score_ += toRemove->getScore();
		for (int i = 0; i < toRemove->getScore(); ++i)
			grow();
		fruits.erase(toRemove);
	}
}

void Snake::grow()
{
	size_t i{nodes_.size()};
	nodes_.push_back(std::make_shared<Circle>(
		nodes_[i - 1]->getPosition() + sf::Vector2f(
										   sin(nodes_[i - 1]->getRotation() / 180 * 3.1415) * 2 * SnakeNode::Radius,
										   -cos(nodes_[i - 1]->getRotation() / 180 * 3.1415) * 2 * SnakeNode::Radius)));
	nodes_.push_back(std::make_shared<Rectangle>(nodes_[i]->getPosition()));
	nodes_[i]->setRotation(nodes_[i - 1]->getRotation());
	nodes_[i + 1]->setRotation(nodes_[i - 1]->getRotation());
}

unsigned Snake::getSize() const
{
	return nodes_.size();
}

bool Snake::hitSelf() const
{
	return hitSelf_;
}

void Snake::checkSelfCollisions()
{
	for (decltype(nodes_.size()) i = 4; i < nodes_.size(); ++i)
	{
		if (headnode.getGlobalBounds().intersects(nodes_[i]->getBounds()))
		{
			dieSound_.play();
			// sf::sleep(sf::seconds(dieBuffer_.getDuration().asSeconds()));
			hitSelf_ = true;
			if (hitSelf_)
				return;
		}
	}
}

void Snake::checkEdgeCollisions()
{
	if (headnode.getPosition().x <= 0)
		headnode.setPosition(Game::Width, headnode.getPosition().y);
	else if (headnode.getPosition().x >= Game::Width)
		headnode.setPosition(0, headnode.getPosition().y);
	else if (headnode.getPosition().y <= 0)
		headnode.setPosition(headnode.getPosition().x, Game::Height);
	else if (headnode.getPosition().y >= Game::Height)
		headnode.setPosition(headnode.getPosition().x, 0);
}

void Snake::move()
{
	{
		// move
		for (decltype(nodes_.size()) i = nodes_.size() - 1; i > 1; --i)
		{
			nodes_[i]->setPosition(nodes_[i - 2]->getPosition());
			nodes_[i]->setRotation(nodes_[i - 2]->getRotation());
		}
		// move [0]
		nodes_[0]->setPosition(headnode.getPosition());
		nodes_[0]->setRotation(headnode.getRotation());

		// move [head]
		headnode.move(direction_.x * SnakeNode::Radius * 2, direction_.y * SnakeNode::Radius * 2);
		headnode.setRotation(-180 / 3.1415 * (direction_.y >= 0 ? atan2(direction_.x, direction_.y) : atan2(direction_.x, direction_.y) + 2 * 3.1415));

		// move [1]
		nodes_[1]->setPosition(
			nodes_[0]->getPosition() - sf::Vector2f(
										   SnakeNode::Radius * sin(headnode.getRotation() / 180 * 3.1415),
										   -SnakeNode::Radius * cos(headnode.getRotation() / 180 * 3.1415)));
		nodes_[1]
			->setRotation(headnode.getRotation());
	}
}

void Snake::render(sf::RenderWindow &window)
{
	window.draw(headnode);
	for (auto node : nodes_)
		node->render(window);
}

sf::Vector2f Snake::tellVec(sf::Vector2i in) const
{
	float x{in.x - position_.x}, y{in.y - position_.y};
	// std::cout << in.x << ' ' << in.y << '\n';
	// std::cout << position_.x << ' ' << position_.y << '\n'
	// 		  << '\n';
	float distance = sqrt(x * x + y * y);

	return sf::Vector2f(x / distance, y / distance);
}

size_t Snake::getScore() const
{
	return score_;
}