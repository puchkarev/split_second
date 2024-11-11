//
// Created by puchkarev on 11/7/24.
//

#include "vec2d.h"

#import <math.h>

vec2d::vec2d() : vec2d(0.0f, 0.0f) {}

vec2d::vec2d(float x, float y) : x_(x), y_(y) {}

float vec2d::x() const { return x_; }
float vec2d::y() const { return y_; }

float vec2d::len() const { return sqrt(x() * x() + y() * y()); }

vec2d vec2d::normalized() const { return *this / len(); }
void vec2d::normalize() { *this = normalized(); }

vec2d vec2d::operator+(const vec2d& other) const {
    return {x() + other.x(), y() + other.y()};
}
void vec2d::operator+=(const vec2d& other) { *this = *this + other; }

vec2d vec2d::operator-(const vec2d& other) const { return *this + other * -1.0f; }
void vec2d::operator-=(const vec2d& other) { *this = *this - other; }

vec2d vec2d::operator*(const float scalar) const {
    return {x() * scalar, y() * scalar};
}
void vec2d::operator*=(const float scalar) { *this = *this * scalar; }

vec2d vec2d::operator/(const float scalar) const { return *this * (1.0f / scalar); }
void vec2d::operator/=(const float scalar) { *this = *this / scalar; }

bool vec2d::operator==(const vec2d& other) const {
    return x() == other.x() && y() == other.y();
}

float vec2d::cross_product(const vec2d& other) const {
    return x() * other.y() - y() * other.x();
}
float vec2d::dot_product(const vec2d& other) const {
    return x() * other.x() + y() * other.y();
}

std::string vec2d::DebugString() const {
    return "{" + std::to_string(x()) + ", " +
           std::to_string(y()) + "}";
}