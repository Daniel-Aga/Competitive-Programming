#include <algorithm>
#include <vector>
#include <math.h>

using namespace std;

const int infty = 1000000000;


struct PSTNode
{
	int l, r, m;
	int minInSubtree;
	int version;
	PSTNode* lNode;
	PSTNode* rNode;
	PSTNode(int l, int r, int ver) : l(l), r(r), version(ver)
	{
		m = (l + r) / 2;
		lNode = NULL;
		rNode = NULL;
		minInSubtree = infty;
	}
	PSTNode(int l, int r, int ver, long long min_inp) : PSTNode(l, r, ver)
	{
		minInSubtree = min_inp;
	}
	void createChildren()
	{
		createLeft();
		createRight();
		updateNode();
	}
	void createLeft()
	{
		if (lNode == NULL)
		{
			lNode = new PSTNode(l, m, version);
		}
		else if (lNode->version != version)
		{
			PSTNode* prev = lNode;
			lNode = new PSTNode(l, m, version, lNode->minInSubtree);
			lNode->lNode = prev->lNode;
			lNode->rNode = prev->rNode;
		}
	}
	void createRight()
	{
		if (rNode == NULL)
		{
			rNode = new PSTNode(m + 1, r, version);
		}
		else if (rNode->version != version)
		{
			PSTNode* prev = rNode;
			rNode = new PSTNode(m + 1, r, version, rNode->minInSubtree);
			rNode->lNode = prev->lNode;
			rNode->rNode = prev->rNode;
		}
	}
	void updateNode()
	{
		if (lNode != NULL && rNode != NULL)
		{
			minInSubtree = min(lNode->minInSubtree, rNode->minInSubtree);
		}
	}
	bool isLeaf()
	{
		return l == r;
	}
};


struct PersistantSegmentTree
{
	vector<PSTNode*> roots;
	int sz;
	PersistantSegmentTree(int sz_inp)
	{
		sz = 1 << ((int)log2(sz_inp) + 2);
		roots.reserve(sz_inp + 2);
		roots.push_back(new PSTNode(0, sz / 2 - 1, 0));
	}
	void updatePoint(int k, int newVal, int ver)
	{
		roots.push_back(copyVersion(ver));
		updatePoint(roots.back(), k, newVal);
	}
	void updatePoint(PSTNode* x, int k, int newVal)
	{
		if (x->l > k || x->r < k)
		{
			return;
		}
		if (x->l == k && x->r == k)
		{
			x->minInSubtree = newVal;
			return;
		}
		x->createChildren();
		updatePoint(x->lNode, k, newVal);
		updatePoint(x->rNode, k, newVal);
		x->updateNode();
	}
	PSTNode* copyVersion(int ver)
	{
		PSTNode* ans = new PSTNode(0, sz / 2 - 1, roots.size(), roots[ver]->minInSubtree);
		ans->lNode = roots[ver]->lNode;
		ans->rNode = roots[ver]->rNode;
		return ans;
	}
	long long query(int val, int ver)
	{
		return query(roots[ver], val);
	}
	long long query(PSTNode* x, int val)
	{
		if (x->isLeaf())
		{
			return x->l;
		}
		x->createChildren();
		if (x->rNode->minInSubtree <= val)
		{
			return query(x->rNode, val);
		}
		return query(x->lNode, val);
	}
};