#pragma once
#include "ofMain.h"
#include "player.h"
#include <string>
#include <boost\lexical_cast.hpp>

class ui
{
public:
	ui();
	~ui();

	void setup(player* player);
	void draw();
	player* _player;
};

