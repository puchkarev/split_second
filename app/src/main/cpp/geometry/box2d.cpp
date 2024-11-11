//
// Created by Victor Puchkarev on 11/7/24.
//

#include "box2d.h"

#include "vec2d.h"

box2d::box2d() : box2d(0.0, 0.0, 0.0, 0.0) {}

box2d::box2d(float x, float y, float width, float height) :
    center_(x, y), half_size_(width * 0.5f, height * 0.5f) {}

vec2d box2d::top_right() const {
    return center_ + half_size_;
}

vec2d box2d::bottom_left() const {
    return center_ - half_size_;
}

float box2d::top() const {
    return top_right().y();
}

float box2d::bottom() const {
    return bottom_left().y();
}

float box2d::left() const {
    return bottom_left().x();
}

float box2d::right() const {
    return top_right().x();
}

vec2d box2d::center() const {
    return center_;
}

void box2d::shift(const vec2d& offset) {
    center_ += offset;
}

box2d box2d::shifted(const vec2d& offset) {
    box2d box = *this;
    box.shift(offset);
    return box;
}

bool box2d::overlaps(const box2d& box) const {
    return box.left() < right() && box.right() > left() &&
           box.top() > bottom() && box.bottom() < top();
}

bool box2d::point_inside(const vec2d& pt) const {
    return pt.x() > left() && pt.x() < right() &&
           pt.y() > bottom() && pt.y() < top();
}

