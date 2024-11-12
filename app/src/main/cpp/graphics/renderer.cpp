//
// Created by Victor Puchkarev on 11/4/2024.
//

#include "renderer.h"

#include <android/asset_manager.h>
#include <map>

#include "camera.h"
#include "gl_assist.h"
#include "image.h"
#include "model.h"

#include "../geometry/mat.h"

#include "../util/log.h"

unsigned char* read_file(AAssetManager *asset_manager, const char* filePath, int *len) {
    if (asset_manager == nullptr) {
        LOG_ERROR("AssetManager not set");
        return nullptr;
    }

    AAsset *asset = AAssetManager_open(asset_manager, filePath, AASSET_MODE_BUFFER);
    if (!asset) {
        LOG_ERROR("Failed to open asset: %s", filePath);
        return nullptr;
    }

    off_t assetLength = AAsset_getLength(asset);
    auto *data = (unsigned char *)malloc(assetLength);
    AAsset_read(asset, data, assetLength);
    AAsset_close(asset);
    *len = assetLength;

    return data;
}

renderer::renderer(AAssetManager *asset_manager) : asset_manager_(asset_manager) {
    program_ = createProgram();
}

renderer::~renderer() {
    if (program_ != 0) {
        deleteProgram(program_);
    }
}

uint renderer::load_texture(const std::string& asset_path) {
    if (program_ == 0) return 0;
    if (textures_.find(asset_path) != textures_.end()) return textures_[asset_path];

    int len = 0;
    unsigned char* raw_data = read_file(asset_manager_, asset_path.c_str(), &len);
    if (raw_data == nullptr) return 0;
    const image image(raw_data, len);
    if (!image.valid()) return 0;
    uint tex_id = loadTexture(image.width(), image.height(), image.channels(),
                             image.data());
    free(raw_data);
    textures_[asset_path] = tex_id;
    return tex_id;
}

camera& renderer::mutable_camera() {
    return camera_;
}

void renderer::start_new_render() const {
    if (program_ == 0) return;
    startNewRender();
}

void renderer::render(const Model& model, const mat& model_transform) {
    if (program_ == 0) return;

    const uint texture = model.texture.empty() ? 0 : load_texture(model.texture);
    const mat mvp = camera_.mvp() * model_transform;
    configureCamera(program_,
                    mvp.data(), mvp.row_major());
    const std::vector<float> normals =
            model.normals.empty() ? Model::ComputeNormals(model.vertices) : model.normals;
    renderModelUsingProgram(program_, model.vertices, normals, model.texcoords, texture);
}
