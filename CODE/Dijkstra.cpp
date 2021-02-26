#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

long long infty = 1000000000000000000;

typedef pair<int, int> pii;
typedef pair<long long, int> pli;

struct Node
{
	vector<pii> outNeighbors;
	bool visited = false;
	long long dist = infty;
	int p;
};

void Dijkstra(Node* graph, int s)
{
	priority_queue<pli, vector<pli>, greater<pli>> q;
	q.push({ 0, s });
	graph[s].p = s;
	graph[s].dist = 0;
	while (!q.empty())
	{
		pli dAndU = q.top();
		q.pop();
		long long d = dAndU.first;
		int u = dAndU.second;
		if (graph[u].visited)
		{
			continue;
		}
		graph[u].visited = true;
		for (int i = 0; i < graph[u].outNeighbors.size(); i++)
		{
			pii currP = graph[u].outNeighbors[i];
			int currNei = currP.first;
			int currW = currP.second;
			if (graph[currNei].visited)
			{
				continue;
			}
			if (graph[currNei].dist > graph[u].dist + currW)
			{
				graph[currNei].dist = graph[u].dist + currW;
				graph[currNei].p = u;
				q.push(make_pair(graph[currNei].dist, currNei));
			}
		}
	}
}