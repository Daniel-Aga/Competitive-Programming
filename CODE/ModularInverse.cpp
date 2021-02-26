long long modularPow(long long a, long long b, long long c) //From Exponentiation.cpp
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

long long modularInverse(long long x, long long p) //The modulus is prime.
{
	return modularPow(x, p - 2, p);
}