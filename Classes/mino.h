#pragma once
#ifndef _TETRIS__MINO__
#define __TETRIS__MINO__

#include <iostream>

class Mino
{
private:

	int direction;
	int color;

public:

	enum kColor {
		none,
		gleen,
		blue,
		yellow,
		iblue,
		pink,
		orange,
		red		
	};

	Mino();
	Mino(int direction, int color);
	~Mino();

	int getdirection();
	int getColor();


	int posX;
	int posY;
	int** blocks;
	int** tmpBlocks;

	enum kShape {
		kShape_last,
		kShape_o, //green
		kShape_i,
		kShape_t,
		kShape_l,
		kShape_rl,
		kShape_z,
		kShape_rz,		
	};

	
	int** newBlocks();
	void deleteBlocks(int** b);

	
	static void makeBlocks(int** b, int shape, int directions[]);

	void turnLeft();
	void turnRight();
	void tmpToMain();

	void setPos(int x, int y);


};

#endif /* defined(__tetris__Block__) */