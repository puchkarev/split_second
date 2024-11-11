//
// Created by ittec on 11/4/2024.
//

#ifndef SPLIT_SECOND_RENDERER_H
#define SPLIT_SECOND_RENDERER_H

#include <android/asset_manager.h>
#include <map>

#include "vec3d.h"
#include "box2d.h"
#include "model.h"

class renderer {
public:
    explicit renderer(AAssetManager *asset_manager);
    ~renderer();

    int load_texture(const std::string& asset_path);
    void configure_camera(vec3d camera_position, vec3d camera_target, vec3d camera_up,
                          float fov_deg, float near_plane, float far_plane,
                          float aspect_ratio) const;
    void start_new_render() const;
    void render(const Model& model);

private:
    AAssetManager *asset_manager_ = nullptr;
    int program_ = 0;
    std::map<std::string, int> textures_;
};


#endif //SPLIT_SECOND_RENDERER_H
