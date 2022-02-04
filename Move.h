#pragma once
#include <iostream>
#include <string>
#include "Board.h"
#include "Spot.h"
#include "Lastmove.h"

struct Move
{
	void make_move(Board& board, Spot start, Spot end);
	void king_castle(Board& board, std::string side, bool white);
	void enpassant(Board& board, Spot start, Spot end);
	void pawnpromotion(Board& board, Spot end, bool white);
	bool king_in_check(Board board, bool king_white, bool check_checkmate = true);
	bool king_checkmate(Board board, Spot king, Spot piece);

	std::vector<Spot> piece_killed_white;
	std::vector<Spot> piece_killed_black;
};


