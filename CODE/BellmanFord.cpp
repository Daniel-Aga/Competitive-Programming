#include <vector>
#include <algorithm>

using namespace std;

const long long infty = 1e18;

typedef pair<int, int> pii;

struct Node
{
	long long dist = infty;
	vector<pii> neighbors;
	int p;
};

struct Edge
{
	int u, v, w;
};

bool relaxEdge(Node* graph, Edge* edges, int i)
{
	if (graph[edges[i].v].dist > graph[edges[i].u].dist + edges[i].w)
	{
		graph[edges[i].v].p = edges[i].u;
		graph[edges[i].v].dist = graph[edges[i].u].dist + edges[i].w;
		return true;
	}
	return false;
}

bool BellmanFordIter(Node* graph, Edge* edges, int n, int m)
{
	bool ans = false;
	for (int i = 0; i < m; i++)
	{
		if (relaxEdge(graph, edges, i))
		{
			ans = true;
		}
	}
	return ans;
}

bool BellmanFord(Node* graph, Edge* edges, int n, int m) //Returns True if there is a negative cycle reachable from s.
{
	for (int i = 0; i < n - 1; i++)
	{
		BellmanFordIter(graph, edges, n, m);
	}
	return BellmanFordIter(graph, edges, n, m);
}
