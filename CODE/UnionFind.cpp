#include <vector>

using namespace std;

struct UFNode
{
	int p;
	int rank;
	void init(int key)
	{
		p = key;
		rank = 0;
	}
};

struct UnionFind
{
	vector<UFNode> arr;
	int make_set()
	{
		UFNode curr;
		curr.init(arr.size());
		arr.push_back(curr);
		return arr.size() - 1;
	}
	void link(int u, int v)
	{
		if (arr[u].rank < arr[v].rank)
		{
			arr[u].p = v;
		}
		else
		{
			arr[v].p = u;
			if (arr[u].rank == arr[v].rank)
			{
				arr[u].rank++;
			}
		}
	}
	void unionSets(int u, int v)
	{
		u = findSet(u);
		v = findSet(v);
		if (u != v)
		{
			link(u, v);
		}
	}
	int findSet(int x)
	{
		if (arr[x].p != x)
		{
			arr[x].p = findSet(arr[x].p);
		}
		return arr[x].p;
	}
};