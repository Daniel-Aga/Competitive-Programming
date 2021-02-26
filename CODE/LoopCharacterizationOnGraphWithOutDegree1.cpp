#include <vector>
#include <algorithm>

using namespace std;

const int MAX_LOG_2_N = 18;

struct Node
{
	int nxt[MAX_LOG_2_N + 1];
	int visStatus = 0;
	int loopId;
	int loopLen;
	bool inLoop;
	int distToStart; // if in loop;
	int distFromLoop; // if not in loop;
	int dep;
	bool mark = false; // "start" of loop;
};

int loops;

void DFS(Node* graph, int s)
{
	graph[s].visStatus = 1;
	int nxt = graph[s].nxt[0];
	if (s == nxt)
	{
		graph[s].loopId = loops++;
		graph[s].loopLen = 1;
		graph[s].inLoop = true;
		graph[s].distFromLoop = 0;
		graph[s].distToStart = 0;
		graph[s].mark = true;
	}
	else if (graph[nxt].visStatus == 1)
	{
		graph[s].loopId = loops++;
		graph[s].loopLen = graph[s].dep - graph[nxt].dep + 1;
		graph[s].inLoop = true;
		graph[s].distFromLoop = 0;
		graph[s].distToStart = 1;
		graph[nxt].mark = true;
	}
	else if (graph[nxt].visStatus == 2)
	{
		graph[s].loopId = graph[nxt].loopId;
		graph[s].loopLen = graph[nxt].loopLen;
		graph[s].inLoop = false;
		graph[s].distFromLoop = graph[nxt].distFromLoop + 1;
	}
	else
	{
		graph[nxt].dep = graph[s].dep + 1;
		DFS(graph, nxt);
		graph[s].loopId = graph[nxt].loopId;
		graph[s].loopLen = graph[nxt].loopLen;
		if (graph[nxt].inLoop)
		{
			if (graph[nxt].mark)
			{
				graph[s].inLoop = false;
				graph[s].distFromLoop = 1;
			}
			else
			{
				graph[s].inLoop = true;
				graph[s].distFromLoop = 0;
				graph[s].distToStart = graph[nxt].distToStart + 1;
			}
		}
		else
		{
			graph[s].inLoop = false;
			graph[s].distFromLoop = graph[nxt].distFromLoop + 1;
		}
	}
	graph[s].visStatus = 2;
}

void preprocess(Node* graph, int n)
{
	loops = 0;
	for (int i = 0; i < n; i++)
	{
		if (graph[i].visStatus == 0)
		{
			graph[i].dep = 0;
			DFS(graph, i);
		}
	}
	for (int i = 1; i <= MAX_LOG_2_N; i++)
	{
		for (int j = 0; j < n; j++)
		{
			graph[j].nxt[i] = graph[graph[j].nxt[i - 1]].nxt[i - 1];
		}
	}
}

int advance(Node* graph, int u, int k) //Advancing K times from U.
{
	int c = 0;
	while (k > 0)
	{
		if (k % 2 == 1)
		{
			u = graph[u].nxt[c];
		}
		c++;
		k /= 2;
	}
	return u;
}

int query(Node* graph, int u, int v) //Minimal number of advances to get from U to V.
{
	if (graph[u].loopId != graph[v].loopId)
	{
		return -1;
	}
	if (graph[v].inLoop)
	{
		if (graph[u].inLoop)
		{
			if (graph[v].distToStart <= graph[u].distToStart)
			{
				return graph[u].distToStart - graph[v].distToStart;
			}
			return graph[u].distToStart + graph[u].loopLen - graph[v].distToStart;
		}
		else
		{
			return query(graph, advance(graph, u, graph[u].distFromLoop), v) + graph[u].distFromLoop;
		}
	}
	else
	{
		if (graph[u].inLoop)
		{
			return -1;
		}
		int distDiff = graph[u].distFromLoop - graph[v].distFromLoop;
		if (distDiff < 0)
		{
			return -1;
		}
		if (advance(graph, u, distDiff) == v)
		{
			return distDiff;
		}
		return -1;
	}
}