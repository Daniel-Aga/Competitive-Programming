#include <iostream>
#include <unordered_map>
#include <queue>
#include <algorithm>
 
using namespace std;
 
int infty = 1000000005;
 
typedef pair<int, int> pii;
 
struct Node
{
	unordered_map<int, int> outNeighbors;
	unordered_map<int, int> startOutNeighbors;
	unordered_map<int, int> usedEdges;
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
			pii currP = *it;
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
 
void subtractFromMap(unordered_map<int, int>& mp, int k, int x)
{
	mp[k] -= x;
	if (mp[k] == 0)
	{
		mp.erase(k);
	}
}
 
bool mapContains(unordered_map<int, int>& mp, int k)
{
	return mp.find(k) != mp.end();
}
 
void addToMap(unordered_map<int, int>& mp, int k, int x)
{
	if (!mapContains(mp, k))
	{
		mp[k] = 0;
	}
	mp[k] += x;
}
 
int usePath(Node* graph, int s, int t)
{
	int curr = t;
	int mxFlowPath = infty;
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
 
void computeUsedEdges(Node* graph, int n)
{
	for (int i = 0; i < n; i++)
	{
		for (auto it = graph[i].startOutNeighbors.begin(); it != graph[i].startOutNeighbors.end(); ++it)
		{
			pii sPair = *it;
			int currNei = sPair.first;
			int sVal = sPair.second;
			int nVal = 0;
			if (mapContains(graph[i].outNeighbors, currNei))
			{
				nVal = graph[i].outNeighbors[currNei];
			}
			if (sVal > nVal)
			{
				graph[i].usedEdges[currNei] = sVal - nVal;
			}
		}
	}
}
 
vector<int> getPath(Node* graph, int s, int t)
{
	vector<int> ans;
	int curr = s;
	while (curr != t)
	{
		ans.push_back(curr);
		int nxtNei = (*graph[curr].usedEdges.begin()).first;
		subtractFromMap(graph[curr].usedEdges, nxtNei, 1);
		curr = nxtNei;
	}
	ans.push_back(t);
	return ans;
}
 
int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);
 
	int n, m;
	cin >> n >> m;
	Node* graph = new Node[n];
	for (int i = 0; i < m; i++)
	{
		int u, v;
		cin >> u >> v;
		u--; v--;
		addToMap(graph[u].outNeighbors, v, 1);
		addToMap(graph[u].startOutNeighbors, v, 1);
	}
	long long ans = maxFlow(graph, 0, n - 1, n);
	cout << ans << endl;
	computeUsedEdges(graph, n);
	for (int i = 0; i < ans; i++)
	{
		vector<int> currPath = getPath(graph, 0, n - 1);
		cout << currPath.size() << endl;
		for (int i = 0; i < currPath.size(); i++)
		{
			cout << currPath[i] + 1 << " ";
		}
		cout << endl;
	}
	cin >> n;
}