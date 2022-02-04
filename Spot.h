#pragma once
#include <iostream>
#include <string.h>
#include "Pieces.h"

class Spot;

class Selector
{
	friend class Spot;

	King king;
	Queen queen;
	Rook rook;
	Knight knight;
	Bishop bishop;
	Pawn pawn;
	bool none = false;

public:
	bool Is_there_piece();
	bool Is_white();
	bool Get_first_move(std::string piece);
	int Get_first_move_spaces();
	bool Get_castling() { return king.is_castling_done(); }
};

class Spot
{
	int x;
	int y;
	Selector s;
	std::string piece;

public:
	void set(int X, int Y, std::string Piece, bool white = false);
	void set_piece(std::string Piece) { piece = Piece; }
	std::string get_piece_name() { return piece; }
	Selector get_piece() { return s; }
	int get_x() { return x; }
	void set_x(int X) { x = X; }
	int get_y() { return y; }
	void set_y(int Y) { y = Y; }
	void Change_first_move(std::string piece);
	void Set_first_move_spaces(int spaces) { s.pawn.first_move_spaces = spaces; }
	void Set_castling(bool castling) { s.king.set_castling_done(castling); }
};



