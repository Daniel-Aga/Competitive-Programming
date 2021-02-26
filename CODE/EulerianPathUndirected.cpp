#include <vector>
#include <list>
#include <unordered_set>

using namespace std;

typedef pair<int, int> pii;

struct Node
{
	int index;
	unordered_set<int> neighbors;
	int deg;
};

list<int> path;

int computeEdgeDigit(int v)
{
	return v & 1;
}

int walkEdge(Node* graph, int s, list<int>::iterator it)
{
	int nei = *(graph[s].neighbors.begin());
	graph[s].neighbors.erase(nei);
	graph[s].deg--;
	path.insert(it, nei);
	return nei;
}

void findEulerCycle(Node* graph, int n, int s) //Assumes an euler cycle exists. can be adapted to euler path.
{
	if (graph[s].deg == 0)
	{
		return;
	}
	int curr = walkEdge(graph, s, path.end());
	while (curr != s)
	{
		curr = walkEdge(graph, curr, path.end());
	}
	for (auto it = path.begin(); it != path.end(); ++it)
	{
		int nei = *it;
		int c = 1;
		++it;
		while (graph[nei].deg > 0)
		{
			curr = walkEdge(graph, nei, it);
			c++;
			while (curr != nei)
			{
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