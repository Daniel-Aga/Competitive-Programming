#include <algorithm>

using namespace std;

int Partition(int* arr, int l, int r)
{
	int x = arr[r];
	int i = l - 1;
	for (int j = l; j < r; j++)
	{
		if (arr[j] <= x)
		{
			i++;
			swap(arr[i], arr[j]);
		}
	}
	swap(arr[i + 1], arr[r]);
	return i + 1;
}

int RandomPartition(int* arr, int l, int r)
{
	int i = (rand() % (r - l + 1)) + l;
	swap(arr[r], arr[i]);
	return Partition(arr, l, r);
}

int QuickSelect(int* arr, int l, int r, int k) //Returns the value in the array, such that there are k smaller values than it.
{
	if (r > l)
	{
		int i = RandomPartition(arr, l, r);
		int numSmaller = i - l;
		if (numSmaller == k)
		{
			return arr[i];
		}
		if (numSmaller < k)
		{
			return QuickSelect(arr, l, i - 1, k);
		}
		return QuickSelect(arr, i + 1, r, k - numSmaller - 1);
	}
}