#include <string>
#include <algorithm>

using namespace std;

long long A = 999999090;
long long B = 1000001453;

long long* p;

void preprocessP(int n)
{
	p = new long long[n + 1];
	p[0] = 1;
	for (int i = 1; i <= n; i++)
	{
		p[i] = (p[i - 1] * A) % B;
	}
}

long long* computeHashes(string& s)
{
	int n = s.size();
	long long* ans = new long long[n];
	ans[0] = s[0];
	for (int i = 1; i < n; i++)
	{
		ans[i] = (((ans[i - 1] * A) % B) + s[i]) % B;
	}
	return ans;
}

long long mod(long long a, long long b)
{
	return ((a % b) + b) % b;
}

long long substrHash(long long* hashes, int x, int y)
{
	if (x == 0)
	{
		return hashes[y];
	}
	return mod(hashes[y] - (hashes[x - 1] * p[y - x + 1]) % B, B);
}