//
// Created by ittec on 11/4/2024.
//
#include "Player.h"

#include "log.h"
#include "model.h"
#include "gl_assist.h"
#include "renderer.h"

Player::Player(float x, float y) {
    x_ = x;
    y_ = y;
}

void Player::move(float x, float y) {
    x_ = x;
    y_ = y;
}

void Player::update(float /*dt*/) {}

void Player::render(renderer& r) const {
    r.render(Model::PlayerModel(x_, y_, 0.1));
}

vec2d Player::pos() const {
    return {x_, y_};
}