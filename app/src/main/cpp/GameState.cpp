//
// Created by Victor Puchkarev on 11/4/2024.
//

#include <GLES2/gl2.h>

#include "GameState.h"
#include "graphics/model.h"
#include "Player.h"
#include "util/project_time.h"
#include "util/log.h"

constexpr float roadWidth = 4.0f;
constexpr float roadLength = 20.0f;

constexpr float playerStartOffset = 0.2f;
constexpr float gameEndOffset = 0.3f;

constexpr float speed = 0.5f;

constexpr float cameraPlayerOffset = 0.6f;

GameState::GameState(std::unique_ptr<renderer> renderer) :
    renderer_(std::move(renderer)) {
    LOG_INFO("Starting Game");
    last_update_ = getCurrentTimeSeconds();
    StartGame();
}

void GameState::StartGame() {
    road_ = Road(roadWidth, roadLength, 0.0, roadLength * 0.5f);
    player_ = Player(0.0f, playerStartOffset);
}

void GameState::click(float x, float y) {
    player_.move(x, player_.pos().y());
}

void GameState::update(float dt) {
    road_.update(dt, speed);
    player_.update(dt, speed);

    player_.move(player_.pos().x(), player_.pos().y() + dt * speed);

    if (player_.pos().y() >= road_.box().top() - gameEndOffset) {
        StartGame();
    }
}

void GameState::render() {
    float now = getCurrentTimeSeconds();
    float dt = now - last_update_;
    update(dt);
    last_update_ = now;

    renderer_->start_new_render();

    renderer_->configure_camera(
            vec3d(0.0, player_.pos().y() + cameraPlayerOffset, 20.0f),
            vec3d(0.0, player_.pos().y() + cameraPlayerOffset, 0.0f),
            vec3d(0.0, 1.0, 0.0),
            10.0f, 1.0f, 1000.0f, 0.5f);

    player_.render(*renderer_);
    road_.render(*renderer_);
}