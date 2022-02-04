#include "Lastmove.h"

void last_move::set_last_move(Spot start, Spot end)
{
	piece = start.get_piece_name();
	white = start.get_piece().Is_white();
	start_x = start.get_x();
	start_y = start.get_y();
	end_x = end.get_x();
	end_y = end.get_y();
}

int last_move::get_start_coord(char coord)
{
	if (coord == 'x')
		return start_x;
	else
		return start_y;
}

int last_move::get_end_coords(char coord)
{
	if (coord == 'x')
		return end_x;
	else
		return end_y;
}