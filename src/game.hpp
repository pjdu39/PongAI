#pragma once
#include <SFML/Graphics.hpp>
#include "events.hpp"
#include "configuration.hpp"
#include "ball.hpp"
#include "paddle.hpp"
#include "physics/collision.hpp"
#include "controllers/paddleController.hpp" 

class Game
{
public:
	Game();
	void run();

private:
	void initialize();
	void processEvents();
	void update();
	void render();

	sf::RenderWindow window;
	Ball ball;
	Paddle paddle_1;
	Paddle paddle_2;

	// Punteros a controladores inyectados para cada paleta
	std::unique_ptr<PaddleController> paddle1Controller;
	std::unique_ptr<PaddleController> paddle2Controller;
};