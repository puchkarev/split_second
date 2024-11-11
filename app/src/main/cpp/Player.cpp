//
// Created by Victor Puchkarev on 11/4/2024.
//
#include "Player.h"

#include "util/log.h"
#include "geometry/vec2d.h"
#include "graphics/model.h"
#include "graphics/gl_assist.h"
#include "graphics/renderer.h"
#include "Models.h"

Player::Player(float x, float y) {
    x_ = x;
    y_ = y;
}

void Player::move(float x, float y) {
    x_ = x;
    y_ = y;
}

void Player::update(float /*dt*/, float /*speed*/) {
    // TODO: Update the player model graphics as needed.
}

void Player::render(renderer& r) const {
    r.render(Models::PlayerModel(x_, y_, 0.1));
}

vec2d Player::pos() const {
    return {x_, y_};
}