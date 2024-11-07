//
// Created by ittec on 11/4/2024.
//
#include "Player.h"

#include "log.h"
#include "model.h"
#include "gl_assist.h"
#include "renderer.h"

Player::Player() {
    x_ = 0.0f;
    y_ = 0.0f;
}

void Player::move(float x, float y) {
    x_ = x;
    y_ = y;
}

void Player::update(float /*dt*/) {}

void Player::render(const renderer& r) const {
    r.render(Model::PlayerModel(x_, y_, 0.1), 0);
}