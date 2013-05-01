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
	int turn;
	double theta[HEIGHT][WIDTH][2];
	double epsilon[HEIGHT][WIDTH][2];
	int visit[HEIGHT][WIDTH][2];
	double lambda;
	double gamma;
	double alpha;
	double Value(int, bool );
	double Value();
	public:
		Agent( Game* , int);
		void setDebug( bool x ) { debug = x; };
		int Turn() {return turn;};
		Game* ChangeGame(Game* other) {
			Game* temp = game;
			game = other;
			return temp;
		};

		int Move();
		void Update();
		void DumpPolicy(string file);
};

//=================================
// end guard
#endif
//=================================
