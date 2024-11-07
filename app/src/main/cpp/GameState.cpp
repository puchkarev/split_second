//
// Created by ittec on 11/4/2024.
//

#include <GLES2/gl2.h>

#include "GameState.h"
#include "model.h"
#include "Player.h"
#include "project_time.h"
#include "log.h"

GameState::GameState(std::unique_ptr<renderer> renderer) : renderer_(std::move(renderer)), player_(), y_(0.0f), x_(0.0f) {
    LOG_INFO("Starting Game");
    renderer_->configure_camera(0.0, 0.0, -20.0f,
                               45.0f, 0.1f, 30.0f,
                               0.5f);
    last_update_ = getCurrentTimeSeconds();
}

void GameState::click(float x, float y) {
    player_.move(x, y * 2.5);
}

void GameState::update(float dt) {
    player_.update(dt);
}

void GameState::render() {
    float now = getCurrentTimeSeconds();
    float dt = now - last_update_;
    update(dt);
    last_update_ = now;

    renderer_->start_new_render();
    renderer_->render(Model::BackgroundModel(x_, y_, 0.0));
    player_.render(*renderer_);
}