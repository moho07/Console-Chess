#pragma once
#include <math.h>
#include "Canmove.h"
#include "Move.h"
#include "Lastmove.h"

bool King_canMove(Board board, Spot start, Spot end)
{
	if (end.get_piece().Is_there_piece())
		if (end.get_piece().Is_white() == start.get_piece().Is_white())
			return false;

	int y = abs(end.get_x() - start.get_x());
	int x = abs(end.get_y() - start.get_y());
	
	if (!start.get_piece().Get_castling() && y == 0 && x == 2)
	{
		if (start.get_piece().Is_white())
		{
			if (end.get_x() == 2)
			{
				if (board.get_box(7, 0).get_piece_name() != "rook" || !board.get_box(7, 0).get_piece().Get_first_move("rook"))
					return false;

				for (int i = 1; i < 4; i++)
				{
					if (board.get_box(7, i).get_piece().Is_there_piece())
						return false;
				}
			}
			else
			{
				if (board.get_box(7, 7).get_piece_name() != "rook" || !board.get_box(7, 7).get_piece().Get_first_move("rook"))
					return false;

				for (int i = 1; i < 3; i++)
				{
					if (board.get_box(7, 7 - i).get_piece().Is_there_piece())
						return false;
				}
			}
		}
		else
		{
			if (end.get_x() == 2)
			{
				if (board.get_box(0, 0).get_piece_name() != "rook" || !board.get_box(0, 0).get_piece().Get_first_move("rook"))
					return false;

				for (int i = 1; i < 4; i++)
				{
					if (board.get_box(0, i).get_piece().Is_there_piece())
						return false;
				}
			}
			else
			{
				if (board.get_box(0, 7).get_piece_name() != "rook" || !board.get_box(0, 7).get_piece().Get_first_move("rook"))
					return false;

				for (int i = 1; i < 3; i++)
				{
					if (board.get_box(0, 7 - i).get_piece().Is_there_piece())
						return false;
				}
			}
		}

		throw 1.0f;  
	}

	if (x + y > 2)
		return false;
	
	return true;
}

bool Queen_canMove(Board board, Spot start, Spot end)
{
	if (end.get_piece().Is_there_piece())
		if (end.get_piece().Is_white() == start.get_piece().Is_white())
			return false;

	int y = abs(end.get_x() - start.get_x());
	int x = abs(end.get_y() - start.get_y());

	if (x != y && (x != 0 && y != 0))
		return false;

	if (x == y)
	{
		if (start.get_x() < end.get_x() && start.get_y() < end.get_y())
		{
			for (int i = 1; i < x; i++)
			{
				if (board.get_box(start.get_x() + i, start.get_y() + i).get_piece().Is_there_piece())
					return false;
			}
		}
		else if (start.get_x() < end.get_x() && start.get_y() > end.get_y())
		{
			for (int i = 1; i < x; i++)
			{
				if (board.get_box(start.get_x() + i, start.get_y() - i).get_piece().Is_there_piece())
					return false;
			}
		}
		else if (start.get_x() > end.get_x() && start.get_y() < end.get_y())
		{
			for (int i = 1; i < x; i++)
			{
				if (board.get_box(start.get_x() - i, start.get_y() + i).get_piece().Is_there_piece())
					return false;
			}
		}
		else if (start.get_x() > end.get_x() && start.get_y() > end.get_y())
		{
			for (int i = 1; i < x; i++)
			{
				if (board.get_box(start.get_x() - i, start.get_y() - i).get_piece().Is_there_piece())
					return false;
			}
		}
	}

	if (x == 0)
	{
		if (start.get_x() < end.get_x())
		{
			for (int i = 1; i < y; i++)
			{
				if (board.get_box(start.get_x() + i, start.get_y()).get_piece().Is_there_piece())
					return false;
			}
		}
		else if (start.get_x() > end.get_x())
		{
			for (int i = 1; i < y; i++)
			{
				if (board.get_box(start.get_x() - i, start.get_y()).get_piece().Is_there_piece())
					return false;
			}
		}
	}

	if (y == 0)
	{
		if (start.get_y() < end.get_y())
		{
			for (int i = 1; i < x; i++)
			{
				if (board.get_box(start.get_x(), start.get_y() + i).get_piece().Is_there_piece())
					return false;
			}
		}
		else if (start.get_y() > end.get_y())
		{
			for (int i = 1; i < x; i++)
			{
				if (board.get_box(start.get_x(), start.get_y() - i).get_piece().Is_there_piece())
					return false;
			}
		}
	}

	return true;
}

bool Rook_canMove(Board board, Spot start, Spot end)
{
	if (end.get_piece().Is_there_piece())
		if (end.get_piece().Is_white() == start.get_piece().Is_white())
			return false;

	int y = abs(end.get_x() - start.get_x());
	int x = abs(end.get_y() - start.get_y());

	if (x != 0 && y != 0)
		return false;

	if (x == 0)
	{
		if (start.get_x() < end.get_x())
		{
			for (int i = 1; i < y; i++)
			{
				if (board.get_box(start.get_x() + i, start.get_y()).get_piece().Is_there_piece())
					return false;
			}
		}
		else if (start.get_x() > end.get_x())
		{
			for (int i = 1; i < y; i++)
			{
				if (board.get_box(start.get_x() - i, start.get_y()).get_piece().Is_there_piece())
					return false;
			}
		}
	}

	if (y == 0)
	{
		if (start.get_y() < end.get_y())
		{
			for (int i = 1; i < x; i++)
			{
				if (board.get_box(start.get_x(), start.get_y() + i).get_piece().Is_there_piece())
					return false;
			}
		}
		else if (start.get_y() > end.get_y())
		{
			for (int i = 1; i < x; i++)
			{
				if (board.get_box(start.get_x(), start.get_y() - i).get_piece().Is_there_piece())
					return false;
			}
		}
	}

	return true;
}

bool Knight_canMove(Board board, Spot start, Spot end)
{
	if (end.get_piece().Is_there_piece())
		if (end.get_piece().Is_white() == start.get_piece().Is_white())
			return false;

	int y = abs(end.get_x() - start.get_x());
	int x = abs(end.get_y() - start.get_y());

	if ((x != 1 || y != 2) && (x != 2 || y != 1))
		return false;

	return true;
}

bool Bishop_canMove(Board board, Spot start, Spot end)
{
	if (end.get_piece().Is_there_piece())
		if (end.get_piece().Is_white() == start.get_piece().Is_white())
			return false;

	int y = abs(end.get_x() - start.get_x());
	int x = abs(end.get_y() - start.get_y());

	if (x != y )
		return false;

	if (start.get_x() < end.get_x() && start.get_y() < end.get_y())
	{
		for (int i = 1; i < x; i++)
		{
			if (board.get_box(start.get_x() + i, start.get_y() + i).get_piece().Is_there_piece())
				return false;
		}
	}
	else if (start.get_x() < end.get_x() && start.get_y() > end.get_y())
	{
		for (int i = 1; i < x; i++)
		{
			if (board.get_box(start.get_x() + i, start.get_y() - i).get_piece().Is_there_piece())
				return false;
		}
	}
	else if (start.get_x() > end.get_x() && start.get_y() < end.get_y())
	{
		for (int i = 1; i < x; i++)
		{
			if (board.get_box(start.get_x() - i, start.get_y() + i).get_piece().Is_there_piece())
				return false;
		}
	}
	else if (start.get_x() > end.get_x() && start.get_y() > end.get_y())
	{
		for (int i = 1; i < x; i++)
		{
			if (board.get_box(start.get_x() - i, start.get_y() - i).get_piece().Is_there_piece())
				return false;
		}
	}

	return true;
}

bool Pawn_canMove(Board board, Spot start, Spot end)
{
	if ((end.get_x() < start.get_x() && !start.get_piece().Is_white()) || (end.get_x() > start.get_x() && start.get_piece().Is_white()))
		return false;

	int y = abs(end.get_x() - start.get_x());
	int x = abs(end.get_y() - start.get_y());

		
	if (x > 1 || y > 2)
		return false;

	if (x == 1 && y != 1)
		return false;

	if (x == 1)
	{
		Spot maybe_pawn = board.get_box(end.get_x() - 1, end.get_y());

		if (end.get_piece().Is_there_piece())
		{
			if (end.get_piece().Is_white() == start.get_piece().Is_white())
				return false;
		}
		else if (maybe_pawn.get_piece_name() == "pawn" && maybe_pawn.get_piece().Is_white() != start.get_piece().Is_white())
		{
			if (last.get_piece_name() == "pawn" && maybe_pawn.get_x() == last.get_end_coords('x') && maybe_pawn.get_y() == last.get_end_coords('y') && maybe_pawn.get_piece().Get_first_move_spaces() == 2)
				throw 2.0f;
			else
				return false;
		}
		else
			return false;
	}

	if (y == 1 && x == 0)
		if (end.get_piece().Is_there_piece())
			return false;

	if (y == 2 && x == 0 && !start.get_piece().Get_first_move("pawn"))
		return false;

	return true;
}

bool CanMove(std::string piece, Board board, Spot start, Spot end)
{
	if (piece == "king")
		return King_canMove(board, start, end);
	else if (piece == "queen")
		return Queen_canMove(board, start, end);
	else if (piece == "rook")
		return Rook_canMove(board, start, end);
	else if (piece == "knight")
		return Knight_canMove(board, start, end);
	else if (piece == "bishop")
		return Bishop_canMove(board, start, end);
	else if (piece == "pawn")
		return Pawn_canMove(board, start, end);
}
