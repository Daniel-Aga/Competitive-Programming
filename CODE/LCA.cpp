#include <vector>

using namespace std;

const int MAX_LOG2_N = 18;

struct Node
{
	vector<int> neighbors;
	int p[MAX_LOG2_N + 1];
	int dep;
	bool vis = false;
};

void DFS(Node* graph, int s)
{
	graph[s].vis = true;
	for (int i = 0; i < graph[s].neighbors.size(); i++)
	{
		int currNei = graph[s].neighbors[i];
		if (graph[currNei].vis)
		{
			continue;
		}
		graph[currNei].dep = graph[s].dep + 1;
		graph[currNei].p[0] = s;
		DFS(graph, currNei);
	}
}

void LCAPreprocess(Node* graph, int n, int s)
{
	graph[s].p[0] = s;
	graph[s].dep = 0;
	DFS(graph, s);
	for (int i = 1; i <= MAX_LOG2_N; i++)
	{
		for (int j = 0; j < n; j++)
		{
			graph[j].p[i] = graph[graph[j].p[i - 1]].p[i - 1];
		}
	}
}

int LCAQuery(Node* graph, int u, int v)
{
	if (graph[u].dep > graph[v].dep)
	{
		return LCAQuery(graph, v, u);
	}
	int depDiff = graph[v].dep - graph[u].dep;
	int c = 0;
	while (depDiff > 0)
	{
		if (depDiff % 2 == 1)
		{
			v = graph[v].p[c];
		}
		c++;
		depDiff /= 2;
	}
	if (u == v)
	{
		return u;
	}
	for (int k = MAX_LOG2_N; k >= 0; k--)
	{
		if (graph[u].p[k] != graph[v].p[k])
		{
			u = graph[u].p[k];
			v = graph[v].p[k];
		}
	}
	return graph[u].p[0];
}