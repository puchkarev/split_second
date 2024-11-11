//
// Created by puchkarev on 11/7/24.
//

#ifndef SPLIT_SECOND_MAT_H
#define SPLIT_SECOND_MAT_H

#include <vector>
#include <functional>
#include <string>

#include "vec3d.h"

class mat {
public:
    // Constructors
    mat();
    mat(int rows, int cols, std::vector<float> vals);
    mat(int rows, int cols, float init);

    static mat zero(int rows, int cols);
    static mat one(int rows, int cols);
    static mat identity(int dim);

    static mat translate(const vec3d& translation);
    static mat rotate_x_roll(float rad);
    static mat rotate_y_pitch(float rad);
    static mat rotate_z_yaw(float rad);

    // Data accessors
    [[nodiscard]] int index(int row, int col) const;
    [[nodiscard]] int size() const;
    [[nodiscard]] float operator()(int row, int col) const;
    [[nodiscard]] float& operator()(int row, int col);
    [[nodiscard]] const float* data() const;

    // Checkers
    [[nodiscard]] bool empty() const;
    [[nodiscard]] bool verify() const;
    void assert_verify() const;
    [[nodiscard]] bool is_zero() const;
    [[nodiscard]] bool is_identity() const;

    // Perform an operation on every element of the mat.
    void operate(const std::function<void(int row, int col, float& v)>& op);
    void operate(const std::function<void(int row, int col, float v)>& op) const;
    [[nodiscard]] mat operated(const std::function<void(int row, int col, float& v)>& op) const;

    // Scalar operations
    [[nodiscard]] mat operator+(float scalar) const;
    [[nodiscard]] mat operator-(float scalar) const;
    [[nodiscard]] mat operator*(float scalar) const;
    [[nodiscard]] mat operator/(float scalar) const;

    void operator+=(float scalar);
    void operator-=(float scalar);
    void operator*=(float scalar);
    void operator/=(float scalar);

    // Matrix operations
    [[nodiscard]] mat operator+(const mat& other) const;
    [[nodiscard]] mat operator-(const mat& other) const;
    [[nodiscard]] mat operator*(const mat& other) const;

    void operator+=(const mat& other);
    void operator-=(const mat& other);
    void operator*=(const mat& other);

    void transpose();
    [[nodiscard]] mat transposed() const;

    [[nodiscard]] bool operator==(const mat& other) const;
    [[nodiscard]] bool operator!=(const mat& other) const;

    // For debugging;
    [[nodiscard]] std::string CriticalDebugString() const;
    [[nodiscard]] std::string DebugString() const;

    static void test();

private:
    int rows_;
    int cols_;
    std::vector<float> data_;
};

namespace std {

std::string to_string(const mat& m);   // NOLINT(*-dcl58-cpp)

}  // namespace std

#endif //SPLIT_SECOND_MAT_H
