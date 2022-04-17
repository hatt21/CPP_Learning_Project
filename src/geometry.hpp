#pragma once

#include <algorithm>
#include <array>
#include <cassert>
#include <cmath>
#include <iostream>
#include <numeric>

template <int size, typename T> struct Point
{
    std::array<T, size> values {};
    Point() = default;

    Point(T x, T y) : values { x, y } { static_assert(size == 2); }

    Point(T x, T y, T z) : values { x, y, z } { static_assert(size == 3); }

    template <typename... numb>
    explicit Point(numb&&... numbers) : values { std::forward<T>(static_cast<T>(numbers))... }
    {
        static_assert(sizeof...(numbers) == size);
    }

    T& x()
    {
        static_assert(size >= 1);
        return values[0];
    }
    T x() const
    {
        static_assert(size >= 1);
        return values[0];
    }

    T& y()
    {
        static_assert(size >= 2);
        return values[1];
    }
    T y() const
    {
        static_assert(size >= 2);
        return values[1];
    }

    T& z()
    {
        static_assert(size >= 3);
        return values[2];
    }
    T z() const
    {
        static_assert(size >= 3);
        return values[2];
    }

    Point& operator+=(const Point& other)
    {
        std::transform(values.begin(), values.end(), other.values.begin(), values.begin(),
                       [](T val, T other_val) { return val + other_val; });
        return *this;
    }

    Point& operator-=(const Point& other)
    {
        std::transform(values.begin(), values.end(), other.values.begin(), values.begin(),
                       [](T val, T other_val) { return val - other_val; });
        return *this;
    }

    Point& operator*=(const float scalar)
    {
        std::transform(values.begin(), values.end(), values.begin(),
                       [scalar](T val) { return val * scalar; });
        return *this;
    }

    Point& operator*=(const Point& other)
    {
        x() *= other.x();
        y() *= other.y();
        return *this;
    }

    Point operator+(const Point& other) const
    {
        Point result = *this;
        result += other;
        return result;
    }

    Point operator*(const Point& other) const
    {
        Point result = *this;
        result *= other;
        return result;
    }

    Point operator*(const T scalar) const
    {
        Point result = *this;
        result *= scalar;
        return result;
    }

    Point operator-(const Point& other) const
    {
        Point result = *this;
        result -= other;
        return result;
    }

    Point operator-() const { return Point { -x(), -y(), -z() }; }

    T length() const
    {
        return std::sqrt(
            std::reduce(values.begin(), values.end(), 0.f, [](T v1, T v2) { return v1 + v2 * v2; }));
    }

    T distance_to(const Point& other) const { return (*this - other).length(); }

    Point& normalize(const T target_len = 1.0f)
    {
        const T current_len = length();
        if (current_len == 0)
        {
            throw std::logic_error("cannot normalize vector of length 0");
        }

        *this *= (target_len / current_len);
        return *this;
    }

    Point& cap_length(const T max_len)
    {
        assert(max_len > 0);

        const T current_len = length();
        if (current_len > max_len)
        {
            *this *= (max_len / current_len);
        }

        return *this;
    }
};

using Point3D = Point<3, float>;
using Point2D = Point<2, float>;

// our 3D-coordinate system will be tied to the airport: the runway is parallel to the x-axis, the z-axis
// points towards the sky, and y is perpendicular to both thus,
// {1,0,0} --> {.5,.5}   {0,1,0} --> {-.5,.5}   {0,0,1} --> {0,1}
inline Point2D project_2D(const Point3D& p)
{
    return { .5f * p.x() - .5f * p.y(), .5f * p.x() + .5f * p.y() + p.z() };
}
