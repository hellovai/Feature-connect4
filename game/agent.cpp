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
	debug = false;
	turn = trn;
	lambda = 0.9;
	gamma = 0.5;
	alpha = 0.02;
	for(int i = 0; i < HEIGHT; i++)
		for(int j = 0; j < WIDTH; j++)
			theta[i][j][0] = theta[i][j][1] = epsilon[i][j][0] = epsilon[i][j][1] = visit[i][j][0] = visit[i][j][1] = 0;
}

//public functions
int Agent::Move() {
	vector<int> possible;
	for(int i = 0; i < WIDTH; i++)
		if(game->Valid(i))
			possible.push_back(i);

	vector<int> index; index.push_back(0);
	double val = Value();
	double max = val+Value( possible[0], true );
	for(int i = 1; i < (int) possible.size(); i++) {
		val += Value(possible[i], true);
		if(val > max) {
			index.clear();
			index.push_back(i);
		} else if(val == max) {
			index.push_back(i);
		}
		val -= Value(possible[i], true);
	}
	return possible[index[rand()%index.size()]];
}

void Agent::Update() {
	double val_next = Value();
	double val_curr = Value() - Value(game->last_move);
	double val = game->Reward() * turn + gamma*val_next - val_curr;
	if(debug) cout<<"Agent "<<turn<<": "<<"Reward for this update: "<<game->Reward()<<" "<<val<<" "<<val_next<<" "<<val_curr<<" "<<Value(game->last_move)<<endl;
	if(debug && val != 0) cin.ignore();
	for(int i = 0; i < HEIGHT; i++)
		for(int j = 0; j < WIDTH; j++) {
			int boardval = game->Board(i,j);
			for(int var = 0; var < 2; var++) {
				if(debug) cout<<"\t"<<"epsilon["<<i<<"]["<<j<<"]["<<var<<"] => "<<epsilon[i][j][var]<<" ";
				epsilon[i][j][var] = gamma*lambda*epsilon[i][j][var];
				if( (j == game->last_move && i == game->Full(game->last_move)-1) && ((var == 0 && boardval == turn) || (var == 1 && boardval == -turn)))
					epsilon[i][j][var] += 1;
				if(debug) cout<<epsilon[i][j][var]<<endl;
				if(debug) cout<<"\t"<<"theta["<<i<<"]["<<j<<"]["<<var<<"] => "<<theta[i][j][var]<<" ";
				theta[i][j][var] += val*epsilon[i][j][var]*alpha;
				if(debug) cout<<theta[i][j][var]<<endl;
			}
		}
}

void Agent::DumpPolicy(string name) {
	cout<<"Value = ";
	for(int i = 0; i < HEIGHT; i++)
		for(int j = 0; j < WIDTH; j++)
			cout<<"[Your Piece] * "<<theta[i][j][0]<<" + "<<"[Opponents Piece] * "<<theta[i][j][1]<<endl;
}

//private functions
double Agent::Value() {
	double sum = 0;
	for(int i = 0; i < HEIGHT; i++)
		for(int j = 0; j < WIDTH; j++) {
			int relative = game->Board(i,j);
			if(relative != 0) {
				sum += theta[i][j][(relative == turn ? 0 : 1)];
				//cout<<"["<<i<<"]["<<j<<"]["<<(relative == turn ? 0 : 1)<<"]"<<endl;
			}
		}
	return sum;
}

double Agent::Value(int move, bool peice) {
	return theta[ game->Full(move)-1 ][move][( peice ? 0 : 1 )];
}

double Agent::Value(int move) {
	return theta[ game->Full(move)-1 ][move][(game->Board(game->Full(move)-1, move) == turn ? 0 : 1)];
}