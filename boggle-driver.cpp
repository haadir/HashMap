#include <iostream>
#include <sstream>
#include <vector>
#include <string>
#include <set>
#include <random>

#include "boggle.h"

using namespace std;

int main(int argc, char* argv[])
{
	if(argc < 4)
	{
		cout << "Usage: boggle-driver <size> <seed> <dictionary file>" << endl;
		exit(1);
	}
	int size = atoi(argv[1]);
	int seed = atoi(argv[2]);
	vector<vector<char> > board = genBoard(size, seed);
	printBoard(board);
	pair<set<string>, set<string> > parsed = parseDict(string(argv[3]));
	set<string> dictionary = parsed.first;
	set<string> prefix = parsed.second;
	set<string> found = boggle(dictionary, prefix, board);
	set<string>::iterator it;
	stringstream os;
	for(it=found.begin();it != found.end(); ++it)
	{
		os << *it << ", ";
	}
	cout << "Found " << found.size() << " words:" << endl;
	cout << os.str().substr(0,os.str().size()-2) << endl;
}
