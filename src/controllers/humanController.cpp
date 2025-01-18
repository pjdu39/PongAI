#include "humanController.hpp"

void HumanController::update(Paddle& paddle, float dt) {
    float speed = 300.f;  // Velocidad en p�xeles por segundo
    sf::Vector2f pos = paddle.shape.getPosition();

    // Mover la pala seg�n las teclas presionadas
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::Left)) {
        pos.x -= speed * dt;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::Right)) {
        pos.x += speed * dt;
    }

    // Opcional: limitar la posici�n para que no salga de la ventana
    // ...

    paddle.shape.setPosition(pos);
}
