#include <jni.h>
#include <GLES2/gl2.h>
#include <EGL/egl.h>
#include <android/log.h>
#include <cstdlib>

#define LOGI(...) ((void)__android_log_print(ANDROID_LOG_INFO, "native-lib", __VA_ARGS__))
#define LOGE(...) ((void)__android_log_print(ANDROID_LOG_ERROR, "native-lib", __VA_ARGS__))

GLuint program;

const char *vertexShaderSource = R"(
    attribute vec4 aPosition;
    void main() {
        gl_Position = aPosition;
    }
)";

const char *fragmentShaderSource = R"(
    precision mediump float;
    void main() {
        gl_FragColor = vec4(1.0, 0.0, 0.0, 1.0); // Red color
    }
)";

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
            LOGE("Error compiling shader: %s", infoLog);
            free(infoLog);
        }
        glDeleteShader(shader);
        return 0;
    }
    return shader;
}

extern "C" JNIEXPORT void JNICALL
Java_com_example_split_1second_MainActivity_initOpenGL(JNIEnv* env, jclass /* this */) {
    LOGI("Initializing OpenGL");
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);   // Black Color

    GLuint vertexShader = loadShader(GL_VERTEX_SHADER, vertexShaderSource);
    GLuint fragmentShader = loadShader(GL_FRAGMENT_SHADER, fragmentShaderSource);

    program = glCreateProgram();
    if (program == 0) {
        LOGE("Error creating program");
        return;
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
            LOGE("Error linking program: %s", infoLog);
            free(infoLog);
        }
        glDeleteProgram(program);
        return;
    }

    glUseProgram(program);
}

extern "C" JNIEXPORT void JNICALL
Java_com_example_split_1second_MainActivity_render(JNIEnv* env, jclass /* this */) {
    // LOGI("Rendering");
    glClear(GL_COLOR_BUFFER_BIT);

    // Define square vertices
    GLfloat vertices[] = {
            -0.5f, -0.5f, // Bottom Left
            0.5f, -0.5f, // Bottom Right
            -0.5, 0.5f, // Top Left
            0.5f, 0.5f, // Top Right
    };

    GLuint positionHandle = glGetAttribLocation(program, "aPosition");
    glEnableVertexAttribArray(positionHandle);
    glVertexAttribPointer(positionHandle, 2, GL_FLOAT, GL_FALSE, 0, vertices);

    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

    glDisableVertexAttribArray(positionHandle);
}

// extern "C" JNIEXPORT jstring JNICALL
// Java_com_example_split_1second_MainActivity_stringFromJNI(
//         JNIEnv* env,
//         jobject /* this */) {
//     std::string hello = "Hello from C++";
//     return env->NewStringUTF(hello.c_str());
// }
