//
// Created by Victor Puchkarev on 11/11/24.
//

#include "camera.h"

// Constructors
camera::camera() = default;

camera::camera(mat intrinsics) : intrinsics_(std::move(intrinsics)) {}

camera::camera(mat intrinsics, vec3d position, vec3d target, vec3d up) :
    intrinsics_(std::move(intrinsics)), position_(position), target_(target), up_(up) {}

// Transformations

void camera::shift(vec3d offset) {
    position_ += offset;
    target_ += offset;
}

void camera::reposition(vec3d new_position) {
    target_ += new_position - position_;
    position_ = new_position;
}

void camera::set_target(vec3d target) {
    target_ = target;
}

void camera::set_up(vec3d up) {
    up_ = up;
}

// Computations.

vec3d camera::position() const {
    return position_;
}

vec3d camera::forward() const {
    return (target_ - position_).normalized();
}

vec3d camera::right() const {
    return forward().cross_product(up_).normalized();
}

vec3d camera::up() const {
    // We re-compute the true up based on forward and right vectors.
    return right().cross_product(forward()).normalized();
}

mat camera::view() const {
    const vec3d f = forward();
    const vec3d r = right();
    const vec3d u = up();

    return mat(4, 4, {
            r.x(), r.y(), r.z(), -r.dot_product(position_),
            u.x(), u.y(), u.z(), -u.dot_product(position_),
            -f.x(), -f.y(), -f.z(), f.dot_product(position_),
            0.0, 0.0, 0.0, 1.0
    }, mat::ROW).of_type(mat::kDefMajorType);
}

mat camera::intrinsics() const {
    return intrinsics_;
}

mat camera::mvp() const {
    return intrinsics() * view();
}

mat camera::perspective_matrix(float fov_deg, float near, float far,
                               float aspect_ratio) {
    const float fov_rad = fov_deg * 3.1415f / 180.0f;
    const float tanHalfFov = tan(fov_rad / 2.0f);

    return mat(4, 4, {
            1.0f / (aspect_ratio * tanHalfFov), 0.0f, 0.0f, 0.0f,
            0.0f, 1.0f / tanHalfFov, 0.0f, 0.0f,
            0.0f, 0.0f, -(far + near) / (far - near), -1.0f,
            0.0f, 0.0f, -(2.0f * far * near) / (far - near), 1.0f
    }, mat::ROW).of_type(mat::kDefMajorType);
}

mat camera::orthographic_matrix(float left, float right, float bottom, float top,
                                float near, float far) {
    return mat(4, 4, {
            2.0f / (right - left), 0.0f, 0.0f, -(right + left) / (right - left),
            0.0f, 2.0f / (top - bottom), 0.0f, -(top + bottom) / (top - bottom),
            0.0f, 0.0f, -2.0f / (far - near), -(far + near) / (far - near),
            0.0f, 0.0f, 0.0f, 1.0f
    }, mat::ROW).of_type(mat::kDefMajorType);
}