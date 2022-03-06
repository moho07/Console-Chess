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
	inline bool Get_castling() { return king.is_castling_done(); }
};

class Spot
{
	int x;
	int y;
	Selector s;
	std::string piece;

public:
	void set(int X, int Y, std::string Piece, bool white = false);
	inline void set_piece(std::string Piece) { piece = Piece; }
	inline std::string get_piece_name() { return piece; }
	inline Selector get_piece() { return s; }
	inline int get_x() { return x; }
	inline void set_x(int X) { x = X; }
	inline int get_y() { return y; }
	inline void set_y(int Y) { y = Y; }
	inline void Change_first_move(std::string piece);
	inline void Set_first_move_spaces(int spaces) { s.pawn.first_move_spaces = spaces; }
	inline void Set_castling(bool castling) { s.king.set_castling_done(castling); }
};



