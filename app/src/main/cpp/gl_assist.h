//
// Created by ittec on 11/4/2024.
//

#ifndef SPLIT_SECOND_GL_ASSIST_H
#define SPLIT_SECOND_GL_ASSIST_H

#include <EGL/egl.h>
#include <GLES2/gl2.h>
#include <vector>

#include "model.h"

namespace shaders {

const char* getVertexShaderSource();
const char* getFragmentShaderSource();

}  // shaders

GLuint loadShader(GLenum type, const char *shaderSrc);

GLuint loadTexture(unsigned char* data, int raw_data_len);

GLuint createProgram(const char *vertexShaderSrc, const char *fragmentShaderSrc);

void configureCamera(GLuint program, float cam_x, float cam_y, float cam_z,
                     float fov_deg, float near_plane, float far_plane, float aspect_ratio);

void startNewRender();

void renderModelUsingProgram(GLuint program, const Model& model, GLuint texture);

#endif //SPLIT_SECOND_GL_ASSIST_H
