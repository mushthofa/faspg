#include <iostream>
#include <cstdlib>

using namespace std;

float rt[55][10];
float rm[55][10];
int rep[55][10];

int startn = 5;
int endn = 50;
int startk = 1;
int endk = 6;
int main(int argc, char* argv[])
{
    int tt = 0;
    if(argc >= 2)
        tt = atoi(argv[1]);
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
	for(int i=startn; i<=endn; i++)
		for(int j=startk; j<=endk; j++)
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
        {
            if(tt==1)
                cout<<", "<<rt[i][j];
            else if(tt==2)
                cout<<", "<<rm[i][j];
            else
            {
                cout<<", "<<rt[i][j];
                cout<<", "<<rm[i][j];
            }
        }
		cout<<endl;
	}


	return 0;
}
