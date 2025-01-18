#include "paddle.hpp"

Paddle::Paddle(sf::Vector2f size, sf::Vector2f initialPosition, sf::Color color)
	: position(initialPosition)
	, shape(size)
	, initialPosition(initialPosition)
{
	shape.setPosition(position);
	shape.setFillColor(color);
}

void Paddle::draw(sf::RenderWindow& window)
{
	window.draw(shape);
}

void Paddle::reset()
{
	shape.setPosition(initialPosition);
}