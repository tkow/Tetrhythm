#include "tetrisscene.h"
#include "config.h"

USING_NS_CC;

//using tetrisscene::Tetris;
//
//void Tetris::cleanBoard(int  targetposy, int targetposx, int Width, int Height, int framepos){
//
//	int grid_x = Width / Tetris::maxy;
//	int grid_y = Height / Tetris::maxx;
//
//	auto sprite = Sprite::create("pink.png");
//
//	sprite->setPosition(Vec2(grid_y*targetposy, grid_x*targetposx));
//
//	// add the sprite as a child to this layer
//	this->addChild(sprite, 0);
//
//}


void Tetris::newblock(){
	bode[19][6] = mino;
	targetposy = 19;
	targetposx = 6;
}


//ç∂Ç…à⁄ìÆ
void Tetris::move_left(){

	for (int i = 0; i < 4; i++) {

		if (targetposx + minoexpand[i].cposx<=0) {
			return;
		}
	}
	for (int i = 0; i < 4; i++) {

		bode[targetposy+minoexpand[i].cposy][targetposx+ minoexpand[i].cposx] = nothing;
		bode[targetposy + minoexpand[i].cposy][targetposx + minoexpand[i].cposx-1] = targetcolor;
	}
		
}

//âEÇ…à⁄ìÆ
bool Tetris::move_right(){
	for (int i = 0; i < 4; i++) {

		if (targetposx + minoexpand[i].cposx <= WIDTH_GRIDX-1) {
			return;
		}
	}
	for (int i = 0; i < 4; i++) {

		bode[targetposy + minoexpand[i].cposy][targetposx + minoexpand[i].cposx] = nothing;
		bode[targetposy + minoexpand[i].cposy][targetposx + minoexpand[i].cposx + 1] = targetcolor;
	}
}

//â∫Ç…à⁄ìÆ
bool Tetris::move_bottom(){
	int y;
	for (y = 19; y < 0; y--){
		if (bode[y][targetposx] != nothing){
			break;
		}
	}

	bode[targetposy][targetposx] = nothing;
	bode[y][targetposx] = mino;

	targetposx = 0;
	targetposy = 0;
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

void Tetris::onPaint(int  targetposy,int targetposx,int Width,int Height,int framepos){

	    int grid_x=Width/Tetris::maxy;
		int grid_y = Height/Tetris::maxx;

	auto sprite = Sprite::create("pink.png");

	sprite->setPosition(Vec2( grid_y*targetposy, grid_x*targetposx));

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


 Scene* Tetris::createSplite()
{
	this->FramePos = Vec2(512, 378);
	auto scene = Scene::create();

	auto block = Sprite::create("./mino/pink.png");
	block->setAnchorPoint(Vec2(0, 0));
	block->setPosition(FramePos);
	this->addChild(block);

	scene->addChild(this);
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



	auto listener = cocos2d::EventListenerKeyboard::create();
	listener->onKeyPressed = [this](cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* keyEvent) {
		if (keyCode == cocos2d::EventKeyboard::KeyCode::KEY_LEFT_ARROW)
		{
			//cocos2d::log("left");
			auto target = static_cast<Sprite*>(keyEvent->getCurrentTarget());
			auto targetmino = target->getChildByName("minos")->getChildByName("target");
			//auto tarch = target->getChildren();
		
			
			

			auto moveTo = MoveBy::create(0, Vec2(-33, 0));
			 //nodes = Node::create();
			/*for (int i = 0; i < 2; i++) {

				auto block = Sprite::create("./mino/pink.png");
				block->setAnchorPoint(Vec2(0, 0));
				block->setPosition(Vec2(100+i*33, 378));
				nodes->addChild(block);
			}*/

			targetmino->runAction(moveTo);
			//this->addChild(targetmino);
			//this->runAction(moveTo);
		}
		else if (keyCode == cocos2d::EventKeyboard::KeyCode::KEY_RIGHT_ARROW)
		{
			auto target = static_cast<Sprite*>(keyEvent->getCurrentTarget());
			auto targetmino = target->getChildByName("minos")->getChildByName("target");
			auto moveTo = MoveBy::create(0, Vec2(33, 0));
			targetmino->runAction(moveTo);
		}
		else if (keyCode == cocos2d::EventKeyboard::KeyCode::KEY_UP_ARROW)
		{
			auto target = static_cast<Sprite*>(keyEvent->getCurrentTarget());
			auto targetmino = target->getChildByName("minos")->getChildByName("target");
			auto moveTo = MoveBy::create(0, Vec2(0, 33));
			targetmino->runAction(moveTo);
		}
		else if (keyCode == cocos2d::EventKeyboard::KeyCode::KEY_DOWN_ARROW)
		{
			auto target = static_cast<Sprite*>(keyEvent->getCurrentTarget());
			auto targetmino = target->getChildByName("minos")->getChildByName("target");
			auto moveTo = MoveBy::create(0, Vec2(0, -33));
			targetmino->runAction(moveTo);

			
			targetmino->setName("Complete");

			createNewMino(target->getChildByName("minos"));



		}
	};
	this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);

    
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
	auto bg = cocos2d::Layer::create();
	bg->setName("bg");
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
    bg->addChild(haikei);
    
    //枠
    auto flame = Sprite::create("waku2.png");
    flame->setPosition(FramePos);
    bg->addChild(flame);
    
    //バー
    auto bar = Sprite::create("bar.png");
    bar->setAnchorPoint(Vec2(0,0));
    bar->setPosition(BarPos_Origin);
    bg->addChild(bar);
    
    //トーン
    auto tone = Sprite::create("tone.png");
    //tone->setPosition(Vec2(BarPos_Center.x + 50,BarPos_Center.y));
    tone->setPosition(Vec2(BarPos_Top.x + 50,BarPos_Top.y));
    bg->addChild(tone);
    
    //next文字
    auto next_moji = Sprite::create("NEXTmoji.png");
    next_moji->setPosition(Vec2(BarPos_Top.x + 650,BarPos_Top.y - 50));
    bg->addChild(next_moji);
    
    //next枠
    auto next = Sprite::create("next2.png");
    next->setPosition(Vec2(BarPos_Top.x + 650,BarPos_Top.y - 200));
    bg->addChild(next);
    
    //score文字
    auto score_moji = Sprite::create("SCOREmoji.png");
    score_moji->setPosition(Vec2(BarPos_Top.x + 650,BarPos_Top.y - 400));
    bg->addChild(score_moji);
    
    //score枠
    auto score = Sprite::create("score2.png");
    score->setPosition(Vec2(BarPos_Top.x + 650,BarPos_Top.y - 500));
    bg->addChild(score);

	//mino操作デバッグ
	auto minos = cocos2d::Layer::create();
	minos->setName("minos");

	auto target = cocos2d::Layer::create();
     target->setName("target");

	 auto targetmino = Sprite::create("./mino/yellow.png");
	 targetmino->setName("cmino");
	 targetmino->setPosition(MinoPos + Vec2(0, 0));
	 target->addChild(targetmino);
	

	 targetmino = Sprite::create("./mino/yellow.png");
	 targetmino->setName("cmino");
	 targetmino->setPosition(MinoPos + Vec2(0, -33));
	 target->addChild(targetmino);



	targetmino = Sprite::create("./mino/yellow.png");
	targetmino->setName("cmino");
	targetmino->setPosition(MinoPos+Vec2(33,0));
	target->addChild(targetmino);
	
	targetmino = Sprite::create("./mino/yellow.png");
	targetmino->setName("cmino");
	targetmino->setPosition(MinoPos + Vec2(-33, 0));
	target->addChild(targetmino);

	minos->addChild(target);



	this->addChild(bg);

	this->addChild(minos);

	
    return true;
}

void Tetris::createNewMino(Node* minos) {
	srand((unsigned int)time(NULL));
	int randNum = rand() % 7+1;

	auto FramePos = Vec2(MinoPosW,MinoPosH);
	auto target = cocos2d::Layer::create();
	target->setName("target");
	
	switch (randNum) {
	case Mino::kShape_t:


		newMino(target, randNum, Vec2(0, 0));
		newMino(target, randNum, Vec2(-MINO_SQ, -MINO_SQ));
		newMino(target, randNum, Vec2(0, - MINO_SQ));
		newMino(target, randNum, Vec2(MINO_SQ, - MINO_SQ));

		/*targetmino = Sprite::create("./mino/yellow.png");
		targetmino->setName("cmino");
		targetmino->setPosition(FramePos + Vec2(0, 0));
		target->addChild(targetmino);


		targetmino = Sprite::create("./mino/yellow.png");
		targetmino->setName("cmino");
		targetmino->setPosition(FramePos + Vec2(-33, -33));
		target->addChild(targetmino);



		targetmino = Sprite::create("./mino/yellow.png");
		targetmino->setName("cmino");
		targetmino->setPosition(FramePos + Vec2(0, -33));
		target->addChild(targetmino);

		targetmino = Sprite::create("./mino/yellow.png");
		targetmino->setName("cmino");
		targetmino->setPosition(FramePos + Vec2(33, -33));
		target->addChild(targetmino);
*/
		break;

	case Mino::kShape_i:

		newMino(target, randNum, Vec2(0, 0));
		newMino(target, randNum, Vec2(0, -MINO_SQ));
		newMino(target, randNum, Vec2(0, -2 * MINO_SQ));
		newMino(target, randNum, Vec2(0, -3 * MINO_SQ));

		//targetmino = Sprite::create("./mino/yellow.png");
		//targetmino->setName("cmino");
		//targetmino->setPosition(FramePos + Vec2(0, 0));
		//target->addChild(targetmino);


		//targetmino = Sprite::create("./mino/yellow.png");
		//targetmino->setName("cmino");
		//targetmino->setPosition(FramePos + Vec2(0, -33));
		//target->addChild(targetmino);



		//targetmino = Sprite::create("./mino/yellow.png");
		//targetmino->setName("cmino");
		//targetmino->setPosition(FramePos + Vec2(0, -66));
		//target->addChild(targetmino);

		//targetmino = Sprite::create("./mino/yellow.png");
		//targetmino->setName("cmino");
		//targetmino->setPosition(FramePos + Vec2(0, -99));
		//target->addChild(targetmino);

		break;

	case Mino::kShape_l:
		newMino(target, randNum, Vec2(0, 0));
		newMino(target, randNum, Vec2(0, -MINO_SQ));
		newMino(target, randNum, Vec2(0, -2*MINO_SQ));
		newMino(target, randNum, Vec2(MINO_SQ, -2*MINO_SQ));

		/* targetmino = Sprite::create("./mino/yellow.png");
		targetmino->setName("cmino");
		targetmino->setPosition(FramePos + Vec2(0, 0));
		target->addChild(targetmino);


		targetmino = Sprite::create("./mino/yellow.png");
		targetmino->setName("cmino");
		targetmino->setPosition(FramePos + Vec2(0, -33));
		target->addChild(targetmino);



		targetmino = Sprite::create("./mino/yellow.png");
		targetmino->setName("cmino");
		targetmino->setPosition(FramePos + Vec2(0, -66));
		target->addChild(targetmino);

		targetmino = Sprite::create("./mino/yellow.png");
		targetmino->setName("cmino");
		targetmino->setPosition(FramePos + Vec2(33, -66));
		target->addChild(targetmino);*/

		
		break;

	case Mino::kShape_rl:
		newMino(target, randNum, Vec2(0, 0));
		newMino(target, randNum, Vec2(0,-MINO_SQ));
		newMino(target, randNum, Vec2(0, -2*MINO_SQ));
		newMino(target, randNum, Vec2(-MINO_SQ, -2*MINO_SQ));

		/*targetmino = Sprite::create("./mino/yellow.png");
		targetmino->setName("cmino");
		targetmino->setPosition(FramePos + Vec2(0, 0));
		target->addChild(targetmino);


		targetmino = Sprite::create("./mino/yellow.png");
		targetmino->setName("cmino");
		targetmino->setPosition(FramePos + Vec2(0, -66));
		target->addChild(targetmino);



		targetmino = Sprite::create("./mino/yellow.png");
		targetmino->setName("cmino");
		targetmino->setPosition(FramePos + Vec2(0, -33));
		target->addChild(targetmino);

		targetmino = Sprite::create("./mino/yellow.png");
		targetmino->setName("cmino");
		targetmino->setPosition(FramePos + Vec2(-33, -66));
		target->addChild(targetmino);
*/
	
		break;

	case Mino::kShape_o:

		newMino(target, randNum, Vec2(0, 0));
		newMino(target, randNum, Vec2(MINO_SQ, 0));
		newMino(target, randNum, Vec2(0, -MINO_SQ));
		newMino(target, randNum, Vec2(MINO_SQ, -MINO_SQ));


		/* targetmino = Sprite::create("./mino/yellow.png");
		targetmino->setName("cmino");
		targetmino->setPosition(FramePos + Vec2(0, 0));
		target->addChild(targetmino);


		targetmino = Sprite::create("./mino/yellow.png");
		targetmino->setName("cmino");
		targetmino->setPosition(FramePos + Vec2(0, -33));
		target->addChild(targetmino);



		targetmino = Sprite::create("./mino/yellow.png");
		targetmino->setName("cmino");
		targetmino->setPosition(FramePos + Vec2(33, 0));
		target->addChild(targetmino);

		targetmino = Sprite::create("./mino/yellow.png");
		targetmino->setName("cmino");
		targetmino->setPosition(FramePos + Vec2(33, -33));
		target->addChild(targetmino);
*/
		
		break;
	case Mino::kShape_z:
		
		
		newMino(target, randNum, Vec2(0, 0));
		newMino(target, randNum, Vec2(-MINO_SQ, 0));
		newMino(target, randNum, Vec2(0, -MINO_SQ));
		newMino(target, randNum, Vec2(MINO_SQ, -MINO_SQ));

		
		/*targetmino = Sprite::create("./mino/yellow.png");
		targetmino->setName("cmino");
		targetmino->setPosition(FramePos + Vec2(0, 0));
		target->addChild(targetmino);


		targetmino = Sprite::create("./mino/yellow.png");
		targetmino->setName("cmino");
		targetmino->setPosition(FramePos + Vec2(-33, 0));
		target->addChild(targetmino);



		targetmino = Sprite::create("./mino/yellow.png");
		targetmino->setName("cmino");
		targetmino->setPosition(FramePos + Vec2(0, -33));
		target->addChild(targetmino);

		targetmino = Sprite::create("./mino/yellow.png");
		targetmino->setName("cmino");
		targetmino->setPosition(FramePos + Vec2(33, -33));
		target->addChild(targetmino);
*/
		
		break;

	case Mino::kShape_rz:

		newMino(target,randNum, Vec2(0, 0));
		newMino(target, randNum, Vec2(MINO_SQ, 0));
		newMino(target, randNum, Vec2(0, -MINO_SQ));
		newMino(target, randNum, Vec2(-MINO_SQ, -MINO_SQ));

		//targetmino = Sprite::create("./mino/yellow.png");
		//targetmino->setName("cmino");
		//targetmino->setPosition(FramePos + Vec2(0, 0));
		//target->addChild(targetmino);


		//targetmino = Sprite::create("./mino/yellow.png");
		//targetmino->setName("cmino");
		//targetmino->setPosition(FramePos + Vec2(33, 0));
		//target->addChild(targetmino);



		//targetmino = Sprite::create("./mino/yellow.png");
		//targetmino->setName("cmino");
		//targetmino->setPosition(FramePos + Vec2(0, -33));
		//target->addChild(targetmino);

		//targetmino = Sprite::create("./mino/yellow.png");
		//targetmino->setName("cmino");
		//targetmino->setPosition(FramePos + Vec2(-33, -33));
		//target->addChild(targetmino);

		
		break;

	}
	minos->addChild(target);
}
void Tetris::newMino(Node* target, int color, Vec2 pos) {
	
    Sprite* targetmino ;
	switch (color) {
	case Mino::yellow:
		 targetmino = Sprite::create("./mino/yellow.png");
		break;
	case Mino::blue:
		 targetmino = Sprite::create("./mino/blue.png");
		break;
	case Mino::gleen:
		 targetmino = Sprite::create("./mino/green.png");
		break;
	case Mino::iblue:
		 targetmino = Sprite::create("./mino/lblue.png");
		break;
	case Mino::red:
		 targetmino = Sprite::create("./mino/red.png");
		break;
	case Mino::pink:
		 targetmino = Sprite::create("./mino/pink.png");
		break;
	case Mino::orange:
		 targetmino = Sprite::create("./mino/orange.png");
		break;
	}
	targetmino->setName("cmino");
	targetmino->setPosition(Vec2(MinoPosW, MinoPosH)+pos);
	target->addChild(targetmino);
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