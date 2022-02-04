#pragma once

class Player
{
	bool whiteside;

public:
	inline void set_side(bool Whiteside) { whiteside = Whiteside; }
	inline bool get_side() { return whiteside; }
};