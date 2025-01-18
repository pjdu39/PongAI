#pragma once
#include <SFML/Graphics.hpp>
#include "configuration.hpp"

struct Paddle
{
	sf::Vector2f position;
	sf::RectangleShape shape;

	sf::Vector2f initialPosition;

	Paddle(const sf::Vector2f size = { 20.f, 100.f }, const sf::Vector2f initialPosition = { 100.f, 100.f }, const sf::Color color = sf::Color::White);

	void draw(sf::RenderWindow& window);
	void reset();
};