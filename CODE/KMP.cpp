#include <vector>
#include <string>
#include <algorithm>

using namespace std;

vector<int> computeKMP(string& s)
{
	vector<int> res(s.size(), 0);
	res[0] = 0;
	int k = 0;
	for (int i = 1; i < s.size(); i++)
	{
		while (k > 0 && s[i] != s[k])
		{
			k = res[k - 1];
		}
		if (s[i] == s[k])
		{
			k++;
		}
		res[i] = k;
	}
	return res;
}

vector<int> match(string& s1, string& s2) //Returns indexes of starts of occurances of s2 in s1.
{
	vector<int> ans;
	vector<int> kmpS2 = computeKMP(s2);
	int q = 0;
	for (int i = 0; i < s1.size(); i++)
	{
		while (q > 0 && s1[i] != s2[q])
		{
			q = kmpS2[q - 1];
		}
		if (s1[i] == s2[q])
		{
			q++;
		}
		if (q == s2.size())
		{
			ans.push_back(i - q);
			q = kmpS2[q - 1];
		}
	}
	return ans;
}