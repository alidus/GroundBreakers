#pragma once
#include "ofMain.h"
#include "gameData.h"
#include "camera.h"
#include <string>

class groundBlock
{

	

public:
	enum BlockTypes {Stone = 0, Gold = 1, Silver = 2, Diamond = 3, Titan = 4};
	BlockTypes blockType;

	groundBlock(BlockTypes _blockType, int _x, int _y, int index, bool exist);
	~groundBlock();

	ofImage texture;
	gameData gameData;

	void draw(float leftSideOffset, camera camera, int tempYOffset);
	void update(groundBlock* blockToFallTo, groundBlock* blockBelow);

	bool isExist;
	bool goingToFall;
	bool isFalling;
	int x;
	int y;

	bool isLadderSetUp;
	bool isPillarSetUp;

	float dX;
	float dY;
	int indexInArray;

	bool dealDamageToBlock(float damage);
	float health;
	float maxHealth;

	void initFalling();
	groundBlock* blockToFallTo;
	
	std::string groundBlock::getTexturePathForBlockType(groundBlock::BlockTypes type);

	void changeTexture(std::string newTexturePath);

private:
	float _goingToFallDelayTime;
	
};

