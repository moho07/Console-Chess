#include "ChessBoard.h"

#define WHITE_SQUARE 0xDB
#define BLACK_SQUARE 0xFF


void printboard(Board b)
{
    bool  white_first = true;
    int n = 1, row = 1, column = 1;
    

    std::cout << "            A         B         C         D         E         F         G         H\n";

    std::cout << "       ";

    for (int i = 1; i <= 80; i++)
        std::cout << "-";

    std::cout << "--";

    std::cout << "\n";

    for (int i = 1; i <= 40; i++)
    {
        column = 1;

        std::cout << "   ";

        if (i % 5 == 3)
        {
            std::cout << n;
            n++;
            std::cout << "   ";
        }
        else
            std::cout << "    ";

        std::cout << "|";

        for (int j = 1; j <= 80; j++)
        {
            if (j % 5 == 0 && (j / 5) % 2 == 1 && i % 5 == 3)
            {
                std::string piece = b.get_box(row - 1, column - 1).get_piece_name();

                if (b.get_box(row - 1, column - 1).get_piece().Is_white())
                {
                    if (piece == "king")
                        std::cout << "K";
                    else if (piece == "queen")
                        std::cout << "Q";
                    else if (piece == "rook")
                        std::cout << "R";
                    else if (piece == "knight")
                        std::cout << "N";
                    else if (piece == "bishop")
                        std::cout << "B";
                    else if (piece == "pawn")
                        std::cout << "P";
                    else
                    {
                        if (white_first)
                            std::cout << char(WHITE_SQUARE);
                        else
                            std::cout << char(BLACK_SQUARE);
                    }
                }
                else
                {
                    if (piece == "king")
                        std::cout << "k";
                    else if (piece == "queen")
                        std::cout << "q";
                    else if (piece == "rook")
                        std::cout << "r";
                    else if (piece == "knight")
                        std::cout << "n";
                    else if (piece == "bishop")
                        std::cout << "b";
                    else if (piece == "pawn")
                        std::cout << "p";
                    else
                    {
                        if (white_first)
                            std::cout << char(WHITE_SQUARE);
                        else
                            std::cout << char(BLACK_SQUARE);
                    }
                }
            }
            else
            {
                if (white_first)
                    std::cout << char(WHITE_SQUARE);
                else
                    std::cout << char(BLACK_SQUARE);
            }

            if (j % 10 == 0)
            {
                column++;
               if (white_first)
                    white_first = false;
                else
                    white_first = true;
            }

        }

        std::cout << "|";

        if (i % 5 == 0)
        {
            row++;
            if (white_first)
                white_first = false;
            else
                white_first = true;
        }

        std::cout << "\n";
    }

    std::cout << "       ";

    for (int i = 1; i <= 80; i++)
        std::cout << "-";

    std::cout << "--\n";

    std::cout << "COMMANDS:     (N)ew Game     (U)ndo     (C)aptured     (S)ave     (L)oad     (R)esign     (Q)uit\n";


}