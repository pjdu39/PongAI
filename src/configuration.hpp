#pragma once
#include <SFML/System/Vector2.hpp>

namespace conf
{
	// Window configuraiton
	sf::Vector2u const window_size = { 1200, 800 };
	sf::Vector2f const window_size_f = static_cast<sf::Vector2f>(window_size);

	uint32_t const max_framerate = 144;
	float const dt = 1.0f / static_cast<float>(max_framerate);

	// Tamaños de objetos
	constexpr float ball_radius = 10.0f;
	constexpr sf::Vector2f paddle_size{ 200.f, 20.f };

	// Posiciones iniciales
	const sf::Vector2f ball_initial_position { (window_size.x - ball_radius) / 2, (window_size.y - ball_radius) / 2 };
	// const sf::Vector2f ball_initial_velocity { 270.f, -500.f };
	const sf::Vector2f paddle_1_initial_position {
		(window_size.x - paddle_size.x) / 2.f,
		0
	};
	const sf::Vector2f paddle_2_initial_position{
		(window_size.x - paddle_size.x) / 2.f,
		(window_size.y - paddle_size.y)
	};
}