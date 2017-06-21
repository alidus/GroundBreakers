#pragma once
#include "ofMain.h"
#include <string>

struct gameData
{
public:
	gameData();
	~gameData();

	// Level
	int numberOfBlockInLevelRow;
	int numberOfBlockInLevelCol;
	int mineWidth;
	int skyHeight;
	int gravity;
	// Blocks
	int blockSize;
	float goingToFallTime;
	// Player
	int defaultPlayerDamage;
	int defaultPlayerEnergy;
	int defaultPlayerLadders;
	int defaultPlayerPillars;
	int playerSpeed;
	// Camera
	int zoomSensitivity;

	void consoleWriteline(std::string string);
	int getFurtherEmptyBlockBelowBlock(int currentBlockIndex);
	bool debugMode;
	ofTrueTypeFont fontRoboto;
};

