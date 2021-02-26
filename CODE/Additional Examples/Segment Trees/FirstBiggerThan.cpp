#include <math.h>
#include <algorithm>

using namespace std;

int infty = 1000000005;

struct STMNode
{
	int mxInRange;
	int l;
	int r;
};

struct SegmentTreeMaxModified
{
	STMNode* arr;
	int sz;
	SegmentTreeMaxModified(int sz_inp, int* vals)
	{
		sz = 1 << ((int)log2(sz_inp) + 2);
		arr = new STMNode[sz];
		initControl(1);
		for (int i = 0; i < sz_inp; i++)
		{
			arr[i + sz / 2].mxInRange = vals[i];
		}
		for (int i = sz_inp + sz / 2; i < sz; i++)
		{
			arr[i].mxInRange = -infty;
		}
		initContent(1);
	}
	void initContent(int x)
	{
		if (isLeaf(x))
		{
			return;
		}
		initContent(left(x));
		initContent(right(x));
		arr[x].mxInRange = max(arr[left(x)].mxInRange, arr[right(x)].mxInRange);
	}
	void initControl(int x)
	{
		if (isLeaf(x))
		{
			arr[x].l = x - sz / 2;
			arr[x].r = x - sz / 2;
			return;
		}
		initControl(left(x));
		initControl(right(x));
		arr[x].l = arr[left(x)].l;
		arr[x].r = arr[right(x)].r;
	}
	void updatePoint(int k, int delta)
	{
		updatePoint(1, k, delta);
	}
	void updatePoint(int x, int k, int delta)
	{
		if (arr[x].l > k || arr[x].r < k)
		{
			return;
		}
		if (arr[x].l == k && arr[x].r == k)
		{
			arr[x].mxInRange += delta;
			return;
		}
		updatePoint(left(x), k, delta);
		updatePoint(right(x), k, delta);
		arr[x].mxInRange = max(arr[left(x)].mxInRange, arr[right(x)].mxInRange);
	}
	int queryFirstBiggerThan(int r)
	{
		return queryFirstBiggerThan(1, r);
	}
	int queryFirstBiggerThan(int x, int r)
	{
		if (arr[x].mxInRange < r)
		{
			return -1;
		}
		if (isLeaf(x))
		{
			return x - sz / 2;
		}
		if (arr[left(x)].mxInRange >= r)
		{
			return queryFirstBiggerThan(left(x), r);
		}
		return queryFirstBiggerThan(right(x), r);
	}

	int left(int x)
	{
		return 2 * x;
	}
	int right(int x)
	{
		return 2 * x + 1;
	}
	int parent(int x)
	{
		return x / 2;
	}
	bool isLeaf(int x)
	{
		return x >= sz / 2;
	}
};