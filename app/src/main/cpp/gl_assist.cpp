//
// Created by ittec on 11/4/2024.
//

#include <GLES2/gl2.h>
#include <EGL/egl.h>
#include <malloc.h>

#ifndef STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#endif  // STB_IMAGE_IMPLEMENTATION

#include "gl_assist.h"
#include "log.h"

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
        vNormal = aNormal;                  // Pass the normal to the fragment shader
        vTexCoord = aTexCoord;              // Pass the texture coordinates to the fragment shader
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

CameraBox getCameraBox(float fov_deg, float dist, float aspect_ratio) {
    const float top = tan(fov_deg * 3.14159f / 360.0f) * dist;
    return {
        .bottom = -top,
        .top = top,
        .left = -top * aspect_ratio,
        .right = top * aspect_ratio,
    };
}

void configureCamera(GLuint program, float cam_x, float cam_y, float cam_z,
                     float fov_deg, float near_plane, float far_plane, float aspect_ratio) {
    // Set up the camera matrices manually
    // View matrix: positions the camera in the world space
    // 4th column represents translation.
    float view[16] = {
            1, 0, 0, cam_x,
            0, 1, 0, cam_y,
            0, 0, 1, cam_z,
            0, 0, 0, 1
    };

    const CameraBox camera_box = getCameraBox(fov_deg, near_plane, aspect_ratio);

    LOG_INFO("Camera config pos(%f, %f, %f) x=(%f %f) y=(%f %f)",
             cam_x, cam_y, cam_z, camera_box.left, camera_box.right,
             camera_box.bottom, camera_box.top);

    // Projection matrix: defines the perspective projection
    float projection[16] = {
            (2 * near_plane) / (camera_box.right - camera_box.left), 0, 0, 0,
            0, (2 * near_plane) / (camera_box.top - camera_box.bottom), 0, 0,
            (camera_box.right + camera_box.left) / (camera_box.right - camera_box.left),
            (camera_box.top + camera_box.bottom) / (camera_box.top - camera_box.bottom),
            -(far_plane + near_plane) / (far_plane - near_plane), -1,
            0, 0, -(2 * far_plane * near_plane) / (far_plane - near_plane),
    };

    // Model matrix: defines the position and orientation of the model in the world space
    float model[16] = {
            1, 0, 0, 0,
            0, 1, 0, 0,
            0, 0, 1, 0,
            0, 0, 0, 1
    };

    // MVP matrix: Model-View-Projection matrix to combine transformations
    float mvp[16];
    for (int i = 0; i < 16; ++i) {
        mvp[i] = 0;
    }

    // Multiply projection, view, and model matrices to get the MVP matrix
    for (int row = 0; row < 4; ++row) {
        for (int col = 0; col < 4; ++col) {
            for (int k = 0; k < 4; ++k) {
                mvp[row * 4 + col] += projection[row * 4 + k] * view[k * 4 + col];
            }
        }
    }

    // Final MVP matrix after combining all transformations
    float finalMVP[16];
    for (int row = 0; row < 4; ++row) {
        for (int col = 0; col < 4; ++col) {
            finalMVP[row * 4 + col] = 0;
            for (int k = 0; k < 4; ++k) {
                finalMVP[row * 4 + col] += mvp[row * 4 + k] * model[k * 4 + col];
            }
        }
    }

    // Pass the final MVP matrix to the shader
    GLuint mvpLocation = glGetUniformLocation(program, "uMVP");
    if (mvpLocation != -1) {
        glUniformMatrix4fv(mvpLocation, 1, GL_FALSE, finalMVP);
    }
}

GLuint loadTexture(unsigned char* raw_data, int raw_data_len) {
    int width, height, channels;
    unsigned char *data = stbi_load_from_memory(raw_data, raw_data_len, &width, &height, &channels, 0);
    if (!data) {
        LOG_ERROR("Failed to load texture image");
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

void renderModelUsingProgram(GLuint program, const Model &model, GLuint texture) {
    if (program == 0) return;

    // Use the shader program
    glUseProgram(program);

    // Determine if we are using a texture
    GLint useTextureHandle = glGetUniformLocation(program, "uUseTexture");
    if (useTextureHandle != -1) {
        glUniform1i(useTextureHandle, texture != 0 ? 1 : 0);
    }

    // Bind the texture
    if (texture != 0) {
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, texture);
        GLint textureHandle = glGetUniformLocation(program, "uTexture");
        if (textureHandle != -1) {
            glUniform1i(textureHandle, 0);  // GL_TEXTURE0 corresponds to 0
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