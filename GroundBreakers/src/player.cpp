#include "player.h"



player::player()
{

}


player::~player()
{
}

void player::setup(level *level) {
	_energy = gameData.defaultPlayerEnergy;
	_ladders = gameData.defaultPlayerLadders;
	_pillars = gameData.defaultPlayerPillars;
	_damage = gameData.defaultPlayerDamage;
	_speed = gameData.playerSpeed;
	_resourcesVector = {0, 0, 0, 0};	// Stone, Silver, Gold, Diamond
	size = gameData.blockSize;
	isAlive = true;

	texture.load("images/player/player.png");
	ladderImage.load("images/ladder.png");
	pillarImage.load("images/pillar.png");

	state = Standing;
	_currentBlockIndex = 0;
	_levelRef = level;
	setNewPosition(_levelRef->blockList[_currentBlockIndex].x, _levelRef->blockList[_currentBlockIndex].y);
}

void player::update() {
	//Check for death
	if (_levelRef->blockList[_currentBlockIndex].isExist)
	{
		playerDie();
	}

	// Robot is standing not on the last row of mine and there is no block under him
	if (_currentBlockIndex / gameData.numberOfBlockInLevelRow < gameData.numberOfBlockInLevelCol && !_levelRef->blockList[_currentBlockIndex + gameData.numberOfBlockInLevelRow].isExist && !_levelRef->blockList[_currentBlockIndex + gameData.numberOfBlockInLevelRow].isLadderSetUp)
	{
		state = Falling;
	}

	switch (state)
	{

	case player::Digging:
		if (_diggingBlock->isExist)
		{
			_energy -= ofGetLastFrameTime();
			if (_energy <= 0)
			{
				playerDie();
			}
			if (_diggingBlock->dealDamageToBlock(_damage * ofGetLastFrameTime()))
			{
				// Ended digging the block
				addResource(_diggingBlock->blockType);
				_levelRef->checkIfBlockIsGoingToFall(&_levelRef->blockList[_diggingBlock->indexInArray - gameData.numberOfBlockInLevelRow]);
			}
		}
		else
		{
			state = Standing;
		}
		break;

	case player::Falling:
		
		if (_fallingTargetBlockIndex == NULL)
		{
			_fallingTargetBlockIndex = _levelRef->getFurtherEmptyBlockBelowBlock(_currentBlockIndex);
		}


		if (y < _levelRef->blockList[_fallingTargetBlockIndex].y)
		{
			setNewPosition(x, y + gameData.gravity * ofGetLastFrameTime());
		}
		else
		{
			// Reached block we fallen to
			setNewPosition(x, _levelRef->blockList[_fallingTargetBlockIndex].y);
			_currentBlockIndex = _fallingTargetBlockIndex;
			state = Standing;
			_fallingTargetBlockIndex = NULL;
		}

		break;

	case player::Standing:

		break;

	case player::ClimbingTop:
		if (y > _levelRef->blockList[_currentBlockIndex - gameData.numberOfBlockInLevelRow].y)
		{
			y -= _speed * ofGetLastFrameTime();
		}
		else
		{
			y = _levelRef->blockList[_currentBlockIndex - gameData.numberOfBlockInLevelRow].y;
			_currentBlockIndex = _currentBlockIndex - gameData.numberOfBlockInLevelRow;
			state = Standing;
			if (_currentBlockIndex / gameData.numberOfBlockInLevelRow == 0)
			{
				upgrade();
			}
		}
		break;

	case player::ClimbingBot:
		if (y < _levelRef->blockList[_currentBlockIndex + gameData.numberOfBlockInLevelRow].y)
		{
			y += _speed * ofGetLastFrameTime();
		}
		else
		{
			y = _levelRef->blockList[_currentBlockIndex + gameData.numberOfBlockInLevelRow].y;
			_currentBlockIndex = _currentBlockIndex + gameData.numberOfBlockInLevelRow;
			state = Standing;
		}
		break;

	case player::Moving:
		if (_blockToMoveTo == NULL)
		{
			_blockToMoveTo = &_levelRef->blockList[_movingToBlockIndex];
			if (x < _blockToMoveTo->x)
			{
				_movingSide = 1;
			}
			else
			{
				_movingSide = 0;
			}
		}
		if (_movingSide == 1)
		{
			if (x + _speed*ofGetLastFrameTime() < _blockToMoveTo->x)
			{
				setNewPosition(x + _speed*ofGetLastFrameTime(), y);
			}
			else
			{
				// Reached block we moved to
				setNewPosition(_blockToMoveTo->x, y);

				state = Standing;
				_currentBlockIndex = _blockToMoveTo->indexInArray;
				_blockToMoveTo = NULL;
			}
		}
		else {
			if (x - _speed*ofGetLastFrameTime() > _blockToMoveTo->x)
			{
				setNewPosition(x - _speed*ofGetLastFrameTime(), y);
			}
			else
			{
				// Reached block we moved to
				setNewPosition(_blockToMoveTo->x, y);

				state = Standing;
				_currentBlockIndex = _blockToMoveTo->indexInArray;
				_blockToMoveTo = NULL;
			}
		}

		break;
	default:
		break;
	}
}
// Draw
void player::draw(float leftSideOffset, camera camera, int tempYOffset) {
	// Ladders and Pillars
	int i = 0;
	while (i < laddersList.size())
	{
		ladderImage.draw(leftSideOffset + laddersList[i][0], laddersList[i][1] - tempYOffset, gameData.blockSize, gameData.blockSize);
		i++;
	}
	i = 0;
	while (i < pillarsList.size())
	{
		pillarImage.draw(leftSideOffset + pillarsList[i][0], pillarsList[i][1] - tempYOffset, gameData.blockSize, gameData.blockSize);
		i++;
	}
	// Character
	texture.draw(leftSideOffset + round(x), round(y) - tempYOffset, size, size);
}

void player::move(movingDir dir) {
	int newBlockIndex;
	switch (dir)
	{
	case player::Up:
		if (_levelRef->blockList[_currentBlockIndex].isLadderSetUp && _currentBlockIndex / gameData.numberOfBlockInLevelRow != 0)
		{
			state = ClimbingTop;
		}
		break;
	case player::Left:
		if (_currentBlockIndex % gameData.numberOfBlockInLevelRow > 0)
		{
			{
				if (!_levelRef->blockList[_currentBlockIndex - 1].isExist)
				{
					state = Moving;
					_movingToBlockIndex = _currentBlockIndex - 1;
				}
				else
				{
					state = Digging;
					_diggingBlock = &_levelRef->blockList[_currentBlockIndex - 1];
				}
			}
		}
		break;
	case player::Right:
		if (_currentBlockIndex % gameData.numberOfBlockInLevelRow < gameData.numberOfBlockInLevelRow-1)
		{
			if (!_levelRef->blockList[_currentBlockIndex+1].isExist)
			{
				state = Moving;
				_movingToBlockIndex = _currentBlockIndex + 1;
			}
			else
			{
				state = Digging;
				_diggingBlock = &_levelRef->blockList[_currentBlockIndex + 1];
			}
		}
		break;
	case player::Down:
		if (_currentBlockIndex / gameData.numberOfBlockInLevelCol < gameData.numberOfBlockInLevelCol - 1)
		{
			newBlockIndex = _currentBlockIndex + gameData.numberOfBlockInLevelRow;
			groundBlock& block = _levelRef->blockList[newBlockIndex];
			if (block.isExist)
			{
				state = Digging;
				_diggingBlock = &block;
			}
			else if (block.isLadderSetUp)
			{
				state = ClimbingBot;
			}
			else {
				state = Falling;
			}
			
		}
		break;
	default:
		break;
	}
}



void player::setNewPosition(float _x, float _y) {
	x = _x;
	y = _y;
}

void player::addResource(groundBlock::BlockTypes type) {
	switch (type)
	{
	case groundBlock::Stone:
		_resourcesVector[0] += 1;
		break;
	case groundBlock::Gold:
		_resourcesVector[2] += 1;
		break;
	case groundBlock::Silver:
		_resourcesVector[1] += 1;
		break;
	case groundBlock::Diamond:
		_resourcesVector[3] += 1;
		break;
	default:
		break;
	}
	std::cout << "Resource" << type << " added" << std::endl;
}

void player::playerDie() {
	isAlive = false;
}

void player::setUpLadder() {
	_levelRef->blockList[_currentBlockIndex].isLadderSetUp = true;
	laddersList.push_back({ _levelRef->blockList[_currentBlockIndex].x, _levelRef->blockList[_currentBlockIndex].y });
	_ladders -= 1;
}

void player::setUpPillar() {
	_levelRef->blockList[_currentBlockIndex].isPillarSetUp = true;
	pillarsList.push_back({ _levelRef->blockList[_currentBlockIndex].x, _levelRef->blockList[_currentBlockIndex].y });
	_pillars -= 1;
}

void player::upgrade() {
	printf("Upgrade!");

	visionExpansion += _resourcesVector[0];
	_resourcesVector[0] = 0;

	addPillars += _resourcesVector[1];
	_resourcesVector[1] = 0;

	addLadders += _resourcesVector[2];
	_resourcesVector[2] = 0;

	addDamage += _resourcesVector[3] * 10;
	_resourcesVector[3] = 0;

	_ladders = gameData.defaultPlayerLadders += addLadders;
	_pillars = gameData.defaultPlayerPillars += addPillars;
	_damage = gameData.defaultPlayerDamage += addDamage;
	addDamage = 0;


}