#pragma once
#include <iostream>
#include <vector>
#include "Spot.h"

class Spot;

class Board
{
	std::vector<std::vector<Spot>> boxes;

public:
	Board() : boxes(8, std::vector<Spot>(8)) {}
	Spot get_box(int x, int y);
	void change_box(int x, int y, Spot piece, bool empty);
	void reset();
};
