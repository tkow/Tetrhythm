#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"

class HelloWorld : public cocos2d::Layer
{
    

public:
    //座標
    cocos2d::Vec2 FramePos;
    cocos2d::Vec2 BarPos_Origin;
    cocos2d::Vec2 BarPos_Center;
    cocos2d::Vec2 BarPos_Top;
    cocos2d::Vec2 MinoPos;
    cocos2d::Vec2 CenterPos;
    
    static cocos2d::Scene* createScene();

    virtual bool init();
    
    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);
    
    // implement the "static create()" method manually
    CREATE_FUNC(HelloWorld);
};

#endif // __HELLOWORLD_SCENE_H__
