#include <iostream>
#include <vector>
#include "Hungarian.h"

using namespace std;

int main()
{
    //Usage example:
	vector<vector<double>> costMatrix;
	HungarianAlgorithm HungAlgo;
	vector<int> assignment;
    
    int n;
    cin >> n;
    costMatrix.assign(n, vector<double>(n, 0));
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            cin >> costMatrix[i][j];
        }
    }
    double cost = HungAlgo.Solve(costMatrix, assignment);    
    cout << "Cost is: " << cost << endl;
	cout << "Assignment is:" << endl;
    for (int i = 0; i < n; i++)
    {
        cout << "\t" << i << " is assigned to: " << assignment[i] << endl;
    }
    cin >> n;
}