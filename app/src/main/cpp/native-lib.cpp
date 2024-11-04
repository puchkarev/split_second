#include <jni.h>
#include "GameState.h"

GameState* state_ = nullptr;

extern "C" JNIEXPORT void JNICALL
Java_com_example_split_1second_MainActivity_initGame(JNIEnv* /*env*/, jclass /*this*/) {
    state_ = new GameState();
}

extern "C" JNIEXPORT void JNICALL
Java_com_example_split_1second_MainActivity_render(JNIEnv* /*env*/, jclass /*this*/) {
    if (state_ != nullptr) {
        state_->render();
    }
}

extern "C" JNIEXPORT void JNICALL
Java_com_example_split_1second_MainActivity_touchEvent(JNIEnv* /*env*/, jclass /*this*/, int width, int height, float eventX, float eventY) {
    // Event coordinates are in pixels (just like width and length), with bottom left
    // bottom left: at x = 0, y = height
    // top right: x = width, y = 0

    // Game coordinates are in range of [-1.0f, 1.0f], [-1.0f, 1.0f]
    // bottom left: x =-1.0f, y=-1.0f
    // top right: x=1.0f, y=1.0f

    // Here we convert event coordinates to game coordinates.
    const float x = (eventX / static_cast<float>(width)) * 2.0f - 1.0f;
    const float y = (1.0f - eventY / static_cast<float>(height)) * 2.0f - 1.0f;
    if (state_ != nullptr) {
        state_->click(x, y);
    }
}
