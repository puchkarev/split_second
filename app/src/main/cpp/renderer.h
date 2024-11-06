//
// Created by ittec on 11/4/2024.
//

#ifndef SPLIT_SECOND_RENDERER_H
#define SPLIT_SECOND_RENDERER_H

#include "model.h"

class renderer {
public:
    renderer();
    ~renderer();

    int load_texture(const char *filePath) const;
    void configure_camera(float cam_x, float cam_y, float cam_z,
                          float fov_deg, float near_plane, float far_plane,
                          float aspect_ratio) const;

    void start_new_render() const;
    void render(const Model& model, int texture) const;

private:
    int program_ = 0;
};


#endif //SPLIT_SECOND_RENDERER_H
