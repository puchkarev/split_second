//
// Created by Victor Puchkarev on 11/7/24.
//

#include "mat.h"

#include <vector>
#include <functional>
#include <string>

#include "vec3d.h"

#include "../util/log.h"
#include "../util/assert.h"

// Constructors
mat::mat(): mat(0, 0, {}) {}

mat::mat(int rows, int cols, float init, Major major) :
    mat(rows, cols, std::vector<float>(rows * cols, init), major) {}

mat::mat(int rows, int cols, std::vector<float> vals, Major major) :
    row_major_(major == ROW), rows_(rows), data_(std::move(vals)) {
    ASSERT_EQ(rows * cols, data_.size());
}

mat mat::zero(int rows, int cols, Major major) {
    return {rows, cols, 0.0f, major};
}

mat mat::one(int rows, int cols, Major major) {
    return {rows, cols, 1.0f, major};
}

mat mat::identity(int dim, Major major) {
    mat res(dim, dim, 0.0f, major);
    for (int d = 0; d < dim; ++d) {
        res(d, d) = 1.0f;
    }
    return res;
}

mat mat::translate(const vec3d& translation, Major major) {
    return mat(4, 4, {1, 0, 0, translation.x(),
                      0, 1, 0, translation.y(),
                      0, 0, 1, translation.z(),
                      0, 0, 0, 1}, mat::ROW).of_type(major);
}

mat mat::rotate_x_roll(float rad, Major major) {
    return mat(4, 4, {1, 0, 0, 0,
                      0, cos(rad), -sin(rad), 0,
                      0, sin(rad), cos(rad), 0,
                      0, 0, 0, 1}, mat::ROW).of_type(major);
}

mat mat::rotate_y_pitch(float rad, Major major) {
    return mat(4, 4, {cos(rad), 0, sin(rad), 0,
                      0, 1, 0, 0,
                      -sin(rad), 0, cos(rad), 0,
                      0, 0, 0, 1}, mat::ROW).of_type(major);
}

mat mat::rotate_z_yaw(float rad, Major major) {
    return mat(4, 4, {cos(rad), -sin(rad), 0, 0,
                      sin(rad), cos(rad), 0, 0,
                      0, 0, 1, 0,
                      0, 0, 0, 1}, mat::ROW).of_type(major);
}

// Data accessors
int mat::index(int row, int col) const {
    ASSERT_TRUE(row >= 0 && row < rows());
    ASSERT_TRUE(col >= 0 && col < cols());

    if (row_major()) {
        return row * cols() + col;
    } else {
        return col * rows() + row;
    }
}

int mat::size() const {
    return static_cast<int>(data_.size());
}

float mat::operator()(int row, int col) const {
    return data_[index(row, col)];
}

float& mat::operator()(int row, int col) {
    return data_[index(row, col)];
}

const float* mat::data() const {
    ASSERT_TRUE(!empty());
    return data_.data();
}

// Checkers
bool mat::empty() const {
    return rows() == 0;
}

bool mat::verify() const {
    return rows() * cols() == size();
}

bool mat::is_zero() const {
    return std::all_of(data_.begin(), data_.end(), [](float v) { return v == 0.0f; });
}

bool mat::is_identity() const {
    bool identity = true;
    operate([&identity](int row, int col, float v) { identity &= (v == (row == col ? 1.0 : 0.0)); });
    return identity;
}

mat::Major mat::type() const {
    return row_major() ? ROW : COL;
}

bool mat::row_major() const {
    return row_major_;
}

bool mat::col_major() const {
    return !row_major();
}

int mat::rows() const {
    return rows_;
}

int mat::cols() const {
    return size() / rows();
}

// Perform an operation on every element of the mat.
void mat::operate(const std::function<void(int row, int col, float& v)>& op) {
    ASSERT_TRUE(op != nullptr);

    for (int row = 0; row < rows(); ++row) {
        for (int col = 0; col < cols(); ++col) {
            op(row, col, this->operator()(row, col));
        }
    }
}

void mat::operate(const std::function<void(int row, int col, float v)>& op) const {
    ASSERT_TRUE(op != nullptr);

    for (int row = 0; row < rows(); ++row) {
        for (int col = 0; col < cols(); ++col) {
            op(row, col, this->operator()(row, col));
        }
    }
}

mat mat::operated(const std::function<void(int row, int col, float& v)>& op) const {
    ASSERT_TRUE(op != nullptr);

    mat res = *this;
    res.operate(op);
    return res;
}

// Scalar operations
mat mat::operator+(const float scalar) const {
    mat res = *this;
    res += scalar;
    return res;
}
mat mat::operator-(const float scalar) const {
    mat res = *this;
    res -= scalar;
    return res;
}
mat mat::operator*(const float scalar) const {
    mat res = *this;
    res *= scalar;
    return res;
}
mat mat::operator/(const float scalar) const {
    mat res = *this;
    res /= scalar;
    return res;
}

void mat::operator+=(const float scalar) {
    this->operate([scalar](int row, int col, float& v){ v += scalar; });
}
void mat::operator-=(const float scalar) {
    this->operator+=(scalar * -1.0f);
}
void mat::operator*=(const float scalar) {
    this->operate([scalar](int row, int col, float& v){ v *= scalar; });
}
void mat::operator/=(const float scalar) {
    ASSERT_TRUE(scalar != 0.0f);

    this->operator*=(1.0f / scalar);
}

// Matrix operations
mat mat::operator+(const mat& other) const {
    mat res = *this;
    res += other;
    return res;
}

mat mat::operator-(const mat& other) const {
    mat res = *this;
    res -= other;
    return res;
}

mat mat::operator*(const mat& other) const {
    ASSERT_TRUE(cols() == other.rows());
    if (empty() || other.empty()) return {};

    mat res(this->rows(), other.cols(),
            std::vector<float>(this->rows() * other.cols(), 0.0f),
            this->type());
    res.operate(
            [&a = *this, &other, cols = cols()](int row, int col, float& v) {
                for (int k = 0; k < cols; ++k) {
                    v += a(row, k) * other(k, col);
                }
            });
    return res;
}

void mat::operator+=(const mat& other) {
    ASSERT_TRUE(rows() == other.rows());
    ASSERT_TRUE(cols() == other.cols());

    this->operate([&other](int row, int col, float& v) { v += other(row, col); });
}
void mat::operator-=(const mat& other) {
    *this += other * -1.0f;
}
void mat::operator*=(const mat& other) {
    *this = *this * other;
}

mat mat::transposed() const {
#pragma clang diagnostic push
#pragma ide diagnostic ignored "ArgumentSelectionDefects"
    mat res(cols(), rows(), 0, type());
#pragma clang diagnostic pop
    for (int row = 0; row < rows(); ++row) {
        for (int col = 0; col < cols(); ++col) {
            res(col, row) = operator()(row, col);
        }
    }
    return res;
}
void mat::transpose() {
    *this = transposed();
}

mat mat::of_type(Major return_type) const {
    if (return_type == type()) return *this;
    if (empty()) return mat(0, 0, {}, return_type);
    mat tmp = transposed();
    return {rows(), cols(), std::move(tmp.data_), return_type};
}

bool mat::operator==(const mat& other) const {
    if (rows() != other.rows() || cols() != other.cols()) return false;
    for(int row = 0; row < rows(); ++row) {
        for (int col = 0; col < cols(); ++col) {
            if (operator()(row, col) != other(row, col)) return false;
        }
    }
    return true;
}

bool mat::operator!=(const mat& other) const {
    return !operator==(other);
}

std::string mat::CriticalDebugString() const {
    std::string out = "rows=" + std::to_string(rows()) + " data=[";
    for (int i = 0; i < size(); ++i) {
        out += std::to_string(data_[i]);
        if (i + 1 < data_.size()) {
            out += ", ";
        }
    }
    out += "]";
    return out;
}

std::string mat::DebugString() const {
    if (empty() || !verify()) {
        return CriticalDebugString();
    }

    std::string out;
    for (int row = 0; row < rows(); ++row) {
        for (int col = 0; col < cols(); ++col) {
            out += std::to_string(operator()(row, col));
            if (col + 1 != cols()) {
                out += ", ";
            }
        }
        if (row + 1 != rows()) {
            out += "\n";
        }
    }
    return out;
}

namespace std {

std::string to_string(const mat& m) { return m.DebugString(); } // NOLINT(*-dcl58-cpp)

}  // namespace std

void mat::test() {
    LOG_INFO("Testing zero");
    EXPECT_TRUE(mat::zero(0, 0).empty());
    EXPECT_TRUE(mat::one(0,0).empty());
    EXPECT_TRUE(mat::identity(0).empty());

    LOG_INFO("Testing one");
    mat z = mat::zero(5, 3);
    EXPECT_TRUE(!z.empty());
    EXPECT_TRUE(z.verify());
    EXPECT_TRUE(z.is_zero());
    EXPECT_TRUE(!z.is_identity());
    EXPECT_EQ(z(2, 1), 0.0f);

    mat g(3, 2, {1, 2, 3, 4, 5, 6}, mat::ROW);
    EXPECT_EQ(g(0, 0), 1);
    EXPECT_EQ(g(0, 1), 2);
    EXPECT_EQ(g(1, 0), 3);
    EXPECT_EQ(g(1, 1), 4);
    EXPECT_EQ(g(2, 0), 5);
    EXPECT_EQ(g(2, 1), 6);

    LOG_INFO("Testing some operations");
    mat o = mat::one(3, 8);
    EXPECT_TRUE(!o.empty());
    EXPECT_TRUE(o.verify());
    EXPECT_TRUE(!o.is_zero());
    EXPECT_TRUE(!o.is_identity());
    EXPECT_EQ(o(2, 1), 1.0f);
    EXPECT_EQ(o - o, o * 0.0f);
    EXPECT_EQ(o + o, o * 2.0f);

    LOG_INFO("Testing identity");
    o = mat::one(1, 1);
    EXPECT_TRUE(o.is_identity());
    mat i = mat::identity(3);
    EXPECT_TRUE(i.is_identity());
    EXPECT_EQ(i * i, i);
    EXPECT_EQ((i + i) / 2.0f, i);

    LOG_INFO("Testing addition");
    mat v1 = mat(2, 3, {1, 2, 3, 4, 5, 6}, mat::ROW);
    EXPECT_EQ(v1 + v1, mat(2, 3, {2, 4, 6, 8, 10, 12}, mat::ROW));

    LOG_INFO("Testing multiplication");
    mat v2 = mat(3, 2, {10, 11, 20, 21, 30, 31}, mat::ROW);
    EXPECT_EQ(v1 * v2, mat(2, 2, {140, 146, 320, 335}, mat::ROW));

    LOG_INFO("Testing transpose");
    EXPECT_EQ(v1.transposed(), mat(3, 2, {1, 4, 2, 5, 3, 6}, mat::ROW));

    LOG_INFO("Testing translation");
    EXPECT_EQ(mat::translate({-3, -2, -1}) * mat::identity(4),
              mat(4, 4, {
                  1, 0, 0, -3,
                  0, 1, 0, -2,
                  0, 0, 1, -1,
                  0, 0, 0, 1}, mat::ROW));
}