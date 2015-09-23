#ifndef __TETRIS_SCENE_H__
#define __TETRIS_SCENE_H__

#include "cocos2d.h"
#include "mino.h"

class Tetris : public cocos2d::Layer
{
public:
	static cocos2d::Scene* createScene();

	struct conponent {
		int cposx;
		int cposy;
	};

	virtual bool init();
	const int nothing = 0;
	const int mino = 1;
	int targetposx = 4;
	int targetposy = 0;
	struct conponent minoexpand[4];
	int targetcolor = 0;
	const int maxx = 20;
	const int maxy = 10;
	int Width = 330;
	int Height = 660;
	int shape;
	int direction;


	//É{Å[Éh
	int bode[20][10];
	void onPaint(int posy, int posx, int width, int height, int framepos);
	// a selector callback
	void menuCloseCallback(cocos2d::Ref* pSender);
	void	newblock();
	bool	move_left();
	bool	move_right();
	int move_bottom();
	void lineDelete();
	void check();
	void upLine();
	void rotateMino(Node* minos);
	bool isKeyPressed(cocos2d::EventKeyboard::KeyCode);
	double keyPressedDuration(cocos2d::EventKeyboard::KeyCode);
	//void createNewMino(cocos2d::Node*);
	void createNewMino(Node * minos, int randShape = rand() % 7 + 1,int direction= rand() % 4,bool rotate=false);
	void newMino(Node* target, int color, cocos2d::Vec2 pos);
	conponent* positionCheckArray(conponent* data,int shape, int direction);
	cocos2d::Scene* createSplite();
	//座標
	cocos2d::Vec2 FramePos;
	cocos2d::Vec2 BarPos_Origin;
	cocos2d::Vec2 BarPos_Center;
	cocos2d::Vec2 BarPos_Top;
	cocos2d::Vec2 MinoPos;
	cocos2d::Vec2 CenterPos;
	cocos2d::Node* nodes;

private:
	static std::map<cocos2d::EventKeyboard::KeyCode,
		std::chrono::high_resolution_clock::time_point> keys;
	cocos2d::Label * label;

public:  virtual void update(float delta) override;

		 // implement the "static create()" method manually
		 CREATE_FUNC(Tetris);
};

#endif // __TETRIS_SCENE_H__


