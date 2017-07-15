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

	int atype, s;
	atype = atoi(argv[1]);
	s = atoi(argv[2]);

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
	mapstr::const_iterator it, it2;
	for(it=nodes.begin(); it!=nodes.end(); ++it)
	{
		cout<<"#show "<<it->first<<"/2."<<endl;
		//cout<<"#show line/3."<<endl;
	}
	cout<<"#const maxT="<<s<<"."<<endl;
	cout<<"time(0..maxT)."<<endl;

	for(it=nodes.begin(); it!=nodes.end(); ++it)
	{
		string nn = it->first;
		string gnn = "g_" + nn;
		cout<<gnn<<0;
		for(j=1; j<=k; j++)
			cout<<" | "<<gnn<<j;
		cout<<"."<<endl;

		for(j=1; j<=k; j++)
			cout<<nn<<"(0, "<<j<<") :- "<<gnn<<j<<"."<<endl;

		for(j=1; j<k; j++)
			cout<<nn<<"(0, "<<j<<") :- "<<nn<<"(0, "<<j+1<<")."<<endl;

		/* All the truth-hierarchical rules */

		cout<<nn<<"(T, "<<0<<") :- time(T)."<<endl;

		for(j=1; j<k; j++)
		{
			cout<<nn<<"(T, "<<j<<")"<<" :- "<<nn<<"(T, "<<j+1<<")."<<endl;
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
		cout<<"% line number "<<linenum<<endl;
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
					cout<<"cnd"<<no<<cndctr<<"(T, "<<ii<<")"<<" :- time(T), "<<ni<<"(T, "<<jj<<"), "<<"const_"<<k-nv<<"("<<k-jj+ii<<")."<<endl;
				}
			}

			for(ii=1; ii<k; ii++)
			{
				cout<<"cnd"<<no<<cndctr<<"(T, "<<ii<<")"<<" :- time(T), "<<"cnd"<<no<<cndctr<<"(T, "<<ii+1<<")."<<endl;
				cout<<"cnd"<<no<<cndctr<<"(T, "<<ii+1<<")"<<" :- time(T), "<<"cnd"<<no<<cndctr<<"(T, "<<ii<<")."<<endl;
			}

			cndctr++;
			/* For every input ni = nv, translate set flag  cnd2 = 1 iff ni>=p */
			cout<<"% cnd"<<no<<cndctr<<" :- not "<<ni<<" * "<<nv<<"/"<<k<<"."<<endl;
			cout<<"% cnd"<<no<<cndctr<<" :- "<<"cnd"<<no<<cndctr<<" + "<<"cnd"<<no<<cndctr<<"."<<endl;


			for(ii=1; ii<=k; ii++)
			{
				for (jj=ii; jj<=k; jj++)
				{
					cout<<"cnd"<<no<<cndctr<<"(T, "<<ii<<")"<<" :- time(T), "<<"not_"<<ni<<"(T, "<<jj<<"), "<<"const_"<<nv<<"("<<k-jj+ii<<")."<<endl;
				}
			}

			for(ii=1; ii<=k; ii++)
				cout<<"not_"<<ni<<"(T, "<<ii<<") :- time(T), not "<<ni<<"(T, "<<k-ii+1<<")."<<endl;

			for(ii=1; ii<k; ii++)
			{
				cout<<"cnd"<<no<<cndctr<<"(T, "<<ii<<")"<<" :- "<<"cnd"<<no<<cndctr<<"(T, "<<ii+1<<")."<<endl;
				cout<<"cnd"<<no<<cndctr<<"(T, "<<ii+1<<")"<<" :- "<<"cnd"<<no<<cndctr<<"(T, "<<ii<<")."<<endl;
			}

			cout<<"line(T, "<<linenum<<", "<<i<<") :- time(T),  not cnd"<<no<<cndctr<<"(T, "<<k<<"), not cnd"<<no<<cndctr-1<<"(T, "<<k<<")."<<endl;

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

		int nodeid = nodes[no];
		cout<<no<<"(T, "<<nvo<<")"<<" :- up("<<nodeid<<", T-1), ";
		for(i=1; i<ts; i++)
			cout<<"line(T-1, "<<linenum<<", "<<i<<"), ";
		cout<<"line(T-1, "<<linenum<<", "<<ts<<"), time(T), T>=1. "<<endl;
		
		
		
	}

	/* Equality constraint for nn and nn_p */

	for(it=nodes.begin(); it!=nodes.end(); ++it)
	{
		string nn = it->first;
		for(i=0; i<=k; i++)
		{
			cout<<" :- "<<nn<<"(0, "<<i<<")"<<", not "<<nn<<"(maxT, "<<i<<")."<<endl;
			cout<<" :- "<<nn<<"(maxT, "<<i<<")"<<", not "<<nn<<"(0, "<<i<<")."<<endl;
		}
	}

	/* Discard steady-states (where nn stays constant) */
	
	for(it=nodes.begin(); it!=nodes.end(); ++it)
	{
		string nn = it->first;
		for(i=0; i<=k; i++)
		{
			cout<<" notconst :- "<<nn<<"(0, "<<i<<")"<<", not "<<nn<<"(1, "<<i<<")."<<endl;
			cout<<" notconst :- "<<nn<<"(1, "<<i<<")"<<", not "<<nn<<"(0, "<<i<<")."<<endl;
		}
	}
	cout<<" :- not notconst."<<endl;
	
	
	/* Update selection rules */
	
		
	
	switch(atype)
	{
		case 0:
			for(i=0; i<n; i++)
				cout<<"up("<<i<<", T) :- time(T)."<<endl;
			break;
		case 1:
			for(i=0; i<n-1; i++)
				cout<<"up("<<i<<", T) |";
			cout<<"up("<<n-1<<", T):- time(T)."<<endl;
			break;
		case 2:
			for(i=0; i<n; i++)
				cout<<" up("<<i<<", T) | -up("<<i<<", T) :- time(T)."<<endl;
			cout<<"sup(T) :- time(T), up(_, T)."<<endl;
			cout<<":- time(T), not sup(T)."<<endl;
			break;
	
		default:
			cerr<<"ERROR: Async type not specified correctly!"<<endl;
			return 1;
	}
	
	return 0;
}
