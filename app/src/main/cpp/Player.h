//
// Created by ittec on 11/4/2024.
//

#ifndef SPLIT_SECOND_PLAYER_H
#define SPLIT_SECOND_PLAYER_H

#include <vector>

#include "renderer.h"
#include "box2d.h"
#include "vec2d.h"

// Represents the player model.
class Player {
public:
    Player() : Player(0.0f, 0.0f) {}
    Player(float x, float y);

    vec2d pos() const;

    void move(float x, float y);
    void update(float dt);
    void render(renderer& r) const;

private:
    float x_;
    float y_;
};

#endif //SPLIT_SECOND_PLAYER_H
