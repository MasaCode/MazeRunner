#include "gameGrid.h"

#include<cstdlib>
#include<ctime>

gameGrid::gameGrid()
{

}

gameGrid::~gameGrid()
{
}


void gameGrid::init(int width, int depth, const Vec2& wallDims) {

	mWidth = width;
	mDepth = depth;
	mWallDims = wallDims;

	std::string temp = "";
	mGameGrid.resize(depth);
	for (int i = 0; i < width; i++) {
		temp += 'E';
	}

	for (int i = 0; i < depth; i++) {
		mGameGrid[i] = temp;
	}

}

void gameGrid::makeWayToGoal() {
	int x = 0, z = 0;
	bool isReached = false;

	srand(time(0));

	/*while (!(x == mWidth-1 && z == mDepth-1)) {
		int temp = rand() % 4;
		switch (temp) {
			case 0:
				if ((z - 1) >= 0) {
					--z;
					mGameGrid[z][x] = 'R';
				}
				break;
			case 1:
				if ((x + 1) < mWidth) {
					++x;
					mGameGrid[z][x] = 'R';
				}
				break;
			case 2:
				if ((z + 1) < mDepth) {
					++z;
					mGameGrid[z][x] = 'R';
				}
				break;
			case 3:
				if ((x - 1) >= 0) {
					--x;
					mGameGrid[z][x] = 'R';
				}
				break;
		}

	}*/

	// TODO : make this truly random.
	int direction;
	int count = 0;
	mGameGrid[0][0] = 'R';
	do {

		if (!isReached && (count % 2) == 0) {
			direction = rand() % 2;
		}

		if (direction == 0) { // for down
			z++;
			if (z >= mDepth) {
				z = mDepth - 1;
				isReached = true;
				direction = 1;
			}
			else {
				mGameGrid[z][x] = 'R';
				count++;
			}

		}
		else { // for right.
			x++;
			if (x >= mWidth) {
				x = mWidth - 1;
				isReached = true;
				direction = 0;
			}else{
				mGameGrid[z][x] = 'R';
				count++;
			}

		}



	} while (!(x == mWidth - 1 && z == mDepth - 1));
	
}

std::vector<Vec2>& gameGrid::getMazeBoxPos(int mazeBoxCount) {
	
	srand(time(0));
	Vec2 pos(0,0);
	mMazeBoxPos.resize(mazeBoxCount);
	int currentCount = 0;
	do {
		
		pos.x = rand() % mWidth;
		pos.y = rand() % mDepth;

		if (mGameGrid[pos.y][pos.x] == 'E') {
			mGameGrid[pos.y][pos.x] = 'W';
			mMazeBoxPos[currentCount].x = pos.x;
			mMazeBoxPos[currentCount].y = pos.y;
			currentCount++;
		}


	} while (currentCount < mazeBoxCount);
 
	//printf("WOWOOW");

	return mMazeBoxPos;
}

void gameGrid::checkCollisionWithWalls(float x, float z, std::vector<Vec2f>& collisions) {

	Vec2 pos;
	pos.x = std::floor(x / (float)mWallDims.x);
	pos.y = std::floor(z / (float)mWallDims.y);

	//If the player (camera) is outside the maze, just return.
	if (pos.x < 0 || pos.x >= mGameGrid[0].size() || pos.y < 0 || pos.y >= mGameGrid.size()) {
		return;
	}


	if (mGameGrid[pos.y][pos.x] == 'W') {
		collisions.push_back(Vec2f(pos.x * (float)mWallDims.x + (mWallDims.x / 2.0f), pos.y * (float)mWallDims.y + (mWallDims.y / 2.0f)));
	}

}


char gameGrid::getSymbol(int x, int z) {
	return mGameGrid[z][x];
}

int gameGrid::getDepth() {
	return mDepth;
}

int gameGrid::getWidth() {
	return mWidth;
}