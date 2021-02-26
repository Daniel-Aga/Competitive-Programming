using namespace std;

const int infty = 1e9;

struct Node
{
	vector<Node*> neighbors;
	Node* pair; //Current pair.
	int dist = infty;

	bool isNull = false;
};

//Implementation follows Wikipedia.

int n, m;
Node* A;
Node* B;
//A, B are both of size n
Node null;

bool BFS()
{
	queue<Node*> q;
	for (int i = 0; i < n; i++)
	{
		if (A[i].pair->isNull)
		{
			A[i].dist = 0;
			q.push(&A[i]);
		}
		else
		{
			A[i].dist = infty;
		}
	}
	null.dist = infty;
	while (!q.empty())
	{
		Node* u = q.front();
		q.pop();
		if (u->dist < null.dist)
		{
			for (int i = 0; i < u->neighbors.size(); i++)
			{
				Node* v = u->neighbors[i];
				Node* pair = v->pair;
				if (pair->dist == infty)
				{
					pair->dist = u->dist + 1;
					q.push(pair);
				}
			}
		}
	}
	return null.dist != infty;
}

bool DFS(Node* u)
{
	if (!u->isNull)
	{
		for (int i = 0; i < u->neighbors.size(); i++)
		{
			Node* v = u->neighbors[i];
			Node* pair = v->pair;
			if (pair->dist == u->dist + 1)
			{
				if (DFS(pair))
				{
					v->pair = u;
					u->pair = v;
					return true;
				}
			}
		}
		u->dist = infty;
		return false;
	}
	return true;
}

int hopcroftKarp() //Returns the size of the maximum matching.
{
    null.isNull = true;
	for (int i = 0; i < n; i++)
	{
		A[i].pair = &null;
		B[i].pair = &null;
	}
	int ans = 0;
	while (BFS())
	{
		for (int i = 0; i < n; i++)
		{
			Node* u = &A[i];
			if (u->pair->isNull)
			{
				if (DFS(u))
				{
					ans++;
				}
			}
		}
	}
	return ans;
}
