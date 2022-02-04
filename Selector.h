#pragma once
#include "Spot.h"

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
	bool Can_move(Board board, Spot start, Spot end);
	bool Get_first_move(std::string piece);
	bool Change_first_move(std::string piece);
	int Get_first_move_spaces();
	void Set_first_move_spaces(int spaces) { pawn.first_move_spaces = spaces; }
	bool Get_castling() { return king.is_castling_done(); }
	void Set_castling(bool castling) { king.set_castling_done(castling); }

};
