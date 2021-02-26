#include <math.h>
#include <algorithm>

using namespace std;

struct STNode
{
	long long sm;
	int l;
	int r;
	bool respSet;
	int st; //value to set to
	STNode()
	{
		respSet = false;
		st = 0;
	}
};

struct SegmentTree
{
	STNode* arr;
	int sz;
	SegmentTree(int sz_inp, int* vals)
	{
		sz = 1 << ((int)log2(sz_inp) + 2);
		arr = new STNode[sz];
		initControl(1);
		for (int i = 0; i < sz_inp; i++)
		{
			arr[i + sz / 2].sm = vals[i];
		}
		for (int i = sz_inp + sz / 2; i < sz; i++)
		{
			arr[i].sm = 0;
		}
		initContent(1);
	}
	void updateNode(int x)
	{
		arr[x].sm = arr[left(x)].sm + arr[right(x)].sm;
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
	void doResp(int x)
	{
		if (arr[x].respSet)
		{
			giveRespSet(left(x), arr[x].st);
			giveRespSet(right(x), arr[x].st);
			arr[x].respSet = false;
			arr[x].st = 0;
		}
	}
	void giveRespSet(int x, int newVal)
	{
		arr[x].sm = ((long long)(arr[x].r - arr[x].l + 1)) * newVal;
		if (!isLeaf(x))
		{
			arr[x].respSet = true;
			arr[x].st = newVal;
		}
	}
	void updateRangeSet(int l, int r, int newVal)
	{
		updateRangeSet(1, l, r, newVal);
	}
	void updateRangeSet(int x, int l, int r, int newVal)
	{
		if (arr[x].l > r || arr[x].r < l)
		{
			return;
		}
		if (arr[x].l >= l && arr[x].r <= r)
		{
			giveRespSet(x, newVal);
			return;
		}
		doResp(x);
		updateRangeSet(left(x), l, r, newVal);
		updateRangeSet(right(x), l, r, newVal);
		updateNode(x);
	}
	long long queryRange(int l, int r)
	{
		return queryRange(1, l, r);
	}
	long long queryRange(int x, int l, int r)
	{
		if (arr[x].l > r || arr[x].r < l)
		{
			return 0;
		}
		if (arr[x].l >= l && arr[x].r <= r)
		{
			return arr[x].sm;
		}
		doResp(x);
		return queryRange(left(x), l, r) + queryRange(right(x), l, r);
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