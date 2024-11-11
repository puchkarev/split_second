//
// Created by ittec on 11/4/2024.
//

#include "renderer.h"

#include <EGL/egl.h>
#include <GLES2/gl2.h>

#include "gl_assist.h"
#include "model.h"
#include "log.h"

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
    program_ = static_cast<int>(createProgram(shaders::getVertexShaderSource(),
                                              shaders::getFragmentShaderSource()));
}

renderer::~renderer() {
    if (program_ != 0) {
        glDeleteProgram(program_);
    }
}

int renderer::load_texture(const std::string& asset_path) {
    if (program_ == 0) return 0;
    if (textures_.find(asset_path) != textures_.end()) return textures_[asset_path];

    int len = 0;
    unsigned char* raw_data = read_file(asset_manager_, asset_path.c_str(), &len);
    if (raw_data == nullptr) return 0;
    int tex_id = static_cast<int>(loadTexture(raw_data, len));
    free(raw_data);
    textures_[asset_path] = tex_id;
    return tex_id;
}

void renderer::configure_camera(vec3d camera_position, vec3d camera_target, vec3d camera_up,
                                float fov_deg, float near_plane, float far_plane,
                                float aspect_ratio) const {
    if (program_ == 0) return;
    configureCamera(static_cast<GLuint>(program_),
                    camera_position, camera_target, camera_up,
                    fov_deg, near_plane, far_plane,
                    aspect_ratio);
}

void renderer::start_new_render() const {
    if (program_ == 0) return;
    startNewRender();
}

void renderer::render(const Model& model) {
    if (program_ == 0) return;

    const int texture = model.texture.empty() ? 0 : load_texture(model.texture);
    renderModelUsingProgram(static_cast<GLuint>(program_), model,
                            static_cast<GLuint>(texture));
}
