//
// Created by Victor Puchkarev on 11/4/2024.
//

#include "project_time.h"

#include <chrono>

long long getCurrentTimeMillis() {
    auto now = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(now.time_since_epoch());
    return duration.count();
}

float getCurrentTimeSeconds() {
    return static_cast<float>(getCurrentTimeMillis()) * 0.001f;
}