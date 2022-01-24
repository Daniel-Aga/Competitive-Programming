#define _USE_MATH_DEFINES
#include <algorithm>
#include <vector>
#include <math.h>

using namespace std;

const long long infty = 1e18;

struct Point
{
	long long x, y;
	Point(long long x, long long y) : x(x), y(y)
	{
	}
	Point() : Point(0, 0)
	{
	}
	Point operator+(Point& other)
	{
		return Point(x + other.x, y + other.y);
	}
	Point operator-(Point& other)
	{
		return Point(x - other.x, y - other.y);
	}
	Point operator-()
	{
		return Point(-x, -y);
	}
	bool operator==(const Point& other)
	{
		return x == other.x && y == other.y;
	}
};

long long dotProduct(Point a, Point b)
{
	return a.x*b.x + a.y * b.y;
}

long long crossProduct(Point a, Point b)
{
	return a.x*b.y - b.x*a.y;
}

long long direction(Point a, Point b, Point c) //returns (b-a)X(c-a)
{
	return crossProduct(b - a, c - a);
}

int counterClockwise(Point a, Point b, Point c) //Whether segment AC is counter-clockwise with respect to AB. 1 if counter-clockwise, 0 if they are colinear, -1 if clockwise.
{
	long long crProd = direction(a, b, c);
	if (crProd > 0)
	{
		return 1;
	}
	if (crProd < 0)
	{
		return -1;
	}
	return 0;
}

int turnLeft(Point a, Point b, Point c) //Whether segment BC is a left turn with respect to AB. 1 if left turn, 0 if they are colinear, -1 if right turn.
{
	return counterClockwise(a, b, c);
}

bool onSegment(Point p1, Point p2, Point q) //Whether Q is on segment P1P2, given Q is on the line P1P2.
{
	return min(p1.x, p2.x) <= q.x &&  max(p1.x, p2.x) >= q.x && min(p1.y, p2.y) <= q.y && max(p1.y, p2.y) >= q.y;
}

bool segmentsIntersect(Point p1, Point p2, Point q1, Point q2) //Returns True if the segments P1P2 and Q1Q2 Intersect.
{
	long long d1 = direction(q1, q2, p1);
	long long d2 = direction(q1, q2, p2);
	long long d3 = direction(p1, p2, q1);
	long long d4 = direction(p1, p2, q2);
	if (((d1 > 0 && d2 < 0) || (d1 < 0 && d2 > 0)) && ((d3 > 0 && d4 < 0) || (d3 < 0 && d4 > 0)))
	{
		return true;
	}
	if (d1 == 0 && onSegment(q1, q2, p1))
	{
		return true;
	}
	if (d2 == 0 && onSegment(q1, q2, p2))
	{
		return true;
	}
	if (d3 == 0 && onSegment(p1, p2, q1))
	{
		return true;
	}
	if (d4 == 0 && onSegment(p1, p2, q2))
	{
		return true;
	}
	return false;
}

bool cmpByY(Point& a, Point& b)
{
	if (a.y == b.y)
	{
		return a.x < b.x;
	}
	return a.y < b.y;
}

bool closerToOrigin(Point origin, Point a, Point b) //returns True if d(A,O) < d(B,O), given A,B,O are colinear.
{
	return abs(a.x - origin.x) < abs(b.x - origin.x);
}

struct ComparatorByAngle
{
	Point origin;
	ComparatorByAngle(Point origin) : origin(origin)
	{

	}
	bool operator()(Point& a, Point& b)
	{
		long long dir = direction(origin, a, b);
		if (dir == 0)
		{
			return closerToOrigin(origin, a, b);
		}
		return dir > 0;
	}
};

vector<Point> convexHull(vector<Point>& points)
{
	int minimalPoint = 0;
	for (int i = 1; i < points.size(); i++)
	{
		if (cmpByY(points[i], points[minimalPoint]))
		{
			minimalPoint = i;
		}
	}
	swap(points[0], points[minimalPoint]);
	sort(points.begin() + 1, points.end(), ComparatorByAngle(points[0]));
	vector<Point> ans = { points[0], points[1], points[2] };
	int i = 3;
	while (turnLeft(ans[0], ans[1], ans[2]) == 0) //TODO: Is this loop really needed?
	{
		ans.erase(ans.begin() + 1);
		ans.push_back(points[i++]);
	}
	for (; i < points.size(); i++)
	{
		while (turnLeft(ans[ans.size() - 2], ans.back(), points[i]) != 1)
		{
			ans.pop_back();
		}
		ans.push_back(points[i]);
	}
	return ans;
}

long double polygonArea(vector<Point>& poly) //Points in polygon are sorted in clockwise/counter-clockwise order.
{
	long double ans = 0;
	for (int i = 0; i < poly.size(); i++)
	{
		ans += crossProduct(poly[i], poly[i + 1]);
	}
	ans += crossProduct(poly.back(), poly.front());
	return abs(ans / 2);
}

bool pointInPolygon(vector<Point>& poly, Point p) //Also returns true if P is on one of the sides.
{
	Point extreme(infty, p.y);

	int sidesIntersect = 0;
	for (int i = 0; i < poly.size(); i++)
	{
		int next = (i + 1) % poly.size();

		if (segmentsIntersect(poly[i], poly[next], p, extreme))
		{
			if (direction(poly[i], p, poly[next]) == 0 && onSegment(poly[i], poly[next], p))
			{
				return true;
			}
			if (poly[i].y < p.y || poly[next].y < p.y) //This fixes the case where the ray hits a vertex, check Wikipedia for example: https://en.wikipedia.org/wiki/Point_in_polygon#Limited_precision
			{
				sidesIntersect++;
			}
		}
	}
	return sidesIntersect % 2 == 1;
}
