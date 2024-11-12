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

constexpr float speed = 1.0f;

constexpr float cameraPlayerOffset = 2.0f;
constexpr float cameraAboveRoad = 20.0;

GameState::GameState(std::unique_ptr<renderer> renderer) :
    renderer_(std::move(renderer)) {
    last_update_ = getCurrentTimeSeconds();
    start_game();
}

void GameState::start_game() {
    LOG_INFO("Starting Game");
    road_ = Road(roadWidth, roadLength, 0.0, 0.0f);
    player_ = Player(0.0f, 0.0f);
}

void GameState::click(float x, float y) {
    const float road_hw = road_.width() * 0.5f;
    const float desired_x = x * road_hw;
    const float clamped_x = fmax(-road_hw + road_.width_edge_offset(),
                                 fmin(road_hw - road_.width_edge_offset(),
                                      desired_x));

    player_.move(clamped_x, player_.pos().y());
}

void GameState::update(float dt) {
    road_.update(dt, speed);
    player_.update(dt, speed);

    player_.move(player_.pos().x(), player_.pos().y() + dt * speed);

    if (player_.pos().y() >= road_.length()) {
        LOG_INFO("Restarting game");
        start_game();
    }
}

void GameState::reconfigure_camera(int width, int height) {
    if (renderer_ != nullptr) {
        const float aspect_ratio = static_cast<float>(width) / static_cast<float>(height);

        // Compute so that we can accurately see the full width of the road.
        const float fov_y_deg = 2.0f
                * atan((road_.width() / aspect_ratio) / (2.0f * cameraAboveRoad))
                * (180.0f / M_PI);

        renderer_->mutable_camera() =
                camera(camera::perspective_matrix(fov_y_deg, 10.0f, 40.0f, aspect_ratio),
                       {0.0f, 0.0f, cameraAboveRoad},
                       {0.0f, 0.0f, 0.0f},
                       {0.0f, 1.0f, 0.0f});
    }
}

void GameState::render(int width, int height) {
    float dt = getCurrentTimeSeconds() - last_update_;
    update(dt);
    last_update_ += dt;

    if (renderer_ != nullptr) {
        reconfigure_camera(width, height);
        renderer_->mutable_camera().reposition(
                {0.0, player_.pos().y() + cameraPlayerOffset, cameraAboveRoad});
        renderer_->start_new_render();
        player_.render(*renderer_);
        road_.render(*renderer_);
    }
}