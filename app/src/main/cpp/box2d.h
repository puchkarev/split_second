//
// Created by puchkarev on 11/7/24.
//

#ifndef SPLIT_SECOND_BOX2D_H
#define SPLIT_SECOND_BOX2D_H

#include "vec2d.h"

class box2d {
public:
    box2d() : box2d(0.0, 0.0, 0.0, 0.0) {}

    box2d(float x, float y, float width, float height) :
    x_(x), y_(y), width_(width), height_(height) {}

    [[nodiscard]] float top() const {
        return y_ + height_ * 0.5f;
    }

    [[nodiscard]]  float bottom() const {
        return y_ - height_ * 0.5f;
    }

    [[nodiscard]] float left() const {
        return x_ - width_ * 0.5f;
    }

    [[nodiscard]] float right() const {
        return x_ + width_ * 0.5f;
    }

    [[nodiscard]] bool overlaps(const box2d& box) const {
        return box.left() < right() && box.right() > left() &&
               box.top() > bottom() && box.bottom() < top();
    }

    [[nodiscard]] bool point_inside(const vec2d& pt) const {
        return pt.x() > left() && pt.x() < right() &&
               pt.y() > bottom() && pt.y() < top();
    }

private:
    float x_;
    float y_;
    float width_;
    float height_;
};


#endif //SPLIT_SECOND_BOX2D_H
