#pragma once
#include <iostream>
#include <vector>
#include <string>
#include "Spot.h"

class last_move
{
	std::string piece;
	bool white;
	int start_x;
	int start_y;
	int end_x;
	int end_y;

public:
	void set_last_move(Spot start, Spot end);
	inline std::string get_piece_name() { return piece; }
	inline bool get_white() { return white; }
	int get_start_coord(char coord);
	int get_end_coords(char coord);
};

extern last_move last;

struct store_move
{
	int start_x;
	int start_y;
	int end_x;
	int end_y;
	void storemove(int sx, int sy, int ex, int ey) { start_x = sx; start_y = sy; end_x = ex; end_y = ey; }
};

extern std::vector<store_move> store;
