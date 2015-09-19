#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"

class HelloWorld : public cocos2d::Layer
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();

    bool isKeyPressed(cocos2d::EventKeyboard::KeyCode);
    double keyPressedDuration(cocos2d::EventKeyboard::KeyCode);

    // implement the "static create()" method manually
    CREATE_FUNC(HelloWorld);

private:
    static std::map<cocos2d::EventKeyboard::KeyCode,
        std::chrono::high_resolution_clock::time_point> keys;
    cocos2d::Label * label;
public:
    virtual void update(float delta) override;
};
#endif // __HELLOWORLD_SCENE_H__
