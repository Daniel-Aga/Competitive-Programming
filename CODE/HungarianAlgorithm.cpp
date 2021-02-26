#include <iostream>
#include <math.h>
#include <vector>
#include <algorithm>

using namespace std;

const double infty = 1e18;

//Implementation follows "Assignment Problems by Rainer Burkard, Mauro Dell'Amico and Silvano Martello (2009)"

//Inputs (to be allocated and assigned before call):
int n;
double** c; //costs is n*n.

//Algorithm variables:
double* u;
double* v;
double* pi;
int* row;
int* phi;
int* pred;

//Outputs:
bool** x; //it is n*n; x[i][j] == true iff i is connected to j.

void initVariables()
{
	x = new bool*[n];
	for (int i = 0; i < n; i++)
	{
		x[i] = new bool[n];
	}
	u = new double[n];
	v = new double[n];
	row = new int[n];
	phi = new int[n];
	pred = new int[n];
	pi = new double[n];
}

void hungarianPreprocessing()
{
    initVariables();
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			x[i][j] = false;
		}
	}
	// row and column reduction:
	for (int i = 0; i < n; i++)
	{
		double mn = infty;
		for (int j = 0; j < n; j++)
		{
			if (c[i][j] < mn)
			{
				mn = c[i][j];
			}
		}
		u[i] = mn;
	}
	for (int j = 0; j < n; j++)
	{
		double mn = infty;
		for (int i = 0; i < n; i++)
		{
			if (c[i][j] - u[i] < mn)
			{
				mn = c[i][j] - u[i];
			}
		}
		v[j] = mn;
	}
	// find a partial feasable solution:
	for (int j = 0; j < n; j++)
	{
		row[j] = -1;
	}
	for (int i = 0; i < n; i++)
	{
		phi[i] = -1;
	}
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			if (row[j] == -1 && c[i][j] - u[i] - v[j] == 0)
			{
				row[j] = i;
				phi[i] = j;
				break;
			}
		}
	}
}

int augment(int k)
{
	for (int j = 0; j < n; j++)
	{
		pi[j] = infty;
	}
	vector<int> SU;
	vector<int> LV;
	vector<int> SV;
	vector<bool> inLV(n, false);
	vector<bool> inSV(n, false);
	int sink = -1;
	int i = k;
	while (sink == -1)
	{
		SU.push_back(i);
		for (int j = 0; j < n; j++)
		{
			if (inLV[j] || c[i][j] - u[i] - v[j] >= pi[j])
			{
				continue;
			}
			pred[j] = i;
			pi[j] = c[i][j] - u[i] - v[j];
			if (pi[j] == 0)
			{
				LV.push_back(j);
				inLV[j] = true;
			}
		}
		bool LVminusSVEmpty = true;
		for (int j = 0; j < n; j++)
		{
			if (inLV[j] && !inSV[j])
			{
				LVminusSVEmpty = false;
				break;
			}
		}
		if (LVminusSVEmpty)
		{
			// dual update.
			double delta = infty;
			for (int j = 0; j < n; j++)
			{
				if (inLV[j])
				{
					continue;
				}
				if (pi[j] < delta)
				{
					delta = pi[j];
				}
			}
			for (int ii = 0; ii < SU.size(); ii++)
			{
				u[SU[ii]] += delta;
			}
			for (int jj = 0; jj < LV.size(); jj++)
			{
				v[LV[jj]] -= delta;
			}
			for (int j = 0; j < n; j++)
			{
				if (inLV[j])
				{
					continue;
				}
				pi[j] -= delta;
				if (pi[j] == 0)
				{
					LV.push_back(j);
					inLV[j] = true;
				}
			}
		}
		int j = -1;
		for (int jj = 0; jj < LV.size(); jj++)
		{
			j = LV[jj];
			if (inSV[j])
			{
				continue;
			}
			break;
		}
		SV.push_back(j);
		inSV[j] = true;
		if (row[j] == -1)
		{
			sink = j;
		}
		else
		{
			i = row[j];
		}
	}
	return sink;
}


double hungarian() //Assumes n & c are already assigned. Returns the minimum cost, and sets the assignment to x.
{
	hungarianPreprocessing();
	vector<int> UBar;
	vector<bool> inUBar(n, false);
	for (int i = 0; i < n; i++)
	{
		if (phi[i] != -1)
		{
			UBar.push_back(i);
			inUBar[i] = true;
		}
	}
	while (UBar.size() < n)
	{
		int k = -1;
		for (int i = 0; i < n; i++)
		{
			if (!inUBar[i])
			{
				k = i;
				break;
			}
		}
		int sink = augment(k);
		UBar.push_back(k);
		inUBar[k] = true;
		int j = sink;
		int i = -1;
		int h = -1;
		do
		{
			i = pred[j];
			row[j] = i;
			h = phi[i];
			phi[i] = j;
			j = h;
		} while (i != k);
	}
	double ans = 0;
	for (int i = 0; i < n; i++)
	{
		int j = phi[i];
		ans += c[i][j];
		x[i][j] = true;
	}
	return ans;
}

int main()
{
    //Usage example
	cin >> n;
    c = new double*[n];
    for (int i = 0; i < n; i++)
    {
        c[i] = new double[n];
        for (int j = 0; j < n; j++)
        {
            cin >> c[i][j];
        }
    }
    cout << hungarian() << endl;
}