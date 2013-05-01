#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>

#include "main.h"
#include "game.h"

using namespace std;

Game::Game() {
	debug = false;
	Reset();
}

void Game::Reset() {
	for(int i=0; i<HEIGHT; i++)
		for(int j=0; j<WIDTH; j++)
			board[i][j] = 0;
	for(int j = 0; j < WIDTH; j++ )
		full[j] = 0;
	last_move = -1;
	curr_player = 1;
	moves = 0;
	myStatus = true;
	winner = 0;
}

void Game::Print() {
	for(int i=0; i<HEIGHT; i++) {
		cout<<"|";
		for(int j=0; j<WIDTH; j++)
			cout<<GUI(board[i][j])<<"|";
		cout<<endl;
	}
}

bool Game::Valid(int block) {
	if(block < WIDTH && full[block] < HEIGHT)
		return true;
	return false;
} 

void Game::Move(int block) {
	int x = full[block], y = block;
	board[x][y] = curr_player;
	moves++;
	full[y]++;
	last_move = block;
	CheckBoard();
	curr_player *= -1;
}

//private functions
string Game::GUI(int num) {
	switch(num)
	{
		case 1: return "\u25A0";
		case -1: return "\u25A1";
		default: return " ";
	}
}

void Game::CheckBoard() {
	if(moves == HEIGHT*WIDTH){
		myStatus = false;
		if(debug) cout<<"Oversize"<<endl;
	}
	if(Win()) {
		myStatus = false;
		winner = curr_player;
		if(debug) cout<<"Winner found!"<<endl;
	}
}

bool Game::Win() {
    int player = curr_player;
    int counter = 0;
    int line = full[last_move]-1;
    int column = last_move;

    while( validcoor(line, column) && (counter < 5) && (board[line][column] == player)) {
        counter++;
        column--;
 
        if(counter == 5)
            return true;
    }
 
    line = full[last_move]-1;
    column = last_move;
    while( validcoor(line, column) && (counter < 5) && (board[line][column] == player)) {
        counter++;
        column++;
 
        if(counter == 5)
            return true;
    }
 	counter = 0;
    line = full[last_move]-1;
    column = last_move;
    while( validcoor(line, column) && (counter < 5) && (board[line][column] == player)) {
        counter++;
        line--;
 
        if(counter == 5)
            return true;
    }
 
    line = full[last_move]-1;
    column = last_move;
    while( validcoor(line, column) && (counter < 5) && (board[line][column] == player)) {
        counter++;
        line++;
 
        if(counter == 5)
            return true;
    }
 
    counter = 0;
    column = last_move;
    while( validcoor(line, column) && (counter < 4) && (board[line][column] == player)) {
        counter++;
        line++;
        column--;
 
        if(counter == 4)
            return true;
    }
 

    line = full[last_move]-1;
    while( validcoor(line, column) && (counter < 5) && (board[line][column] == player)) {
        counter++;
        line--;
        column++;
 
        if(counter == 5)
            return true;
    }
 
    counter = 0;
    line = full[last_move]-1;
    column = last_move;
    while( validcoor(line, column) && (counter < 4) && (board[line][column] == player)) {
        counter++;
        line++;
        column++;
 
        if(counter == 4)
            return true;
    }
 
    line = full[last_move]-1;
    column = last_move;
    while( validcoor(line, column) && (counter < 5) && (board[line][column] == player)) {
        counter++;
        line--;
        column--;
 
        if(counter == 5)
            return true;
    }
 
    return false;
}

bool Game::validcoor(int x, int y) {
	if(x < HEIGHT && y < WIDTH && x >= 0 && y >= 0) return true;
	return false;
}