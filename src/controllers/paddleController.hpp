#pragma once
#include "../paddle.hpp"

class PaddleController {
public:
    virtual ~PaddleController() = default;
    virtual void update(Paddle& paddle, float dt) = 0;
};