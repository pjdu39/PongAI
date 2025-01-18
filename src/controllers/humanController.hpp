#pragma once
#include <SFML/Window/Keyboard.hpp>
#include "paddleController.hpp"
#include "../paddle.hpp"

class HumanController : public PaddleController {
public:
    HumanController() = default;
    ~HumanController() override = default;

    void update(Paddle& paddle, float dt) override;
};