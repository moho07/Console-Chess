#pragma once
#include <iostream>
#include <vector>
#include <string>
#include "Game.h"
#include "Canmove.h"
#include "Lastmove.h"
#include "ChessBoard.h"

last_move last;
std::vector <store_move> store;

void Game::initialize(Player P1, Player P2)
{
	status = ACTIVE;
	
	p1 = P1;
	p2 = P2;

	board.reset();
}

void Game::playermove(int start_x, int start_y, int end_x, int end_y)
{
	if (start_x < 0 || start_x > 7 || start_y < 0 || start_y > 7 || end_x < 0 || end_x > 7 || end_y < 0 || end_y > 7)
		throw - 6;

	if (currentplayer.get_side() != board.get_box(start_x, start_y).get_piece().Is_white())
		throw - 7;

	if (board.get_box(start_x, start_y).get_piece_name() == "none")
		throw - 8;

	if (start_x == end_x && start_y == end_y)
		throw - 11;

	move(board.get_box(start_x, start_y), board.get_box(end_x, end_y));
}

void Game::move(Spot start, Spot end)
{	
	Board board_temp = board;
	
	try
	{
		if (CanMove(start.get_piece_name(), board, start, end))
		{
			if (start.get_piece_name() == "rook" && start.get_piece().Get_first_move("rook"))
				start.Change_first_move("rook");
			else if (start.get_piece_name() == "king" && start.get_piece().Get_castling())
				start.Set_castling(false);
			else if (start.get_piece_name() == "pawn" && start.get_piece().Get_first_move("pawn"))
			{
				start.Change_first_move("pawn");
				start.Set_first_move_spaces(abs(start.get_x() - end.get_x()));
			}

			m.make_move(board_temp, start, end);
			::last.set_last_move(start, end);

			if (start.get_piece_name() == "pawn" && (end.get_x() == 7 || end.get_x() == 0))
				m.pawnpromotion(board_temp, end, start.get_piece().Is_white());
		}
		else
			throw - 1;
	}
	catch(float e)
	{
		if (e == 1.0f)
		{
			if (start.get_x() == 7)
			{
				if (status == 2)
					throw - 9;

				board_temp.get_box(7, 4).Set_castling(false);

				if (end.get_y() == 6)
				{
					
					board_temp.get_box(7, 7).Change_first_move("rook");
					m.king_castle(board_temp, "king", true);
				}
				else
				{
					m.king_castle(board_temp, "queen", true);
					board_temp.get_box(7, 0).Change_first_move("rook");
				}
			}
			else
			{
				if (status == 3)
					throw - 9;

				board_temp.get_box(0, 4).Set_castling(false);

				if (end.get_y() == 6)
				{
					board_temp.get_box(0, 7).Change_first_move("rook");
					m.king_castle(board_temp, "king", false);
				}
				else
				{
					m.king_castle(board_temp, "queen", false);
					board_temp.get_box(0, 0).Change_first_move("rook");
				}
			}
		}
		else if (e == 2.0f)
			m.enpassant(board_temp, start, end);
	}

	if (m.king_in_check(board_temp, start.get_piece().Is_white(), false))
		throw - 10;
		
	board = board_temp;
	store_move temp;
	temp.storemove(start.get_x(), start.get_y(), end.get_x(), end.get_y());
	store.push_back(temp);
	
	try
	{
		if (m.king_in_check(board, !start.get_piece().Is_white()))
		{
			if (start.get_piece().Is_white())
			{
				std::cout << "Black King in Check\n";
				status = BLACK_KING_CHECK;
			}
			else
			{
				std::cout << "White King in Check\n";
				status = WHITE_KING_CHECK;
			}
		}
		else
			status = ACTIVE;
	}
	catch (float e)
	{
		std::cout << "Checkmate!\n";
		if (start.get_piece().Is_white())
		{
			status = BLACK_WIN;
			std::cout << "Black Wins!\n";
		}
		else
		{
			status = WHITE_WIN;
			std::cout << "White Wins!\n";
		}

		printboard(board);
		exit(0);
		
	}
}

std::vector<std::string> Game::get_captured(bool white)
{
	std::vector<std::string> whitep;
	std::vector<std::string> blackp;

	if (white)
	{
		for (int i = 0; i < m.piece_killed_white.size(); i++)
			whitep.push_back(m.piece_killed_white[i].get_piece_name());
		return whitep;
	}
	else
	{
		for (int i = 0; i < m.piece_killed_black.size(); i++)
			blackp.push_back(m.piece_killed_black[i].get_piece_name());
		return blackp;
	}

}




