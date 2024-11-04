//
// Created by ittec on 11/4/2024.
//

#include <GLES2/gl2.h>

#include "GameState.h"
#include "Player.h"
#include "log.h"

GameState::GameState() : player_() {
    LOG_INFO("Starting Game");
    glClearColor(0.0f, 0.1f, 0.0f, 1.0f);
}

void GameState::click(float x, float y) {
    player_.click(x, y);
}

void GameState::render() const {
    player_.render();
}