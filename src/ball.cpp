#include "ball.hpp"

Ball::Ball(float radius, sf::Vector2f initialPosition)
	: position(initialPosition)
	, shape(radius)
{
	shape.setOrigin({radius, radius});
	shape.setPosition(initialPosition);
	shape.setFillColor(sf::Color::White);

	velocity.x = getRndm(-250, 250);
	velocity.y = -700.f;
}

void Ball::draw(sf::RenderWindow& window)
{
	window.draw(shape);
}

void Ball::update(float dt)
{
	position += velocity * dt;
	shape.setPosition(position);
}

void Ball::reset()
{
	position = conf::ball_initial_position;

	velocity.x = getRndm(-250, 250);
	velocity.y = -700.f;
}

namespace {
	std::random_device rd;
	std::mt19937 gen(rd());
}

float Ball::getRndm(float min, float max) {
	std::uniform_real_distribution<float> dis(min, max);
	return dis(gen);
}