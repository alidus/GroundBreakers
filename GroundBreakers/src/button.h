#pragma once
#include "ofMain.h"
#include <string>
#include "gameData.h"

class button
{
public:
	button();
	button(int _x, int _y, int _width, int _height, ofColor _color, std::string _text, std::string _buttonName);
	~button();
	int x;
	int y;
	int width;
	int height;
	std::string text;
	bool isHighlighted;
	ofColor color;

	std::string buttonName;
	gameData gameData;
	void draw();
	void enableDisableHighlight(bool state);
};

