#include <math.h>

using namespace std;

struct FenwickTree
{
	long long* arr;
	long long sz;
	FenwickTree(long long sz_in)
	{
		sz = 1 << (long long)(log2(sz_in) + 1);
		arr = new long long[sz + 1];
		for (long long i = 0; i <= sz; i++)
		{
			arr[i] = 0;
		}
	}
	void update(long long x, long long delta)
	{
		for (x++; x <= sz; x += x & (-x))
		{
			arr[x] += delta;
		}
	}
	long long query(long long x)
	{
		long long ans = 0;
		for (x++; x > 0; x -= x & (-x))
		{
			ans += arr[x];
		}
		return ans;
	}
	long long query(long long x, long long y)
	{
		return query(y) - query(x - 1);
	}
	void initValues(long long* arr, long long sz_in)
	{
		for (long long i = 0; i < sz_in; i++)
		{
			update(i, arr[i]);
		}
	}
};
struct RangeFenwickTree
{
	FenwickTree ft;
	long long sz;
	RangeFenwickTree(long long sz_inp) : ft(sz_inp), sz(sz_inp)
	{
	}
	void initValues(long long* vals)
	{
		long long* diffVals = new long long[sz];
		diffVals[0] = vals[0];
		for (long long i = 1; i < sz; i++)
		{
			diffVals[i] = vals[i] - vals[i - 1];
		}
		ft.initValues(diffVals, sz);
	}
	void update(long long a, long long b, long long delta)
	{
		ft.update(a, delta);
		if (b < sz - 1)
		{
			ft.update(b + 1, -delta);
		}
	}
	long long query(long long a)
	{
		return ft.query(0, a);
	}
};
struct RangeRangeFenwickTree
{
	RangeFenwickTree ft1;
	RangeFenwickTree ft2;
	long long sz;
	RangeRangeFenwickTree(long long sz_in) : ft1(sz_in), ft2(sz_in), sz(sz_in)
	{

	}
	void update(long long x, long long y, long long delta)
	{
		ft1.update(x, y, delta);
		ft2.update(x, y, -delta * (x - 1));
		ft2.update(y + 1, sz, delta*(y - x + 1));
	}
	long long query(long long x)
	{
		if (x < 0)
		{
			return 0;
		}
		return ft1.query(x)*x + ft2.query(x);
	}
	long long query(long long x, long long y)
	{
		return query(y) - query(x - 1);
	}
	long long queryPoint(long long x)
	{
		return query(x, x);
	}
	void initValues(long long* arr, long long sz_in)
	{
		for (long long i = 0; i < sz_in; i++)
		{
			update(i, i, arr[i]);
		}
	}
};