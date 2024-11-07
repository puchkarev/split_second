//
// Created by puchkarev on 11/7/24.
//

#ifndef SPLIT_SECOND_VEC2D_H
#define SPLIT_SECOND_VEC2D_H


class vec2d {
public:
    vec2d() : vec2d(0.0f, 0.0f) {}
    vec2d(float x, float y) : x_(x), y_(y) {}
    [[nodiscard]] float x() const { return x_; }
    [[nodiscard]] float y() const { return x_; }

    vec2d operator +(const vec2d& other) const {
        return {x() + other.x(), y() + other.y()};
    }

    vec2d operator -(const vec2d other) const {
        return {x() - other.x(), y() - other.y()};
    }

    void operator += (const vec2d& other) {
        x_ += other.x();
        y_ += other.y();
    }

    void operator -= (const vec2d& other) {
        x_ -= other.x();
        y_ -= other.y();
    }

private:
    float x_;
    float y_;
};


#endif //SPLIT_SECOND_VEC2D_H
