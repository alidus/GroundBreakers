#include "groundBlock.h"



groundBlock::groundBlock(BlockTypes _blockType, int _x, int _y, int index, bool exist)
{
	isExist = exist;
	isFalling = false;
	goingToFall = false;
	_goingToFallDelayTime = gameData.goingToFallTime;
	blockType = _blockType;

	std::string newTexturePath = getTexturePathForBlockType(blockType);
	texture.load(newTexturePath);
	isLadderSetUp = false;
	isPillarSetUp = false;

	indexInArray = index;
	x = _x;
	y = _y;
	dX = x;
	dY = y;
	health = maxHealth;
}

std::string groundBlock::getTexturePathForBlockType(groundBlock::BlockTypes type)
{
	switch (type)
	{
	case Stone:
		maxHealth = 100;
		return "images/ore/o_stone.png";
		break;
	case Silver:
		maxHealth = 120;
		return "images/ore/o_silver.png";
		break;
	case Gold:
		maxHealth = 150;
		return "images/ore/o_gold.png";
		break;
	case Diamond:
		maxHealth = 200;
		return "images/ore/o_diamond.png";
		break;
	case Titan:
		maxHealth = 10;
		return "images/ore/o_titan.png";
		break;

	default:
		return NULL;
		break;
	}
}

void groundBlock::draw(float leftSideOffset, camera camera, int tempYOffset)
{
	ofSetColor(255, 155 + 100 * (health/maxHealth), 155 + 100 * (health / maxHealth));
	texture.draw(leftSideOffset + dX , dY - tempYOffset, gameData.blockSize, gameData.blockSize);

	// Dubug
	if (gameData.debugMode)
	{
		ofSetColor(255, 255, 255, 255);
		ofDrawBitmapString(indexInArray, leftSideOffset + x + gameData.blockSize/2 , y + gameData.blockSize/2 - tempYOffset);
		if (goingToFall)
		{
			ofSetColor(0, 0, 255, health);
		}
		else if (isFalling)
		{
			ofSetColor(255, 0, 0, health);
		}
		else
		{
			ofSetColor(0, 255, 0, health);
		}
		ofRect(leftSideOffset + dX, dY - tempYOffset, gameData.blockSize, gameData.blockSize);
	}
	ofSetColor(255, 255, 255, 255);
}

groundBlock::~groundBlock()
{
}

bool groundBlock::dealDamageToBlock(float damage)
{
	health -= damage;
	if (health <= 0)
	{
		
		isExist = false;
		return true;
	}
	return false;
}

void groundBlock::initFalling() {
	goingToFall = true;

}

void groundBlock::update(groundBlock* blockToFallTo, groundBlock* blockBelow)
{
	if (goingToFall || isFalling) {
		if (blockBelow->isPillarSetUp) {
			isFalling = false;
			goingToFall = false;
			_goingToFallDelayTime = gameData.goingToFallTime;
		}
	}

	if (goingToFall)
	{
		// Calc delay time
		_goingToFallDelayTime -= ofGetLastFrameTime();
		if (_goingToFallDelayTime <= 0)
		{
			blockToFallTo = blockToFallTo;
			// Start falling
			isFalling = true;
			goingToFall = false;
		}
	}
	else if (isFalling) {
		// Falling
		float dYnew = dY + ofGetLastFrameTime() * gameData.gravity;
		if (dYnew < blockToFallTo->y)
		{
			dY = dYnew;
		}
		else
		{
			dY = blockToFallTo->y;
			isExist = false;
			isFalling = false;
			_goingToFallDelayTime = gameData.goingToFallTime;
			blockToFallTo->isExist = true;
			blockToFallTo->health = health;
			blockToFallTo->blockType = blockType;
			std::string newTexturePath = getTexturePathForBlockType(blockType);
			blockToFallTo->changeTexture(newTexturePath);
			dY = y;
		}
	}
	// Check if block below is falling
}

void groundBlock::changeTexture(std::string newTexturePath) {
	texture.load(newTexturePath);
}

