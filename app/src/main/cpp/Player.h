//
// Created by ittec on 11/4/2024.
//

#ifndef SPLIT_SECOND_PLAYER_H
#define SPLIT_SECOND_PLAYER_H

#include <vector>

#include "renderer.h"

// Represents the player model.
class Player {
public:
    Player();

    void move(float x, float y);
    void update(float dt);
    void render(const renderer& r) const;

private:
    float x_;
    float y_;
};

#endif //SPLIT_SECOND_PLAYER_H
