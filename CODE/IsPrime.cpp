bool isPrime(long long x)
{
	for (long long d = 2; d * d <= x; d++)
	{
		if (x % d == 0)
		{
			return false;
		}
	}
	return true;
}