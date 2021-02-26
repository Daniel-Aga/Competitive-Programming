#include <algorithm>
#include <math.h>

using namespace std;

const int MAX_LOG2_N = 18;

int** preprocessMin(int* arr, int n)
{
	int** ans = new int*[n];
	for (int i = 0; i < n; i++)
	{
		ans[i] = new int[MAX_LOG2_N + 1];
		ans[i][0] = arr[i];
	}
	for (int l = 1; l <= MAX_LOG2_N; l++)
	{
		for (int i = 0; i < n; i++)
		{
			int nxt = i + (1 << (l - 1));
			if (nxt >= n)
			{
				nxt = i;
			}
			ans[i][l] = min(ans[i][l - 1], ans[nxt][l - 1]);
		}
	}
	return ans;
}

int queryMin(int** mins, int a, int b)
{
	int powOf2 = log2(b - a + 1);
	return min(mins[a][powOf2], mins[b + 1 - (1 << powOf2)][powOf2]);
}