#pragma once
#include "PaddleController.hpp"
#include "../ball.hpp"
#include "../paddle.hpp"

class DeterministicController : public PaddleController {
public:
    explicit DeterministicController(const Ball& ballRef) : ball(ballRef) {}
    ~DeterministicController() override = default;

    void update(Paddle& paddle, float dt) override;

private:
    const Ball& ball;
};
