#pragma once
#include <iostream>
#include <string>
#include "Board.h"
#include "Spot.h"

bool CanMove(std::string piece, Board board, Spot start, Spot end);