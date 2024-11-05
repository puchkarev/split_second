//
// Created by ittec on 11/4/2024.
//

#include <GLES2/gl2.h>

#include "GameState.h"
#include "model.h"
#include "Player.h"
#include "project_time.h"
#include "log.h"

namespace {

Model BackgroundModel(float x, float y) {
    return {
        .vertices {
            x - 1.0f, y - 1.0f, 0.0f,  // Bottom left
            x + 1.0f, y - 1.0f, 0.0f,  // Bottom right
            x + 1.0f, y + 1.0f, 0.0f,  // Top right

            x + 1.0f, y + 1.0f, 0.0f,  // Top right
            x - 1.0f, y + 1.0f, 0.0f,   // Top left
            x - 1.0f, y - 1.0f, 0.0f,  // Bottom left
        },
        .normals = {
            // First triangle
            0.0f, 0.0f, 1.0f,  // Bottom left
            0.0f, 0.0f, 1.0f,  // Bottom right
            0.0f, 0.0f, 1.0f,  // Top right

            // Second triangle
            0.0f, 0.0f, 1.0f,  // Top right
            0.0f, 0.0f, 1.0f,  // Top left
            0.0f, 0.0f, 1.0f   // Bottom left
        },
        .texcoords {
            0.0f, 0.0f,  // Bottom left
            1.0f, 0.0f,  // Bottom right
            1.0f, 1.0f,  // Top right

            1.0f, 1.0f,  // Top right
            0.0f, 1.0f,   // Top left
            0.0f, 0.0f,  // Bottom left
        }
    };
}

}  // namespace

GameState::GameState() : renderer_(), player_() {
    LOG_INFO("Starting Game");
    // glClearColor(0.0f, 0.1f, 0.0f, 1.0f);
    last_update_ = getCurrentTimeSeconds();
}

void GameState::click(float x, float y) {
    player_.click(x, y);
}

void GameState::update(float dt) {
    player_.update(dt);
}

void GameState::render() {
    float now = getCurrentTimeSeconds();
    float dt = now - last_update_;
    update(dt);
    last_update_ = now;


    renderer_.render(BackgroundModel(0.0f, 0.0f), 0);
    player_.render(renderer_);
}