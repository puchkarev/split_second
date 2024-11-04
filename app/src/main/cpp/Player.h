//
// Created by ittec on 11/4/2024.
//

#ifndef SPLIT_SECOND_PLAYER_H
#define SPLIT_SECOND_PLAYER_H

#include <vector>

// Represents the player model.
class Player {
public:
    Player();
    ~Player();

    void click(float x, float y);
    void move(float dx, float dy);
    void render() const;

private:
    float x_;
    float y_;
};

#endif //SPLIT_SECOND_PLAYER_H
