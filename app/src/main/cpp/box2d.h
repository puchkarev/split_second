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
        center_(x, y), half_size_(width * 0.5f, height * 0.5f) {}

    [[nodiscard]] vec2d top_right() const {
        return center_ + half_size_;
    }

    [[nodiscard]] vec2d bottom_left() const {
        return center_ - half_size_;
    }

    [[nodiscard]] float top() const {
        return top_right().y();
    }

    [[nodiscard]]  float bottom() const {
        return bottom_left().y();
    }

    [[nodiscard]] float left() const {
        return bottom_left().x();
    }

    [[nodiscard]] float right() const {
        return top_right().x();
    }

    [[nodiscard]] vec2d center() const {
        return center_;
    }

    void shift(const vec2d& offset) {
        center_ += offset;
    }

    box2d shifted(const vec2d& offset) {
        box2d box = *this;
        box.shift(offset);
        return box;
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
    vec2d center_;
    vec2d half_size_;
};


#endif //SPLIT_SECOND_BOX2D_H
