#pragma once
#include <SFML/Graphics.hpp>
#include "configuration.hpp"
#include <random>

struct Ball
{
	sf::Vector2f position;
	sf::CircleShape shape;
	sf::Vector2f velocity;

	Ball(float radius = 10.0f, const sf::Vector2f initialPosition = { 0.f, 0.f });

	void draw(sf::RenderWindow& window);
	void update(float dt);
	void reset();

	private:
		static float getRndm(float min, float max);
};