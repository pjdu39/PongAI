#include "deterministicController.hpp"

void DeterministicController::update(Paddle& paddle, float dt) {
    sf::Vector2f pos = paddle.shape.getPosition();
    pos.x = ball.shape.getPosition().x - paddle.shape.getSize().x / 2;
    paddle.shape.setPosition(pos);
}