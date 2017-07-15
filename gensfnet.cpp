//============================================================================
// Name        : gensfnet.cpp
// Author      : Mushthofa
// Version     :
// Copyright   : 
// Description : Hello World in C++, Ansi-style
//============================================================================
#include <iostream>
#include <cstdlib>
#include <string>
#include <vector>
#include <sstream>
#include <ctime>
#include <iostream>

using namespace std;


int adjmat[50][50];

bool randomBool(float percentage)
{
	return (rand()%1000)<(percentage*1000);
}

void gensfmat(int sz, int m, float alpha)
{
	/* Connect the first m genes */
	for (int i=0; i<sz; i++)
		for (int j=i+1; j<sz; j++)
			adjmat[i][j] = adjmat[j][i] = 0;
	for (int i=0; i<m; i++)
		for (int j=i+1; j<m; j++)
			adjmat[i][j] = adjmat[j][i] = 1;

	/* Add genes one by one, and connect with probability proportional to current degrees */

	for (int i=m+1; i<sz; i++)
	{
		float degree[50];
		for (int k=0; k<sz; k++)
			degree[k] = 0;
		for (int k=0; k<i; k++)
			for(int l=0; l<sz; l++)
				degree[k] += adjmat[k][l];
		float sumdegree = 0;
		for(int k=0; k<i; k++)
			sumdegree += degree[k];
		for(int k=0; k<i; k++)
			degree[k] /= sumdegree;

		for(int j=0; j<i; j++)
		{
			if(randomBool(degree[j] + alpha))
				adjmat[j][i] = adjmat[i][j] = 1;
		}

	}

	/* randomly select direction of edges (either one or both directions) */
	for(int i=0; i<sz; i++)
	{
		for(int j=i+1; j<sz; j++)
		{
			/* Left */
			if((adjmat[i][j]==1) && randomBool(0.5))
				adjmat[i][j] = 0;
			if((adjmat[i][j]==1) && randomBool(0.5))
				adjmat[j][i] = 0;

		}
	}



}


void enumexprec(vector<string> nodes, int headnode, string pref, vector<int> restnode, int k)
{

	if(restnode.size()==1)
	{
		for(int i=0; i<=k; i++)
		{
			int rv = (rand())%(k+1);
			cout << nodes[headnode] <<" "<< rv <<" "<<pref<<" "<<nodes[restnode[0]]<<" "<< i << std::endl;
		}
	}
	else
	{
		int curnode = restnode.back();
		restnode.pop_back();
		for(int i=0; i<=k; i++)
		{
			ostringstream oss;
			oss<<nodes[curnode]<<" "<<i<<" ";
			string curpref;
			curpref = pref + oss.str();
			enumexprec(nodes, headnode, curpref, restnode, k);
		}
	}
}

void enumexp(vector<string> nodes, int headnode, vector<int> incoming, int k)
{
	string empty;
	enumexprec(nodes, headnode, empty, incoming, k);
}


int main(int argc, char** argv)
{
	srand(time(0));
	int n = atoi(argv[1]);
	int k = atoi(argv[2]);
	int i,j;
	cout<<n<<" "<<k<<endl;
	vector<string> nodes;
	for(i=0; i<n; i++)
	{
		std::ostringstream oss;
		oss << i;
		nodes.push_back(string("node_") + oss.str());
	}

	gensfmat(n, 3, 0.1);



	int degree[50];
	for (i=0; i<n; i++)
		degree[i] = 0;
	for (i=0; i<n; i++)
		for(j=0; j<n; j++)
			degree[i] += adjmat[j][i];

	for(i=0; i<n; i++)
		cout<<nodes[i]<<endl;

	for(i=0; i<n; i++)
	{
		//cout<<nodes[i] << degree[i]<<endl;

		vector<int> incoming;
		for (j=0; j<n; j++)
			if(adjmat[j][i] > 0 && incoming.size()<4)
				incoming.push_back(j);
		int deg = incoming.size();
		if(deg > 0)
			enumexp(nodes, i, incoming, k);
	}


	return 0;
}
