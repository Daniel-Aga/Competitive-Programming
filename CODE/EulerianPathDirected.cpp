#include <vector>
#include <list>

using namespace std;

typedef pair<int, int> pii;

struct Node
{
	int index;
	vector<int> neighbors;
	int inDeg;
	int outDeg;
};

list<int> path;

int walkEdge(Node* graph, int s, list<int>::iterator it)
{
	int nei = graph[s].neighbors[graph[s].neighbors.size() - 1];
	graph[s].neighbors.pop_back();
	graph[s].outDeg--;
	graph[nei].inDeg--;
	path.insert(it, nei);
	return nei;
}

void findEulerPath(Node* graph, int s, int e, int n) //Assumes an euler path exists. Can be adapted to an euler cycle.
{
	if (graph[s].outDeg == 0)
	{
		return;
	}
	int curr = walkEdge(graph, s, path.end());
	while (curr != e)
	{
		if (graph[curr].outDeg == 0)
		{
			return;
		}
		curr = walkEdge(graph, curr, path.end());
	}
	for (auto it = path.begin(); it != path.end(); ++it)
	{
		int nei = *it;
		int c = 1;
		++it;
		while (graph[nei].outDeg > 0)
		{
			curr = walkEdge(graph, nei, it);
			c++;
			while (curr != nei)
			{
				if (graph[curr].outDeg == 0)
				{
					return;
				}
				curr = walkEdge(graph, curr, it);
				c++;
			}
		}
		for (int i = 0; i < c; i++)
		{
			--it;
		}
	}
}