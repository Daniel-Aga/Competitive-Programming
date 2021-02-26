#include <vector>
#include <algorithm>

using namespace std;

struct Node
{
	vector<int> outNeighbors;
	bool vis;
};

vector<int> topoSorted;

bool DFS(Node* graph, int s) //Returns True if finds cycle.
{
	graph[s].vis = true;
	for (int i = 0; i < graph[s].outNeighbors.size(); i++)
	{
		int currNei = graph[s].outNeighbors[i];
		if (graph[currNei].vis)
		{
			return true;
		}
		if (DFS(graph, currNei))
		{
			return true;
		}
	}
	topoSorted.push_back(s);
	return false;
}

bool topologicalSort(Node* graph, int n) //Returns True if finds cycle.
{
	for (int i = 0; i < n; i++)
	{
		if (!graph[i].vis)
		{
			if (DFS(graph, i))
			{
				return true;
			}
		}
	}
	reverse(topoSorted.begin(), topoSorted.end());
	return false;
}