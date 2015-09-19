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
   void onPaint(int posy,int posx,int width ,int height,int framepos);
    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);
   void	newblock();
   void	move_left();
   void	move_right();
   void move_bottom();
   void check();
    bool isKeyPressed(cocos2d::EventKeyboard::KeyCode);
    double keyPressedDuration(cocos2d::EventKeyboard::KeyCode);
    
    //座標
    cocos2d::Vec2 FramePos;
    cocos2d::Vec2 BarPos_Origin;
    cocos2d::Vec2 BarPos_Center;
    cocos2d::Vec2 BarPos_Top;
    cocos2d::Vec2 MinoPos;
    cocos2d::Vec2 CenterPos;
    
    
private:
    static std::map<cocos2d::EventKeyboard::KeyCode,
    std::chrono::high_resolution_clock::time_point> keys;
    cocos2d::Label * label;
    
public:  virtual void update(float delta) override;
    
    // implement the "static create()" method manually
	CREATE_FUNC(Tetris);
};

#endif // __TETRIS_SCENE_H__


