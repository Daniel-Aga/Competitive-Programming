#include <iostream>
#include <vector>
#include <set>
#include <math.h>

using namespace std;

long long md = 1000000007;
long long inv2 = 500000004;

long long removeFactor(long long n, long long p)
{
	while (n % p == 0)
	{
		n /= p;
	}
	return n;
}

vector<long long> primeFactors(long long n)
{
	vector<long long> ans;
	if (n % 2 == 0)
	{
		ans.push_back(2);
		n = removeFactor(n, 2);
	}
	long long sqr = (long long)(sqrt(n) + 1LL);
	for (long long i = 3; i <= sqr; i += 2)
	{
		if (n % i == 0)
		{
			ans.push_back(i);
			n = removeFactor(n, i);
			//sqr = (long long)(sqrt(n) + 1LL);
		}
	}
	if (n != 1)
	{
		ans.push_back(n);
	}
	return ans;
}

long long mod2(long long x, long long y)
{
	if (x % y <= 0)
	{
		return y + x%y;
	}
	return x % y;
}

long long sumDiv(long long a, long long b, long long d)
{
	if (a > b)
	{
		return 0;
	}
	long long numOfElems = ((b - a) / d + 1) % md;
	long long sm = (b + a) % md;
	long long mult = (numOfElems * sm) % md;
	return (mult * inv2) % md;
}

long long sum(long long a, long long b, long long d)
{
	if (a > b)
	{
		return 0;
	}
	long long firstDiv = a - mod2(a, d) + d;
	long long lastDiv = b - (b % d);
	return sumDiv(firstDiv, lastDiv, d);
}

void applySubset(vector<long long>& factors, long long& ans, long long a, long long b, long long sz, long long sgn, long long currMult, long long from)
{
	if (sz > factors.size())
	{
		return;
	}
	if (sz == 0)
	{
		ans = mod2((ans + sum(a, b, currMult) * sgn), md);
		return;
	}
	for (int i = from; i < factors.size(); i++)
	{
		long long curr = factors[i];
		applySubset(factors, ans, a, b, sz - 1, sgn, mod2((currMult * curr), md), i + 1);
	}
}

void doInclusionExclusion(vector<long long>& factors, long long& ans, long long a, long long b)
{
	for (long long i = 1; i <= factors.size(); i++)
	{
		long long sgn = 1;
		if (i % 2 == 1)
		{
			sgn = -1;
		}
		applySubset(factors, ans, a, b, i, sgn, 1, 0);
	}
}

int main()
{
	int q;
	cin >> q;
	for (int i = 0; i < q; i++)
	{
		long long n;
		cin >> n;
		long long a;
		cin >> a;
		long long b;
		cin >> b;
		vector<long long> factors = primeFactors(n);
		long long ans = sum(a, b, 1);
		doInclusionExclusion(factors, ans, a, b);
		cout << ans << endl;
	}
	cin >> q;
}