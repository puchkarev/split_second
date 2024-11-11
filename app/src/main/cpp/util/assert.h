//
// Created by Victor Puchkarev on 11/11/24.
//

#ifndef SPLIT_SECOND_UTIL_ASSERT_H
#define SPLIT_SECOND_UTIL_ASSERT_H

#include "log.h"

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

#endif //SPLIT_SECOND_UTIL_ASSERT_H
