#include <algorithm>

using namespace std;

int random()
{
	return rand() ^ (rand() << 15);
}

struct node //NOTE: This may need to be rewritten, to match style.
{
	int key, resp, amount;
	node* l, *r;
	node(int key) : key(key)
	{
		resp = random();
		l = r = NULL;
		amount = 1;
	}
	void update()
	{
		amount = (l ? l->amount : 0) + (r ? r->amount : 0) + 1;
	}
};

void split(node* t, node*& l, node*& r, int k)
{
	if (!t) l = r = NULL;
	else if (t->key > k) split(t->l, l, t->l, k), t->update(), r = t;
	else split(t->r, t->r, r, k), t->update(), l = t;
}

void size_split(node* t, node*& l, node*& r, int k)
{
	if (!t) l = r = NULL;
	else if ((t->l ? t->l->amount : 0) >= k) size_split(t->l, l, t->l, k), t->update(), r = t;
	else size_split(t->r, t->r, r, k - (t->l ? t->l->amount : 0) - 1), t->update(), l = t;
}

void merge(node*& t, node* l, node* r)
{
	if (!l || !r) t = l ? l : r;
	else if (l->resp < r->resp) merge(l->r, l->r, r), t = l, t->update();
	else merge(r->l, l, r->l), t = r, t->update();
}

class treap
{
	node* root;
public:
	treap()
	{
		root = NULL;
	}
	void add(int k)
	{
		node* l, *r;
		split(root, l, r, k);
		root = new node(k);
		merge(root, l, root);
		merge(root, root, r);
	}
	bool has(int k)
	{
		bool res;
		node* l, *r;
		split(root, l, r, k);
		split(l, l, root, k - 1);
		res = (root != NULL);
		merge(root, l, root);
		merge(root, root, r);
		return res;
	}
	void remove(int k)
	{
		node* l, *r;
		split(root, l, r, k);
		split(l, l, root, k - 1);
		merge(root, l, r);
	}
	int operator[](int k)
	{
		int res;
		node* l, *r;
		size_split(root, l, r, k);
		size_split(r, root, r, 1);
		res = root->key;
		merge(root, l, root);
		merge(root, root, r);
		return res;
	}
};