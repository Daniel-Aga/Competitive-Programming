#include <algorithm>
#include <math.h>

using namespace std;

const int infty = 1e9; //Neutral under the MIN operation.

struct STMNode
{
	int mn;
	int l;
	int r;
};

struct SegmentTreeMin
{
	STMNode* arr;
	int sz;
	SegmentTreeMin(int sz_inp, int* vals)
	{
		sz = 1 << ((int)log2(sz_inp) + 2);
		arr = new STMNode[sz];
		initControl(1);
		for (int i = 0; i < sz_inp; i++)
		{
			arr[i + sz / 2].mn = vals[i];
		}
		for (int i = sz_inp + sz / 2; i < sz; i++)
		{
			arr[i].mn = infty;
		}
		initContent(1);
	}
	void updateNode(int x)
	{
		arr[x].mn = min(arr[left(x)].mn, arr[right(x)].mn);
	}
	void initContent(int x)
	{
		if (isLeaf(x))
		{
			return;
		}
		initContent(left(x));
		initContent(right(x));
		updateNode(x);
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
	void updatePoint(int k, int newVal)
	{
		updatePoint(1, k, newVal);
	}
	void updatePoint(int x, int k, int newVal)
	{
		if (arr[x].l > k || arr[x].r < k)
		{
			return;
		}
		if (arr[x].l == k && arr[x].r == k)
		{
			arr[x].mn = newVal;
			return;
		}
		updatePoint(left(x), k, newVal);
		updatePoint(right(x), k, newVal);
		updateNode(x);
	}
	int queryRange(int a, int b)
	{
		return queryRange(1, a, b);
	}
	int queryRange(int x, int a, int b)
	{
		if (arr[x].l > b || arr[x].r < a)
		{
			return infty;
		}
		if (arr[x].l >= a && arr[x].r <= b)
		{
			return arr[x].mn;
		}
		return min(queryRange(left(x), a, b), queryRange(right(x), a, b));
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