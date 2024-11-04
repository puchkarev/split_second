//
// Created by ittec on 11/4/2024.
//

#include <GLES2/gl2.h>
#include <EGL/egl.h>

#include "Player.h"
#include "log.h"
#include "gl_assist.h"

namespace {

const char *vertexShaderSource = R"(
    attribute vec4 aPosition;
    void main() {
        gl_Position = aPosition;
    }
)";

const char *fragmentShaderSource = R"(
    precision mediump float;
    void main() {
        gl_FragColor = vec4(0.0, 1.0, 0.0, 1.0); // Green color
    }
)";

GLuint g_player_program_ = 0;

constexpr float kPlayerMinX = -0.75f;
constexpr float kPlayerMaxX = 0.75f;
constexpr float kPlayerMinY = -0.9f;
constexpr float kPlayerMaxY = 0.3f;

constexpr float kStepX = 0.02;
constexpr float kStepY = 0.02;

constexpr float kMaxSpeed = 100.0;

std::vector<GLfloat> PlayerModel(float x, float y) {
    return {
            x - 0.1f, y - 0.05f, // Bottom Left
            x + 0.1f, y - 0.05f, // Bottom Right
            x - 0.1f, y + 0.05f, // Top Left
            x + 0.1f, y + 0.05f, // Top Right
    };
}

}  // namespace

Player::Player() {
    x_ = 0.0f;
    y_ = 0.0f;
    speed_ = 0.0f;

    if (g_player_program_ == 0) {
        g_player_program_ = createProgram(vertexShaderSource, fragmentShaderSource);
    }
}

Player::~Player() {
    if (g_player_program_ != 0) {
        // glDeleteProgram(g_player_program_);
    }
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

void Player::render() const {
    renderTriangleStripUsingProgram(g_player_program_, PlayerModel(x_, y_));
}