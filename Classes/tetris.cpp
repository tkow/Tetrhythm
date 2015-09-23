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


void Tetris::newblock() {
	bode[19][6] = mino;
	targetposy = 19;
	targetposx = 6;
}


//ç∂Ç…à⁄ìÆ
bool Tetris::move_left() {

	for (int i = 0; i < 4; i++) {

		if (targetposx + minoexpand[i].cposx <= 0||bode[targetposy + minoexpand[i].cposy][targetposx + minoexpand[i].cposx-1]>0) {
			return false;
		}
	}
	targetposx--;
	return true;
	/*for (int i = 0; i < 4; i++) {

		bode[targetposy+minoexpand[i].cposy][targetposx+ minoexpand[i].cposx] = nothing;
		bode[targetposy + minoexpand[i].cposy][targetposx + minoexpand[i].cposx-1] = targetcolor;
	}*/

}

//âEÇ…à⁄ìÆ
bool Tetris::move_right() {
	for (int i = 0; i < 4; i++) {

		if (targetposx + minoexpand[i].cposx >= WIDTH_GRIDX - 1 || bode[targetposy + minoexpand[i].cposy][targetposx + minoexpand[i].cposx+1]>0) {
			return false;
		}
	}
	targetposx++;
	return true;
	//for (int i = 0; i < 4; i++) {

	//	bode[targetposy + minoexpand[i].cposy][targetposx + minoexpand[i].cposx] = nothing;
	//	bode[targetposy + minoexpand[i].cposy][targetposx + minoexpand[i].cposx + 1] = targetcolor;
	//}
}

//â∫Ç…à⁄ìÆ
int Tetris::move_bottom() {


	int movecount = WIDTH_GRIDY;
	for (int i = 0; i < 4; i++) {
		bool reject_check = false;

		for (int j = 0; j < 4; j++) {
			if (minoexpand[i].cposx == minoexpand[j].cposx&&minoexpand[i].cposy < minoexpand[j].cposy) {
				reject_check = true;
				break;
			}
		}
		if (reject_check) { continue; }
		int tx = minoexpand[i].cposx + targetposx;
		int ty = minoexpand[i].cposy + targetposy;
		int tempcounter = 0;
		while (++ty < 20) {

			if (bode[ty][tx]>0) {
				break;
			}
			tempcounter++;
		}
		if (movecount > tempcounter) {
			movecount = tempcounter;
		}


	}

	for (int i = 0; i < 4; i++) {
		bode[minoexpand[i].cposy + targetposy + movecount][targetposx + minoexpand[i].cposx] = targetcolor;
	}

	/*bode[targetposy][targetposx] = nothing;
	bode[y][targetposx] = mino;
*/
	targetposy += movecount;
	return movecount;
}

//è¡ãéîªíË
void Tetris::check() {
	int count = 0;

	for (int y = 0; y < WIDTH_GRIDY; y++) {
		bool checker = true;
		for (int i = 0; i < WIDTH_GRIDX; i++) {
			if (bode[y][i] == 0) {
				checker = false;
				break;
			}
		}

		if (!checker) {
			continue;
		}
		for (int x = 0; x < WIDTH_GRIDX; x++) {
			bode[y][x] = 0;
			this->getChildByName("minos")->removeChildByTag(y*WIDTH_GRIDX + x);
			for (int j = y - 1; j >= 0; j--) {
				if (bode[j][x] > 0) {
					bode[j + 1][x] = bode[j][x];
					bode[j][x] = 0;
					auto movec = this->getChildByName("minos")->getChildByTag(j*WIDTH_GRIDX + x);
					movec->runAction(MoveBy::create(0, Vec2(0, -33)));
					movec->setTag((j + 1)*WIDTH_GRIDX + x);
				}
			}
		}

	}
}

void Tetris::upLine() {
	int count = 0;

	for (int y = 0; y < WIDTH_GRIDY; y++) {
		bool checker = true;
		for (int i = 0; i < WIDTH_GRIDX; i++) {
			if (bode[y][i] == 0) {
				checker = false;
				break;
			}
		}

		if (!checker) {
			continue;
		}
		for (int x = 0; x < WIDTH_GRIDX; x++) {
			bode[y][x] = 0;
			this->getChildByName("minos")->removeChildByTag(y*WIDTH_GRIDX + x);
			for (int j = y - 1; j >= 0; j--) {
				if (bode[j][x] > 0) {
					bode[j + 1][x] = bode[j][x];
					bode[j][x] = 0;
					auto movec = this->getChildByName("minos")->getChildByTag(j*WIDTH_GRIDX + x);
					movec->runAction(MoveBy::create(0, Vec2(0, -33)));
					movec->setTag((j + 1)*WIDTH_GRIDX + x);
				}
			}
		}

	}
}


void Tetris::lineDelete() {

}

void Tetris::onPaint(int  targetposy, int targetposx, int Width, int Height, int framepos) {

	int grid_x = Width / Tetris::maxy;
	int grid_y = Height / Tetris::maxx;

	auto sprite = Sprite::create("pink.png");

	sprite->setPosition(Vec2(grid_y*targetposy, grid_x*targetposx));

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
	srand((unsigned int)time(NULL));
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
			if (!Tetris::move_left()) { return; }

			//cocos2d::log("left");
			auto target = static_cast<Sprite*>(keyEvent->getCurrentTarget());
			auto targetmino = target->getChildByName("minos")->getChildByName("target");
			auto moveTo = MoveBy::create(0, Vec2(-33, 0));			
			targetmino->runAction(moveTo);
		}
		else if (keyCode == cocos2d::EventKeyboard::KeyCode::KEY_RIGHT_ARROW)
		{
			if (!Tetris::move_right()) { return; }
			auto target = static_cast<Sprite*>(keyEvent->getCurrentTarget());
			auto targetmino = target->getChildByName("minos")->getChildByName("target");
			auto moveTo = MoveBy::create(0, Vec2(33, 0));
			targetmino->runAction(moveTo);
		}
		else if (keyCode == cocos2d::EventKeyboard::KeyCode::KEY_UP_ARROW)
		{
			auto target = static_cast<Sprite*>(keyEvent->getCurrentTarget());
			auto targetminos = target->getChildByName("minos");
		/*	auto targetmino = target->getChildByName("minos")->getChildByName("target");*/

			/*if (targetposx > 0 && targetposx < WIDTH_GRIDX - 1) {
				if ((targetposx >= WIDTH_GRIDX - 2)&&(shape==Mino::kShape_i)&&(direction==0|| direction == 2)) {
				
				}
				else {
					
				}
				
			}*/
			rotateMino(targetminos);
			//auto target = static_cast<Sprite*>(keyEvent->getCurrentTarget());
			//auto targetmino = target->getChildByName("minos")->getChildByName("target");
			//auto moveTo = MoveBy::create(0, Vec2(0, 33));
			//targetmino->runAction(moveTo);
		}
		else if (keyCode == cocos2d::EventKeyboard::KeyCode::KEY_DOWN_ARROW)
		{
			auto target = static_cast<Sprite*>(keyEvent->getCurrentTarget());
			auto targetminos = target->getChildByName("minos");
			auto targetmino = targetminos->getChildByName("target");

			auto moveTo = MoveBy::create(0, Vec2(0, -move_bottom() * 33));
			targetmino->runAction(moveTo);



			auto children = targetmino->getChildren();

			//targetmino->setName("Completed");
			//	for (  ) {
				//CCObject* tchild = NULL;

			//CCARRAY_FOREACH_REVERSE(this->getChildren(), tchild){
				/*CCSprite *child = (CCSprite*)tchild;
				child->setTag((targetposy + minoexpand[i].cposy)*WIDTH_GRIDX + (targetposx + minoexpand[i].cposx));
				child->retain();
				child->removeFromParentAndCleanup(false);
				targetminos->addChild(child);
				i++;*/
				//}
			int len = targetmino->getChildrenCount();
			for (int i = len - 1; i >= 0; i--) {
				auto child = children.at(i);

				auto pos = child->getPosition();
				child->setTag((targetposy + minoexpand[i].cposy)*WIDTH_GRIDX + (targetposx + minoexpand[i].cposx));
				//child->retain();			
				child->setPosition(Vec2(MinoPosBottomLX + (targetposx + minoexpand[i].cposx)*MINO_SQ, MinoPosBottomLY + (WIDTH_GRIDY - 1 - (targetposy + minoexpand[i].cposy))*MINO_SQ));
				child->removeFromParentAndCleanup(true);
				//child->setPosition();
				targetminos->addChild(child);
			}

			check();

			//}
			targetminos->removeChildByName("target");

			createNewMino(target->getChildByName("minos"));



		}
	};
	this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);


	auto closeItem = MenuItemImage::create(
		"CloseNormal.png",
		"CloseSelected.png",
		CC_CALLBACK_1(Tetris::menuCloseCallback, this));

	closeItem->setPosition(Vec2(origin.x + visibleSize.width - closeItem->getContentSize().width / 2,
		origin.y + closeItem->getContentSize().height / 2));

	// create menu, it's an autorelease object
	auto menu = Menu::create(closeItem, NULL);
	menu->setPosition(Vec2::ZERO);
	this->addChild(menu, 1);

	//画像の配置
	//座標定義
	auto bg = cocos2d::Layer::create();
	bg->setName("bg");
	FramePos = Vec2(512, 378);
	BarPos_Origin = Vec2(200, FramePos.y - 340);
	BarPos_Center = Vec2(BarPos_Origin.x, FramePos.y);
	BarPos_Top = Vec2(BarPos_Origin.x, BarPos_Center.y + 340);
	//BarPos = Vec2(262,378);
	MinoPos = Vec2(MinoPosW, MinoPosH);
	CenterPos = Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y);




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
	bar->setAnchorPoint(Vec2(0, 0));
	bar->setPosition(BarPos_Origin);
	bg->addChild(bar);

	//トーン
	auto tone = Sprite::create("tone.png");
	//tone->setPosition(Vec2(BarPos_Center.x + 50,BarPos_Center.y));
	tone->setPosition(Vec2(BarPos_Top.x + 50, BarPos_Top.y));
	bg->addChild(tone);

	//next文字
	auto next_moji = Sprite::create("NEXTmoji.png");
	next_moji->setPosition(Vec2(BarPos_Top.x + 650, BarPos_Top.y - 50));
	bg->addChild(next_moji);

	//next枠
	auto next = Sprite::create("next2.png");
	next->setPosition(Vec2(BarPos_Top.x + 650, BarPos_Top.y - 200));
	bg->addChild(next);

	//score文字
	auto score_moji = Sprite::create("SCOREmoji.png");
	score_moji->setPosition(Vec2(BarPos_Top.x + 650, BarPos_Top.y - 400));
	bg->addChild(score_moji);

	//score枠
	auto score = Sprite::create("score2.png");
	score->setPosition(Vec2(BarPos_Top.x + 650, BarPos_Top.y - 500));
	bg->addChild(score);

	//mino操作デバッグ
	auto minos = cocos2d::Layer::create();
	minos->setName("minos");


	Tetris::createNewMino(minos);




	this->addChild(bg);

	this->addChild(minos);


	return true;
}

void Tetris::createNewMino(Node* minos, int randShape, int direction,bool rotate) {

	//int randShape = rand() % 7+1;
	shape = randShape;
	this->direction = direction;
	if (!rotate) {
		targetposx = 4;
		targetposy = 0;
	}
	auto FramePos = Vec2(MinoPosW, MinoPosH);
	auto target = cocos2d::Layer::create();
	target->setName("target");
	switch (randShape) {
	case Mino::kShape_t:

		switch (direction) {
		case 0:
			newMino(target, randShape, Vec2(0, 0));
			newMino(target, randShape, Vec2(-MINO_SQ, -MINO_SQ));
			newMino(target, randShape, Vec2(0, -MINO_SQ));
			newMino(target, randShape, Vec2(MINO_SQ, -MINO_SQ));

			//minoexpand[0] = { 0,0 };
			//minoexpand[1] = { -1,1 };
			//minoexpand[2] = { 0,1 };
			//minoexpand[3] = { 1,1 };
			 positionCheckArray(minoexpand ,randShape, direction);
			break;
		case 1:
			newMino(target, randShape, Vec2(0, 0));
			newMino(target, randShape, Vec2(0, -MINO_SQ));
			newMino(target, randShape, Vec2(0, -2 * MINO_SQ));
			newMino(target, randShape, Vec2(MINO_SQ, -MINO_SQ));

			/*minoexpand[0] = { 0,0 };
			minoexpand[1] = { 0,1 };
			minoexpand[2] = { 0 ,2 };
			minoexpand[3] = { 1 ,1 };*/
			  positionCheckArray(minoexpand ,randShape, direction);
			break;

		case 2:
			newMino(target, randShape, Vec2(0, 0));
			newMino(target, randShape, Vec2(-MINO_SQ, 0));
			newMino(target, randShape, Vec2(MINO_SQ, 0));
			newMino(target, randShape, Vec2(0, -MINO_SQ));

			/*minoexpand[0] = { 0,0 };
			minoexpand[1] = { -1,0 };
			minoexpand[2] = { 1 ,0 };
			minoexpand[3] = { 0 ,1 };*/
			  positionCheckArray(minoexpand ,randShape, direction);
			break;
		case 3:
			newMino(target, randShape, Vec2(0, 0));
			newMino(target, randShape, Vec2(0, -MINO_SQ));
			newMino(target, randShape, Vec2(-MINO_SQ, -MINO_SQ));
			newMino(target, randShape, Vec2(0, -2 * MINO_SQ));

			/*minoexpand[0] = { 0,0 };
			minoexpand[1] = { 0,1 };
			minoexpand[2] = { -1 ,1 };
			minoexpand[3] = { 0 ,2 };*/
			  positionCheckArray(minoexpand ,randShape, direction);
			break;


		}

		break;

	case Mino::kShape_i:
		switch (direction) {
		case 0:
		case 2:
			newMino(target, randShape, Vec2(0, 0));
			newMino(target, randShape, Vec2(0, -MINO_SQ));
			newMino(target, randShape, Vec2(0, -2 * MINO_SQ));
			newMino(target, randShape, Vec2(0, -3 * MINO_SQ));
			/*minoexpand[0] = { 0,0 };
			minoexpand[1] = { 0,1 };
			minoexpand[2] = { 0,2 };
			minoexpand[3] = { 0,3 };*/
			  positionCheckArray(minoexpand ,randShape, direction);
			break;
		case 1:
		case 3:
			newMino(target, randShape, Vec2(0, 0));
			newMino(target, randShape, Vec2(-MINO_SQ, 0));
			newMino(target, randShape, Vec2(1 * MINO_SQ, 0));
			newMino(target, randShape, Vec2(2 * MINO_SQ, 0));
			/*minoexpand[0] = { 0,0 };
			minoexpand[1] = { -1,0 };
			minoexpand[2] = { 1,0 };
			minoexpand[3] = { 2,0 };*/
			  positionCheckArray(minoexpand ,randShape, direction);

			break;
		}
		break;

	case Mino::kShape_l:
		switch (direction) {
		case 0:
			newMino(target, randShape, Vec2(0, 0));
			newMino(target, randShape, Vec2(0, -MINO_SQ));
			newMino(target, randShape, Vec2(0, -2 * MINO_SQ));
			newMino(target, randShape, Vec2(MINO_SQ, -2 * MINO_SQ));
			/*minoexpand[0] = { 0,0 };
			minoexpand[1] = { 0,1 };
			minoexpand[2] = { 0,2 };
			minoexpand[3] = { 1,2 };*/
			  positionCheckArray(minoexpand ,randShape, direction);
			break;
		case 1:
			newMino(target, randShape, Vec2(0, 0));
			newMino(target, randShape, Vec2(-MINO_SQ, 0));
			newMino(target, randShape, Vec2(-MINO_SQ, -MINO_SQ));
			newMino(target, randShape, Vec2(MINO_SQ, 0));
			//minoexpand[0] = { 0,0 };
			//minoexpand[1] = { -1,0 };
			//minoexpand[2] = { -1,1 };
			//minoexpand[3] = { 1,0 };
			  positionCheckArray(minoexpand ,randShape, direction);

			break;
		case 2:
			newMino(target, randShape, Vec2(0, 0));
			newMino(target, randShape, Vec2(-MINO_SQ, 0));
			newMino(target, randShape, Vec2(0, -MINO_SQ));
			newMino(target, randShape, Vec2(0, -2 * MINO_SQ));
			//minoexpand[0] = { 0,0 };
			//minoexpand[1] = { -1,0 };
			//minoexpand[2] = { 0,1 };
			//minoexpand[3] = { 0,2 };
			  positionCheckArray(minoexpand ,randShape, direction);

			break;
		case 3:
			newMino(target, randShape, Vec2(MINO_SQ, 0));
			newMino(target, randShape, Vec2(MINO_SQ, -MINO_SQ));
			newMino(target, randShape, Vec2(0, -MINO_SQ));
			newMino(target, randShape, Vec2(-MINO_SQ, -MINO_SQ));
			//minoexpand[0] = { 1,0 };
			//minoexpand[1] = { 1,1 };
			//minoexpand[2] = { 0,1 };
			//minoexpand[3] = { -1,1 };
			  positionCheckArray(minoexpand ,randShape, direction);

			break;

		}

		break;

	case Mino::kShape_rl:
		switch (direction) {
		case 0:
			newMino(target, randShape, Vec2(0, 0));
			newMino(target, randShape, Vec2(0, -MINO_SQ));
			newMino(target, randShape, Vec2(0, -2 * MINO_SQ));
			newMino(target, randShape, Vec2(-MINO_SQ, -2 * MINO_SQ));
			//minoexpand[0] = { 0,0 };
			//minoexpand[1] = { 0,1 };
			//minoexpand[2] = { 0,2 };
			//minoexpand[3] = { -1,2 };
			  positionCheckArray(minoexpand ,randShape, direction);
			break;

		case 1:
			newMino(target, randShape, Vec2(-MINO_SQ, 0));
			newMino(target, randShape, Vec2(-MINO_SQ, -MINO_SQ));
			newMino(target, randShape, Vec2(0, -MINO_SQ));
			newMino(target, randShape, Vec2(MINO_SQ, -MINO_SQ));
			//minoexpand[0] = { -1,0 };
			//minoexpand[1] = { -1,1 };
			//minoexpand[2] = { 0,1 };
			//minoexpand[3] = { 1,1 };
			  positionCheckArray(minoexpand ,randShape, direction);

			break;

		case 2:
			newMino(target, randShape, Vec2(0, 0));
			newMino(target, randShape, Vec2(MINO_SQ, 0));
			newMino(target, randShape, Vec2(0, -MINO_SQ));
			newMino(target, randShape, Vec2(0, -2 * MINO_SQ));
			//minoexpand[0] = { 0,0 };
			//minoexpand[1] = { 1,0 };
			//minoexpand[2] = { 0,1 };
			//minoexpand[3] = { 0,2 };
			  positionCheckArray(minoexpand ,randShape, direction);

			break;
		case 3:
			newMino(target, randShape, Vec2(0, 0));
			newMino(target, randShape, Vec2(-MINO_SQ, 0));
			newMino(target, randShape, Vec2(MINO_SQ, -MINO_SQ));
			newMino(target, randShape, Vec2(MINO_SQ, 0));
			/*minoexpand[0] = { 0,0 };
			minoexpand[1] = { -1,0 };
			minoexpand[2] = { 1,1 };
			minoexpand[3] = { 1,0 };
*/
			  positionCheckArray(minoexpand ,randShape, direction);

			break;

		}

		break;

	case Mino::kShape_o:

		newMino(target, randShape, Vec2(0, 0));
		newMino(target, randShape, Vec2(MINO_SQ, 0));
		newMino(target, randShape, Vec2(0, -MINO_SQ));
		newMino(target, randShape, Vec2(MINO_SQ, -MINO_SQ));
	/*	minoexpand[0] = { 0,0 };
		minoexpand[1] = { 1,0 };
		minoexpand[2] = { 0,1 };
		minoexpand[3] = { 1,1 };*/
		  positionCheckArray(minoexpand ,randShape, direction);


		break;
	case Mino::kShape_z:

		switch (direction) {
		case 0:
		case 2:
			newMino(target, randShape, Vec2(0, 0));
			newMino(target, randShape, Vec2(-MINO_SQ, 0));
			newMino(target, randShape, Vec2(0, -MINO_SQ));
			newMino(target, randShape, Vec2(MINO_SQ, -MINO_SQ));

			/*minoexpand[0] = { 0,0 };
			minoexpand[1] = { -1,0 };
			minoexpand[2] = { 0,1 };
			minoexpand[3] = { 1,1 };*/
			  positionCheckArray(minoexpand ,randShape, direction);

			break;
		case 1:
		case 3:
			newMino(target, randShape, Vec2(MINO_SQ, 0));
			newMino(target, randShape, Vec2(MINO_SQ, -MINO_SQ));
			newMino(target, randShape, Vec2(0, -MINO_SQ));
			newMino(target, randShape, Vec2(0, -2 * MINO_SQ));
			//minoexpand[0] = { 1,0 };
			//minoexpand[1] = { 1,1 };
			//minoexpand[2] = { 0,1 };
			//minoexpand[3] = { 0,2 };
			  positionCheckArray(minoexpand ,randShape, direction);

			break;
		}

		break;

	case Mino::kShape_rz:
		switch (direction) {
		case 0:
		case 2:
			newMino(target, randShape, Vec2(0, 0));
			newMino(target, randShape, Vec2(MINO_SQ, 0));
			newMino(target, randShape, Vec2(0, -MINO_SQ));
			newMino(target, randShape, Vec2(-MINO_SQ, -MINO_SQ));
			//minoexpand[0] = { 0,0 };
			//minoexpand[1] = { 1, 0 };
			//minoexpand[2] = { 0,1 };
			//minoexpand[3] = { -1,1 };
			  positionCheckArray(minoexpand ,randShape, direction);
			break;
		case 1:
		case 3:
			newMino(target, randShape, Vec2(-MINO_SQ, 0));
			newMino(target, randShape, Vec2(-MINO_SQ, -MINO_SQ));
			newMino(target, randShape, Vec2(0, -MINO_SQ));
			newMino(target, randShape, Vec2(0, -2 * MINO_SQ));
			//minoexpand[0] = { -1,0 };
			//minoexpand[1] = { -1,1 };
			//minoexpand[2] = { 0,1 };
			//minoexpand[3] = { 0,2 };
			  positionCheckArray(minoexpand ,randShape, direction);
			break;
		}
		break;

	}
	minos->addChild(target);
}
void Tetris::newMino(Node* target, int color, Vec2 pos) {

	Sprite* targetmino;
	targetcolor = color;
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
	targetmino->setPosition(Vec2(MinoPosW, MinoPosH) + pos);
	target->addChild(targetmino);
}

void Tetris::rotateMino(Node* minos) {
	//Node* minos, int randShape, int direction, bool rotate


	if (targetposx > 0 && targetposx < WIDTH_GRIDX - 1) {
		if ((targetposx >= WIDTH_GRIDX - 2) && (shape == Mino::kShape_i) && (direction == 0 || direction == 2)) {
			return;
		}
		else {
			conponent tempmino[4];
			positionCheckArray(tempmino,shape,(direction+1)%4);
			for (int i = 0; i < (int)(sizeof(tempmino) / sizeof(conponent)); i++) {
				if (bode[tempmino[i].cposy + targetposy][tempmino[i].cposx+targetposx]>0) {
					return;
				}
			}

		}
	
	}
	else { return; }

	Vec2 temppos= minos->getChildByName("target")->getPosition();
	minos->removeChildByName("target");
	createNewMino(minos,shape,(direction+1)%4,true);
	minos->getChildByName("target")->setPosition(temppos);
}

Tetris::conponent* Tetris::positionCheckArray(conponent* minoexist,int shape,int direction)
{
	

	switch (shape) {
	case Mino::kShape_t:

		switch (direction) {
		case 0:
			
			minoexist[0] = { 0,0 };
			minoexist[1] = { -1,1 };
			minoexist[2] = { 0,1 };
			minoexist[3] = { 1,1 };

			break;
		case 1:
			
			minoexist[0] = { 0,0 };
			minoexist[1] = { 0,1 };
			minoexist[2] = { 0 ,2 };
			minoexist[3] = { 1 ,1 };

			break;

		case 2:
			

			minoexist[0] = { 0,0 };
			minoexist[1] = { -1,0 };
			minoexist[2] = { 1 ,0 };
			minoexist[3] = { 0 ,1 };

			break;
		case 3:
			

			minoexist[0] = { 0,0 };
			minoexist[1] = { 0,1 };
			minoexist[2] = { -1 ,1 };
			minoexist[3] = { 0 ,2 };

			break;


		}

		break;

	case Mino::kShape_i:
		switch (direction) {
		case 0:
		case 2:
			
			minoexist[0] = { 0,0 };
			minoexist[1] = { 0,1 };
			minoexist[2] = { 0,2 };
			minoexist[3] = { 0,3 };
			break;
		case 1:
		case 3:
			
			minoexist[0] = { 0,0 };
			minoexist[1] = { -1,0 };
			minoexist[2] = { 1,0 };
			minoexist[3] = { 2,0 };


			break;
		}
		break;

	case Mino::kShape_l:
		switch (direction) {
		case 0:
	
			minoexist[0] = { 0,0 };
			minoexist[1] = { 0,1 };
			minoexist[2] = { 0,2 };
			minoexist[3] = { 1,2 };
			break;
		case 1:
			
			minoexist[0] = { 0,0 };
			minoexist[1] = { -1,0 };
			minoexist[2] = { -1,1 };
			minoexist[3] = { 1,0 };

			break;
		case 2:
		
			minoexist[0] = { 0,0 };
			minoexist[1] = { -1,0 };
			minoexist[2] = { 0,1 };
			minoexist[3] = { 0,2 };

			break;
		case 3:
			
			minoexist[0] = { 1,0 };
			minoexist[1] = { 1,1 };
			minoexist[2] = { 0,1 };
			minoexist[3] = { -1,1 };

			break;

		}

		break;

	case Mino::kShape_rl:
		switch (direction) {
		case 0:
		
			minoexist[0] = { 0,0 };
			minoexist[1] = { 0,1 };
			minoexist[2] = { 0,2 };
			minoexist[3] = { -1,2 };
			break;

		case 1:
			
			minoexist[0] = { -1,0 };
			minoexist[1] = { -1,1 };
			minoexist[2] = { 0,1 };
			minoexist[3] = { 1,1 };

			break;

		case 2:
			
			minoexist[0] = { 0,0 };
			minoexist[1] = { 1,0 };
			minoexist[2] = { 0,1 };
			minoexist[3] = { 0,2 };

			break;
		case 3:
			
			minoexist[0] = { 0,0 };
			minoexist[1] = { -1,0 };
			minoexist[2] = { 1,1 };
			minoexist[3] = { 1,0 };

			break;

		}

		break;

	case Mino::kShape_o:

		
		minoexist[0] = { 0,0 };
		minoexist[1] = { 1,0 };
		minoexist[2] = { 0,1 };
		minoexist[3] = { 1,1 };


		break;
	case Mino::kShape_z:

		switch (direction) {
		case 0:
		case 2:
			
			minoexist[0] = { 0,0 };
			minoexist[1] = { -1,0 };
			minoexist[2] = { 0,1 };
			minoexist[3] = { 1,1 };
			break;
		case 1:
		case 3:
			
			minoexist[0] = { 1,0 };
			minoexist[1] = { 1,1 };
			minoexist[2] = { 0,1 };
			minoexist[3] = { 0,2 };
			break;
		}

		break;

	case Mino::kShape_rz:
		switch (direction) {
		case 0:
		case 2:
			
			minoexist[0] = { 0,0 };
			minoexist[1] = { 1, 0 };
			minoexist[2] = { 0,1 };
			minoexist[3] = { -1,1 };
			break;
		case 1:
		case 3:
			
			minoexist[0] = { -1,0 };
			minoexist[1] = { -1,1 };
			minoexist[2] = { 0,1 };
			minoexist[3] = { 0,2 };
			break;
		}
		break;

	}
	return minoexist;
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