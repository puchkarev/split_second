#include <jni.h>
#include <android/asset_manager.h>
#include <android/asset_manager_jni.h>

#include "GameState.h"

#include "graphics/renderer.h"
#include "geometry/mat.h"

#include "util/log.h"

GameState* g_state_ = nullptr;

int g_screen_width_ = 1080;
int g_screen_height_ = 2400;

AAssetManager *g_asset_manager_ = nullptr;

void test() {
    LOG_INFO("Testing mat");
    mat::test();
}

extern "C" JNIEXPORT void JNICALL
Java_com_puchkarev_split_1second_MainActivity_initGame(JNIEnv* /*env*/, jclass /*this*/) {
    test();
    g_state_ = new GameState(std::make_unique<renderer>(g_asset_manager_));
}

extern "C" JNIEXPORT void JNICALL
Java_com_puchkarev_split_1second_MainActivity_render(JNIEnv* /*env*/, jclass /*this*/) {
    if (g_state_ != nullptr) {
        g_state_->render(g_screen_width_, g_screen_height_);
    }
}

extern "C" JNIEXPORT void JNICALL
Java_com_puchkarev_split_1second_MainActivity_touchEvent(JNIEnv* /*env*/, jclass /*this*/, int width, int height, float eventX, float eventY, int type) {
    // Event coordinates are in pixels (just like width and length), with bottom left
    // bottom left: at x = 0, y = height
    // top right: x = width, y = 0

    // Game coordinates are in range of [-1.0f, 1.0f], [-1.0f, 1.0f]
    // bottom left: x =-1.0f, y=-1.0f
    // top right: x=1.0f, y=1.0f

    // Here we convert event coordinates to game coordinates.
    const float x = (eventX / static_cast<float>(width)) * 2.0f - 1.0f;
    const float y = (1.0f - eventY / static_cast<float>(height)) * 2.0f - 1.0f;
    if (g_state_ != nullptr) {
        g_state_->click(x, y, static_cast<GameState::ClickType>(type));
    }
}

extern "C"
JNIEXPORT void JNICALL
Java_com_puchkarev_split_1second_MainActivity_nativeSetAssetManager(JNIEnv *env, jclass /* this */, jobject assetManager) {
    g_asset_manager_ = AAssetManager_fromJava(env, assetManager);
}

// JNI function to set screen size
extern "C" JNIEXPORT void JNICALL
Java_com_puchkarev_split_1second_MainActivity_setScreenSize(JNIEnv* /*env*/, jclass /*this*/, jint width, jint height) {
    g_screen_width_ = width;
    g_screen_height_ = height;
    LOG_INFO("Screen size changed to %d %d", width, height);
}