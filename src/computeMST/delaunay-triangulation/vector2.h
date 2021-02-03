#ifndef H_VECTOR2
#define H_VECTOR2

#include <iostream>
#include <cmath>

class Vec2f
{
	public:
		//
		// Constructors
		//

		Vec2f()
		{
			x = 0;
			y = 0;
		}

		Vec2f(double _x, double _y)
		{
			x = _x;
			y = _y;
		}

		Vec2f(const Vec2f &v)
		{
			x = v.x;
			y = v.y;
		}

		void set(const Vec2f &v)
		{
			x = v.x;
			y = v.y;
		}

		//
		// Operations
		//
		double dist2(const Vec2f &v) const
		{
			double dx = x - v.x;
			double dy = y - v.y;
			return dx * dx + dy * dy;
		}

		double dist(const Vec2f &v) const
		{
			return sqrtf(dist2(v));
		}

        friend std::ostream &operator << (std::ostream &str, Vec2f p)
        {
            str << "Point: x: " << p.x << " y: " << p.y;
            return str;
        }


        bool operator == (const Vec2f& right) const
        {
            return (x == right.x) && (y == right.y);
        }

        bool operator < (const Vec2f& right) const
        {
            if (x != right.x) return x < right.x;
            return y < right.y;
        }

		double x;
		double y;

};

#endif
