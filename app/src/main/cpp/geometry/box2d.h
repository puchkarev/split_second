//
// Created by Victor Puchkarev on 11/7/24.
//

#ifndef SPLIT_SECOND_GEOMETRY_BOX2D_H
#define SPLIT_SECOND_GEOMETRY_BOX2D_H

#include "vec2d.h"

class box2d {
public:
    box2d();
    box2d(float x, float y, float width, float height);

    [[nodiscard]] vec2d top_right() const;
    [[nodiscard]] vec2d bottom_left() const;
    [[nodiscard]] float top() const;
    [[nodiscard]]  float bottom() const;
    [[nodiscard]] float left() const;
    [[nodiscard]] float right() const;
    [[nodiscard]] vec2d center() const;

    void shift(const vec2d& offset);
    box2d shifted(const vec2d& offset);

    [[nodiscard]] bool overlaps(const box2d& box) const;
    [[nodiscard]] bool point_inside(const vec2d& pt) const;

private:
    vec2d center_;
    vec2d half_size_;
};

#endif //SPLIT_SECOND_GEOMETRY_BOX2D_H
