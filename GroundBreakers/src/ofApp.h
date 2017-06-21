#pragma once

#include "ofMain.h"
#include "player.h"
#include "level.h"
#include "gameData.h"
#include "player.h"
#include "camera.h"
#include "menu.h"
#include "ui.h"

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
		void drawShadowOfMine();
		void gameOver();
		void drawGameOverScreen();
		void startGame();
		void drawBlackFilter();

		level level;
		player player;
		camera camera;
		gameData gameData;
		menu menu;
		ui ui;
		ofSoundPlayer musicPlayer;
		ofImage shadowOfMine;

		int tempYOffset;
		bool isAlive;
		bool isInMenu;
		bool isDrawingGameOverScreen;
		float leftSideOffset;

		float viewExpX;
		float viewExpY;
		void recalcView();
		
};
