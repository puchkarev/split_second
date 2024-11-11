//
// Created by Victor Puchkarev on 11/4/2024.
//

#ifndef SPLIT_SECOND_GRAPHICS_RENDERER_H
#define SPLIT_SECOND_GRAPHICS_RENDERER_H

#include <android/asset_manager.h>
#include <map>

#include "model.h"
#include "camera.h"

#include "../geometry/mat.h"

class renderer {
public:
    explicit renderer(AAssetManager *asset_manager);
    ~renderer();

    int load_texture(const std::string& asset_path);
    camera& mutable_camera();
    void start_new_render() const;
    void render(const Model& model, const mat& model_transform = mat::identity(4));

private:
    AAssetManager *asset_manager_ = nullptr;
    int program_ = 0;
    std::map<std::string, int> textures_;
    camera camera_;
};

#endif //SPLIT_SECOND_GRAPHICS_RENDERER_H
