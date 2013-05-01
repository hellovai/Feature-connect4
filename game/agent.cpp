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
	gamma = 1;
	alpha = 0.3;
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
	double val_curr = Value();
	double val_prev = Value() - Value(game->last_move, game->Turn() == turn);
	double val = gamma*val_prev + val_curr;
	val += game->Reward() * turn;
	if(debug) cout<<"Agent "<<turn<<": "<<"Reward for this update: "<<game->Reward()*turn<<endl;
	for(int i = 0; i < HEIGHT; i++)
		for(int j = 0; j < WIDTH; j++) {
			int var = game->Board(i,j);
			epsilon[i][j][0] = gamma*lambda*epsilon[i][j][0] + (var == turn ? 1 : 0) * val_curr;
			epsilon[i][j][1] = gamma*lambda*epsilon[i][j][1] + (var == -turn ? 1 : 0) * val_curr;
			theta[i][j][0] += val*epsilon[i][j][0]*alpha;
			theta[i][j][1] += val*epsilon[i][j][1]*alpha;
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
			sum += (relative == turn ? 1 : 0)*theta[i][j][0];
			sum += (relative == -turn ? 1 : 0)*theta[i][j][1];
		}
	return sum;
}

double Agent::Value(int move, bool peice) {
	return theta[ game->Full(move) ][move][( peice ? 0 : 1 )];
}