//
// Created by Victor Puchkarev on 11/4/2024.
//

#include <GLES2/gl2.h>
#include <EGL/egl.h>
#include <malloc.h>

#include "gl_assist.h"

#include "../util/log.h"

namespace shaders {
namespace {

const char *vertexShaderSource = R"(
    attribute vec4 aPosition;   // Vertex position
    attribute vec3 aNormal;     // Vertex normal (not used here)
    attribute vec2 aTexCoord;   // Texture coordinates for this vertex

    varying vec3 vNormal;       // Passing normal to fragment shader
    varying vec2 vTexCoord;     // Passing texture coordinates to fragment shader

    uniform mat4 uMVP;          // Model-View-Projection matrix

    void main() {
        gl_Position = uMVP * aPosition;     // Transform the vertex position
        vNormal = aNormal;                           // Pass the normal to the fragment shader
        vTexCoord = aTexCoord;                       // Pass the texture coordinates to the fragment shader
    }
)";

const char *fragmentShaderSource = R"(
    precision mediump float;

    varying vec3 vNormal;       // Normal for lighting (not used in this example)
    varying vec2 vTexCoord;     // Texture coordinates from the vertex shader

    uniform sampler2D uTexture; // The texture sampler
    uniform bool uUseTexture;   // Flag to determine if a texture is available

    void main() {
        if (uUseTexture) {
            // Sample the texture using the texture coordinates
            vec4 textureColor = texture2D(uTexture, vTexCoord);
            gl_FragColor = textureColor;
        } else {
            // Use the gradient if no texture is supplied
            gl_FragColor = vec4(vTexCoord, 0.5, 1.0);
        }
    }
)";

const char *getVertexShaderSource() {
    return vertexShaderSource;
}

const char *getFragmentShaderSource() {
    return fragmentShaderSource;
}

GLuint loadShader(GLenum type, const char *shaderSrc) {
    GLuint shader = glCreateShader(type);
    glShaderSource(shader, 1, &shaderSrc, nullptr);
    glCompileShader(shader);

    GLint compiled;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &compiled);
    if (!compiled) {
        GLint infoLen = 0;
        glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &infoLen);
        if (infoLen > 0) {
            char *infoLog = (char *) malloc(infoLen);
            glGetShaderInfoLog(shader, infoLen, nullptr, infoLog);
            LOG_ERROR("Error compiling shader: %s", infoLog);
            free(infoLog);
        }
        glDeleteShader(shader);
        return 0;
    }
    return shader;
}

}  // namespace
}  // namespace shaders

uint createProgram() {
    GLuint vertexShader = shaders::loadShader(GL_VERTEX_SHADER, shaders::vertexShaderSource);
    GLuint fragmentShader = shaders::loadShader(GL_FRAGMENT_SHADER, shaders::fragmentShaderSource);

    GLuint program = glCreateProgram();
    if (program == 0) {
        LOG_ERROR("Error creating program");
        return 0;
    }

    glAttachShader(program, vertexShader);
    glAttachShader(program, fragmentShader);
    glLinkProgram(program);

    GLint linked;
    glGetProgramiv(program, GL_LINK_STATUS, &linked);
    if (!linked) {
        GLint infoLen = 0;
        glGetProgramiv(program, GL_INFO_LOG_LENGTH, &infoLen);
        if (infoLen > 0) {
            char *infoLog = (char *)malloc(infoLen);
            glGetProgramInfoLog(program, infoLen, nullptr, infoLog);
            LOG_ERROR("Error linking program: %s", infoLog);
            free(infoLog);
        }
        glDeleteProgram(program);
        return 0;
    }

    glUseProgram(program);

    return static_cast<uint>(program);
}

void deleteProgram(uint program) {
    glDeleteProgram(static_cast<GLuint>(program));
}

void configureCamera(uint program, const float* mvp, bool row_major) {
    // Pass the final MVP matrix to the shader
    GLint mvpLocation = glGetUniformLocation(static_cast<GLuint>(program), "uMVP");
    if (mvpLocation != -1) {
        glUniformMatrix4fv(mvpLocation, 1,
                           row_major ? GL_TRUE : GL_FALSE,
                           mvp);
    }
}

uint loadTexture(int width, int height, int channels, unsigned char* data) {
    if (data == nullptr) {
        LOG_ERROR("No texture data provided");
        return 0;
    }

    GLuint texture;
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);

    GLenum format = (channels == 3) ? GL_RGB : GL_RGBA;
    glTexImage2D(GL_TEXTURE_2D, 0, static_cast<GLint>(format),
                 width, height, 0, format, GL_UNSIGNED_BYTE, data);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    return static_cast<uint>(texture);
}

void startNewRender() {
    // Enable depth test
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);

    // Enable face culling (optional)
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);
    glFrontFace(GL_CCW);

    // Clear both color and depth buffers before drawing each frame
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void renderModelUsingProgram(uint program,
                             const std::vector<float>& vertices,
                             const std::vector<float>& normals,
                             const std::vector<float>& texcoords,
                             uint texture) {
    if (program == 0) return;

    const auto gpu_program = static_cast<GLuint>(program);
    const auto gpu_texture = static_cast<GLuint>(texture);

    // Use the shader program
    glUseProgram(gpu_program);

    // Determine if we are using a texture
    GLint useTextureHandle = glGetUniformLocation(gpu_program, "uUseTexture");
    if (useTextureHandle != -1) {
        glUniform1i(useTextureHandle, gpu_texture != 0 ? 1 : 0);
    }

    // Bind the texture
    if (gpu_texture != 0) {
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, gpu_texture);
        GLint textureHandle = glGetUniformLocation(gpu_program, "uTexture");
        if (textureHandle != -1) {
            glUniform1i(textureHandle, 0);  // GL_TEXTURE0 corresponds to 0
        }
    }

    // Pass in vertex position data
    GLuint positionHandle = glGetAttribLocation(gpu_program, "aPosition");
    if (positionHandle != -1) {
        glEnableVertexAttribArray(positionHandle);
        glVertexAttribPointer(positionHandle, 3, GL_FLOAT, GL_FALSE,
                              0, static_cast<const GLfloat*>(vertices.data()));
    }

    // Pass in normal data, if available
    GLuint normalHandle = glGetAttribLocation(gpu_program, "aNormal");
    if (normalHandle != -1 && !normals.empty()) {
        glEnableVertexAttribArray(normalHandle);
        glVertexAttribPointer(normalHandle, 3, GL_FLOAT, GL_FALSE,
                              0, static_cast<const GLfloat*>(normals.data()));
    }

    // Pass in texture coordinate data, if available
    GLuint texCoordHandle = glGetAttribLocation(gpu_program, "aTexCoord");
    if (texCoordHandle != -1 && !texcoords.empty()) {
        glEnableVertexAttribArray(texCoordHandle);
        glVertexAttribPointer(texCoordHandle, 2, GL_FLOAT, GL_FALSE,
                              0, static_cast<const GLfloat*>(texcoords.data()));
    }

    // Draw the model using GL_TRIANGLES (assuming your model is composed of triangles)
    glDrawArrays(GL_TRIANGLES, 0, static_cast<GLsizei>(vertices.size() / 3));

    // Disable attribute arrays to clean up
    if (positionHandle != -1) {
        glDisableVertexAttribArray(positionHandle);
    }
    if (normalHandle != -1) {
        glDisableVertexAttribArray(normalHandle);
    }
    if (texCoordHandle != -1) {
        glDisableVertexAttribArray(texCoordHandle);
    }

    if (gpu_texture != 0) {
        glBindTexture(GL_TEXTURE_2D, 0);
    }
}