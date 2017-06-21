#pragma once
#include "ofMain.h"
#include "groundBlock.h"
#include <vector>
#include "gameData.h"
#include <string>
#include "camera.h"

class level
{
public:
	level();
	~level();

	void setup(int width, int height);
	void update();
	void draw(float leftSideOffset, camera camera, int tempYOffset);
	
	gameData gameData;
	std::vector <groundBlock> blockList;
	ofImage background;
	ofImage sky;

	float mineOffsetX;
	int drawingBlockX;
	int drawingBlockY;
	int levelWidth;
	void checkIfBlockIsGoingToFall(groundBlock* block);
	int getFurtherEmptyBlockBelowBlock(int currentBlockIndex);
	int lastFallingBlockIndex;
};

