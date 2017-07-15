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
	s = atoi(argv[1]);

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
		cout<<no<<"(T, "<<nvo<<")"<<" :- ";
		for(i=1; i<ts; i++)
			cout<<"line(T-1, "<<linenum<<", "<<i<<"), ";
		cout<<"line(T-1, "<<linenum<<", "<<ts<<"), time(T), T>=1. "<<endl;
		
		
		
	}
	
	
	cout<<"truth_val(1.."<<k<<")."<<endl;
	/* Check for only one possible next state
	*/
	for(it=nodes.begin(); it!=nodes.end(); ++it)
	{
		string nn = it->first;
		
		cout<<"diff_"<<nn<<" :- "<<nn<<"(T+1, Val), not "<<nn<<"(T, Val), time(T), truth_val(Val)."<<endl;
		cout<<"diff_"<<nn<<" :- "<<nn<<"(T, Val), not "<<nn<<"(T+1, Val), time(T), truth_val(Val)."<<endl;
	}
	
	vector<string> allnodenames;
	for(it=nodes.begin(); it!=nodes.end(); ++it)
	{
		allnodenames.push_back(it->first);
	}
	
	for(i=0; i<allnodenames.size(); i++)
		for(j=i+1; j<allnodenames.size(); j++)
			cout<<":- diff_"<<allnodenames[i]<<", diff_"<<allnodenames[j]<<"."<<endl;
	
	cout<<" :- ";
	for(i=0; i<allnodenames.size()-1; i++)
		cout<<" not diff_"<<allnodenames[i]<<", ";
	cout<<" not diff_"<<allnodenames[allnodenames.size()-1]<<"."<<endl;

	/* Check equality for at least one l, 1<=l<=s of state at 0 andstate at l */

	for(it=nodes.begin(); it!=nodes.end(); ++it)
	{
		string nn = it->first;
		for(j=1; j<=s; j++)
		{
			for(i=0; i<=k; i++)
			{
				cout<<" notcyc_"<<j<<" :- "<<nn<<"(0, "<<i<<")"<<", not "<<nn<<"("<<j<<", "<<i<<")."<<endl;
				cout<<" notcyc_"<<j<<" :- "<<nn<<"("<<j<<", "<<i<<")"<<", not "<<nn<<"(0, "<<i<<")."<<endl;
			}
		}
	}

	cout<<" :- ";
	for(j=1; j<s; j++)
		cout<<" not notcyc_"<<j<<", ";
	cout<<"not notcyc_"<<s<<"."<<endl;

	
	return 0;
}
