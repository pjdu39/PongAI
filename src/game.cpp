#include "game.hpp"
#include <iostream>
#include "controllers/deterministicController.hpp"
#include "controllers/humanController.hpp"

Game::Game()
	: window(sf::VideoMode({ conf::window_size.x, conf::window_size.y }), "Pong AI")
	, ball(
		conf::ball_radius,
		conf::ball_initial_position)
	, paddle_1(
		conf::paddle_size,
		conf::paddle_1_initial_position,
		sf::Color::Red)
	, paddle_2(
		conf::paddle_size,
		conf::paddle_2_initial_position,
		sf::Color::Green)
	, paddle1Controller(std::make_unique<DeterministicController>(ball))
	, paddle2Controller(std::make_unique<HumanController>())
{
	window.setFramerateLimit(conf::max_framerate);
}

void Game::run()
{
	while (window.isOpen())
	{
		processEvents();
		update();
		render();
	}
}

void Game::processEvents()
{
	::processEvents(window);
}

void Game::update()
{
	const sf::Vector2f position = ball.position;
	const float radius = ball.shape.getRadius();

	// Updates
	ball.update(conf::dt);

	if (paddle1Controller) {
		paddle1Controller->update(paddle_1, conf::dt);
	}
	if (paddle2Controller) {
		paddle2Controller->update(paddle_2, conf::dt);
	}

	// Ajuste de límites para paddle_1
	{
		sf::Vector2f pos = paddle_1.shape.getPosition();
		float paddleWidth = conf::paddle_size.x;
		float windowWidth = static_cast<float>(conf::window_size.x);

		if (pos.x < 0.f) {
			pos.x = 0.f;
		}
		else if (pos.x + paddleWidth > windowWidth) {
			pos.x = windowWidth - paddleWidth;
		}
		paddle_1.shape.setPosition(pos);
	}

	// Ajuste de límites para paddle_2
	{
		sf::Vector2f pos = paddle_2.shape.getPosition();
		float paddleWidth = conf::paddle_size.x;
		float windowWidth = static_cast<float>(conf::window_size.x);

		if (pos.x < 0.f) {
			pos.x = 0.f;
		}
		else if (pos.x + paddleWidth > windowWidth) {
			pos.x = windowWidth - paddleWidth;
		}
		paddle_2.shape.setPosition(pos);
	}

	// Colisiones con paletas
	if (Collision::circleIntersectsRectangle(ball.shape, paddle_1.shape))
	{
		ball.position = { position.x, position.y };
		ball.velocity.y = - ball.velocity.y;
	}

	if (Collision::circleIntersectsRectangle(ball.shape, paddle_2.shape))
	{
		ball.position = { position.x, position.y };
		ball.velocity.y = - ball.velocity.y;
	}

	// Marcar punto
	if (ball.position.y - radius < 0.f) {
		ball.reset();
		paddle_1.reset();
		paddle_2.reset();

		// ... player 2 marca un punto
    }
	if (ball.position.y + radius > conf::window_size_f.y) {
		ball.reset();
		paddle_1.reset();
		paddle_2.reset();

		// ... player 1 marca un punto
	}

	// Colisiones con paredes
	if (position.x - radius < 0.f) {
		ball.position = { position.x + 1, position.y };
		ball.velocity.x = -ball.velocity.x;
	}

	if (position.x + radius > conf::window_size_f.x) {
		ball.position = { position.x - 1, position.y };
		ball.velocity.x = -ball.velocity.x;
	}


}


void Game::render()
{
	window.clear();

	ball.draw(window);
	paddle_1.draw(window);
	paddle_2.draw(window);

	window.display();
}
