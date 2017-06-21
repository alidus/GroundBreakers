#include "level.h"
#include "math\ofMath.h"

level::level()
{
}


level::~level()
{
}

void level::setup(int width, int height)
{

	// Generate vector of blocks
	std::cout << "Setting up level: " << width << ", " << height << std::endl;
	int i = 0;

	for (int h = 0; h < height; h++)
	{
		for (int w = 0; w < width; w++)
		{
			bool existing = true;
			if (h == 0) {
				existing = false;
			}
			int randomNumber = rand() % 100;
			
			groundBlock::BlockTypes blockType;
			
			if (randomNumber <= 3)
			{
				blockType = groundBlock::Diamond;
			}
			else if (randomNumber <= 15)
			{
				blockType = groundBlock::Gold;
			}
			else if (randomNumber <= 25)
			{
				blockType = groundBlock::Silver;
			}
			else if (randomNumber <= 40)
			{
				blockType = groundBlock::Titan;
			}
			else
			{
				blockType = groundBlock::Stone;
			}
			blockList.push_back(groundBlock(blockType, w*gameData.blockSize, h*gameData.blockSize + gameData.skyHeight, i, existing));
			i++;
		}
		
	}

	std::cout << blockList.size() << std::endl;
	
	levelWidth = width * gameData.blockSize;
	
	// Load level backgound textures
	background.load("images/mineBg.jpg");
	sky.load("images/sky.png");

}

void level::update() {
	lastFallingBlockIndex = NULL;
	mineOffsetX = (ofGetWindowWidth() - gameData.mineWidth) / 2;
	int i = 0;
	while (i < blockList.size())
	{
		if (blockList[i].isExist)
		{
			if (!blockList[i].isFalling || blockList[i].goingToFall)
			{
				if (i / gameData.numberOfBlockInLevelRow != gameData.numberOfBlockInLevelCol - 1)
				{
					blockList[i].update(NULL, &blockList[i + gameData.numberOfBlockInLevelRow]);
				}
				else
				{
					blockList[i].update(NULL, NULL);
				}
				
			}
			else
			{
				blockList[i].update(&blockList[getFurtherEmptyBlockBelowBlock(blockList[i].indexInArray)], &blockList[i + gameData.numberOfBlockInLevelRow]);
				lastFallingBlockIndex = i;
			}
			
		}
		i++;
	}
	if (lastFallingBlockIndex != NULL)
	{
		int tempBlockIndex = lastFallingBlockIndex - gameData.numberOfBlockInLevelRow;
		while (tempBlockIndex > 0)
		{
			blockList[tempBlockIndex].isFalling = true;
			tempBlockIndex -= gameData.numberOfBlockInLevelRow;
		}
	}
}

void level::draw(float leftSideOffset, camera camera, int tempYOffset)
{
	ofSetColor(255, 255, 255);
	// Draw mine background
	background.draw(leftSideOffset , gameData.skyHeight - tempYOffset, levelWidth , gameData.numberOfBlockInLevelCol * gameData.blockSize);
	// Draw blocks
	int i = 0;
	while (i < blockList.size())
	{
		if (blockList[i].isExist)
		{
			blockList[i].draw(leftSideOffset, camera, tempYOffset);
		}
		
		i++;
	}
	// Draw sky
	sky.draw(leftSideOffset , -tempYOffset, levelWidth, gameData.skyHeight);
}

void level::checkIfBlockIsGoingToFall(groundBlock* block) {
	std::cout << "Checking on falling block " << block->indexInArray << std::endl;
	if (block->isExist)
	{
		block->blockToFallTo = &blockList[getFurtherEmptyBlockBelowBlock(block->indexInArray)];
		block->initFalling();
	}

}

int level::getFurtherEmptyBlockBelowBlock(int currentBlockIndex) {
	int currentVirtualBlockIndex = currentBlockIndex;
	while (currentVirtualBlockIndex / gameData.numberOfBlockInLevelRow < gameData.numberOfBlockInLevelCol && !blockList[currentVirtualBlockIndex + gameData.numberOfBlockInLevelRow].isExist)
	{
		currentVirtualBlockIndex += gameData.numberOfBlockInLevelRow;
	}
	return currentVirtualBlockIndex;
}