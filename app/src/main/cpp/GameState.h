//
// Created by ittec on 11/4/2024.
//

#ifndef SPLIT_SECOND_GAMESTATE_H
#define SPLIT_SECOND_GAMESTATE_H

#include "Player.h"

class GameState {
public:
    GameState();
    void click(float x, float y);
    void update(float dt);
    void render();
private:
    Player player_;
    float last_update_;
};

#endif //SPLIT_SECOND_GAMESTATE_H
