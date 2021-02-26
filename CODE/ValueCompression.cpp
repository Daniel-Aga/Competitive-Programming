#include <vector>
#include <algorithm>
#include <unordered_map>

using namespace std;

bool mapContains(unordered_map<int, int>& mp, int x)
{
	return mp.find(x) != mp.end();
}

unordered_map<int, int> compressValues(vector<int> vals) //Ignores duplicates.
{
	sort(vals.begin(), vals.end());
	int c = 0;
	unordered_map<int, int> ans;
	for (int i = 0; i < vals.size(); i++)
	{
		if (!mapContains(ans, vals[i]))
		{
			ans[vals[i]] = c++;
		}
	}
	return ans;
}