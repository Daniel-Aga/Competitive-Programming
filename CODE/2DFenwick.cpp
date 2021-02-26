#include <math.h>

using namespace std;

struct Fenwick2D
{
	long long** arr;
	int sz1, sz2;
	Fenwick2D(int sz1_inp, int sz2_inp)
	{
		sz1 = 1 << (int)(log2(sz1_inp) + 1);
		sz2 = 1 << (int)(log2(sz2_inp) + 1);
		arr = new long long*[sz1 + 1];
		for (int i = 0; i <= sz1; i++)
		{
			arr[i] = new long long[sz2 + 1];
			for (int j = 0; j <= sz2; j++)
			{
				arr[i][j] = 0;
			}
		}
	}
	void setValues(int** vals, int sz1_inp, int sz2_inp)
	{
		for (int i = 0; i < sz1_inp; i++)
		{
			for (int j = 0; j < sz2_inp; j++)
			{
				updatePoint(i, j, vals[i][j]);
			}
		}
	}
	void updatePoint(int x, int y, int delta)
	{
		x++; y++;
		for (; x <= sz1; x += x & (-x))
		{
			int currY = y;
			for (; currY <= sz2; currY += currY & (-currY))
			{
				arr[x][currY] += delta;
			}
		}
	}
	long long queryRange(int x1, int y1, int x2, int y2)
	{
		x1++; y1++; x2++; y2++;
		long long ans = queryRange(x2, y2);
		if (x1 > 1)
		{
			ans -= queryRange(x1 - 1, y2);
		}
		if (y1 > 1)
		{
			ans -= queryRange(x2, y1 - 1);
		}
		if (x1 > 1 && y1 > 1)
		{
			ans += queryRange(x1 - 1, y1 - 1);
		}
		return ans;
	}
	long long queryRange(int x, int y)
	{
		long long ans = 0;
		for (; x > 0; x -= x & (-x))
		{
			int currY = y;
			for (; currY > 0; currY -= currY & (-currY))
			{
				ans += arr[x][currY];
			}
		}
		return ans;
	}
};