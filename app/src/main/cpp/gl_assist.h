//
// Created by ittec on 11/4/2024.
//

#ifndef SPLIT_SECOND_GL_ASSIST_H
#define SPLIT_SECOND_GL_ASSIST_H

#include <GLES2/gl2.h>
#include <EGL/egl.h>

GLuint loadShader(GLenum type, const char *shaderSrc);

GLuint createProgram(const char *vertexShaderSrc, const char *fragmentShaderSrc);

#endif //SPLIT_SECOND_GL_ASSIST_H
