#include <string>
#include <algorithm>

using namespace std;


int* computeZArray(string& s)
{
	int n = s.size();
	int* z = new int[n];
	z[0] = 0;
	int x = 0;
	int y = 0;
	for (int i = 1; i < n; i++)
	{
		z[i] = max(0, min(z[i - x], y - i + 1));
		while (i + z[i] < n && s[i + z[i]] == s[z[i]])
		{
			x = i;
			y = i + z[i];
			z[i]++;
		}
	}
	return z;
}

int numMatches(string& s, string& p)
{
	string concat = p + '$' + s;
	int* z = computeZArray(concat);
	int ans = 0;
	for (int i = p.size() + 1; i < s.size() + p.size() + 1; i++)
	{
		if (z[i] == p.size())
		{
			ans++;
		}
	}
	return ans;
}