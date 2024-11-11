//
// Created by Victor Puchkarev on 11/4/2024.
//

#ifndef SPLIT_SECOND_UTIL_LOG_H
#define SPLIT_SECOND_UTIL_LOG_H

#include <android/log.h>

#define LOG_INFO(...) ((void)__android_log_print(ANDROID_LOG_INFO, "native-lib", __VA_ARGS__))
#define LOG_ERROR(...) ((void)__android_log_print(ANDROID_LOG_ERROR, "native-lib", __VA_ARGS__))
#define LOG_FATAL(...) ((void)__android_log_print(ANDROID_LOG_FATAL, "native-lib", __VA_ARGS__))

#endif //SPLIT_SECOND_UTIL_LOG_H
