#include <algorithm>
#include <vector>
#include <math.h>

using namespace std;

struct PSTNode
{
	int l, r, m;
	long long sum;
	int version;
	PSTNode* lNode;
	PSTNode* rNode;
	PSTNode(int l, int r, int ver) : l(l), r(r), version(ver)
	{
		m = (l + r) / 2;
		lNode = NULL;
		rNode = NULL;
		sum = 0;
	}
	PSTNode(int l, int r, int ver, long long sum_inp) : PSTNode(l, r, ver)
	{
		sum = sum_inp;
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
			lNode = new PSTNode(l, m, version, lNode->sum);
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
			rNode = new PSTNode(m + 1, r, version, rNode->sum);
			rNode->lNode = prev->lNode;
			rNode->rNode = prev->rNode;
		}
	}
	void updateNode()
	{
		if (lNode != NULL && rNode != NULL)
		{
			sum = lNode->sum + rNode->sum;
		}
	}
};

/*
void buildSegmentTree(PSTNode* nd)
{
	nd->lNode = new PSTNode(nd->l, nd->m, nd->version);
	nd->rNode = new PSTNode(nd->m + 1, nd->r, nd->version);
	if (nd->l != nd->r)
	{
		buildSegmentTree(nd->lNode);
		buildSegmentTree(nd->rNode);
	}
}
*/

struct PersistantSegmentTree
{
	vector<PSTNode> roots;
	int sz;
	PersistantSegmentTree(int* startingVals, int sz_inp)
	{
		sz = 1 << ((int)log2(sz_inp) + 2);
		roots.push_back(PSTNode(0, sz / 2 - 1, 0));
		//buildSegmentTree(&roots[0]);
		for (int i = 0; i < sz_inp; i++)
		{
			updatePoint(i, startingVals[i], 0);
		}
	}
	void updatePoint(int k, int newVal, int ver)
	{
		roots[ver] = *(copyVersion(ver));
		updatePoint(&roots[ver], k, newVal);
	}
	void updatePoint(PSTNode* x, int k, int newVal)
	{
		if (x->l > k || x->r < k)
		{
			return;
		}
		if (x->l == k && x->r == k)
		{
			x->sum = newVal;
			return;
		}
		x->createChildren();
		updatePoint(x->lNode, k, newVal);
		updatePoint(x->rNode, k, newVal);
		x->updateNode();
	}
	PSTNode* copyVersion(int ver)
	{
		PSTNode* ans = new PSTNode(0, sz / 2 - 1, roots.size(), roots[ver].sum);
		ans->lNode = roots[ver].lNode;
		ans->rNode = roots[ver].rNode;
		return ans;
	}
	void addCopiedVersion(int ver)
	{
		PSTNode* copied = copyVersion(ver);
		roots.push_back(*copied);
	}
	long long query(int l, int r, int ver)
	{
		return query(&roots[ver], l, r);
	}
	long long query(PSTNode* x, int l, int r)
	{
		if (x->l > r || x->r < l)
		{
			return 0;
		}
		if (x->l >= l && x->r <= r)
		{
			return x->sum;
		}
		x->createChildren();
		return query(x->lNode, l, r) + query(x->rNode, l, r);
	}
};