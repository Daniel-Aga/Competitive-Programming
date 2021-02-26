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

void QuickSort(int* arr, int l, int r)
{
	if (r > l)
	{
		int i = RandomPartition(arr, l, r);
		QuickSort(arr, l, i - 1);
		QuickSort(arr, i + 1, r);
	}
}