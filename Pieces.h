#pragma once
#include "Board.h"

class Spot;

class Piece
{
	bool white;
	bool there = false;

public:
	inline bool is_there() { return there; }
	inline void set_there(bool There) { there = There; }
	inline bool is_white() { return white; }
	inline void set_white(bool White) { white = White; }
};

class King : public Piece
{
	bool castling_done = false;

public:
	inline bool is_castling_done() { return castling_done; }
	inline void set_castling_done(bool Castling) { castling_done = Castling; }
};

class Queen : public Piece
{
};

class Rook : public Piece
{
	bool first_move = true;

public:
	inline bool get_first_move() { return first_move; }
	inline void change_first_move() { first_move = false; }
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
	inline bool get_first_move() { return first_move; }
	inline void change_first_move() { first_move = false; }
};