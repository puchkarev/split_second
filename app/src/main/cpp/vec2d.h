//
// Created by puchkarev on 11/7/24.
//

#ifndef SPLIT_SECOND_VEC2D_H
#define SPLIT_SECOND_VEC2D_H

#import <math.h>
#import <string>

class vec2d {
public:
    vec2d();
    vec2d(float x, float y);

    [[nodiscard]] float x() const;
    [[nodiscard]] float y() const;

    [[nodiscard]] float len() const;

    [[nodiscard]] vec2d normalized() const;
    void normalize();

    [[nodiscard]]  vec2d operator +(const vec2d& other) const;
    void operator +=(const vec2d& other);

    [[nodiscard]]  vec2d operator -(const vec2d& other) const;
    void operator -=(const vec2d& other);

    [[nodiscard]]  vec2d operator *(float scalar) const;
    void operator *=(float scalar);

    [[nodiscard]] vec2d operator /(float scalar) const;
    void operator /=(float scalar);

    [[nodiscard]] bool operator ==(const vec2d& other) const;

    [[nodiscard]] float cross_product(const vec2d& other) const;
    [[nodiscard]] float dot_product(const vec2d& other) const;

    [[nodiscard]] std::string DebugString() const;

private:
    float x_ = 0.0f;
    float y_ = 0.0f;
};

#endif //SPLIT_SECOND_VEC2D_H
