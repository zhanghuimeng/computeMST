#ifndef H_TRIANGLE
#define H_TRIANGLE

#include "vector2.h"
#include "edge.h"

class Triangle
{
	public:
		Triangle(const Vec2f &_p1, const Vec2f &_p2, const Vec2f &_p3);

		bool containsVertex(const Vec2f &v);
		bool circumCircleContains(const Vec2f &v);

		Vec2f p1;
		Vec2f p2;
		Vec2f p3;
		Edge e1;
		Edge e2;
		Edge e3;

		///
		///
		/// This has to be a friend.
		friend std::ostream &operator << (std::ostream &str, const Triangle& t)
        {
            str << "Triangle:" << std::endl;
            str << t.p1 << std::endl;
            str << t.p2 << std::endl;
            str << t.p3 << std::endl;
            str << t.e1 << std::endl << t.e2 << std::endl << t.e3 << std::endl;
            return str;
        }

        bool operator == (const Triangle &t2) const
        {
            return	(p1 == t2.p1 || p1 == t2.p2 || p1 == t2.p3) &&
                    (p2 == t2.p1 || p2 == t2.p2 || p2 == t2.p3) &&
                    (p3 == t2.p1 || p3 == t2.p2 || p3 == t2.p3);
        }
};





#endif
