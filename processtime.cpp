#include <iostream>


using namespace std;

float rt[50][5];
float rm[50][5];
int rep[50][5];

int startn = 5;
int endn = 30;
int startk = 1;
int endk = 4;
int main()
{
	for(int i=0; i<50; i++)
		for(int j=0; j<5; j++)
			rep[i][j] = rt[i][j] = rm[i][j] = 0;

	int n;
	while(cin>>n)
	{
		int k;
		cin>>k;
		float runtime, memory;
		cin>>runtime>>memory;
		rt[n][k] += runtime;
		rm[n][k] += memory;
		rep[n][k] ++;
	}
	for(int i=0; i<50; i++)
		for(int j=0; j<5; j++)
		{
			rt[i][j] /= rep[i][j];
			rm[i][j] /= rep[i][j];
		}
		
	for(int i=startn; i<=endn; i++)
		cout<<", "<<i;
	cout<<endl;
	
	for(int j=startk; j<=endk; j++)
	{
		cout<<j<<" ";
		for(int i=startn; i<=endn; i++)
			cout<<", "<<rt[i][j];
		cout<<endl;
	}
	for(int i=startn; i<=endn; i++)
		cout<<"_";
	cout<<endl;
	
	for(int i=startn; i<=endn; i++)
		cout<<", "<<i;
	cout<<endl;
	
	for(int j=startk; j<=endk; j++)
	{
		cout<<j<<" ";
		for(int i=startn; i<=endn; i++)
			cout<<", "<<rm[i][j];
		cout<<endl;
	}
	return 0;
}