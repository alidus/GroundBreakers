#pragma once
#include "ofMain.h"
#include "gameData.h"
#include "level.h"
#include <vector>
#include "groundBlock.h"
#include "camera.h"


class player
{
public:
	player();
	~player();
	void draw(float leftSideOffset, camera camera, int tempYOffset);
	void setup(level *level);
	void update();
	float x;
	float y;
	int size;
	enum movingDir {Up, Left, Right, Down};
	void move(movingDir dir);
	void setNewPosition(float _x, float _y);
	bool isAlive;
	int _energy;
	int _ladders;
	int _pillars;

	enum playerStates { Digging, Falling, Standing, Moving, ClimbingTop, ClimbingBot };

	std::vector<int> _resourcesVector;

	int visionExpansion;


private:
	int _damage;
	int _speed;
	

	
	ofImage texture;
	gameData gameData;
	groundBlock* _diggingBlock;

	groundBlock* _blockToMoveTo;
	int _movingSide;

	int _currentBlockIndex;
	int _fallingTargetBlockIndex;
	int _movingToBlockIndex;
	level* _levelRef;

	int getNearestBlockUnderRobot();

	

	std::vector<std::vector<int>> laddersList;
	std::vector<std::vector<int>> pillarsList;

	ofImage pillarImage;
	ofImage ladderImage;

	void addResource(groundBlock::BlockTypes type);

	void playerDie();
	void upgrade();

	// Upgrades
	
	int addLadders;
	int addPillars;
	int addDamage;


public:
	playerStates state;
	void setUpLadder();
	void setUpPillar();

};

