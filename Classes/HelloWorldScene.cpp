#include "HelloWorldScene.h"

USING_NS_CC;

Scene* HelloWorld::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = HelloWorld::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    /////////////////////////////
    // 2. add a menu item with "X" image, which is clicked to quit the program
    //    you may modify it.

    // add a "close" icon to exit the progress. it's an autorelease object
    auto closeItem = MenuItemImage::create(
                                           "CloseNormal.png",
                                           "CloseSelected.png",
                                           CC_CALLBACK_1(HelloWorld::menuCloseCallback, this));
    
	closeItem->setPosition(Vec2(origin.x + visibleSize.width - closeItem->getContentSize().width/2 ,
                                origin.y + closeItem->getContentSize().height/2));

    // create menu, it's an autorelease object
    auto menu = Menu::create(closeItem, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);

    //画像の配置
    //座標定義
    FramePos = Vec2(512,378);
    BarPos_Origin = Vec2(200,FramePos.y - 340);
    BarPos_Center = Vec2(BarPos_Origin.x,FramePos.y);
    BarPos_Top = Vec2(BarPos_Origin.x,BarPos_Center.y + 340);
    //BarPos = Vec2(262,378);
    MinoPos = Vec2(364,62);
    CenterPos = Vec2(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y);
    
    //背景
    auto haikei = Sprite::create("haikei.png");
    haikei->setPosition(CenterPos);
    this->addChild(haikei);
    
    //枠
    auto flame = Sprite::create("waku2.png");
    flame->setPosition(FramePos);
    this->addChild(flame);
    
    //バー
    auto bar = Sprite::create("bar.png");
    bar->setAnchorPoint(Vec2(0,0));
    bar->setPosition(BarPos_Origin);
    this->addChild(bar);
    
    //トーン
    auto tone = Sprite::create("tone.png");
    //tone->setPosition(Vec2(BarPos_Center.x + 50,BarPos_Center.y));
    tone->setPosition(Vec2(BarPos_Top.x + 50,BarPos_Top.y));
    this->addChild(tone);
    
    //next文字
  // auto next_moji = Sprite::create("NEXTmoji.png");
   // next_moji->setPosition(Vec2(BarPos_Top.x + 650,BarPos_Top.y - 50));
   // this->addChild(next_moji);
    
    //next枠
    auto next = Sprite::create("next2.png");
    next->setPosition(Vec2(BarPos_Top.x + 650,BarPos_Top.y - 200));
    this->addChild(next);
    
    //score文字
   // auto score_moji = Sprite::create("SCOREmoji.png");
   // score_moji->setPosition(Vec2(BarPos_Top.x + 650,BarPos_Top.y - 400));
   // this->addChild(score_moji);
    
    //score枠
    auto score = Sprite::create("score2.png");
    score->setPosition(Vec2(BarPos_Top.x + 650,BarPos_Top.y - 500));
    this->addChild(score);
    
    
    
    return true;
}


void HelloWorld::menuCloseCallback(Ref* pSender)
{
    Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}
