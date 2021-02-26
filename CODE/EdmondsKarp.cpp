#include <iostream>
#include <unordered_map>
#include <queue>
#include <algorithm>
 
using namespace std;
 
int infty = 1000000005;
 
typedef pair<int, long long> pil;
 
struct Node
{
	unordered_map<int, long long> outNeighbors;
	int p = -1;
	bool vis = false;
};

bool BFS(Node* graph, int s, int t)
{
	queue<int> q;
	q.push(s);
	graph[s].p = s;
	graph[s].vis = true;
	while (!q.empty())
	{
		int u = q.front();
		q.pop();
		if (u == t)
		{
			return true;
		}
		for (auto it = graph[u].outNeighbors.begin(); it != graph[u].outNeighbors.end(); ++it)
		{
			pil currP = *it;
			int currNei = currP.first;
			if (graph[currNei].vis)
			{
				continue;
			}
			graph[currNei].p = u;
			graph[currNei].vis = true;
			q.push(currNei);
		}
	}
	return false;
}
 
void resetGraph(Node* graph, int n)
{
	for (int i = 0; i < n; i++)
	{
		graph[i].vis = false;
		graph[i].p = -1;
	}
}
 
void subtractFromMap(unordered_map<int, long long>& mp, int k, long long x)
{
	mp[k] -= x;
	if (mp[k] == 0)
	{
		mp.erase(k);
	}
}
 
bool mapContains(unordered_map<int, long long>& mp, int k)
{
	return mp.find(k) != mp.end();
}
 
void addToMap(unordered_map<int, long long>& mp, int k, long long x)
{
	if (!mapContains(mp, k))
	{
		mp[k] = 0;
	}
	mp[k] += x;
}
 
long long usePath(Node* graph, int s, int t)
{
	int curr = t;
	long long mxFlowPath = infty;
	while (curr != s)
	{
		int currP = graph[curr].p;
		mxFlowPath = min(mxFlowPath, graph[currP].outNeighbors[curr]);
		curr = currP;
	}
	curr = t;
	while (curr != s)
	{
		int currP = graph[curr].p;
		subtractFromMap(graph[currP].outNeighbors, curr, mxFlowPath);
		addToMap(graph[curr].outNeighbors, currP, mxFlowPath);
		curr = currP;
	}
	return mxFlowPath;
}
 
long long maxFlow(Node* graph, int s, int t, int n)
{
	long long ans = 0;
	while (BFS(graph, s, t))
	{
		ans += usePath(graph, s, t);
		resetGraph(graph, n);
	}
	return ans;
}
 
int main()
{
    //Usage example:
	int n, m;
	cin >> n >> m;
	Node* graph = new Node[n];
	for (int i = 0; i < m; i++)
	{
		int u, v, w;
		cin >> u >> v >> w;
		u--; v--;
		addToMap(graph[u].outNeighbors, v, w);
	}
	long long ans = maxFlow(graph, 0, n - 1, n);
	cout << ans << endl;
	cin >> n;
}