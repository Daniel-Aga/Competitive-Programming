long long modularPow(long long a, long long b, long long c)
{
	a %= c;
	long long ans = 1;
	while (b > 0)
	{
		if ((b & 1) == 1)
		{
			ans = (ans * a) % c;
		}
		b /= 2;
		a = (a*a) % c;
	}
	return ans;
}

long long modifiedPow(long long a, long long b)
{
	long long ans = 1;
	while (b > 0)
	{
		if ((b & 1) == 1)
		{
			ans *= a;
		}
		b /= 2;
		a *= a;
	}
	return ans;
}