long long gcd(long long a, long long b) //From GCD.cpp
{
	if (b == 0)
	{
		return a;
	}
	return gcd(b, a % b);
}

long long lcm(long long a, long long b)
{
	return (a / gcd(a, b)) * b;
}