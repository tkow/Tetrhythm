#ifndef __TETRIS_SCENE_H__
#define __TETRIS_SCENE_H__

#include "cocos2d.h"

class Tetris : public cocos2d::Layer
{
public:
	static cocos2d::Scene* createScene();

	virtual bool init();
	const int nothing = 0;
	const int mino = 1;
	int posx;
    int posy;
	const int maxx = 20;
	const int maxy = 10;
	int Width = 330;
	int Height = 660;
		//É{Å[Éh
   int bode[20][10];
   void Tetris::onPaint(int posy,int posx,int width ,int height,int framepos);
	// a selector callback
	void menuCloseCallback(cocos2d::Ref* pSender);
   void	Tetris::newblock();
   void	Tetris::move_left();
   void	Tetris::move_right();
   void Tetris::move_bottom();
   void Tetris::check();
	// implement the "static create()" method manually
	CREATE_FUNC(Tetris);
};

#endif // __HELLOWORLD_SCENE_H__


