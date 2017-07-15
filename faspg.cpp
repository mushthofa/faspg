#include <iostream>
#include <cstdlib>
#include <string>
#include <sstream>
#include <vector>
#include <map>
#include <cctype>
#include <boost/foreach.hpp>
#include <boost/tokenizer.hpp>
#include <boost/algorithm/string.hpp>

using namespace std;
using namespace boost;
using namespace boost::algorithm;

typedef map<string, int> mapstr;


void dumpnodes(const mapstr& nodes)
{
	mapstr::const_iterator it;
	for(it=nodes.begin(); it!=nodes.end(); ++it)
		cout<<it->second<<" "<<it->first<<endl;
}

int main(int argc, char** argv)
{

	int n,k, i, j;
	mapstr nodes;
	string lineinput;
	while(cin.peek()!=-1 && !isdigit(cin.peek()))
	{
		getline(cin, lineinput);
		cout<<lineinput<<endl;
	}
	cin>>n>>k;
	for(i=0; i<n; i++)
	{
		string node1;
		cin>>node1;
		nodes.insert(pair<string, int>(node1, i));
	}

	//cout<<"n = "<<n<<endl;
	//dumpnodes(nodes);


	// print shows
	mapstr::const_iterator it;
	for(it=nodes.begin(); it!=nodes.end(); ++it)
	{
		cout<<"#show "<<it->first<<"/1."<<endl;
		//cout<<"#show "<<it->first<<"_p/1."<<endl;
		//cout<<"#show line/2."<<endl;
	}

	for(it=nodes.begin(); it!=nodes.end(); ++it)
	{
		string nn = it->first;
		string gnn = "g_" + nn;
		cout<<gnn<<0;
		for(j=1; j<=k; j++)
			cout<<" | "<<gnn<<j;
		cout<<"."<<endl;

		for(j=1; j<=k; j++)
			cout<<nn<<"("<<j<<") :- "<<gnn<<j<<"."<<endl;

		for(j=1; j<k; j++)
			cout<<nn<<"("<<j<<") :- "<<nn<<"("<<j+1<<")."<<endl;

		/* All the truth-hierarchical rules */

		cout<<nn<<"("<<0<<")."<<endl;
		cout<<nn<<"_p("<<0<<")."<<endl;
		for(j=1; j<k; j++)
		{
			cout<<nn<<"("<<j<<")"<<" :- "<<nn<<"("<<j+1<<")."<<endl;
			cout<<nn<<"_p("<<j<<")"<<" :- "<<nn<<"_p("<<j+1<<")."<<endl;
		}
	}

	/* print all possible constants */

	for(i=1; i<=k; i++)
	{
		for(j=1; j<=i; j++)
			cout<<"const_"<<i<<"("<<j<<")."<<endl;
	}


	char_separator<char> sep(" ");
    int cndctr = 0;
    int linenum = 0;
	while(getline(cin, lineinput))
	{

		trim_right(lineinput);
		if(lineinput=="")
			continue;

		linenum ++;
		cout <<"%"<<lineinput<<endl;
		tokenizer< char_separator<char> > tokens(lineinput, sep);
		vector<string> tt;
		BOOST_FOREACH (const string& t, tokens)
			tt.push_back(t);
		int ts = tt.size()/2 - 1;
		string no = tt[0];
		string novstr = tt[1];
		int nvo;
		istringstream(novstr) >> nvo;

		//cout<<"ts = "<<ts<<endl;


		int startctr = cndctr;
		for(i=1; i<=ts; i++)
		{
			//cout<<"i = "<<i<<endl;
			string ni = tt[2*i];
			string nvstr = tt[2*i+1];
			int nv;
			istringstream(nvstr) >> nv;

			cout<<"% "<<ni<<" = "<<nv<<"/"<<k<<endl;
			cndctr++;
			/* For every input ni = nv, translate set flag  cnd1 = 1 iff ni<=p */
			cout<<"% cnd"<<no<<cndctr<<" :- "<<ni<<" * "<<k-nv<<"/"<<k<<"."<<endl;
			cout<<"% cnd"<<no<<cndctr<<" :- "<<"cnd"<<no<<cndctr<<" + "<<"cnd"<<no<<cndctr<<"."<<endl;
			int ii,jj;
			for(ii=1; ii<=k; ii++)
			{
				for (jj=ii; jj<=k; jj++)
				{
					cout<<"cnd"<<no<<cndctr<<"("<<ii<<")"<<" :- "<<ni<<"("<<jj<<"), "<<"const_"<<k-nv<<"("<<k-jj+ii<<")."<<endl;
				}
			}

			for(ii=1; ii<k; ii++)
			{
				cout<<"cnd"<<no<<cndctr<<"("<<ii<<")"<<" :- "<<"cnd"<<no<<cndctr<<"("<<ii+1<<")."<<endl;
				cout<<"cnd"<<no<<cndctr<<"("<<ii+1<<")"<<" :- "<<"cnd"<<no<<cndctr<<"("<<ii<<")."<<endl;
			}

			cndctr++;
			/* For every input ni = nv, translate set flag  cnd2 = 1 iff ni>=p */
			cout<<"% cnd"<<no<<cndctr<<" :- not "<<ni<<" * "<<nv<<"/"<<k<<"."<<endl;
			cout<<"% cnd"<<no<<cndctr<<" :- "<<"cnd"<<no<<cndctr<<" + "<<"cnd"<<no<<cndctr<<"."<<endl;


			for(ii=1; ii<=k; ii++)
			{
				for (jj=ii; jj<=k; jj++)
				{
					cout<<"cnd"<<no<<cndctr<<"("<<ii<<")"<<" :- "<<"not_"<<ni<<"("<<jj<<"), "<<"const_"<<nv<<"("<<k-jj+ii<<")."<<endl;
				}
			}

			for(ii=1; ii<=k; ii++)
				cout<<"not_"<<ni<<"("<<ii<<") :- not "<<ni<<"("<<k-ii+1<<")."<<endl;

			for(ii=1; ii<k; ii++)
			{
				cout<<"cnd"<<no<<cndctr<<"("<<ii<<")"<<" :- "<<"cnd"<<no<<cndctr<<"("<<ii+1<<")."<<endl;
				cout<<"cnd"<<no<<cndctr<<"("<<ii+1<<")"<<" :- "<<"cnd"<<no<<cndctr<<"("<<ii<<")."<<endl;
			}

			cout<<"line("<<linenum<<", "<<i<<") :- not cnd"<<no<<cndctr<<"("<<k<<"), not cnd"<<no<<cndctr-1<<"("<<k<<")."<<endl;

		}

		/* For every line of input, create a rule specifying the input if all conditional flags are satisfied. */
		/*int stopctr = cndctr;
		cout<<no<<"_p("<<nvo<<")"<<" :- ";
		for(i=stopctr; i>startctr+1; i--)
		{
			cout<<"not cnd"<<no<<i<<"("<<k<<"), ";
		}
		cout<<"not cnd"<<no<<startctr+1<<"("<<k<<")."<<endl;
		*/

		cout<<no<<"_p("<<nvo<<")"<<" :- ";
		for(i=1; i<ts; i++)
			cout<<"line("<<linenum<<", "<<i<<"), ";
		cout<<"line("<<linenum<<", "<<ts<<"). "<<endl;
	}

	/* Equality constraint for nn and nn_p */

	
	for(it=nodes.begin(); it!=nodes.end(); ++it)
	{
		string nn = it->first;
		for(i=0; i<=k; i++)
		{
			cout<<" :- "<<nn<<"("<<i<<")"<<", not "<<nn<<"_p"<<"("<<i<<")."<<endl;
			cout<<" :- "<<nn<<"_p"<<"("<<i<<")"<<", not "<<nn<<"("<<i<<")."<<endl;
		}
	}
	
	return 0;
}

