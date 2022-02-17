#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <cctype>
#include "Player.h"
#include "Game.h"
#include "Board.h"
#include "ChessBoard.h"
#include "Lastmove.h"
#include "Global.h"

/*

Excepiton List:

1.0f: Castling Applied
2.0f: Enpassant Applied
3.0f: Corrupted Pawn Promotion Records File


10f: Game Over

e: Corrupted File

-1: Invalid Move
-6: Invalid rows or columns entered
-7: Invalid row and column selected.. Player & Piece color not same
-8: No Piece Selected
-9: Castle not allowed when king in check
-10: Invalid Move as King will be in check
-11: Start and End Spot can't be same

*/


void exception(int e)
{
	switch (e)
	{
	case -1:std::cout << "Invalid Move!\n"; break;
	case -6:std::cout << "Invalid Row or Column entered \n"; break;
	case -7:std::cout << "Invalid Piece Color Selected\n"; break;
	case -8:std::cout << "No Piece Selected\n"; break;
	case -9:std::cout << "Castle not allowed when King in Check\n"; break;
	case -10:std::cout << "Invalid Move. King will be in check\n"; break;
	case -11:std::cout << "Start and End Spot can't be same"; break;
	}
}

bool readfromfile = false;

int main()
{
	Game game;
	std::vector<Game> save;
	Player p1, p2, currentplayer;
	std::string currentplayername, start, end;
	int row_start, column_start, row_end, column_end;

	p1.set_side(true);
	p2.set_side(false);

	game.initialize(p1, p2);
	game.set_currentplayer(p1, "p1");

	save.push_back(game);

	while (game.get_status() != 3 || game.get_status() != 4)
	{
		
		printboard(game.get_board());

		if (game.get_current_player() == "p1")
			std::cout << "\nWHITE'S TURN (UPPER CASE): ";
		else
			std::cout << "\nBLACK'S TURN (lower case): ";
			
		std::cin >> start;

		if (start.length() == 1)
		{
			if (start == "N")
			{
				game.initialize(p1, p2);
				game.set_currentplayer(p1, "p1");
				continue;
			}
			else if (start == "U")
			{
				save.pop_back();
				store.pop_back();
				if (!save.empty())
					game = save[save.size() - 1];
				else
					std::cout << "Cannot Undo. No Previous Move found \n";
				continue;
			}
			else if (start == "C")
			{
				std::vector <std::string> captured = game.get_captured(true);

				std::cout << "White: ";
				for (int i = 0; i < captured.size(); i++)
				{
					if (((char)toupper(captured[i][0])) == 'K')
						std::cout << 'N';
					else
						std::cout << (char)toupper(captured[i][0]) << " ";
				}

				captured = game.get_captured(false);
				std::cout << "\n";

				std::cout << "Black: ";
				for (int i = 0; i < captured.size(); i++)
				{
					if (((char)toupper(captured[i][0])) == 'K')
						std::cout << 'N';
					else
						std::cout << captured[i][0] << " ";
				}

				std::cout << "\n";

				continue;
			}
			else if (start == "S")
			{
				std::ofstream f("Chess.dat", std::ios::binary);
				std::ofstream g("PawnPromotion.dat", std::ios::binary);

				for (int i = 0; i < store.size(); i++)
					f.write((char*)&store[i], sizeof(store_move));

				if(!pprecords.empty())
					for (int i = 0; i < pprecords.size(); i++)
						g.write((char*)&pprecords[i], sizeof(char));

				f.close();
				g.close();

				std::cout << "Game Saved Succesfully!\n";

				continue;
			}
			else if (start == "L")
			{
				readfromfile = true;
				store.clear();
				pprecords.clear();
				
				store_move store_temp;
				Game game_temp;
				char pp;
				game_temp.initialize(p1, p2);
				game_temp.set_currentplayer(p1, "p1");

				std::ifstream f("Chess.dat", std::ios::binary);
				std::ifstream g("PawnPromotion.dat", std::ios::binary);

				if (g.peek() != std::ifstream::traits_type::eof())
					while (g.read((char*)&pp, sizeof(char)))
						pprecords.push_back(pp);

				try
				{
					while (f.read((char*)&store_temp, sizeof(store_move)))
					{
						game_temp.playermove(store_temp.start_x, store_temp.start_y, store_temp.end_x, store_temp.end_y);

						if (game_temp.get_current_player() == "p1")
							game_temp.set_currentplayer(p2, "p2");
						else
							game_temp.set_currentplayer(p1, "p1");

						system("CLS");
					}
				}
				catch (char e)
				{
					std::cout << "File Corrupted, Cannot Load Game\n\n";
					f.close();
					readfromfile = false;
					continue;
				}
				f.close();

				game = game_temp;

				std::cout << "Game Loaded Succesfully!\n\n";

				readfromfile = false;

				continue;
			}
			else if (start == "R")
			{
				if (game.get_current_player() == "p1")
				{
					game.set_status(BLACK_WIN);
					std::cout << "Black Wins!!";
				}
				else
				{
					game.set_status(WHITE_WIN);
					std::cout << "White Wins!!";
				}

				exit(0);
			}
			else if (start == "Q")
				exit(0);
			else
			{
				std::cout << "Invalid Command Entered \n";
				continue;
			}
		}
		else if (start.length() == 2)
		{
			column_start = int(start[0]) - 65;
			row_start = int(start[1]) - 49;

			std::cout << "To: ";
			
			std::cin >> end;

			if (end.length() == 2)
			{
				column_end = int(end[0]) - 65;
				row_end = int(end[1]) - 49;
			}
			else
			{
				std::cout << "Invalid Board Address Entered\n";
				continue;
			}
		}
		else
		{
			std::cout << "Invalid Board Address Entered\n";
			continue;
		}
			
		
		try
		{
			game.playermove(row_start, column_start, row_end, column_end);
		}
		catch (int e)
		{
			exception(e);
			continue;
		}

		if (game.get_current_player() == "p1")
			game.set_currentplayer(p2, "p2");
		else
			game.set_currentplayer(p1, "p1");

		save.push_back(game);
	}
	
	return 0;
}