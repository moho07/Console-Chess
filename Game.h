#pragma once
#include "Player.h"
#include "Spot.h"
#include "Board.h"
#include "Move.h"

enum Gamestatus
{
	ACTIVE,
	WHITE_KING_CHECK,
	BLACK_KING_CHECK,
	BLACK_WIN,
	WHITE_WIN,
};

class Game
{
	Gamestatus status;
	Board board;
	Player p1, p2, currentplayer;
	std::string currentplayername;
	Move m;
	
public:
	Game() { board = Board(); }
	inline Gamestatus get_status() { return status; }
	inline void set_status(Gamestatus Status) { status = Status; }
	inline Board get_board() { return board; }
	void initialize(Player P1, Player P2);
	void set_currentplayer(Player p, std::string Currentplayername) { currentplayer = p; currentplayername = Currentplayername; }
	std::string get_current_player() { return currentplayername; }
	void playermove(int start_x, int start_y, int end_x, int end_y);
	void move(Spot start, Spot end);
	std::vector<std::string> get_captured(bool white);
};
