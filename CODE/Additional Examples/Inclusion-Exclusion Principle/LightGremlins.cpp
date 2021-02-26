#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int n;
long long s;
vector<int> primes;
long long ans;
int sz;
long long sgn;
int fr;

bool multBiggerThanS(long long a, int b)
{
	return (long long)(s / a) < b - 1;
}

long long numDiv(long long d)
{
	long long lastDiv = s - (s % d);
	if (d > lastDiv)
	{
		return 0;
	}
	return lastDiv / d;
}


void applySubset(long long currMult)
{
	if (sz == 0)
	{
		ans += numDiv(currMult) * sgn;
		return;
	}
	int tmpFr = fr;
	sz--;
	long long mxPrime = (long long)(s / currMult) + 1;
	if (mxPrime < 10000)
	{
		int mxPrimeInt = (int)mxPrime;
		for (int i = fr; i < n; i++)
		{
			if (primes[i] >= mxPrimeInt)
			{
				break;
			}
			fr++;
			applySubset(currMult * primes[i]);
		}
	}
	else
	{
		for (int i = fr; i < n; i++)
		{
			fr++;
			applySubset(currMult * primes[i]);
		}
	}
	sz++;
	fr = tmpFr;
}

void doInclusionExclusion()
{
	sgn = 1;
	for (int i = 1; i <= primes.size(); i++)
	{
		sz = i;
		fr = 0;
		applySubset(1);
		sgn <<= 1;
		sgn *= -1;
	}
}

int main()
{
	int t;
	cin >> t;
	for (int abc = 0; abc < t; abc++)
	{
		cin >> s;
		cin >> n;
		primes.clear();
		for (int i = 0; i < n; i++)
		{
			int currPrime;
			cin >> currPrime;
			primes.push_back(currPrime);
		}
		sort(primes.begin(), primes.end());
		ans = 0;
		doInclusionExclusion();
		cout << ans << endl;
	}
	cin >> t;
}