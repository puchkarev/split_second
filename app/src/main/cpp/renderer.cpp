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

int renderer::load_texture(const char* filePath) {
    return static_cast<int>(loadTexture(filePath));
}

void renderer::render(const Model& model, int texture) const {
    if (program_ == 0) return;
    renderModelUsingProgram(static_cast<GLuint>(program_), model,
                            static_cast<GLuint>(texture));
}

