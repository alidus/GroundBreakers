#include "camera.h"



camera::camera()
{
	zoomLevel = 1;
	x = 0;
	y = 0;
	_aspectRatio = 1.67;
	width = gameData.mineWidth;
	height = width / _aspectRatio;
	printCameraSettings();
}


camera::~camera()
{
}

void camera::update()
{
	
}

void camera::draw(float leftSideOffset, int tempYOffset)
{
	ofSetColor(255, 0, 0);
	ofNoFill();
	ofSetLineWidth(3);
	ofRect(leftSideOffset + x, y, width, height);
	ofFill();
	ofSetColor(255, 255, 255);
}

void camera::setZoomLevel(int _zoomLevel)
{
	std::cout << "Setting camera zoom to " << _zoomLevel << std::endl;
	zoomLevel = _zoomLevel;
	width = gameData.mineWidth / zoomLevel;
	height = width / _aspectRatio;
	printCameraSettings();
}

void camera::printCameraSettings()
{
	std::cout << "Camera settings: " << x << " " << y << " " << width << " " << height << " " << _aspectRatio << std::endl;
}

void camera::setCameraCenter(int _x, int _y)
{
	x = _x - width / 2;
	y = _y - height / 2;
	if (x < 0)
	{
		x = 0;
	}
	if (x + width > gameData.mineWidth)
	{
		x = gameData.mineWidth - width;
	}
	if (y < 0)
	{
		y = 0;
	}
	if (y + height > ofGetWindowHeight())
	{
		y = ofGetWindowHeight() - height;
	}
}