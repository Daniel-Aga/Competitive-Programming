#include <vector>
#include <algorithm>

using namespace std;

struct Node
{
	vector<int> neighbors;
	bool vis = false;
	int low;
	int d;
	int p;

	bool articulation = false;
	bool bridge = false; // Refers to edge (p, this).
};

int DFSTime = 0;

int DFS(Node* graph, int s) //Returns the number of tree edges from s (Needed only to check if the root is an articulation point).
{
	graph[s].vis = true;
	graph[s].d = DFSTime++;
	graph[s].low = graph[s].d;
	int ans = 0;
	for (int i = 0; i < graph[s].neighbors.size(); i++)
	{
		int currNei = graph[s].neighbors[i];
		if (graph[currNei].vis)
		{
			if (graph[s].p != currNei) //Should be changed if the graph is a multigraph.
			{
				graph[s].low = min(graph[s].low, graph[currNei].d);
			}
			continue;
		}
		ans++;
		graph[currNei].p = s;
		DFS(graph, currNei);
		graph[s].low = min(graph[s].low, graph[currNei].low);
		if (graph[currNei].low >= graph[s].d)
		{
			graph[s].articulation = true;
		}
	}
	if (graph[s].low == graph[s].d)
	{
		graph[s].bridge = true;
	}
	return ans;
}

void computeBiconnectivity(Node* graph, int n)
{
	graph[0].p = 0;
	int numSons = DFS(graph, 0);
	graph[0].bridge = false;
	graph[0].articulation = numSons > 1;
}