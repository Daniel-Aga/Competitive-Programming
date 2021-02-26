#include <vector>
#include <algorithm>

using namespace std;

struct Node
{
	int index;
	int ufInd;
};

struct Edge
{
	int u, v, w;
};

struct UFNode
{
	int key;
	int p;
	int rank;
	void init(int key_inp)
	{
		key = key_inp;
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

bool cmpByW(Edge a, Edge b)
{
	return a.w < b.w;
}

long long kruskal(Node* graph, Edge* edges, UnionFind& uf, int n, int m)
{
	for (int i = 0; i < n; i++)
	{
		graph[i].ufInd = uf.make_set();
	}
	sort(edges, edges + m, cmpByW);
	long long ans = 0;
	for (int i = 0; i < m; i++)
	{
		if (uf.findSet(graph[edges[i].u].ufInd) != uf.findSet(graph[edges[i].v].ufInd))
		{
			ans += edges[i].w;
			uf.unionSets(graph[edges[i].u].ufInd, graph[edges[i].v].ufInd);
		}
	}
	return ans;
}
