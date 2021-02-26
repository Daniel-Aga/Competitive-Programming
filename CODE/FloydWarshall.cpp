#include <algorithm>

using namespace std;

long long infty = 1000000000000000000;

void FloydWarshall(long long** graph, int n)
{
	for (int k = 1; k <= n; k++)
	{
		for (int i = 0; i < n; i++)
		{
			for (int j = 0; j < n; j++)
			{
				graph[i][j] = min(graph[i][j], graph[i][k - 1] + graph[k - 1][j]);
			}
		}
	}
}