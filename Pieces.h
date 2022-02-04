#pragma once
#include "Board.h"

class Spot;

class Piece
{
	bool white;
	bool there = false;

public:
	bool is_there() { return there; }
	void set_there(bool There) { there = There; }
	bool is_white() { return white; }
	void set_white(bool White) { white = White; }
};

class King : public Piece
{
	bool castling_done = false;
	
	
public:
	
	bool is_castling_done() { return castling_done; }
	void set_castling_done(bool Castling) { castling_done = Castling; }
};

class Queen : public Piece
{
};

class Rook : public Piece
{
	bool first_move = true;

public:
	bool get_first_move() { return first_move; }
	void change_first_move() { first_move = false; }
};

class Knight : public Piece
{
};

class Bishop : public Piece
{
};

class Pawn : public Piece
{
	bool first_move = true;
public:
	int first_move_spaces;
	bool get_first_move() { return first_move; }
	void change_first_move() { first_move = false; }
};