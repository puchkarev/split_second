//
// Created by Victor Puchkarev on 11/4/2024.
//

#ifndef SPLIT_SECOND_GAMESTATE_H
#define SPLIT_SECOND_GAMESTATE_H

#include "Player.h"
#include "Road.h"

#include "graphics/renderer.h"

class GameState {
public:
    explicit GameState(std::unique_ptr<renderer> renderer);
    void click(float x, float y);
    void update(float dt);
    void render();

    void StartGame();

private:
    std::unique_ptr<renderer> renderer_;
    Player player_;
    Road road_;
    float last_update_;
};

#endif //SPLIT_SECOND_GAMESTATE_H
