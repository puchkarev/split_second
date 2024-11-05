//
// Created by ittec on 11/4/2024.
//
#include "Player.h"

#include "log.h"
#include "model.h"
#include "gl_assist.h"
#include "renderer.h"

namespace {

constexpr float kPlayerMinX = -0.75f;
constexpr float kPlayerMaxX = 0.75f;
constexpr float kPlayerMinY = -0.9f;
constexpr float kPlayerMaxY = 0.3f;

constexpr float kStepX = 0.02;
constexpr float kStepY = 0.02;

constexpr float kMaxSpeed = 100.0;

Model PlayerModel(float x, float y) {
    return {
        .vertices = {
            // First triangle
            x - 0.1f, y - 0.05f, 0.0f,  // Bottom left
            x + 0.1f, y - 0.05f, 0.0f,  // Bottom right
            x + 0.1f,  y + 0.05f, 0.0f,  // Top right

            // Second triangle
            x + 0.1f,  y + 0.05f, 0.0f,  // Top right
            x + -0.1f,  y + 0.05f, 0.0f,  // Top left
            x + -0.1f, y - 0.05f, 0.0f   // Bottom left
        },
        .normals = {
            // First triangle
            0.0f, 0.0f, 1.0f,  // Bottom left
            0.0f, 0.0f, 1.0f,  // Bottom right
            0.0f, 0.0f, 1.0f,  // Top right

            // Second triangle
            0.0f, 0.0f, 1.0f,  // Top right
            0.0f, 0.0f, 1.0f,  // Top left
            0.0f, 0.0f, 1.0f   // Bottom left
        },
        .texcoords = {
            // First triangle
            0.0f, 1.0f,  // Bottom left (green)
            0.0f, 1.0f,  // Bottom right (green)
            0.0f, 1.0f,  // Top right (green)

            // Second triangle
            0.0f, 1.0f,  // Top right (green)
            0.0f, 1.0f,  // Top left (green)
            0.0f, 1.0f   // Bottom left (green)
        },
    };
}

}  // namespace

Player::Player() {
    x_ = 0.0f;
    y_ = 0.0f;
    speed_ = 0.0f;
}

void Player::click(float x, float y) {
    if (x < x_) {
        move(-kStepX, 0.0);
    } else if (x > x_) {
        move(+kStepX, 0.0);
    }

    if (y < y_) {
        move(0.0, -kStepY);
    } else if (y > y_) {
        move(0.0, +kStepY);
    }
}

void Player::move(float dx, float dy) {
    x_ = fmin(fmax(x_ + dx, kPlayerMinX), kPlayerMaxX);
    y_ = fmin(fmax(y_ + dy, kPlayerMinY), kPlayerMaxY);
}

void Player::update_speed() {
    const float f_y = (y_ - kPlayerMinY) / (kPlayerMaxY - kPlayerMinY);
    speed_ = f_y * kMaxSpeed;
}

void Player::update(float /*dt*/) {
    update_speed();
}

void Player::render(const renderer& r) const {
    r.render(PlayerModel(x_, y_), 0);
}