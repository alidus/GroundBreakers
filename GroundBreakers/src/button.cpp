#include "button.h"




button::button(int _x, int _y, int _width, int _height, ofColor _color, std::string _text, std::string _buttonName)
{
	isHighlighted = false;
	x = _x;
	y = _y;
	width = _width;
	height = _height;
	color = _color;
	text = _text;
	buttonName = _buttonName;
}

button::button()
{
	isHighlighted = false;
}

button::~button()
{
}

void button::draw() {
	std::cout << isHighlighted;
	if (isHighlighted)
	{
		ofSetColor(color + ofColor(50, 50, 50));
		
	}
	else
	{
		ofSetColor(color);
	}
	ofRect(x, y, width, height);
	ofSetColor(255, 255, 255);
	gameData.fontRoboto.drawString(text, x + width*0.1, y + height*0.65);

}

void button::enableDisableHighlight(bool state)
{
	isHighlighted = state;
}
