//
// Created by ittec on 11/4/2024.
//

#include <GLES2/gl2.h>
#include <EGL/egl.h>
#include <malloc.h>

#include "gl_assist.h"
#include "log.h"

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

void renderTriangleStripUsingProgram(GLuint program, const std::vector<GLfloat>& vertices) {
    if (program == 0) return;

    glClear(GL_COLOR_BUFFER_BIT);

    GLuint positionHandle = glGetAttribLocation(program, "aPosition");
    glEnableVertexAttribArray(positionHandle);

    glVertexAttribPointer(positionHandle, 2, GL_FLOAT, GL_FALSE, 0, &vertices[0]);

    glDrawArrays(GL_TRIANGLE_STRIP, 0, static_cast<int>(vertices.size()) / 2);

    glDisableVertexAttribArray(positionHandle);
}
