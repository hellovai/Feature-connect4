#include <stdlib.h>
#include <cstdlib>
#include <time.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>
#include <cmath>
#include <sstream>

#include "main.h"
#include "game.h"
#include "agent.h"

using namespace std;

void BenchMark(Agent* , int , int );

int main(int argc, char* argv[]) {	
	srand ( time(NULL) );
	string filename = "stats.dat"; 
	ofstream myFile;
	myFile.open(filename.c_str());
	int gameCounter = 1;
	bool debug = false, c1 = false, c2 = false;
	string dumpfile = "data";
	//read arguments and define variable based on them
	for(int i=1; i<argc; i++) {
		string temp = argv[i];
		if (temp.compare("-debug") == 0) {
			debug = true;
		} else if (temp.compare("-g") == 0) {
			if(++i<argc)
				gameCounter = atoi(argv[i]);
			else
				usage_err(temp);
		} else if (temp.compare("-c1") == 0) {
			c1 = true;
		} else if (temp.compare("-c2") == 0) {
			c2 = true;
		} else if (temp.compare("-dump") == 0) {
			if(++i<argc)
				dumpfile = argv[i];
			else
				usage_err(temp);
		} else
			usage_err(temp);
	}
	Game *game = new Game();
	
	Agent *p1, *p2;

	if(c1) { 
		system("touch agent1_stats.dat; rm agent1_stats.dat");
		p1 = new Agent(game, 1);
		p1 -> setDebug(debug);
	}	
	if(c2) { 
		system("touch agent2_stats.dat; rm agent2_stats.dat");
		p2 = new Agent(game, -1);
		p2 -> setDebug(debug);
	}
	int p1win = 0, p2win = 0, tie = 0;
	game->setDebug(false);
	//Agent *agent = new Agent(game);
	//agent->setDebug(debug);

	for(int i=0; i<gameCounter; i++) {
		if(debug) cout<<"Running Trial: "<<i<<endl;
		if(i % 10 == 0) {
			if(debug) cout<<"BenchMarking"<<endl;
			if(c1) BenchMark(p1, -1, i);
			if(c2) BenchMark(p2, 1, i);
		}
		game->Reset();
		if(debug) game->Print();
		while(game->Status()) {
			int move;
			if(game->curr_player == 1 && c1) {
				move = p1->Move();
			} else if (game->curr_player == -1 && c2) {
				move = p2->Move();
			} else {
				cout<<"Move: ";
				cin>>move;
			}
			if(game->Valid(move)) {
				game->Move(move);
			} else
				cout<<"Invalid Move!"<<endl;
			if(debug) game->Print();
			//cout<<"Game Reward: "<<game->Reward()<<endl;
			//if(game->Reward() != 0) cin.ignore();
			if(game->Status()) {
				if(c1 && game->curr_player == -1) p1->Update();
				else if(c2 && game->curr_player == 1) p2->Update();
			}
		}
		p1->Update();
		p2->Update();
		if(debug) cout<<"Winner is: "<<game->Reward()<<endl;
		if(game->Reward() == 1) p1win++;
		else if (game->Reward() == -1) p2win++;
		else tie++;
		myFile<<i<<" "<<game->Reward()<<endl;
	}
	cout<<"Results"<<endl;
	cout<<"Player 1:\t"<<p1win<<endl;
	cout<<"Player 2:\t"<<p2win<<endl;
	cout<<"Tie:\t"<<tie<<endl;
	p1->DumpPolicy("string");
	myFile.close();
	return 0;
}

void usage_err(string key) {
	if(key.compare("-h") != 0)
		cout<<"Improper usage of "<<key<<endl;
	cout<<"Usage: ./connect [-g episode] [-dump file] [-debug]"<<endl;
	cout<<"./connect -h displays usage"<<endl;
	cout<<"View README for info"<<endl;
	exit(0);
}

void BenchMark(Agent *agent, int otherturn, int gameCtr) {
	string filename = ( otherturn == -1 ? "agent1_stats.dat" : "agent2_stats.dat"); 
	ofstream myFile;
	myFile.open( filename.c_str(), ios::out | ios::app );
	Game *game = new Game();
	Agent *opponent = new Agent(game, otherturn);
	Game *hold = agent->ChangeGame(game);
	agent->ToggleDebug();
	int tie = 0, p1win = 0, p2win = 0;
	for(int i = 0; i < 100; i++) {
		game->Reset();
		while(game->Status()) {
			int move;
			if(game->curr_player == agent->Turn()) {
				move = agent->Move();
			} else {
				move = opponent->Move();
			}
			game->Move(move);
		}
		if(game->Reward() == 1) p1win++;
		else if (game->Reward() == -1) p2win++;
		else tie++;		
	}
	myFile<<gameCtr<<" "<<p1win<<" "<<p2win<<" "<<tie<<endl;
	myFile.close();
	agent->ChangeGame(hold);
	agent->ToggleDebug();
}