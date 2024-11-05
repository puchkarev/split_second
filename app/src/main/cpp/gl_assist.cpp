//
// Created by ittec on 11/4/2024.
//

#include <GLES2/gl2.h>
#include <EGL/egl.h>
#include <malloc.h>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#include "gl_assist.h"
#include "log.h"

namespace shaders {
namespace {

const char *vertexShaderSource = R"(
    attribute vec4 aPosition;
    attribute vec3 aNormal;
    attribute vec2 aTexCoord;

    varying vec3 vNormal;
    varying vec2 vTexCoord;

    void main() {
        gl_Position = aPosition;
        vNormal = aNormal;
        vTexCoord = aTexCoord;
    }
)";

const char *fragmentShaderSource = R"(
    precision mediump float;

    varying vec3 vNormal;
    varying vec2 vTexCoord;

    void main() {
        // Use the normal and texture coordinates for rendering (simple example)
        gl_FragColor = vec4(vTexCoord, 0.5, 1.0); // Example rendering using texCoord as color
    }
)";

}  // namespace

const char *getVertexShaderSource() {
    return vertexShaderSource;
}

const char *getFragmentShaderSource() {
    return fragmentShaderSource;
}

}  // shaders

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
            char *infoLog = (char *)malloc(infoLen);
            glGetShaderInfoLog(shader, infoLen, nullptr, infoLog);
            LOG_ERROR("Error compiling shader: %s", infoLog);
            free(infoLog);
        }
        glDeleteShader(shader);
        return 0;
    }
    return shader;
}

GLuint createProgram(const char *vertexShaderSrc, const char *fragmentShaderSrc) {
    GLuint vertexShader = loadShader(GL_VERTEX_SHADER, vertexShaderSrc);
    GLuint fragmentShader = loadShader(GL_FRAGMENT_SHADER, fragmentShaderSrc);

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

    return program;
}

GLuint loadTexture(const char *filePath) {
    int width, height, channels;
    unsigned char *data = stbi_load(filePath, &width, &height, &channels, 0);
    if (!data) {
        LOG_ERROR("Failed to load texture image: %s", filePath);
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

    stbi_image_free(data);
    return texture;
}

void renderModelUsingProgram(GLuint program, const Model &model, GLuint texture) {
    if (program == 0) return;

    // Clear the color buffer
    // glClear(GL_COLOR_BUFFER_BIT);

    // glEnable(GL_DEPTH_TEST);
    // glEnable(GL_CULL_FACE);

    // Use the shader program
    glUseProgram(program);

    // Bind the texture
    if (texture != 0) {
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, texture);
        GLint textureHandle = glGetUniformLocation(program, "uTexture");
        if (textureHandle != -1) {
            glUniform1i(textureHandle, 0);
        }
    }

    // Pass in vertex position data
    GLuint positionHandle = glGetAttribLocation(program, "aPosition");
    if (positionHandle != -1) {
        glEnableVertexAttribArray(positionHandle);
        glVertexAttribPointer(positionHandle, 3, GL_FLOAT, GL_FALSE, 0, model.vertices.data());
    }

    // Pass in normal data, if available
    GLuint normalHandle = glGetAttribLocation(program, "aNormal");
    if (normalHandle != -1 && !model.normals.empty()) {
        glEnableVertexAttribArray(normalHandle);
        glVertexAttribPointer(normalHandle, 3, GL_FLOAT, GL_FALSE, 0, model.normals.data());
    }

    // Pass in texture coordinate data, if available
    GLuint texCoordHandle = glGetAttribLocation(program, "aTexCoord");
    if (texCoordHandle != -1 && !model.texcoords.empty()) {
        glEnableVertexAttribArray(texCoordHandle);
        glVertexAttribPointer(texCoordHandle, 2, GL_FLOAT, GL_FALSE, 0, model.texcoords.data());
    }

    // Draw the model using GL_TRIANGLES (assuming your model is composed of triangles)
    glDrawArrays(GL_TRIANGLES, 0, static_cast<GLsizei>(model.vertices.size() / 3));

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

    if (texture != 0) {
        glBindTexture(GL_TEXTURE_2D, 0);
    }
}