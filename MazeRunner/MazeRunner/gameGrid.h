#pragma once

#include <iostream>
#include <vector>


//TODO : Think about the collision with camera.
//	   : To do that, I need to think about the size of camera.
//	   : Now I am thinking the maze box as 5x10x5.




// Symbols : W -> Wall, E -> Empty, R -> route.

struct Vec2 {
	int x;
	int y;

	Vec2() {
		x = 0;
		y = 0;
	}
	Vec2(int X, int Y) {
		x = X;
		y = Y;
	}

};

struct Vec2f {
	float x;
	float y;
	Vec2f() {
		x = 0;
		y = 0;
	}
	Vec2f(float X, float Y) {
		x = X;
		y = Y;
	}

};

class gameGrid
{
public:
	gameGrid();
	~gameGrid();

	void init(int width = 10, int depth = 10, const Vec2& wallDims = Vec2(0,0));
	void makeWayToGoal();
	std::vector<Vec2>& getMazeBoxPos(int mazeBoxCount = 0);
	void checkCollisionWithWalls(float x, float z, std::vector<Vec2f>& collisions);

	char getSymbol(int x, int z);
	int getDepth();
	int getWidth();


private:

	std::vector<std::string> mGameGrid;
	std::vector<Vec2> mMazeBoxPos;
	int mWidth = 0;
	int mDepth = 0;
	Vec2 mWallDims = Vec2(0,0);

};

