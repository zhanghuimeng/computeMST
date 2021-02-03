#pragma once

#include <cmath>
#include <iostream>

namespace cmst
{
    /// Points in a 2D plane.
    class Point2D
    {
    public:

        /// Constructor
        Point2D(double x = 0.0, double y = 0.0) : m_x(x), m_y(y) {}

        /// Copy-constructor
        Point2D(const Point2D& other) : m_x(other.x()), m_y(other.y()) {}

        /// \return x
        double x() const { return m_x; }

        /// \return y
        double y() const { return m_y; }

        /// Compare points by x coordinates and y coordinates
        bool operator < (const Point2D& right) const
        {
            if (m_x != right.m_x) return m_x < right.m_x;
            return m_y < right.m_y;
        }

        /// Compare if two points are the same.
        ///
        /// Some epsilon loss is allowed.
        bool operator == (const Point2D& right) const
        {
            return abs(m_x - right.m_x) <= EPS_MIN && abs(m_y - right.m_y) <= EPS_MIN;
        }

        friend std::ostream& operator << (std::ostream& out, const Point2D& p)
        {
            return out << "Point (" << p.m_x << ", " << p.m_y << ")";
        }

    private:
        double m_x; ///<  x coordinate
        double m_y; ///< y coordinate
    };
}
