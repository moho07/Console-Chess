#include "Board.h"

Spot Board::get_box(int x, int y)
{
	return boxes[x][y];
}


void Board::reset()
{
	boxes[0][0].set(0, 0, "rook", false);
	boxes[0][1].set(0, 1, "knight", false);
	boxes[0][2].set(0, 2, "bishop", false);
	boxes[0][3].set(0, 3, "queen", false);
	boxes[0][4].set(0, 4, "king", false);
	boxes[0][5].set(0, 5, "bishop", false);
	boxes[0][6].set(0, 6, "knight", false);
	boxes[0][7].set(0, 7, "rook", false);

	boxes[1][0].set(1, 0, "pawn", false);
	boxes[1][1].set(1, 1, "pawn", false);
	boxes[1][2].set(1, 2, "pawn", false);
	boxes[1][3].set(1, 3, "pawn", false);
	boxes[1][4].set(1, 4, "pawn", false);
	boxes[1][5].set(1, 5, "pawn", false);
	boxes[1][6].set(1, 6, "pawn", false);
	boxes[1][7].set(1, 7, "pawn", false);

	boxes[7][0].set(7, 0, "rook", true);
	boxes[7][1].set(7, 1, "knight", true);
	boxes[7][2].set(7, 2, "bishop", true);
	boxes[7][3].set(7, 3, "queen", true);
	boxes[7][4].set(7, 4, "king", true);
	boxes[7][5].set(7, 5, "bishop", true);
	boxes[7][6].set(7, 6, "knight", true);
	boxes[7][7].set(7, 7, "rook", true);

	boxes[6][0].set(6, 0, "pawn", true);
	boxes[6][1].set(6, 1, "pawn", true);
	boxes[6][2].set(6, 2, "pawn", true);
	boxes[6][3].set(6, 3, "pawn", true);
	boxes[6][4].set(6, 4, "pawn", true);
	boxes[6][5].set(6, 5, "pawn", true);
	boxes[6][6].set(6, 6, "pawn", true);
	boxes[6][7].set(6, 7, "pawn", true);

	for (int i = 2; i < 6; i++)
		for (int j = 0; j < 8; j++)
			boxes[i][j].set(i, j, "none");
}

void Board::change_box(int x, int y, Spot piece, bool empty)
{
	if (empty)
		boxes[x][y].set(x, y, "none");
	else
	{
		boxes[x][y] = piece;
		boxes[x][y].set_x(x);
		boxes[x][y].set_y(y);
	}
}


