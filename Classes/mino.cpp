#include "mino.h"
#include "config.h"

Mino::Mino(int direction, int color)
	:direction(direction)
	, color(color)
{
}

Mino::~Mino()
{
}

int Mino::getdirection()
{
	return direction;
}

int Mino::getColor()
{
	return color;
}


Mino::Mino()
	:posX(0)
	, posY(0)
{
	blocks = newBlocks();
	tmpBlocks = newBlocks();
}

//Mino::~Mino()
//{
//	deleteBlocks(blocks);
//	deleteBlocks(tmpBlocks);
//}

void Mino::setPos(int x, int y)
{
	posX = x;
	posY = y;
}


void Mino::makeBlocks(int **b, int shape, int ids[])
{
	

	switch (shape) {
	case kShape_o:
		b[1][1] = (int) Mino::kColor::gleen;
		b[1][2] = (int) Mino::kColor::gleen;
		b[2][1] = (int) Mino::kColor::gleen;
		b[2][2] = (int) Mino::kColor::gleen;
		break;

	case kShape_i:
		b[0][1] = (int)Mino::kColor::blue;
		b[1][1] = (int)Mino::kColor::blue;
		b[2][1] = (int)Mino::kColor::blue;
		b[3][1] = (int)Mino::kColor::blue;
		break;

	case kShape_t:
		b[1][1] = (int)Mino::kColor::yellow;
		b[2][1] = (int)Mino::kColor::yellow;
		b[2][2] = (int)Mino::kColor::yellow;
		b[3][1] = (int)Mino::kColor::yellow;
		break;

	case kShape_l:
		b[1][1] = (int)Mino::kColor::iblue;
		b[1][2] = (int)Mino::kColor::iblue;
		b[2][1] = (int)Mino::kColor::iblue;
		b[3][1] = (int)Mino::kColor::iblue;
		break;

	case kShape_rl:
		b[1][1] = (int)Mino::kColor::pink;
		b[1][2] = (int)Mino::kColor::pink;
		b[2][2] = (int)Mino::kColor::pink;
		b[3][2] = (int)Mino::kColor::pink;
		break;

	case kShape_z:
		b[1][2] = (int)Mino::kColor::orange;
		b[2][1] = (int)Mino::kColor::orange;
		b[2][2] = (int)Mino::kColor::orange;
		b[3][1] = (int)Mino::kColor::orange;
		break;

	case kShape_rz:
		b[1][1] = (int)Mino::kColor::red;
		b[2][1] = (int)Mino::kColor::red;
		b[2][2] = (int)Mino::kColor::red;
		b[3][2] = (int)Mino::kColor::red;
		break;

	default:
		break;
	}
}

int** Mino::newBlocks()
{
	int** b;
	for (int i = 0; i < MINO_HEIGHT; i++) {
		for (int j = 0; j < MINO_WIDTH; j++) {
			b[i][j] = (int) Mino::kColor::none;
		}
	}
	return b;
}

void Mino::deleteBlocks(int **b)
{
	for (int i = 0; i < MINO_HEIGHT; i++) {
		for (int j = 0; j < MINO_WIDTH; j++) {
			 b[i][j] = (int)Mino::kColor::none;
		}
	}
}

void Mino::turnRight()
{
	for (int i = 0; i < MINO_HEIGHT; i++) {
		for (int j = 0; j < MINO_WIDTH; j++) {
			int turned_x = MINO_WIDTH - 1 - i;
			int turned_y = j;
			tmpBlocks[turned_y][turned_x] = blocks[i][j];
		}
	}
	tmpToMain();
}

void Mino::turnLeft()
{
	for (int i = 0; i < MINO_HEIGHT; i++) {
		for (int j = 0; j < MINO_WIDTH; j++) {
			int turned_x = i;
			int turned_y = MINO_WIDTH - 1 - j;
			tmpBlocks[turned_y][turned_x] = blocks[i][j];
		}
	}
	tmpToMain();
}

void Mino::tmpToMain()
{
	for (int i = 0; i < MINO_HEIGHT; i++) {
		for (int j = 0; j < MINO_WIDTH; j++) {
			blocks[i][j] = tmpBlocks[i][j];
			tmpBlocks[i][j] = (int)Mino::kColor::none;
		}
	}
}