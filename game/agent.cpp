#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>
#include <cstdlib> 

#include "main.h"
#include "game.h"
#include "agent.h"

using namespace std;
Agent::Agent( Game* gmptr, int trn) {
	game=gmptr;
	turn = trn;

	int board[3][3] = {{0,0,0}, {0,0,0}, {0,0,0}};
	states.push_back(0);
	val.push_back(0);
}

//public functions
int Agent::Move() {
	vector<int> possible = game->valid_moves();
	vector<int> index = {-1};
	double max = -100;
	for(int k = 0; k < (int) possible.size(); k++) {
		//set board to current move
		int board[3][3];
		for( int i = 0; i < 3; i++ )
		for( int j = 0; j < 3; j++ )
			board[i][j] = game->Board()[i][j];
		board[k/3][k%3] = turn;
		double boardval = value(board);
		if( max < boardval) {
			index.clear();
			index.push_back(k);
			max = boardval;
		} else if ( max == boardval ){
			index.push_back(k);
		}
	}
	return possible[index[rand()%index.size()]];
}

void Agent::Update() {
	
}

void Agent::DumpPolicy(string name) {

}

//private functions