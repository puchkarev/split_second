//
// Created by ittec on 11/4/2024.
//

#include <GLES2/gl2.h>

#include "GameState.h"
#include "model.h"
#include "Player.h"
#include "project_time.h"
#include "log.h"

constexpr float roadWidth = 2.0f;
constexpr float roadLength = 20.0f;
constexpr float speed = 1.0f;
constexpr float playerStartY = -1.5f;
constexpr float kEndOffset = 0.2f;

GameState::GameState(std::unique_ptr<renderer> renderer) :
    renderer_(std::move(renderer)) {
    LOG_INFO("Starting Game");
    renderer_->configure_camera(0.0, 0.0, -20.0f,
                               45.0f, 0.1f, 30.0f,
                               0.5f);
    last_update_ = getCurrentTimeSeconds();
    StartGame();
}

void GameState::StartGame() {
    player_ = Player(0.0f, playerStartY),
    road_ = Road(roadWidth, roadLength, -roadLength * 0.5f + 1.5f);
}

void GameState::click(float x, float y) {
    player_.move(x, playerStartY);
}

void GameState::update(float dt) {
    road_.update(dt, speed);
    player_.update(dt);

    if (player_.pos().y() >= road_.box().top() - kEndOffset) {
        StartGame();
    }
}

void GameState::render() {
    float now = getCurrentTimeSeconds();
    float dt = now - last_update_;
    update(dt);
    last_update_ = now;

    renderer_->start_new_render();
    road_.render(*renderer_);
    player_.render(*renderer_);
}