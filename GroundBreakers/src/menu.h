#pragma once
#include "ofMain.h"
#include "button.h"
#include <vector>


class menu
{
private:
	ofImage _bgImage;
	
	button startGameButton;
	button exitGameButton;

public:
	menu();
	~menu();
	void draw();
	std::vector<button> buttonList;
};

