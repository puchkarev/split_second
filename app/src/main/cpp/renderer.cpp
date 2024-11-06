//
// Created by ittec on 11/4/2024.
//

#include "renderer.h"

#include <EGL/egl.h>
#include <GLES2/gl2.h>

#include "gl_assist.h"
#include "model.h"

renderer::renderer() {
    program_ = static_cast<int>(createProgram(shaders::getVertexShaderSource(),
                                              shaders::getFragmentShaderSource()));
}

renderer::~renderer() {
    if (program_ != 0) {
        glDeleteProgram(program_);
    }
}

int renderer::load_texture(const char* filePath) const {
    if (program_ == 0) return 0;
    return static_cast<int>(loadTexture(filePath));
}

void renderer::configure_camera(float cam_x, float cam_y, float cam_z,
                                float fov_deg, float near_plane, float far_plane,
                                float aspect_ratio) const {
    if (program_ == 0) return;
    configureCamera(static_cast<GLuint>(program_), cam_x, cam_y, cam_z,
                    fov_deg, near_plane, far_plane, aspect_ratio);
}

void renderer::start_new_render() const {
    if (program_ == 0) return;
    startNewRender();
}

void renderer::render(const Model& model, int texture) const {
    if (program_ == 0) return;
    renderModelUsingProgram(static_cast<GLuint>(program_), model,
                            static_cast<GLuint>(texture));
}

