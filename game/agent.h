//=================================
// include guard
#ifndef __AGENT_H_INCLUDED__
#define __AGENT_H_INCLUDED__
//=================================

#include <stdio.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

class Agent {
	
	Game* game;
	bool debug;
	vector<int[3][3]> states;
	vector<double> val;
	
	double value(int[3][3] );

	public:
		Agent( Game* );
		void setDebug( bool x ) { debug = x; };

		int Move();
		void Update();
		void DumpPolicy(string file);
};

//=================================
// end guard
#endif
//=================================
