//
// Created by Victor Puchkarev on 11/7/24.
//

#include "vec3d.h"

#import <math.h>
#import <string>

#import "vec2d.h"

vec3d::vec3d() : vec3d(0.0f, 0.0f, 0.0f) {}

vec3d::vec3d(float x, float y, float z) : x_(x), y_(y), z_(z) {}

vec2d vec3d::xy() const { return {x(), y()}; }

float vec3d::x() const { return x_; }
float vec3d::y() const { return y_; }
float vec3d::z() const { return z_; }

float vec3d::len() const { return sqrt(x() * x() + y() * y() + z() * z()); }

vec3d vec3d::normalized() const { return *this / len(); }
void vec3d::normalize() { *this = normalized(); }

vec3d vec3d::operator+(const vec3d& other) const {
    return {x() + other.x(), y() + other.y(), z() + other.z()};
}
void vec3d::operator+=(const vec3d& other) { *this = *this + other; }

vec3d vec3d::operator-(const vec3d& other) const { return *this + other * -1.0f; }
void vec3d::operator-=(const vec3d& other) { *this = *this - other; }

vec3d vec3d::operator*(const float scalar) const {
    return {x() * scalar, y() * scalar, z() * scalar};
}
void vec3d::operator*=(const float scalar) { *this = *this * scalar; }

vec3d vec3d::operator/(const float scalar) const { return *this * (1.0f / scalar); }
void vec3d::operator/=(const float scalar) { *this = *this / scalar; }

bool vec3d::operator==(const vec3d& other) const {
    return x() == other.x() && y() == other.y() && z() == other.z();
}

vec3d vec3d::cross_product(const vec3d& other) const {
    return {
            y() * other.z() - z() * other.y(),
            z() * other.x() - x() * other.z(),
            x() * other.y() - y() * other.x()
    };
}
float vec3d::dot_product(const vec3d& other) const {
    return x() * other.x() + y() * other.y() + z() * other.z();
}

std::string vec3d::DebugString() const {
    return "{" + std::to_string(x()) + ", " +
        std::to_string(y()) + ", " +
        std::to_string(z()) + "}";
}