#include <vector>

using namespace std;

const int md = 1e9 + 7;

struct matrix
{
	vector<vector<long long>> contents;
	int sz1, sz2;
	matrix(int sz1, int sz2) : sz1(sz1), sz2(sz2)
	{
		contents.assign(sz1, vector<long long>(sz2, 0));
	}
	matrix(int sz) : matrix(sz, sz)
	{

	}
	vector<long long>& operator[](int x)
	{
		return contents[x];
	}
	matrix operator*(matrix other)
	{
		if (sz2 != other.sz1)
		{
			return matrix(0);
		}
		matrix ans(sz1, other.sz2);
		for (int i = 0; i < sz1; i++)
		{
			for (int j = 0; j < other.sz2; j++)
			{
				for (int k = 0; k < sz2; k++)
				{
					ans[i][j] += (contents[i][k] * other[k][j]) % md;
					ans[i][j] %= md;
					//NOTE: This can be adapted for MIN/PLUS product and OR/AND product
				}
			}
		}
		return ans;
	}
};

matrix idMat(int n)
{
	matrix ans(n);
	for (int i = 0; i < n; i++)
	{
		ans[i][i] = 1;
	}
	return ans;
}

matrix matPow(matrix a, long long b)
{
	matrix ans = idMat(a.sz1);
	while (b > 0)
	{
		if (b % 2 == 1)
		{
			ans = ans * a;
		}
		a = a * a;
		b /= 2;
	}
	return ans;
}