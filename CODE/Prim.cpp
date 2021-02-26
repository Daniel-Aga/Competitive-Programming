#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

const long long infty = 1e18;

typedef pair<int, int> pii;

struct Node
{
	vector<int> neighbors;
	int distFromTree = infty;
	bool vis = false;
	int p = -1;
	int pEdge = -1;
};

struct Edge
{
	int u, v, w;
	int other(int x)
	{
		return x == u ? v : u;
	}
};

vector<int> Prim(Node* graph, Edge* edges, int s)
{
	vector<int> ans;
	graph[s].distFromTree = 0;
	graph[s].p = s;
	priority_queue<pii, vector<pii>, greater<pii>> q;
	q.push({ 0, s });
	while (!q.empty())
	{
		pii distAndU = q.top();
		q.pop();
		int u = distAndU.second;
		if (graph[u].vis)
		{
			continue;
		}
		graph[u].vis = true;
		if (s != u)
		{
			ans.push_back(graph[u].pEdge);
		}
		for (int i = 0; i < graph[u].neighbors.size(); i++)
		{
			int currEdge = graph[u].neighbors[i];
			int currNei = edges[currEdge].other(u);
			int currW = edges[currEdge].w;
			if (graph[currNei].vis)
			{
				continue;
			}
			if (graph[currNei].distFromTree > currW)
			{
				graph[currNei].distFromTree = currW;
				graph[currNei].p = u;
				graph[currNei].pEdge = currEdge;
				q.push({ currW, currNei });
			}
		}
	}
	return ans;
}