#include <vector>

using namespace std;

const int MAX_LOG_2_N = 18;

struct Node
{
	int nxt[MAX_LOG_2_N + 1];
};

void preprocess(Node* graph, int n)
{
	for (int i = 1; i <= MAX_LOG_2_N; i++)
	{
		for (int j = 0; j < n; j++)
		{
			graph[j].nxt[i] = graph[graph[j].nxt[i - 1]].nxt[i - 1];
		}
	}
}

int query(Node* graph, int x, int k) //Advancing K times from X.
{
	int curr = x;
	int c = 0;
	while (k > 0)
	{
		if (k % 2 == 1)
		{
			curr = graph[curr].nxt[c];
		}
		k /= 2;
		c++;
	}
	return curr;
}