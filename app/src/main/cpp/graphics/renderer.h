//
// Created by Victor Puchkarev on 11/4/2024.
//

#ifndef SPLIT_SECOND_GRAPHICS_RENDERER_H
#define SPLIT_SECOND_GRAPHICS_RENDERER_H

#include <android/asset_manager.h>
#include <map>

#include "camera.h"
#include "model.h"

#include "../geometry/mat.h"

class renderer {
public:
    explicit renderer(AAssetManager *asset_manager);
    ~renderer();

    camera& mutable_camera();
    void start_new_render() const;
    void render(const Model& model,
                const mat& model_transform,
                float alpha);

private:
    uint load_texture(const std::string& asset_path);

    AAssetManager *asset_manager_ = nullptr;
    uint program_ = 0;
    std::map<std::string, uint> textures_;
    camera camera_;
};

#endif //SPLIT_SECOND_GRAPHICS_RENDERER_H
