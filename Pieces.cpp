#include "Pieces.h"
#include "Move.h"
#include <math.h>

//when calling these function check that spot start & spot end are 
//same or not- if same give error that start & end destination are same

bool King::canMove(Board board, Spot start, Spot end)
{
	if (end.get_piece().Is_there_piece())
		if (end.get_piece().Is_white() == start.get_piece().Is_white())
			throw - 1;

	int x = abs(end.get_x() - start.get_x());
	int y = abs(end.get_y() - start.get_y());
	
	if (!is_castling_done && y == 0 && x == 2)
	{
		if (start.get_piece().Is_white())
		{
			if (end.get_x() == 2)
			{
				if (board.get_box(7, 0).get_piece_name() != "rook" || !board.get_box(7, 0).get_piece().Get_first_move("rook"))
					throw - 4;

				for (int i = 1; i < 4; i++)
				{
					if (board.get_box(7, i).get_piece().Is_there_piece())
						throw - 3;
				}
			}
			else
			{
				if (board.get_box(7, 7).get_piece_name() != "rook" || !board.get_box(7, 7).get_piece().Get_first_move("rook"))
					throw - 4;

				for (int i = 1; i < 3; i++)
				{
					if (board.get_box(7, 7 - i).get_piece().Is_there_piece())
						throw - 3;
				}
			}
		}
		else
		{
			if (end.get_x() == 2)
			{
				if (board.get_box(0, 0).get_piece_name() != "rook" || !board.get_box(0, 0).get_piece().Get_first_move("rook"))
					throw - 4;

				for (int i = 1; i < 4; i++)
				{
					if (board.get_box(0, i).get_piece().Is_there_piece())
						throw - 3;
				}
			}
			else
			{
				if (board.get_box(0, 7).get_piece_name() != "rook" || !board.get_box(0, 7).get_piece().Get_first_move("rook"))
					throw - 4;

				for (int i = 1; i < 3; i++)
				{
					if (board.get_box(0, 7 - i).get_piece().Is_there_piece())
						throw - 3;
				}
			}
		}

		throw 1;  
	}

	if (x + y > 2)
		throw - 2;
	
	return true;
}

bool Queen::canMove(Board board, Spot start, Spot end)
{
	if (end.get_piece().Is_there_piece())
		if (end.get_piece().Is_white() == start.get_piece().Is_white())
			throw - 1;

	int x = abs(end.get_x() - start.get_x());
	int y = abs(end.get_y() - start.get_y());

	if (x != y && (x != 0 && y != 0))
		throw - 2;

	if (x == y)
	{
		if (start.get_x() < end.get_x() && start.get_y() < end.get_y())
		{
			for (int i = 1; i < x; i++)
			{
				if (board.get_box(start.get_x() + i, start.get_y() + i).get_piece().Is_there_piece())
					throw - 3;
			}
		}
		else if (start.get_x() < end.get_x() && start.get_y() > end.get_y())
		{
			for (int i = 1; i < x; i++)
			{
				if (board.get_box(start.get_x() + i, start.get_y() - i).get_piece().Is_there_piece())
					throw - 3;
			}
		}
		else if (start.get_x() > end.get_x() && start.get_y() < end.get_y())
		{
			for (int i = 1; i < x; i++)
			{
				if (board.get_box(start.get_x() - i, start.get_y() + i).get_piece().Is_there_piece())
					throw - 3;
			}
		}
		else if (start.get_x() < end.get_x() && start.get_y() < end.get_y())
		{
			for (int i = 1; i < x; i++)
			{
				if (board.get_box(start.get_x() - i, start.get_y() - i).get_piece().Is_there_piece())
					throw - 3;
			}
		}
	}

	if (x == 0)
	{
		if (start.get_y() < end.get_y())
		{
			for (int i = 1; i < y; i++)
			{
				if (board.get_box(start.get_x(), start.get_y() + i).get_piece().Is_there_piece())
					throw - 3;
			}
		}
		else if (start.get_y() > end.get_y())
		{
			for (int i = 1; i < y; i++)
			{
				if (board.get_box(start.get_x(), start.get_y() - i).get_piece().Is_there_piece())
					throw - 3;
			}
		}
	}

	if (y == 0)
	{
		if (start.get_x() < end.get_x())
		{
			for (int i = 1; i < x; i++)
			{
				if (board.get_box(start.get_x() + i, start.get_y()).get_piece().Is_there_piece())
					throw - 3;
			}
		}
		else if (start.get_x() > end.get_x())
		{
			for (int i = 1; i < x; i++)
			{
				if (board.get_box(start.get_x() - i, start.get_y()).get_piece().Is_there_piece())
					throw - 3;
			}
		}
	}

	return true;
}

bool Rook::canMove(Board board, Spot start, Spot end)
{
	if (end.get_piece().Is_there_piece())
		if (end.get_piece().Is_white() == start.get_piece().Is_white())
			throw - 1;

	int x = abs(end.get_x() - start.get_x());
	int y = abs(end.get_y() - start.get_y());

	if (x != 0 && y != 0)
		throw - 2;

	if (x == 0)
	{
		if (start.get_y() < end.get_y())
		{
			for (int i = 1; i < y; i++)
			{
				if (board.get_box(start.get_x(), start.get_y() + i).get_piece().Is_there_piece())
					throw - 3;
			}
		}
		else if (start.get_y() > end.get_y())
		{
			for (int i = 1; i < y; i++)
			{
				if (board.get_box(start.get_x(), start.get_y() - i).get_piece().Is_there_piece())
					throw - 3;
			}
		}
	}

	if (y == 0)
	{
		if (start.get_x() < end.get_x())
		{
			for (int i = 1; i < x; i++)
			{
				if (board.get_box(start.get_x() + i, start.get_y()).get_piece().Is_there_piece())
					throw - 3;
			}
		}
		else if (start.get_x() > end.get_x())
		{
			for (int i = 1; i < x; i++)
			{
				if (board.get_box(start.get_x() - i, start.get_y()).get_piece().Is_there_piece())
					throw - 3;
			}
		}
	}

	return true;
}

bool Knight::canMove(Board board, Spot start, Spot end)
{
	if (end.get_piece().Is_there_piece())
		if (end.get_piece().Is_white() == start.get_piece().Is_white())
			throw - 1;

	int x = abs(end.get_x() - start.get_x());
	int y = abs(end.get_y() - start.get_y());

	if ((x != 1 || y != 2) && (x != 2 || y != 1))
		throw - 2;

	return true;
}

bool Bishop::canMove(Board board, Spot start, Spot end)
{
	if (end.get_piece().Is_there_piece())
		if (end.get_piece().Is_white() == start.get_piece().Is_white())
			throw - 1;

	int x = abs(end.get_x() - start.get_x());
	int y = abs(end.get_y() - start.get_y());

	if (x != y )
		throw - 2;

	if (start.get_x() < end.get_x() && start.get_y() < end.get_y())
	{
		for (int i = 1; i < x; i++)
		{
			if (board.get_box(start.get_x() + i, start.get_y() + i).get_piece().Is_there_piece())
				throw - 3;
		}
	}
	else if (start.get_x() < end.get_x() && start.get_y() > end.get_y())
	{
		for (int i = 1; i < x; i++)
		{
			if (board.get_box(start.get_x() + i, start.get_y() - i).get_piece().Is_there_piece())
				throw - 3;
		}
	}
	else if (start.get_x() > end.get_x() && start.get_y() < end.get_y())
	{
		for (int i = 1; i < x; i++)
		{
			if (board.get_box(start.get_x() - i, start.get_y() + i).get_piece().Is_there_piece())
				throw - 3;
		}
	}
	else if (start.get_x() < end.get_x() && start.get_y() < end.get_y())
	{
		for (int i = 1; i < x; i++)
		{
			if (board.get_box(start.get_x() - i, start.get_y() - i).get_piece().Is_there_piece())
				throw - 3;
		}
	}

	return true;
}

bool Pawn::canMove(Board board, Spot start, Spot end)
{
	if ((end.get_y() < start.get_y() && !is_white()) || (end.get_y() > start.get_y() && is_white()))
		throw - 1;

	int x = abs(end.get_x() - start.get_x());
	int y = abs(end.get_y() - start.get_y());

		
	if (x > 1 || y > 2)
		throw - 2;

	if (x == 1 && y != 1)
		throw - 2;

	if (x == 1)
	{
		Spot maybe_pawn = board.get_box(end.get_x() - 1, end.get_y());

		if (end.get_piece().Is_there_piece())
		{
			if (end.get_piece().Is_white() == start.get_piece().Is_white())
				throw - 1;
		}
		else if (maybe_pawn.get_piece_name() == "pawn" && maybe_pawn.get_piece().Is_white() != start.get_piece().Is_white())
		{
			if (last.get_piece_name() == "pawn" && maybe_pawn.get_x() == last.get_end_coords('x') && maybe_pawn.get_y() == last.get_end_coords('y') && maybe_pawn.get_piece().Get_first_move_spaces() == 2)
				throw 2;
			else
				throw - 5;
		}
		else
			throw - 2;
	}

	if (y == 1 && x == 0)
		if (end.get_piece().Is_there_piece())
			throw - 2;

	if (y == 2 && x == 0 && !first_move)
		throw -2;

	return true;
}

