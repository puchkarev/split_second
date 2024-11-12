//
// Created by Victor Puchkarev on 11/4/2024.
//

#include "GameState.h"

#include "Player.h"
#include "Road.h"

#include "graphics/model.h"
#include "graphics/camera.h"
#include "graphics/renderer.h"

#include "util/project_time.h"
#include "util/log.h"

constexpr float roadWidth = 4.0f;
constexpr float roadLength = 20.0f;

constexpr float speed = 0.5f;

constexpr float cameraPlayerOffset = 0.6f;

GameState::GameState(std::unique_ptr<renderer> renderer) :
    renderer_(std::move(renderer)) {

    if (renderer_ != nullptr) {
        renderer_->mutable_camera() =
                camera(camera::perspective_matrix(10.0f, 1.0f, 1000.0f, 0.5f));
    }

    last_update_ = getCurrentTimeSeconds();
    StartGame();
}

void GameState::StartGame() {
    LOG_INFO("Starting Game");
    road_ = Road(roadWidth, roadLength, 0.0, 0.0f);
    player_ = Player(0.0f, 0.0f);

    if (renderer_ != nullptr) {
        LOG_INFO("Configuring camera");
        renderer_->mutable_camera().reposition({0.0f, 0.0f, 20.0f});
        renderer_->mutable_camera().set_target({0.0f, 0.0f, 0.0f});
        renderer_->mutable_camera().set_up({0.0f, 1.0f, 0.0f});
    }
}

void GameState::click(float x, float y) {
    player_.move(x, player_.pos().y());
}

void GameState::update(float dt) {
    road_.update(dt, speed);
    player_.update(dt, speed);

    player_.move(player_.pos().x(), player_.pos().y() + dt * speed);

    if (player_.pos().y() >= road_.length()) {
        LOG_INFO("Restarting game");
        StartGame();
    }
}

void GameState::render() {
    float now = getCurrentTimeSeconds();
    float dt = now - last_update_;
    update(dt);
    last_update_ = now;

    if (renderer_ != nullptr) {
        renderer_->mutable_camera().reposition({0.0, player_.pos().y() + cameraPlayerOffset, 20.0});
        renderer_->start_new_render();
        player_.render(*renderer_);
        road_.render(*renderer_);
    }
}