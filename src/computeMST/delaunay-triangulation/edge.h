#ifndef H_EDGE
#define H_EDGE

#include "vector2.h"

class Edge
{
	public:
		Edge(const Vec2f &p1, const Vec2f &p2) : p1(p1), p2(p2) {};
		Edge(const Edge &e) : p1(e.p1), p2(e.p2) {};

		Vec2f p1;
		Vec2f p2;

		friend std::ostream &operator << (std::ostream &str, const Edge& e)
        {
            return str << "Edge " << e.p1 << ", " << e.p2;
        }

        bool operator == (const Edge & e2) const
        {
            return 	(p1 == e2.p1 && p2 == e2.p2) ||
                    (p1 == e2.p2 && p2 == e2.p1);
        }
};





#endif

