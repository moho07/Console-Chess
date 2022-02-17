#include "Move.h"
#include "Canmove.h"
#include "Global.h"

std::deque<char> pprecords;

void Move::make_move(Board& board, Spot start, Spot end)
{
	Spot garbage;

	if (end.get_piece().Is_there_piece())
	{
		if (end.get_piece().Is_white())
		{
			std::cout << "White " << end.get_piece_name() << " is killed\n";
			piece_killed_white.push_back(end);
		}
		else
		{
			std::cout << "Black " << end.get_piece_name() << " is killed\n";
			piece_killed_black.push_back(end);
		}
	}
	
	board.change_box(end.get_x(), end.get_y(), start, false);
	board.change_box(start.get_x(), start.get_y(), garbage, true);
}

void Move::king_castle(Board& board, std::string side, bool white)
{
	Spot garbage;

	if (white)
	{
		if (side == "king")
		{
			board.change_box(7, 6, board.get_box(7,4), false);
			board.change_box(7, 4, garbage, true);
			board.change_box(7, 5, board.get_box(7, 7), false);
			board.change_box(7, 7, garbage, true);

		}
		else if (side == "queen")
		{
			board.change_box(7, 2, board.get_box(7, 4), false);
			board.change_box(7, 4, garbage, true);
			board.change_box(7, 3, board.get_box(7, 7), false);
			board.change_box(7, 0, garbage, true);
		}
	}
	else
	{
		if (side == "king")
		{
			board.change_box(0, 6, board.get_box(7, 4), false);
			board.change_box(0, 4, garbage, true);
			board.change_box(0, 5, board.get_box(7, 7), false);
			board.change_box(0, 7, garbage, true);

		}
		else if (side == "queen")
		{
			board.change_box(0, 2, board.get_box(7, 4), false);
			board.change_box(0, 4, garbage, true);
			board.change_box(0, 3, board.get_box(7, 7), false);
			board.change_box(0, 0, garbage, true);
		}
	}
}

void Move::enpassant(Board& board, Spot start, Spot end)
{
	Spot garbage;

		if (!start.get_piece().Is_white())
		{
			std::cout << "White Pawn is killed through Enpassant\n";
			piece_killed_white.push_back(board.get_box(end.get_x() - 1, end.get_y()));
		}
		else
		{
			std::cout << "Black pawn is killed through Enpassant\n";
			piece_killed_black.push_back(board.get_box(end.get_x() + 1, end.get_y()));
		}
	
	make_move(board, start, end);

	if(start.get_piece().Is_white())
		board.change_box(end.get_x() + 1, end.get_y(), garbage, true);
	else
		board.change_box(end.get_x() - 1, end.get_y(), garbage, true);
	
}

void Move::pawnpromotion(Board& board, Spot end, bool white)
{
	char piece = 'K';

	Spot promotion;

	if (readfromfile && pprecords.empty())
		throw 3.0f;

	if (!readfromfile)
	{
		while (piece == 'K')
		{
			if (white)
			{
				std::cout << "Which Piece for White Pawn Promotion?\n";
				std::cout << "(Q)ueen      (R)ook      (B)ishop      K(N)ight\n";
			}
			else
			{
				std::cout << "Which Piece for Black Pawn Promotion?\n";
				std::cout << "(q)ueen      (r)ook      (b)ishop      k(n)ight\n";
			}

			std::cin >> piece;

			if (piece != 'Q' && piece != 'q' && piece != 'R' && piece != 'r' && piece != 'B' && piece != 'b' && piece != 'N' && piece != 'n')
			{
				std::cout << "Invalid Text Entered...Try again\n";
				piece = 'K';
			}
		}
	}
	else
	{
		piece = pprecords[0];
		pprecords.pop_front();
	}

	if (piece == 'Q' || piece == 'q')
		promotion.set(end.get_x(), end.get_y(), "queen", white);
	else if (piece == 'R' || piece == 'r')
		promotion.set(end.get_x(), end.get_y(), "rook", white);
	else if (piece == 'B' || piece == 'b')
		promotion.set(end.get_x(), end.get_y(), "bishop", white);
	else if (piece == 'N' || piece == 'n')
		promotion.set(end.get_x(), end.get_y(), "knight", white);

	pprecords.push_back(piece);

	board.change_box(end.get_x(), end.get_y(), promotion, false);
}

bool Move::king_in_check(Board board, bool king_white, bool check_checkmate)
{
	Spot king_spot;
	Spot piece_spot;

	bool in_check = false;

	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			if (board.get_box(i, j).get_piece_name() == "king" && board.get_box(i, j).get_piece().Is_white() == king_white)
			{
				king_spot = board.get_box(i, j);
				break;
			}
		}
	}

	for (int i = 0; i < 8 && !in_check; i++)
	{
		for (int j = 0; j < 8 && !in_check; j++)
		{
			if (board.get_box(i, j).get_piece_name() != "none" && board.get_box(i, j).get_piece().Is_white() != king_white)
				if (CanMove(board.get_box(i, j).get_piece_name(), board, board.get_box(i, j), king_spot))
				{
					in_check = true;
					piece_spot = board.get_box(i, j);
				}
		}
	}

	if (in_check && check_checkmate)
		if (king_checkmate(board, king_spot, piece_spot))
			throw 10.0f; 

	return in_check;
}

bool Move::king_checkmate(Board board, Spot king, Spot piece)
{
	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			if (board.get_box(i, j).get_piece_name() != "none" && board.get_box(i, j).get_piece_name() != "king" && board.get_box(i, j).get_piece().Is_white() != piece.get_piece().Is_white())
				if (CanMove(board.get_box(i, j).get_piece_name(), board, board.get_box(i, j), piece))
					return false;
		}
	}	

	bool king_white = king.get_piece().Is_white();
	Spot garbage;

	Board board_temp = board;

	if (king.get_x() + 1 < 7)
	{
		if (CanMove(king.get_piece_name(), board, king, board.get_box(king.get_x() + 1, king.get_y())))
		{
			board_temp.change_box(king.get_x() + 1, king.get_y(), king, false);
			board_temp.change_box(king.get_x(), king.get_y(), garbage, true);
			if (!king_in_check(board_temp, king_white, false))
				return false;
		}
	}

	if (king.get_x() - 1 > 0)
	{
		if (CanMove(king.get_piece_name(), board, king, board.get_box(king.get_x() - 1, king.get_y())))
		{
			Board board_temp = board;
			board_temp.change_box(king.get_x() - 1, king.get_y(), king, false);
			board_temp.change_box(king.get_x(), king.get_y(), garbage, true);
			if (!king_in_check(board_temp, king_white, false))
				return false;
		}
	}

	if (king.get_x() + 1 < 7 && king.get_y() + 1 < 7)
	{
		if (CanMove(king.get_piece_name(), board, king, board.get_box(king.get_x() + 1, king.get_y() + 1)))
		{
			Board board_temp = board;
			board_temp.change_box(king.get_x() + 1, king.get_y() + 1, king, false);
			board_temp.change_box(king.get_x(), king.get_y(), garbage, true);
			if (!king_in_check(board_temp, king_white, false))
				return false;
		}
	}

	if (king.get_x() + 1 < 7 && king.get_y() - 1 > 0)
	{
		if (CanMove(king.get_piece_name(), board, king, board.get_box(king.get_x() + 1, king.get_y() - 1)))
		{
			Board board_temp = board;
			board_temp.change_box(king.get_x() + 1, king.get_y() - 1, king, false);
			board_temp.change_box(king.get_x(), king.get_y(), garbage, true);
			if (!king_in_check(board_temp, king_white, false))
				return false;
		}
	}

	if (king.get_x() - 1 > 0 && king.get_y() - 1 > 0)
	{
		if (CanMove(king.get_piece_name(), board, king, board.get_box(king.get_x() - 1, king.get_y() - 1)))
		{
			Board board_temp = board;
			board_temp.change_box(king.get_x() - 1, king.get_y() - 1, king, false);
			board_temp.change_box(king.get_x(), king.get_y(), garbage, true);
			if (!king_in_check(board_temp, king_white, false))
				return false;
		}
	}

	if (king.get_y() + 1 < 7)
	{
		if (CanMove(king.get_piece_name(), board, king, board.get_box(king.get_x(), king.get_y() + 1)))
		{
			Board board_temp = board;
			board_temp.change_box(king.get_x(), king.get_y() + 1, king, false);
			board_temp.change_box(king.get_x(), king.get_y(), garbage, true);
			if (!king_in_check(board_temp, king_white, false))
				return false;
		}
	}

	if (king.get_y() - 1 > 0)
	{
		if (CanMove(king.get_piece_name(), board, king, board.get_box(king.get_x(), king.get_y() - 1)))
		{
			Board board_temp = board;
			board_temp.change_box(king.get_x(), king.get_y() - 1, king, false);
			board_temp.change_box(king.get_x(), king.get_y(), garbage, true);
			if (!king_in_check(board_temp, king_white, false))
				return false;
		}
	}

	if (king.get_x() - 1 > 0 && king.get_y() + 1 < 7)
	{
		if (CanMove(king.get_piece_name(), board, king, board.get_box(king.get_x() - 1, king.get_y() + 1)))
		{
			Board board_temp = board;
			board_temp.change_box(king.get_x() - 1, king.get_y() + 1, king, false);
			board_temp.change_box(king.get_x(), king.get_y(), garbage, true);
			if (!king_in_check(board_temp, king_white, false))
				return false;
		}
	}

	std::string piece_name = piece.get_piece_name();

	if (piece_name == "pawn" || piece_name == "knight")
		return true;
	else
	{
		int y = abs(piece.get_x() - king.get_x());
		int x = abs(piece.get_y() - king.get_y());

		if (piece_name == "queen")
		{
			for (int i = 0; i < 8; i++)
			{
				for (int j = 0; j < 8; j++)
				{
					if (board.get_box(i, j).get_piece_name() != "none" && board.get_box(i, j).get_piece_name() != "king" && board.get_box(i, j).get_piece().Is_white() != piece.get_piece().Is_white())
					{
						if (x == y)
						{
							if (piece.get_x() < king.get_x() && piece.get_y() < king.get_y())
							{
								for (int k = 1; k < x; k++)
								{
									if (CanMove(board.get_box(i, j).get_piece_name(), board, board.get_box(i, j), board.get_box(piece.get_x() + k, piece.get_y() + k)))
										return false;
								}
							}
							else if (piece.get_x() < king.get_x() && piece.get_y() > king.get_y())
							{
								for (int k = 1; k < x; k++)
								{
									if (CanMove(board.get_box(i, j).get_piece_name(), board, board.get_box(i, j), board.get_box(piece.get_x() + k, piece.get_y() - k)))
										return false;
								}
							}
							else if (piece.get_x() > king.get_x() && piece.get_y() < king.get_y())
							{
								for (int k = 1; k < x; k++)
								{
									if (CanMove(board.get_box(i, j).get_piece_name(), board, board.get_box(i, j), board.get_box(piece.get_x() - k, piece.get_y() + k)))
										return false;
								}
							}
							else if (piece.get_x() > king.get_x() && piece.get_y() > king.get_y())
							{
								for (int k = 1; k < x; k++)
								{
									if (CanMove(board.get_box(i, j).get_piece_name(), board, board.get_box(i, j), board.get_box(piece.get_x() - k, piece.get_y() - k)))
										return false;
								}
							}
						}

						if (x == 0)
						{
							if (piece.get_x() < king.get_x())
							{
								for (int k = 1; k < y; k++)
								{
									if (CanMove(board.get_box(i, j).get_piece_name(), board, board.get_box(i, j), board.get_box(piece.get_x() + k, piece.get_y() )))
										return false;
								}
							}
							else if (piece.get_x() > king.get_x())
							{
								for (int k = 1; k < y; k++)
								{
									if (CanMove(board.get_box(i, j).get_piece_name(), board, board.get_box(i, j), board.get_box(piece.get_x() - k, piece.get_y())))
										return false;
								}
							}
						}

						if (y == 0)
						{
							if (piece.get_y() < king.get_y())
							{

								for (int k = 1; k < x; k++)
								{
									if (CanMove(board.get_box(i, j).get_piece_name(), board, board.get_box(i, j), board.get_box(piece.get_x(), piece.get_y() + k)))
										return false;
								}
							}
							else if (piece.get_y() > king.get_y())
							{
								for (int k = 1; k < x; k++)
								{
									if (CanMove(board.get_box(i, j).get_piece_name(), board, board.get_box(i, j), board.get_box(piece.get_x(), piece.get_y() - k)))
										return false;
								}
							}
						}
					}

				}
			}
		}
		else if (piece_name == "rook")
		{
			for (int i = 0; i < 8; i++)
			{
				for (int j = 0; j < 8; j++)
				{
					if (board.get_box(i, j).get_piece_name() != "none" && board.get_box(i, j).get_piece_name() != "king" && board.get_box(i, j).get_piece().Is_white() != piece.get_piece().Is_white())
					{
						if (x == 0)
						{
							if (piece.get_x() < king.get_x())
							{
								for (int k = 1; k < y; k++)
								{
									if (CanMove(board.get_box(i, j).get_piece_name(), board, board.get_box(i, j), board.get_box(piece.get_x() + k, piece.get_y())))
										return false;
								}
							}
							else if (piece.get_x() > king.get_x())
							{
								for (int k = 1; k < y; k++)
								{
									if (CanMove(board.get_box(i, j).get_piece_name(), board, board.get_box(i, j), board.get_box(piece.get_x() - k, piece.get_y())))
										return false;
								}
							}
						}

						if (y == 0)
						{
							if (piece.get_y() < king.get_y())
							{

								for (int k = 1; k < x; k++)
								{
									if (CanMove(board.get_box(i, j).get_piece_name(), board, board.get_box(i, j), board.get_box(piece.get_x(), piece.get_y() + k)))
										return false;
								}
							}
							else if (piece.get_y() > king.get_y())
							{
								for (int k = 1; k < x; k++)
								{
									if (CanMove(board.get_box(i, j).get_piece_name(), board, board.get_box(i, j), board.get_box(piece.get_x(), piece.get_y() - k)))
										return false;
								}
							}
						}
					}
				}
			}
		}
		else if (piece_name == "bishop")
		{
			for (int i = 0; i < 8; i++)
			{
				for (int j = 0; j < 8; j++)
				{
					if (board.get_box(i, j).get_piece_name() != "none" && board.get_box(i, j).get_piece_name() != "king" && board.get_box(i, j).get_piece().Is_white() != piece.get_piece().Is_white())
					{
						if (piece.get_x() < king.get_x() && piece.get_y() < king.get_y())
						{
							for (int k = 1; k < x; k++)
							{
								if (CanMove(board.get_box(i, j).get_piece_name(), board, board.get_box(i, j), board.get_box(piece.get_x() + k, piece.get_y() + k)))
									return false;
							}
						}
						else if (piece.get_x() < king.get_x() && piece.get_y() > king.get_y())
						{
							for (int k = 1; k < x; k++)
							{
								if (CanMove(board.get_box(i, j).get_piece_name(), board, board.get_box(i, j), board.get_box(piece.get_x() + k, piece.get_y() - k)))
									return false;
							}
						}
						else if (piece.get_x() > king.get_x() && piece.get_y() < king.get_y())
						{
							for (int k = 1; k < x; k++)
							{
								if (CanMove(board.get_box(i, j).get_piece_name(), board, board.get_box(i, j), board.get_box(piece.get_x() - k, piece.get_y() + k)))
									return false;
							}
						}
						else if (piece.get_x() > king.get_x() && piece.get_y() > king.get_y())
						{
							for (int k = 1; k < x; k++)
							{
								if (CanMove(board.get_box(i, j).get_piece_name(), board, board.get_box(i, j), board.get_box(piece.get_x() - k, piece.get_y() - k)))
									return false;
							}
						}
					}
				}
			}
		}
	}

	return true;
}