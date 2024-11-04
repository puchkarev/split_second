//
// Created by ittec on 11/4/2024.
//

#include <GLES2/gl2.h>

#include "GameState.h"
#include "Player.h"
#include "log.h"

GameState::GameState() : player_(0.0f, 0.0f) {
    LOG_INFO("Starting Game");
}

void GameState::click(float x, float y) {
    // Since typical screen dimensions are close to 1:2 we adjust step size here.
    constexpr float kStepX = 0.02;
    constexpr float kStepY = 0.04;

    if (x < player_.x()) {
        player_.move(-kStepX, 0.0);
    } else if (x > player_.x()) {
        player_.move(+kStepX, 0.0);
    }

    if (y < player_.y()) {
        player_.move(0.0, -kStepY);
    } else if (y > player_.y()) {
        player_.move(0.0, +kStepY);
    }
}

void GameState::render() const {
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);   // Black Color
    player_.render();
}