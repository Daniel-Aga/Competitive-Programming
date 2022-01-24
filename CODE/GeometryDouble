#define _USE_MATH_DEFINES
#include <algorithm>
#include <vector>
#include <math.h>

using namespace std;

const long double infty = 1e18;
const long double EPS = 1e-10;

struct Point
{
	long double x, y;
	Point(long double x, long double y) : x(x), y(y)
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
		return abs(x - other.x) < EPS && abs(y - other.y) < EPS;
	}
};

long double dotProduct(Point a, Point b)
{
	return a.x*b.x + a.y * b.y;
}

long double crossProduct(Point a, Point b)
{
	return a.x*b.y - b.x*a.y;
}

long double direction(Point a, Point b, Point c) //returns (b-a)X(c-a)
{
	return crossProduct(b - a, c - a);
}

int counterClockwise(Point a, Point b, Point c) //Whether segment AC is counter-clockwise with respect to AB. 1 if counter-clockwise, 0 if they are colinear, -1 if clockwise.
{
	long double crProd = direction(a, b, c);
	if (crProd > EPS)
	{
		return 1;
	}
	if (crProd < -EPS)
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
	return min(p1.x, p2.x) < q.x + EPS && max(p1.x, p2.x) > q.x - EPS && min(p1.y, p2.y) < q.y + EPS && max(p1.y, p2.y) > q.y - EPS;
}

bool segmentsIntersect(Point p1, Point p2, Point q1, Point q2) //Returns True if the segments P1P2 and Q1Q2 Intersect.
{
	long double d1 = direction(q1, q2, p1);
	long double d2 = direction(q1, q2, p2);
	long double d3 = direction(p1, p2, q1);
	long double d4 = direction(p1, p2, q2);
	if (((d1 > EPS && d2 < -EPS) || (d1 < -EPS && d2 > EPS)) && ((d3 > EPS && d4 < -EPS) || (d3 < -EPS && d4 > EPS)))
	{
		return true;
	}
	if (abs(d1) < EPS && onSegment(q1, q2, p1))
	{
		return true;
	}
	if (abs(d2) < EPS && onSegment(q1, q2, p2))
	{
		return true;
	}
	if (abs(d3) < EPS && onSegment(p1, p2, q1))
	{
		return true;
	}
	if (abs(d4) < EPS && onSegment(p1, p2, q2))
	{
		return true;
	}
	return false;
}

bool cmpByY(Point& a, Point& b)
{
	if (abs(a.y - b.y) < EPS)
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
		long double dir = direction(origin, a, b);
		if (abs(dir) < EPS)
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
			if (abs(direction(poly[i], p, poly[next])) < EPS && onSegment(poly[i], poly[next], p))
			{
				return true;
			}
			if (poly[i].y < p.y - EPS || poly[next].y < p.y - EPS) //This fixes the case where the ray hits a vertex, check Wikipedia for example: https://en.wikipedia.org/wiki/Point_in_polygon#Limited_precision
			{
				sidesIntersect++;
			}
		}
	}
	return sidesIntersect % 2 == 1;
}
