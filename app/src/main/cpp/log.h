//
// Created by ittec on 11/4/2024.
//

#ifndef SPLIT_SECOND_LOG_H
#define SPLIT_SECOND_LOG_H

#include <android/log.h>

#define LOG_INFO(...) ((void)__android_log_print(ANDROID_LOG_INFO, "native-lib", __VA_ARGS__))
#define LOG_ERROR(...) ((void)__android_log_print(ANDROID_LOG_ERROR, "native-lib", __VA_ARGS__))
#define LOG_FATAL(...) ((void)__android_log_print(ANDROID_LOG_FATAL, "native-lib", __VA_ARGS__))

#define CUSTOM_INTERNAL_EQ(A, B, LOG_TYPE)     \
    {                       \
        const auto& a = A;   \
        const auto& b = B;   \
        if (a == b) {       \
        } else {            \
            LOG_TYPE("%s(%s) != %s(%s)", #A, std::to_string(a).c_str(), #B, std::to_string(b).c_str()); \
        }                   \
    }

#define ASSERT_EQ(A, B) CUSTOM_INTERNAL_EQ(A, B, LOG_FATAL)
#define ASSERT_TRUE(A) ASSERT_EQ(A, true)

#define EXPECT_EQ(A, B) CUSTOM_INTERNAL_EQ(A, B, LOG_ERROR)
#define EXPECT_TRUE(A) EXPECT_EQ(A, true)

#endif //SPLIT_SECOND_LOG_H
