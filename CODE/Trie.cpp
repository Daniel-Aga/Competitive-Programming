#include <string>
#include <vector>

using namespace std;

const int ENGLISH_LETTERS = 26;
const int md = 1000000007;

struct TNode
{
	bool endsHere = false;
	int* nextPointers;
	TNode()
	{
		nextPointers = new int[ENGLISH_LETTERS];
		for (int i = 0; i < ENGLISH_LETTERS; i++)
		{
			nextPointers[i] = -1;
		}
	}
	bool hasPointer(int l)
	{
		return nextPointers[l] != -1;
	}
};

struct TRIE
{
	vector<TNode> arr;
	TRIE()
	{
		addNode();
	}
	int addNode()
	{
		arr.push_back(TNode());
		return arr.size() - 1;
	}
	void addWord(string& s)
	{
		int curr = 0;
		for (int i = 0; i < s.size(); i++)
		{
			if (!canTraverse(curr, s[i] - 'a'))
			{
				arr[curr].nextPointers[s[i] - 'a'] = addNode();
			}
			curr = traverse(curr, s[i] - 'a');
		}
		arr[curr].endsHere = true;
	}
	bool hasWord(string& s)
	{
		int curr = 0;
		for (int i = 0; i < s.size(); i++)
		{
			if (!canTraverse(curr, s[i] - 'a'))
			{
				return false;
			}
			curr = traverse(curr, s[i] - 'a');
		}
		return arr[curr].endsHere;
	}
	bool canTraverse(int curr, int letter)
	{
		return arr[curr].hasPointer(letter);
	}
	int traverse(int curr, int letter)
	{
		return arr[curr].nextPointers[letter];
	}
	bool endsHere(int curr)
	{
		return arr[curr].endsHere;
	}
};