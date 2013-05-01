//=================================
// include guard
#ifndef __GAME_H_INCLUDED__
#define __GAME_H_INCLUDED__
//=================================

#include <stdio.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

class Game {
	int board[HEIGHT][WIDTH];
	int full[WIDTH];
	int moves;
	int winner;
	bool debug;
	bool myStatus;
	void CheckBoard(); 
	string GUI(int);
	bool Win();
	bool validcoor(int, int);
	public:
		Game();
		void Reset();
		void Print();
		void Move(int );
		bool Valid(int);

		bool Status() {return myStatus; }
		int Board( int i , int j ) { return board[i][j]; };
		int Full(int x ) { return full[x]; };
		int curr_player;
		bool Turn() { return curr_player; };
		int Reward() {return winner;};
		int last_move;
		void setDebug(bool x) {debug = x;};
		int Moves() { return moves; };
};

//=================================
// end guard
#endif
//=================================
