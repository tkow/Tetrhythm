#include "HelloWorldScene.h"

USING_NS_CC;

using namespace std;



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
	
    /////////////////////////////
    
	screenSize = Director::getInstance()->getVisibleSize();

	Sprite* sprite = Sprite::create();
	sprite->setTextureRect(Rect(0, 0, 50, screenSize.height*0.8));
	sprite->setColor(Color3B::WHITE);
    
	float boxX = screenSize.width * 0.8;
	float boxY = screenSize.height / 2;
	sprite->setPosition(Point(boxX, boxY));
	this->addChild(sprite);

	CCSize size = CCDirector::sharedDirector()->getWinSize();
	CCDrawNode* node = CCDrawNode::create();
	node->setPosition(ccp(size.width / 2, size.height / 2));
	this->addChild(node);

	draw = CCDrawNode::create();
	draw->setPosition(ccp(0, 0));
	draw->setTag(1);
	this->addChild(draw);

	drawStartX = screenSize.width * 0.8 - 25;
	drawY = screenSize.height / 2;
	drawEndX = screenSize.width * 0.8 + 25;

	this->scheduleUpdate();
    
	upFlag = false;
	return true;
}

void HelloWorld::update() {
	
	if (!upFlag) {
		drawY-=2;
	}else {
		drawY+=2;
	}
	draw->clear();
	draw->drawSegment(ccp(drawStartX, drawY),
		ccp(drawEndX, drawY), 2, ccc4FFromccc3B(Color3B::RED));

	/*if (screenSize.height * 0.2 > drawY) {
		upFlag = true;
	}else if(screenSize.height * 0.8 < drawY){
		upFlag = false;
	}*/
}


void HelloWorld::menuCloseCallback(Ref* pSender)
{
    Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}
