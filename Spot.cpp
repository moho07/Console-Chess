#include "Spot.h"

void Spot::set(int X, int Y, std::string Piece, bool white)
{
	piece = Piece;
	x = X;
	y = Y;

	if (piece == "king")
	{
		s.king.set_there(true);
		s.king.set_white(white);
	}
	else if (piece == "queen")
	{
		s.queen.set_there(true);
		s.queen.set_white(white);
	}
	else if (piece == "rook")
	{
		s.rook.set_there(true);
		s.rook.set_white(white);
	}
	else if (piece == "knight")
	{
		s.knight.set_there(true);
		s.knight.set_white(white);
	}
	else if (piece == "bishop")
	{
		s.bishop.set_there(true);
		s.bishop.set_white(white);
	}
	else if (piece == "pawn")
	{
		s.pawn.set_there(true);
		s.pawn.set_white(white);
	}
	else if (piece == "none")
		s.none = true;
}

void Spot::Change_first_move(std::string piece)
{
	if (piece == "rook")
		s.rook.change_first_move();
	else if (piece == "pawn")
		s.pawn.change_first_move();
}

bool Selector::Is_there_piece()
{
	if (none)
		return false;

	return true;
}

bool Selector::Is_white()
{
	if (king.is_there())
		return king.is_white();
	else if (queen.is_there())
		return queen.is_white();
	else if (rook.is_there())
		return rook.is_white();
	else if (knight.is_there())
		return knight.is_white();
	else if (bishop.is_there())
		return bishop.is_white();
	else if (pawn.is_there())
		return pawn.is_white();
}

bool Selector::Get_first_move(std::string piece)
{
	if (piece == "rook")
		return rook.get_first_move();
	else if (piece == "pawn")
		return pawn.get_first_move();
}

int Selector::Get_first_move_spaces()
{
	if (pawn.is_there())
		return pawn.first_move_spaces;
	else
		return 0;
}

