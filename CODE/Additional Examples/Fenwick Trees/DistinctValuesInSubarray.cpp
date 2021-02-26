#include <iostream>
#include <math.h>
#include <algorithm>
#include <vector>
 
using namespace std;
 
typedef pair<int, int> pii;
 
struct Query
{
	int index;
	int a, b;
	int ans;
};
 
struct FenwickTree
{
	long long* arr;
	int sz;
	FenwickTree(int sz_inp)
	{
		sz = 1 << ((int)log2(sz_inp) + 1);
		arr = new long long[sz + 1];
		for (int i = 0; i <= sz; i++)
		{
			arr[i] = 0;
		}
	}
	void update(int x, int delta)
	{
		x++;
		for (; x <= sz; x += x & (-x))
		{
			arr[x] += delta;
		}
	}
	long long query(int a, int b)
	{
		a++; b++;
		long long ans = query(b);
		if (a > 1)
		{
			ans -= query(a - 1);
		}
		return ans;
	}
	long long query(int x)
	{
		long long ans = 0;
		for (; x > 0; x -= x & (-x))
		{
			ans += arr[x];
		}
		return ans;
	}
};
 
pair<vector<int>, int> compressValues(vector<pii> vals)
{
	vector<int> ans(vals.size());
	sort(vals.begin(), vals.end());
	int c = 0;
	for (int i = 0; i < vals.size(); i++)
	{
		if (i > 0 && vals[i].first != vals[i - 1].first)
		{
			c++;
		}
		ans[vals[i].second] = c;
	}
	return make_pair(ans, c);
}
 
bool cmpQueriesByIndex(Query& a, Query& b)
{
	return a.index < b.index;
}
 
bool cmpQueriesByEnd(Query& a, Query& b)
{
	return a.b < b.b;
}
 
int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);
 
	int n, q;
	cin >> n >> q;
 
	vector<pii> allValues(n);
	for (int i = 0; i < n; i++)
	{
		allValues[i].second = i;
	}
 
	int* xArr = new int[n];
	for (int i = 0; i < n; i++)
	{
		cin >> xArr[i];
		allValues[i].first = xArr[i];
	}
 
	Query* queries = new Query[q];
	for (int i = 0; i < q; i++)
	{
		queries[i].index = i;
		cin >> queries[i].a >> queries[i].b;
		queries[i].a--; queries[i].b--;
	}
	sort(queries, queries + q, cmpQueriesByEnd);
 
	pair<vector<int>, int> compressedP = compressValues(allValues);
	vector<int> compressedVec = compressedP.first;
	for (int i = 0; i < n; i++)
	{
		xArr[i] = compressedVec[i];
	}
	int c = compressedP.second + 1;
 
	FenwickTree ft(n);
	
	int* lastOccuranceOfVal = new int[c];
	for (int i = 0; i < c; i++)
	{
		lastOccuranceOfVal[i] = -1;
	}
	
	int currIndex = 0;
	for (int i = 0; i < q; i++)
	{
		while (currIndex <= queries[i].b)
		{
			if (lastOccuranceOfVal[xArr[currIndex]] != -1)
			{
				ft.update(lastOccuranceOfVal[xArr[currIndex]], -1);
			}
			lastOccuranceOfVal[xArr[currIndex]] = currIndex;
			ft.update(currIndex, 1);
			currIndex++;
		}
		queries[i].ans = ft.query(queries[i].a, queries[i].b);
	}
	sort(queries, queries + q, cmpQueriesByIndex);
 
	for (int i = 0; i < q; i++)
	{
		cout << queries[i].ans << endl;
	}
	cin >> n;
}