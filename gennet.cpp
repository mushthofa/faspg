#include <iostream>
#include <cstdlib>
#include <string>
#include <vector>
#include <sstream>

using namespace std;

int main(int argc, char** argv)
{
	srand(time(0));
	int n = atoi(argv[1]);
	int k = atoi(argv[2]);
	int cc = 1;
	int i,j;
	
	cout<<n<<" "<<k<<endl;
	vector<string> nodes;
	for(i=0; i<n; i++)
	{
		std::ostringstream oss;
		oss << i;
		nodes.push_back(string("node_") + oss.str());
	}
	
	for(i=0; i<n; i++)
		cout<<nodes[i]<<endl;
	for(i=0; i<n; i++)
	{
		// select 3 random nodes;
		int ni1 = rand()%n;
		int ni2 = rand()%n;
		int ni3 = rand()%n;
		while (ni1==ni2 || ni1==ni3 || ni2==ni3)
		{
			ni1 = rand()%n;
			ni2 = rand()%n;
			ni3 = rand()%n;
		}
		int ii, jj, ll;
		for(ii=0; ii<=k; ii++)
		{
			for(jj=0; jj<=k; jj++)
			{
				for(ll=0; ll<=k; ll++)
				{
					int rv = rand()%(k+1);
					cout<<nodes[i]<<" "<<rv<<" "<<nodes[ni1]<<" "<<ii<<" "<<nodes[ni2]<<" "<<jj<<" "<<nodes[ni3]<<" "<<ll<<endl;
				}
			}
		}
	}
	return 0;
	
}