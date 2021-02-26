#include <vector>

using namespace std;

typedef pair<int, int> pii;

struct Node
{
	vector<int> outNeighbors;
	vector<int> inNeighbors;
	int visited;
	int scc;
};

vector<int> sortedByF;

void DFS1(Node* graph, int s)
{
	graph[s].visited = 1;
	for (int i = 0; i < graph[s].outNeighbors.size(); i++)
	{
		int currNei = graph[s].outNeighbors[i];
		if (graph[currNei].visited == 1)
		{
			continue;
		}
		DFS1(graph, currNei);
	}
	sortedByF.push_back(s);
}

void DFS2(Node* graph, int s, int scc)
{
	graph[s].visited = 2;
	graph[s].scc = scc;
	for (int i = 0; i < graph[s].inNeighbors.size(); i++)
	{
		int currNei = graph[s].inNeighbors[i];
		if (graph[currNei].visited == 2)
		{
			continue;
		}
		DFS2(graph, currNei, scc);
	}
}

int SCC(Node* graph, int n) //Returns the number of SCCs.
{
	for (int i = 0; i < n; i++)
	{
		if (graph[i].visited != 1)
		{
			DFS1(graph, i);
		}
	}
	reverse(sortedByF.begin(), sortedByF.end());
	int scc = 0;
	for (int i = 0; i < n; i++)
	{
		int currNode = sortedByF[i];
		if (graph[currNode].visited != 2)
		{
			DFS2(graph, currNode, scc++);
		}
	}
	return scc;
}