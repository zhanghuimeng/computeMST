#pragma once

#include "Edge2D.h"

namespace cmst
{
    /// Edge with start and end point indices in an array.
    class IndexEdge2D : public Edge2D
    {

    public:

        IndexEdge2D() {}

        /// Store the edge as an undirected one. The two end points will be sorted according to
        /// indices.
        IndexEdge2D(Point2D p1, Point2D p2, int index1, int index2) : Edge2D(p1, p2)
        {
            if (index1 > index2)
            {
                std::swap(index1, index2);
                swap_points();
            }
            m_index[0] = index1;
            m_index[1] = index2;
        }

        /// The index of the starting point.
        int startIndex() const { return m_index[0]; }

        /// The index of the end point.
        int endIndex() const { return m_index[1]; }

        /// Compares edges by length.
        bool operator < (const IndexEdge2D& right) const
        {
            return length() < right.length();
        }

        /// Compares edges by length.
        bool operator > (const IndexEdge2D& right) const
        {
            return length() > right.length();
        }

        friend std::ostream &operator << (std::ostream &str, const IndexEdge2D& e)
        {
            str << "Indexed Edge " << e.m_index[0] << ", " << e.m_index[1] << std::endl;
            str << "     length: " << e.length() << std::endl;
            str << "     " << e.start() << " " << e.end();
            return str;
        }

    private:

        int m_index[2]; ///< Indices of the end points.
    };
}
