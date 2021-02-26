#include <algorithm>

using namespace std;

class tree //NOTE: This may need to be rewritten, to match style
{
	int from, to, mid, sum, up;
	bool resp;
	tree* l, *r;
public:
	tree(int from, int to) : from(from), to(to)
	{
		mid = (from + to) / 2;
		resp = false;
		sum = 0;
		l = r = NULL;
	}
	void responsibility()
	{
		if (!l) l = new tree(from, mid);
		if (!r) r = new tree(mid + 1, to);
		if (!resp) return;
		l->update(from, mid, up);
		r->update(mid + 1, to, up);
		resp = false;
	}
	void update(int x1, int x2, int k)
	{
		if (x1 > to || x2 < from) return;
		if (x1 <= from && x2 >= to)
		{
			up = k;
			resp = true;
			sum = (to - from + 1) * k;
			return;
		}
		responsibility();
		l->update(x1, x2, k);
		r->update(x1, x2, k);
		sum = l->sum + r->sum;
	}
	int query(int x1, int x2)
	{
		if (x1 > to || x2 < from) return 0;
		if (x1 <= from && x2 >= to) return sum;
		responsibility();
		return l->query(x1, x2) + r->query(x1, x2);
	}
};