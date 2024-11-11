//
// Created by Victor Puchkarev on 11/11/24.
//

#ifndef SPLIT_SECOND_UTIL_ASSERT_H
#define SPLIT_SECOND_UTIL_ASSERT_H

#include "log.h"

#define CUSTOM_INTERNAL_EQ(A, CMP, B, LOG_TYPE)     \
    {                       \
        const auto& a = A;   \
        const auto& b = B;   \
        if (a CMP b) {       \
        } else {            \
            LOG_TYPE("%s(%s) EXP_%s %s(%s)", #A, std::to_string(a).c_str(), #CMP, #B, std::to_string(b).c_str()); \
        }                   \
    }

#define ASSERT_EQ(A, B) CUSTOM_INTERNAL_EQ(A, ==, B, LOG_FATAL)
#define ASSERT_GT(A, B) CUSTOM_INTERNAL_EQ(A, >, B, LOG_FATAL)
#define ASSERT_LT(A, B) CUSTOM_INTERNAL_EQ(A, <, B, LOG_FATAL)
#define ASSERT_GE(A, B) CUSTOM_INTERNAL_EQ(A, >=, B, LOG_FATAL)
#define ASSERT_LE(A, B) CUSTOM_INTERNAL_EQ(A, <=, B, LOG_FATAL)
#define ASSERT_TRUE(A) ASSERT_EQ(A, true)
#define ASSERT_FALSE(A) ASSERT_EQ(A, false)

#define EXPECT_EQ(A, B) CUSTOM_INTERNAL_EQ(A, ==, B, LOG_ERROR)
#define EXPECT_GT(A, B) CUSTOM_INTERNAL_EQ(A, >, B, LOG_ERROR)
#define EXPECT_LT(A, B) CUSTOM_INTERNAL_EQ(A, <, B, LOG_ERROR)
#define EXPECT_GE(A, B) CUSTOM_INTERNAL_EQ(A, >=, B, LOG_ERROR)
#define EXPECT_LE(A, B) CUSTOM_INTERNAL_EQ(A, <=, B, LOG_ERROR)
#define EXPECT_TRUE(A) EXPECT_EQ(A, true)
#define EXPECT_FALSE(A) EXPECT_EQ(A, false)

#endif //SPLIT_SECOND_UTIL_ASSERT_H
