#include "menu.h"



menu::menu()
{
	_bgImage.load("images/menu.jpg");
	// Start Game button
	startGameButton = button(ofGetWindowWidth() * 0.2, ofGetWindowHeight() * 0.2, ofGetWindowWidth()*0.6, ofGetWindowHeight() * 0.2, ofColor(100, 150, 80), "Start Game", "startGameButton");
	buttonList.push_back(startGameButton);
	// Exit Game button
	exitGameButton = button(ofGetWindowWidth() * 0.2, ofGetWindowHeight() * 0.5, ofGetWindowWidth()*0.6, ofGetWindowHeight() * 0.2, ofColor(100, 150, 80), "Exit", "exitGameButton");
	buttonList.push_back(exitGameButton);
}


menu::~menu()
{
}

void menu::draw() {
	ofSetColor(255, 255, 255);
	_bgImage.draw(0, 0, ofGetWindowWidth(), ofGetWindowHeight());
	for each (button button in buttonList)
	{
		button.draw();
	}
}

