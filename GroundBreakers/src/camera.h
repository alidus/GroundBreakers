#pragma once
#include "ofMain.h"
#include "gameData.h"

class camera
{
private:
	

public:
	
	camera();
	~camera();

	float _aspectRatio;
	int zoomLevel;
	int x;
	int y;
	int width;
	int height;

	void update();
	void draw(float leftSideOffset, int tempYOffset);
	void setZoomLevel(int zoomLevel);
	void setCameraCenter(int _x, int _y);
	void printCameraSettings();
	gameData gameData;
};

