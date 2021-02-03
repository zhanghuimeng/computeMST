#pragma once

#include <cmath>
#include <iostream>

#include "Point2D.h"

namespace cmst
{
    /// Stores edges in 2D plane.
    ///
    /// The start and end points are stored in the edge.
    class Edge2D
    {
    public:

        Edge2D() {}

        /// Constructor
        ///
        /// Calculates the length.
        Edge2D(const Point2D& start, const Point2D& end) : m_start(start), m_end(end)
        {
            m_length = (m_start.x() - m_end.x()) * (m_start.x() - m_end.x())
                +  (m_start.y() - m_end.y()) * (m_start.y() - m_end.y());
            m_length = sqrt(m_length);
        }

        /// Returns the length of the edge.
        ///
        /// \return length of the edge
        double length() const { return m_length; }

        /// Returns the start point.
        ///
        /// \return start point
        Point2D start() const { return m_start; }

        /// Returns the end point.
        ///
        /// \return end point
        Point2D end() const { return m_end; }

        /// Compares edges by length.
        bool operator < (const Edge2D& right) const
        {
            return m_length < right.m_length;
        }

        /// Compares cmst::Edge2D by start point and end point.
        ///
        /// Take the cmst::Edge2D as undirected.
        bool operator == (const Edge2D& right) const
        {
            return (m_start==right.m_start && m_end==right.m_end) || (m_start==right.m_end && m_end==right.m_start);
        }

        /// Prints information about the edge.
        ///
        /// Prints the length, start point and end point.
        friend std::ostream& operator << (std::ostream& out, const Edge2D& e)
        {
            return out << "Edge " << std::endl << e.m_length << std::endl << e.m_start << ' ' << e.m_end;
        }

    protected:

        /// Swaps the start and end point.
        void swap_points() { std::swap(m_start, m_end); }

    private:

        Point2D m_start; ///< Start point.

        Point2D m_end; ///< End point.

        double m_length; ///< Length.
    };
}
