//
// Created by Victor Puchkarev on 11/4/2024.
//

#ifndef SPLIT_SECOND_PLAYER_H
#define SPLIT_SECOND_PLAYER_H

#include <vector>

#include "graphics/renderer.h"
#include "geometry/vec2d.h"

// Represents the player model.
class Player {
public:
    Player() : Player(0.0f, 0.0f) {}
    Player(float x, float y);

    [[nodiscard]] vec2d pos() const;

    void move(float x, float y);
    void update(float dt, float speed);
    void render(renderer& r) const;

private:
    float x_ = 0.0f;
    float y_ = 0.0f;
};

#endif //SPLIT_SECOND_PLAYER_H
