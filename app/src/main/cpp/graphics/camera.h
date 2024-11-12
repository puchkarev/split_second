//
// Created by Victor Puchkarev on 11/11/24.
//

#ifndef SPLIT_SECOND_GRAPHICS_CAMERA_H
#define SPLIT_SECOND_GRAPHICS_CAMERA_H

#include "../geometry/vec3d.h"
#include "../geometry/mat.h"

class camera {
public:
    // Constructors
    camera();
    explicit camera(mat intrinsics);
    camera(mat intrinsics, vec3d position, vec3d target, vec3d up);

    // Transformations
    void shift(vec3d offset);
    void reposition(vec3d new_position);
    void set_target(vec3d target);
    void set_up(vec3d up);

    // Computations.
    [[nodiscard]] vec3d position() const;
    [[nodiscard]] vec3d forward() const;
    [[nodiscard]] vec3d right() const;
    [[nodiscard]] vec3d up() const;
    [[nodiscard]] mat view() const;
    [[nodiscard]] mat intrinsics() const;
    [[nodiscard]] mat mvp() const;

    // Intrinsics computations.
    static mat perspective_matrix(float fov_y_deg, float near, float far,
                                  float aspect_ratio);
    static mat orthographic_matrix(float left, float right, float bottom, float top,
                                   float near, float far);

private:
    mat intrinsics_ = perspective_matrix(10.0f, 1.0f, 1000.0f, 0.5f);

    vec3d position_ = {0.0f, 0.0f, 20.0f};
    vec3d target_ = {0.0f, 0.0f, 0.0f};
    vec3d up_ = {0.0f, 1.0f, 0.0f};
};

#endif //SPLIT_SECOND_GRAPHICS_CAMERA_H
