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

static void handlePaddleCollision(Ball& ball, const Paddle& paddle,
	const sf::Vector2f& prev_ball_position,
	float adjustmentMagnitude, float desiredSpeed)
{
	if (Collision::circleIntersectsRectangle(ball.shape, paddle.shape)) {
		ball.position = prev_ball_position;

		sf::FloatRect paddleBounds = paddle.shape.getGlobalBounds();

		// Calcular el centro horizontal de la pala usando .position y .size
		float paddleCenterX = paddleBounds.position.x + paddleBounds.size.x / 2.f;

		// Obtener la posición x del centro de la bola en el momento de la colisión
		float ballCenterX = ball.position.x;

		// Calcular la diferencia entre el centro de la bola y el centro de la pala
		float diffX = ballCenterX - paddleCenterX;

		// Normalizar la diferencia respecto al ancho de la pala (va de -1 a 1 aproximadamente)
		float factor = diffX / (paddleBounds.size.x / 2.f);

		// Ajustar la componente x de la velocidad en función de 'factor'
		ball.velocity.x += factor * adjustmentMagnitude;

		// Invertir la componente vertical para el rebote
		ball.velocity.y = -ball.velocity.y;

		// Normalizar la velocidad para que su magnitud sea desiredSpeed
		float currentSpeed = std::sqrt(ball.velocity.x * ball.velocity.x + ball.velocity.y * ball.velocity.y);
		if (currentSpeed != 0.f) {
			ball.velocity.x = (ball.velocity.x / currentSpeed) * desiredSpeed;
			ball.velocity.y = (ball.velocity.y / currentSpeed) * desiredSpeed;
		}
	}
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
	const sf::Vector2f prev_ball_position = ball.position;
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
	float adjustmentMagnitude = 300.f;
	float desiredSpeed = 700.f;

	handlePaddleCollision(ball, paddle_1, prev_ball_position, adjustmentMagnitude, desiredSpeed);
	handlePaddleCollision(ball, paddle_2, prev_ball_position, adjustmentMagnitude, desiredSpeed);


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
	if (ball.position.x - radius < 0.f) {
		ball.position = { prev_ball_position.x + 1, prev_ball_position.y };
		ball.velocity.x = -ball.velocity.x;
	}

	if (ball.position.x + radius > conf::window_size_f.x) {
		ball.position = { prev_ball_position.x - 1, prev_ball_position.y };
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