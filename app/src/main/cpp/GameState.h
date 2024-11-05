//
// Created by ittec on 11/4/2024.
//

#ifndef SPLIT_SECOND_GAMESTATE_H
#define SPLIT_SECOND_GAMESTATE_H

#include "Player.h"
#include "renderer.h"

class GameState {
public:
    GameState();
    void click(float x, float y);
    void update(float dt);
    void render();

private:
    renderer renderer_;
    Player player_;
    float last_update_;
    float y_;
    float x_;
};

#endif //SPLIT_SECOND_GAMESTATE_H
