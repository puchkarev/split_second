//
// Created by ittec on 11/4/2024.
//

#ifndef SPLIT_SECOND_GL_ASSIST_H
#define SPLIT_SECOND_GL_ASSIST_H

#include <EGL/egl.h>
#include <GLES2/gl2.h>
#include <vector>

GLuint loadShader(GLenum type, const char *shaderSrc);

GLuint createProgram(const char *vertexShaderSrc, const char *fragmentShaderSrc);

void renderTriangleStripUsingProgram(GLuint program, const std::vector<GLfloat>& vertices);

#endif //SPLIT_SECOND_GL_ASSIST_H
