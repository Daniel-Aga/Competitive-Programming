#include <math.h>
#include <algorithm>

using namespace std;

long long infty = 1000000000000000005;

long long sumOrNegInfty(long long a, long long b)
{
	if (a == -infty || b == -infty)
	{
		return -infty;
	}
	return a + b;
}

struct STNode
{
	long long maxPrefix;
	long long maxSuffix;
	long long maxSubarray;
	long long sum;
	int l;
	int r;
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
			arr[i + sz / 2].maxPrefix = vals[i];
			arr[i + sz / 2].maxSuffix = vals[i];
			arr[i + sz / 2].maxSubarray = vals[i];
			arr[i + sz / 2].sum = vals[i];
		}
		for (int i = sz_inp + sz / 2; i < sz; i++)
		{
			arr[i].maxPrefix = -infty;
			arr[i].maxSuffix = -infty;
			arr[i].maxSubarray = -infty;
			arr[i].sum = -infty;
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
		arr[x].sum = sumOrNegInfty(arr[left(x)].sum, arr[right(x)].sum);
		arr[x].maxPrefix = max(arr[left(x)].maxPrefix, sumOrNegInfty(arr[left(x)].sum, arr[right(x)].maxPrefix));
		arr[x].maxSuffix = max(arr[right(x)].maxSuffix, sumOrNegInfty(arr[right(x)].sum, arr[left(x)].maxSuffix));
		arr[x].maxSubarray = max(max(arr[left(x)].maxSubarray, arr[right(x)].maxSubarray), sumOrNegInfty(arr[left(x)].maxSuffix, arr[right(x)].maxPrefix));
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
			arr[x].sum = newVal;
			arr[x].maxPrefix = newVal;
			arr[x].maxSuffix = newVal;
			arr[x].maxSubarray = newVal;
			return;
		}
		updatePoint(left(x), k, newVal);
		updatePoint(right(x), k, newVal);
		arr[x].sum = sumOrNegInfty(arr[left(x)].sum, arr[right(x)].sum);
		arr[x].maxPrefix = max(arr[left(x)].maxPrefix, sumOrNegInfty(arr[left(x)].sum, arr[right(x)].maxPrefix));
		arr[x].maxSuffix = max(arr[right(x)].maxSuffix, sumOrNegInfty(arr[right(x)].sum, arr[left(x)].maxSuffix));
		arr[x].maxSubarray = max(max(arr[left(x)].maxSubarray, arr[right(x)].maxSubarray), sumOrNegInfty(arr[left(x)].maxSuffix, arr[right(x)].maxPrefix));
	}
	long long query()
	{
		return arr[1].maxSubarray;
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