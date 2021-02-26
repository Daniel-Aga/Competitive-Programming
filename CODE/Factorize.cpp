#include<vector>

using namespace std;

typedef pair<int, int> pii;

vector<int> primes = { 2, 3, 5 }; //Replace by primes from 2 to (at least) Sqrt(N)
int primesLen = primes.size();

int removeFactor(long long& x, int a)
{
	int p = 0;
	while (x % a == 0)
	{
		x /= a;
		p++;
	}
	return p;
}


vector<pii> factorize(long long x)
{
	vector<pii> ans;
	for (int i = 0; i < primesLen; i++)
	{
		if (x % primes[i] == 0)
		{
			ans.push_back(make_pair(primes[i], removeFactor(x, primes[i])));
			if (x == 1)
			{
				break;
			}
		}
	}
	if (x != 1)
	{
		ans.push_back(make_pair(x, 1));
	}
	return ans;
}