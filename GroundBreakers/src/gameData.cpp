#include "gameData.h"



gameData::gameData()
{
	fontRoboto.load("fonts/Roboto-Regular.ttf", 50);
	defaultPlayerDamage = 100;
	defaultPlayerEnergy = 1000;
	defaultPlayerPillars = 5;
	defaultPlayerLadders = 5;
	numberOfBlockInLevelRow = 10;
	numberOfBlockInLevelCol = 10;
	gravity = 200;
	playerSpeed = 300;
	
	skyHeight = 100;
	blockSize = 80;
	goingToFallTime = 2;

	mineWidth = blockSize * numberOfBlockInLevelRow;
	zoomSensitivity = 50;
	debugMode = false;
}


gameData::~gameData()
{
}

void gameData::consoleWriteline(std::string string) {
	std::cout << string << std::endl;
}

