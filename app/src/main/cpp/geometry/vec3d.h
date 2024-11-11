//
// Created by Victor Puchkarev on 11/7/24.
//

#ifndef SPLIT_SECOND_GEOMETRY_VEC3D_H
#define SPLIT_SECOND_GEOMETRY_VEC3D_H

#import <math.h>
#import <string>

#import "vec2d.h"

class vec3d {
public:
    vec3d();
    vec3d(float x, float y, float z);

    [[nodiscard]] vec2d xy() const;

    [[nodiscard]] float x() const;
    [[nodiscard]] float y() const;
    [[nodiscard]] float z() const;

    [[nodiscard]] float len() const;

    [[nodiscard]] vec3d normalized() const;
    void normalize();

    [[nodiscard]] vec3d operator +(const vec3d& other) const;
    void operator +=(const vec3d& other);

    [[nodiscard]] vec3d operator -(const vec3d& other) const;
    void operator -=(const vec3d& other);

    [[nodiscard]] vec3d operator *(float scalar) const;
    void operator *=(float scalar);

    [[nodiscard]] vec3d operator /(float scalar) const;
    void operator /=(float scalar);

    [[nodiscard]] bool operator ==(const vec3d& other) const;

    [[nodiscard]] vec3d cross_product(const vec3d& other) const;
    [[nodiscard]] float dot_product(const vec3d& other) const;

    [[nodiscard]] std::string DebugString() const;

private:
    float x_ = 0.0f;
    float y_ = 0.0f;
    float z_ = 0.0f;
};

#endif //SPLIT_SECOND_GEOMETRY_VEC3D_H
