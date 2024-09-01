#pragma once

#include "utils.hpp"
#include <cmath>
#include <glm/glm.hpp>

const double PI = 3.14159265359;

inline double radians(double degrees)
{
    return degrees * PI / 180;
}

// TODO: It would be better to have a single vector class with a template parameter for the number of components, which
//  will be stored in an array. I haven't done this yet because I don't know if the compiler will optimise the arrays
//  when they only have a few components, but I will look into it once there is more code using these classes.

template <typename T = double>
class Vector3
{
  public:
    T x = 0, y = 0, z = 0;
    Vector3(T x, T y, T z)
        : x{x}, y{y}, z{z}
    {
    }
    Vector3() = default;

    Vector3<T> normalised() const
    {
        return (Vector3{x, y, z} / magnitude());
    }

    [[nodiscard]] double magnitude() const
    {
        return std::sqrt(x * x + y * y + z * z);
    }

    Vector3<T> operator/(T scalar) const
    {
        return {x / scalar, y / scalar, z / scalar};
    }

    void operator+=(T scalar)
    {
        x += scalar;
        y += scalar;
        z += scalar;
    }

    void operator-=(T scalar)
    {
        operator+=(-scalar);
    }

    Vector3<T> operator+(Vector3<T> rhs) const
    {
        return {x + rhs.x, y + rhs.y, z + rhs.z};
    }

    Vector3<T> operator-(Vector3<T> rhs) const
    {
        return {x - rhs.x, y - rhs.y, z - rhs.z};
    }

    void operator+=(Vector3<T> rhs)
    {
        x += rhs.x;
        y += rhs.y;
        z += rhs.z;
    }

    void operator-=(Vector3<T> rhs)
    {
        x -= rhs.x;
        y -= rhs.y;
        z -= rhs.z;
    }

    bool operator>(Vector3<T> rhs) const
    {
        return x > rhs.x && y > rhs.y && z > rhs.z;
    }

    bool operator>=(Vector3<T> rhs) const
    {
        return x >= rhs.x && y >= rhs.y && z >= rhs.z;
    }

    bool operator<(Vector3<T> rhs) const
    {
        return x < rhs.x && y < rhs.y && z < rhs.z;
    }

    bool operator<=(Vector3<T> rhs) const
    {
        return x <= rhs.x && y <= rhs.y && z <= rhs.z;
    }

    template <typename NewType>
    explicit operator Vector3<NewType>() const
    {
        return {static_cast<NewType>(x), static_cast<NewType>(y), static_cast<NewType>(z)};
    }

    explicit operator glm::vec3() const
    {
        return {x, y, z};
    }

    explicit operator std::string() const
    {
        return "(" + std::to_string(x) + ", " + std::to_string(y) + ", " + std::to_string(z) + ")";
    }
};

template <typename T = double>
Vector3<T> operator*(T scalar, const Vector3<T> &vector)
{
    return {vector.x * scalar, vector.y * scalar, vector.z * scalar};
}

template <typename T = double>
Vector3<T> operator*(const Vector3<T> &vector, T scalar)
{
    return scalar * vector;
}

template <typename T = double>
T dot(Vector3<T> a, Vector3<T> b)
{
    return a.x * b.x + a.y * b.y + a.z * b.z;
}

template <typename T = double>
Vector3<T> cross(Vector3<T> a, Vector3<T> b)
{
    /*
     * |  i   j   k  |
     * | a.x a.y a.z |
     * | b.x b.y b.z |
     */
    return {a.y * b.z - a.z * b.y, -(a.x * b.z - a.z * b.x), a.x * b.y - a.y * b.x};
}

template <typename T = double>
class Vector2
{
  public:
    T x = 0, y = 0;

    Vector2<T> operator-(const Vector2<T> &rhs) const
    {
        return {x - rhs.x, y - rhs.y};
    }

    void operator*=(T scalar)
    {
        x *= scalar;
        y *= scalar;
    }
};

// M rows, N columns
// i = row index, j = column index
// TODO (currently using glm for matrices)
template <int M, int N, typename T>
class Matrix
{
  public:
    const Vector2<unsigned int> dim{N, M};

    [[nodiscard]] unsigned int det() const
    {
        return 0;
    }

    template <int N2>
    Matrix operator*(Matrix<M, N2, T> rhs) const
    {
        // https://en.wikipedia.org/wiki/Matrix_multiplication_algorithm#Iterative_algorithm
        Matrix<N, N2, T> result;

        for (int i = 0; i < N; i++)
        {
            for (int j = 0; j < N2; j++)
            {
                int sum = 0;
                for (int k = 0; k < M; k++)
                {
                    sum += this[i][k] * rhs[k][j];
                }
                result[i][j] = sum;
            }
        }

        return result;
    }

    // Returns the i-th row
    std::array<T, N> operator[](int i) const
    {
        return matrix[i];
    }

  private:
    // rows[column[]]
    std::array<std::array<T, N>, M> matrix;
};