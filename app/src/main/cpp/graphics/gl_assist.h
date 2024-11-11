//
// Created by Victor Puchkarev on 11/4/2024.
//

#ifndef SPLIT_SECOND_GRAPHICS_GL_ASSIST_H
#define SPLIT_SECOND_GRAPHICS_GL_ASSIST_H

#include <EGL/egl.h>
#include <GLES2/gl2.h>
#include <vector>

#include "../geometry/mat.h"

namespace shaders {

const char* getVertexShaderSource();
const char* getFragmentShaderSource();

}  // shaders

GLuint loadShader(GLenum type, const char *shaderSrc);
GLuint loadTexture(unsigned char* data, int raw_data_len);
GLuint createProgram(const char *vertexShaderSrc = nullptr, const char *fragmentShaderSrc = nullptr);

void startNewRender();
void configureCamera(GLuint program, const mat& mvp);
void renderModelUsingProgram(GLuint program,
                             const std::vector<GLfloat>& vertices,
                             const std::vector<GLfloat>& normals,
                             const std::vector<GLfloat>& texcoords,
                             GLuint texture);

#endif //SPLIT_SECOND_GRAPHICS_GL_ASSIST_H
