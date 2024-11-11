//
// Created by Victor Puchkarev on 11/4/2024.
//

#include <GLES2/gl2.h>
#include <EGL/egl.h>
#include <malloc.h>

#ifndef STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#endif  // STB_IMAGE_IMPLEMENTATION

#include "gl_assist.h"
#include "../util/log.h"
#include "../geometry/vec3d.h"
#include "../geometry/mat.h"

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

box2d getCameraBox(float fov_deg, float dist, float aspect_ratio) {
    const float height = tan(fov_deg * 3.14159f / 360.0f) * dist * 2.0f;
    return {0.0, 0.0, height * aspect_ratio, height};
}

mat getViewMatrix(vec3d eye, vec3d target, vec3d up) {
    vec3d f = (target - eye).normalized();                // Forward
    vec3d r = f.cross_product(up).normalized();     // Right
    vec3d u = r.cross_product(f);                   // True Up

    // LOG_INFO("f=%s r=%s u=%s", f.DebugString().c_str(), r.DebugString().c_str(), u.DebugString().c_str());

    return mat(4, 4, {
        r.x(), r.y(), r.z(), -r.dot_product(eye),
        u.x(), u.y(), u.z(), -u.dot_product(eye),
        -f.x(), -f.y(), -f.z(), f.dot_product(eye),
        0.0, 0.0, 0.0, 1.0
    });
}

mat getPerspectiveMatrix(float fov_deg, float aspect, float near, float far) {
    const float fov_rad = fov_deg * 3.1415f / 180.0f;
    const float tanHalfFov = tan(fov_rad / 2.0f);

    return mat(4, 4, {
            1.0f / (aspect * tanHalfFov), 0.0f, 0.0f, 0.0f,
            0.0f, 1.0f / tanHalfFov, 0.0f, 0.0f,
            0.0f, 0.0f, -(far + near) / (far - near), -1.0f,
            0.0f, 0.0f, -(2.0f * far * near) / (far - near), 1.0f
    });
}

mat getProjectionMatrix(float fov_deg, float aspect_ratio, float near_plane, float far_plane) {
    // Projection matrix: defines the perspective projection
    const box2d camera_box = getCameraBox(fov_deg, near_plane, aspect_ratio);
    return mat(4, 4, {
            (2 * near_plane) / (camera_box.right() - camera_box.left()), 0, 0, 0,
            0, (2 * near_plane) / (camera_box.top() - camera_box.bottom()), 0, 0,
            (camera_box.right() + camera_box.left()) / (camera_box.right() - camera_box.left()),
            (camera_box.top() + camera_box.bottom()) / (camera_box.top() - camera_box.bottom()),
            -(far_plane + near_plane) / (far_plane - near_plane), -1,
            0, 0, -(2 * far_plane * near_plane) / (far_plane - near_plane), 1
    });
}

mat getOrthographicMatrix(float left, float right, float bottom, float top, float near, float far) {
    return mat(4, 4, {
            2.0f / (right - left), 0.0f, 0.0f, -(right + left) / (right - left),
            0.0f, 2.0f / (top - bottom), 0.0f, -(top + bottom) / (top - bottom),
            0.0f, 0.0f, -2.0f / (far - near), -(far + near) / (far - near),
            0.0f, 0.0f, 0.0f, 1.0f
    });
}

void configureCamera(GLuint program,
                     vec3d camera_position,
                     vec3d camera_target,
                     vec3d camera_up,
                     float fov_deg, float near_plane, float far_plane, float aspect_ratio) {
    // LOG_INFO("Camera position=%s target=%s up=%s",
    //         camera_position.DebugString().c_str(),
    //         camera_target.DebugString().c_str(),
    //         camera_up.DebugString().c_str());

    // Create the view matrix using right, up, and forward vectors
    const mat view = getViewMatrix(camera_position, camera_target, camera_up);

    // Projection matrix: defines the perspective projection
    const mat projection = getPerspectiveMatrix(fov_deg, aspect_ratio, near_plane, far_plane);
    // const mat projection = getOrthographicMatrix(-5, 5, -10, 10, near_plane, far_plane);

    // Model matrix: defines the position and orientation of the model in the world space
    const mat model = mat::identity(4);

    // MVP matrix: Model-View-Projection matrix to combine transformations
    // Multiply projection, view, and model matrices to get the MVP matrix
    const mat mvp = projection * view * model;

    // LOG_INFO("view\n%s", view.DebugString().c_str());
    // LOG_INFO("projection\n%s", projection.DebugString().c_str());
    // LOG_INFO("model\n%s", model.DebugString().c_str());
    // LOG_INFO("mpv\n%s", mvp.DebugString().c_str());

    // Pass the final MVP matrix to the shader
    GLint mvpLocation = glGetUniformLocation(program, "uMVP");
    if (mvpLocation != -1) {
        glUniformMatrix4fv(mvpLocation, 1, GL_TRUE, mvp.data());
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