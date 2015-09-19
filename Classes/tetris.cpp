#include "tetrisscene.h"

USING_NS_CC;

//using tetrisscene::Tetris;
//
//void Tetris::cleanBoard(int  posy, int posx, int Width, int Height, int framepos){
//
//	int grid_x = Width / Tetris::maxy;
//	int grid_y = Height / Tetris::maxx;
//
//	auto sprite = Sprite::create("pink.png");
//
//	sprite->setPosition(Vec2(grid_y*posy, grid_x*posx));
//
//	// add the sprite as a child to this layer
//	this->addChild(sprite, 0);
//
//}


void Tetris::newblock(){
	bode[19][6] = mino;
	posy = 19;
	posx = 6;
}


//ç∂Ç…à⁄ìÆ
void Tetris::move_left(){
	if (posx - 1 >= 0){
		bode[posy][posx] = nothing;
		posx--;
	}
	bode[posy][posx] = mino;
}

//âEÇ…à⁄ìÆ
void Tetris::move_right(){
	if (posx + 1 < 12){
		bode[posy][posx] = nothing;
		posx++;
	}
	bode[posy][posx] = mino;
}

//â∫Ç…à⁄ìÆ
void Tetris::move_bottom(){
	int y;
	for (y = 19; y < 0; y--){
		if (bode[y][posx] != nothing){
			break;
		}
	}

	bode[posy][posx] = nothing;
	bode[y][posx] = mino;

	posx = 0;
	posy = 0;
}

//è¡ãéîªíË
void Tetris::check(){
	int count = 0;

	for (int y = 0; y < 20; y++){
		for (int x = 0; x < 12; x++){
			if (bode[y][x] == mino){
				count++;
			}
		}

		if (count == 12){
			for (int x = 0; x < 12; x++){
				bode[y][x] = nothing;
			}
		}
		count = 0;
	}
}

void Tetris::onPaint(int  posy,int posx,int Width,int Height,int framepos){

	    int grid_x=Width/Tetris::maxy;
		int grid_y = Height/Tetris::maxx;

	auto sprite = Sprite::create("pink.png");

	sprite->setPosition(Vec2( grid_y*posy, grid_x*posx));

	// add the sprite as a child to this layer
	this->addChild(sprite, 0);

}

Scene* Tetris::createScene()
{
	// 'scene' is an autorelease object
	auto scene = Scene::create();

	// 'layer' is an autorelease object
	auto layer = Tetris::create();

	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;
}

bool Tetris::init()
{
	if (!Layer::init())
	{
		return false;
	}

	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
    
    auto closeItem = MenuItemImage::create(
                                           "CloseNormal.png",
                                           "CloseSelected.png",
                                           CC_CALLBACK_1(Tetris::menuCloseCallback, this));
    
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
    auto next_moji = Sprite::create("NEXTmoji.png");
    next_moji->setPosition(Vec2(BarPos_Top.x + 650,BarPos_Top.y - 50));
    this->addChild(next_moji);
    
    //next枠
    auto next = Sprite::create("next2.png");
    next->setPosition(Vec2(BarPos_Top.x + 650,BarPos_Top.y - 200));
    this->addChild(next);
    
    //score文字
    auto score_moji = Sprite::create("SCOREmoji.png");
    score_moji->setPosition(Vec2(BarPos_Top.x + 650,BarPos_Top.y - 400));
    this->addChild(score_moji);
    
    //score枠
    auto score = Sprite::create("score2.png");
    score->setPosition(Vec2(BarPos_Top.x + 650,BarPos_Top.y - 500));
    this->addChild(score);
    
    return true;
}



bool Tetris::isKeyPressed(EventKeyboard::KeyCode code) {
    if (keys.find(code) != keys.end())
        return true;
    return false;
}

// double Tetris::keyPressedDuration(EventKeyboard::KeyCode code) {
//     if(!isKeyPressed(EventKeyboard::KeyCode::KEY_UP_ARROW))
//         return 0;  // Not pressed, so no duration obviously
//
//     // Return the amount of time that has elapsed between now and when the user
//     // first started holding down the key in milliseconds
//     // Obviously the start time is the value we hold in our std::map keys
//     return std::chrono::duration_cast<std::chrono::milliseconds>
//             (std::chrono::high_resolution_clock::now() - keys[code]).count();
// }

void Tetris::update(float delta) {
    Node::update(delta);
    if (isKeyPressed(EventKeyboard::KeyCode::KEY_UP_ARROW)) {
        std::stringstream ss;
        ss << "UP key has been pressed";
        label->setString(ss.str().c_str());
    }
    else
    if (isKeyPressed(EventKeyboard::KeyCode::KEY_DOWN_ARROW)) {
        std::stringstream ss;
        ss << "DOWN key has been pressed";
        label->setString(ss.str().c_str());
    }
    else
    if (isKeyPressed(EventKeyboard::KeyCode::KEY_LEFT_ARROW)) {
        std::stringstream ss;
        ss << "LEFT key has been pressed";
        label->setString(ss.str().c_str());
    }
    else
    if (isKeyPressed(EventKeyboard::KeyCode::KEY_RIGHT_ARROW)) {
        std::stringstream ss;
        ss << "RIGHT key has been pressed";
        label->setString(ss.str().c_str());
    }
    else {
        label->setString("Press the CTRL Key");
    }
}


void Tetris::menuCloseCallback(Ref* pSender)
{
    Director::getInstance()->end();
    
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}

std::map<cocos2d::EventKeyboard::KeyCode,
std::chrono::high_resolution_clock::time_point> Tetris::keys;