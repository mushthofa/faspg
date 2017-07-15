#include <iostream>
#include <cstdlib>

using namespace std;

int main()
{
	int n, k, i, s;
	for(n=2; n<=20; n++)
	{
		cout<<n<<"\t";
		for(k=2; k<=5; k++)
		{
			
			float mintime = 1000;
			for(i=1; i<=3; i++)
			{
				bool done = false;
				float totals = 0;
				int numas = 0;
				for(s=2; s<=10; s++)
				{
					int rn, rk, ri, rs;
					int prevnumas = 0;
					string dummy;
					float time;
					cin>>rn>>rk>>ri>>rs;
					cin>>numas;
					cin>>dummy>>time;
					cin>>dummy>>dummy;
					cin>>dummy>>dummy;
					
					//cout<<n<<" "<<k<<" "<<i<<" "<<time<<endl;
					if(!done)
						totals += time;
					if(numas > 0)
						done = true;
				}
				//cout<<n<<" "<<k<<" "<<i<<" "<<totals<<endl;
				if(totals<mintime)
					mintime=totals;
			}
			
			int mt = 1000*mintime;
			cout<<"\t"<<mt;
			
		}
		cout<<endl;
	}
}