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



void Tetris::initRoutine(conponent minoroutine[7]) {
	for (int i = 0; i < 7; i++) {
		minoroutine[i] = { i + 1,  rand() % 4 };
	}
	for (int mix = 0; mix < 100; mix++) {
		int indexi = rand() % 7;
		int indexj = rand() % 7;
		if (indexi != indexj) {
			auto temp = minoroutine[indexi];
			minoroutine[indexi] = minoroutine[indexj];
			minoroutine[indexj] = temp;
		}
	}
}

//ç∂Ç…à⁄ìÆ
bool Tetris::move_left() {

	for (int i = 0; i < 4; i++) {

		if (targetposx + minoexpand[i].cposx <= 0 || bode[targetposy + minoexpand[i].cposy][targetposx + minoexpand[i].cposx - 1]>0) {
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

		if (targetposx + minoexpand[i].cposx >= WIDTH_GRIDX - 1 || bode[targetposy + minoexpand[i].cposy][targetposx + minoexpand[i].cposx + 1]>0) {
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


void Tetris::lineAdd() {

	int hole=rand()%WIDTH_GRIDX;
	auto minos = this->getChildByName("minos");
	for (int y = 0; y < WIDTH_GRIDY; y++) {
		for (int x = 0; x < WIDTH_GRIDX; x++) {
			if (bode[y+1][x] > 0 &&y!= WIDTH_GRIDY-1) {
				bode[y][x] = bode[y+1][x];
				bode[y + 1][x] = 0;
				minos->removeChildByTag(y*WIDTH_GRIDX + x);

				//if (getChildByTag((y + 1)*WIDTH_GRIDX + x) != nullptr) {
					auto movec = minos->getChildByTag((y + 1)*WIDTH_GRIDX + x);
					movec->runAction(MoveBy::create(0, Vec2(0, 33)));
					movec->setTag((y)*WIDTH_GRIDX + x);
				//}
			}
			if (y == WIDTH_GRIDY - 1) {
				if (x!=hole) {
					bode[y][x] = Mino::yellow;
					auto tempos = Vec2(MinoPosBottomLX+x*MINO_SQ, MinoPosBottomLY);
					auto newmino = Sprite::create("./mino/yellow.png");
					newmino->setPosition(tempos);
					newmino->setTag(y*WIDTH_GRIDX + x);
					minos->addChild(newmino);
				}
				else {
					bode[y][x] = 0;
				}
			}
			
		}
	}
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
	//srand((unsigned int)time(NULL));
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
			

			
	
			auto target = static_cast<Sprite*>(keyEvent->getCurrentTarget());
			auto utonepos=target->getChildByName("bg")->getChildByName("uptone")->getPosition();
			//auto dtonepos = target->getChildByName("bg")->getChildByName("downtone")->getPosition();

			if ( std::abs(utonepos.y-378) <= 66) {
		    evalgood = true;

			auto good=target->getChildByName("bg")->getChildByName("good");
			good->setVisible(true);
			good->runAction(Sequence::create( FadeIn::create(0.2f), FadeOut::create(0.5f),nullptr));
			}
			else {
				auto bad = target->getChildByName("bg")->getChildByName("bad");
				bad->setVisible(true);
				bad->runAction(Sequence::create(FadeIn::create(0.2f), FadeOut::create(0.5f), nullptr));
				lineAdd();
				return;
			}

			if (!Tetris::move_left()) { return; }


			auto targetmino = target->getChildByName("minos")->getChildByName("target");
			auto moveTo = MoveBy::create(0, Vec2(-33, 0));
			targetmino->runAction(moveTo);
		}
		else if (keyCode == cocos2d::EventKeyboard::KeyCode::KEY_RIGHT_ARROW)
		{


			auto target = static_cast<Sprite*>(keyEvent->getCurrentTarget());
			auto utonepos = target->getChildByName("bg")->getChildByName("uptone")->getPosition();
			//auto dtonepos = target->getChildByName("bg")->getChildByName("downtone")->getPosition();

			if (std::abs(utonepos.y - 378) <= 66) {
				evalgood = true;

				auto good = target->getChildByName("bg")->getChildByName("good");
				good->setVisible(true);
				good->runAction(Sequence::create(FadeIn::create(0.2f), FadeOut::create(0.5f), nullptr));
			}
			else {
				auto bad = target->getChildByName("bg")->getChildByName("bad");
				bad->setVisible(true);
				bad->runAction(Sequence::create(FadeIn::create(0.2f), FadeOut::create(0.5f), nullptr));
				lineAdd();
				return;
			}

			if (!Tetris::move_right()) { return; }
			//auto target = static_cast<Sprite*>(keyEvent->getCurrentTarget());
			auto targetmino = target->getChildByName("minos")->getChildByName("target");
			auto moveTo = MoveBy::create(0, Vec2(33, 0));
			targetmino->runAction(moveTo);
		}
		else if (keyCode == cocos2d::EventKeyboard::KeyCode::KEY_UP_ARROW)
		{


			auto target = static_cast<Sprite*>(keyEvent->getCurrentTarget());
			auto utonepos = target->getChildByName("bg")->getChildByName("uptone")->getPosition();
			//auto dtonepos = target->getChildByName("bg")->getChildByName("downtone")->getPosition();

			if (std::abs(utonepos.y - 378) <= 66) {
				evalgood = true;

				auto good = target->getChildByName("bg")->getChildByName("good");
				good->setVisible(true);
				good->runAction(Sequence::create(FadeIn::create(0.2f), FadeOut::create(0.5f), nullptr));
			}
			else {
				auto bad = target->getChildByName("bg")->getChildByName("bad");
				bad->setVisible(true);
				bad->runAction(Sequence::create(FadeIn::create(0.2f), FadeOut::create(0.5f), nullptr));
				lineAdd();
				return;
			}

			//auto target = static_cast<Sprite*>(keyEvent->getCurrentTarget());
			auto targetminos = target->getChildByName("minos");
			
			rotateMino(targetminos);
			
		}
		else if (keyCode == cocos2d::EventKeyboard::KeyCode::KEY_DOWN_ARROW)
		{

			auto target = static_cast<Sprite*>(keyEvent->getCurrentTarget());
			auto utonepos = target->getChildByName("bg")->getChildByName("uptone")->getPosition();
			//auto dtonepos = target->getChildByName("bg")->getChildByName("downtone")->getPosition();

			if (std::abs(utonepos.y - 378) <= 66) {
				evalgood = true;

				auto good = target->getChildByName("bg")->getChildByName("good");
				good->setVisible(true);
				good->runAction(Sequence::create(FadeIn::create(0.2f), FadeOut::create(0.5f), nullptr));
			}
			else {
				auto bad = target->getChildByName("bg")->getChildByName("bad");
				bad->setVisible(true);
				bad->runAction(Sequence::create(FadeIn::create(0.2f), FadeOut::create(0.5f), nullptr));
				lineAdd();
				return;
			}

			//auto target = static_cast<Sprite*>(keyEvent->getCurrentTarget());
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
			createNewMino(targetminos,minoexpand ,minoroutine[routineindex].cposx, minoroutine[routineindex].cposy);



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
	auto uptone = Sprite::create("tone.png");
	uptone->setPosition(Vec2(BarPos_Top.x + 50, BarPos_Top.y));
	uptone->runAction(RepeatForever::create(Sequence::create(MoveTo::create(0, Vec2(BarPos_Top.x + 50, BarPos_Top.y)), MoveTo::create(0.5f, Vec2(BarPos_Center.x + 50, BarPos_Center.y)), DelayTime::create(0.1f), CallFunc::create([this]() {if (!evalgood) {
		auto bad = this->getChildByName("bg")->getChildByName("bad");
		bad->setVisible(true);
		bad->runAction(Sequence::create(FadeIn::create(0.2f), FadeOut::create(0.5f), nullptr));
		lineAdd();
	}  evalgood = false;  }), nullptr)));
	uptone->setName("uptone");
	bg->addChild(uptone);
	

	auto downtone = Sprite::create("tone.png");
	downtone->setName("downtone");
	downtone->setPosition(Vec2(BarPos_Origin.x + 50, BarPos_Origin.y));

	downtone->runAction(RepeatForever::create(Sequence::create(MoveTo::create(0, Vec2(BarPos_Origin.x + 50, BarPos_Origin.y)), MoveTo::create(0.5f, Vec2(BarPos_Center.x + 50, BarPos_Center.y)), DelayTime::create(0.1f), nullptr)));

	bg->addChild(downtone);
	//eval文字

	auto good = Sprite::create("./GOOD.png");
	good->setName("good");
	good->setPosition(Vec2 (BarPos_Center.x -100, BarPos_Center.y));
	good->setVisible(false);
	bg->addChild(good);

	auto BAD = Sprite::create("./BAD.png");
	BAD->setName("bad");
	BAD->setPosition(Vec2(BarPos_Center.x - 100, BarPos_Center.y-66));
	BAD->setVisible(false);
	bg->addChild(BAD);


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



	createNewMino(minos,minoexpand,minoroutine[routineindex].cposx, minoroutine[routineindex].cposy);





	this->addChild(bg);

	this->addChild(minos);


	return true;
}

void Tetris::createNewMino(Node* minos, conponent minoex[4], int randShape, int direction, bool rotate,std::string label) {

	//int randShape = rand() % 7+1;
	
	if (rotate) {
		this->direction = direction;
	}

	if (!rotate&&label == "target") {
		targetposx = 4;
		targetposy = 0;
		this->direction = direction;
		shape = randShape;
	}
	auto FramePos = Vec2(MinoPosW, MinoPosH);

	if (label == "nextMino") {
		FramePos = Vec2(NextMinoPosW, NextMinoPosH);
	}

	auto target = cocos2d::Layer::create();
	target->setName(label);
	switch (randShape) {
	case Mino::kShape_t:

		switch (direction) {
		case 0:
			newMino(target, randShape, Vec2(0, 0),FramePos);
			newMino(target, randShape, Vec2(-MINO_SQ, -MINO_SQ),FramePos);
			newMino(target, randShape, Vec2(0, -MINO_SQ),FramePos);
			newMino(target, randShape, Vec2(MINO_SQ, -MINO_SQ),FramePos);

			//minoex[0] = { 0,0 };
			//minoex[1] = { -1,1 };
			//minoex[2] = { 0,1 };
			//minoex[3] = { 1,1 };
			positionCheckArray(minoex, randShape, direction);
			break;
		case 1:
			newMino(target, randShape, Vec2(0, 0),FramePos);
			newMino(target, randShape, Vec2(0, -MINO_SQ),FramePos);
			newMino(target, randShape, Vec2(0, -2 * MINO_SQ),FramePos);
			newMino(target, randShape, Vec2(MINO_SQ, -MINO_SQ),FramePos);

			/*minoex[0] = { 0,0 };
			minoex[1] = { 0,1 };
			minoex[2] = { 0 ,2 };
			minoex[3] = { 1 ,1 };*/
			positionCheckArray(minoex, randShape, direction);
			break;

		case 2:
			newMino(target, randShape, Vec2(0, 0),FramePos);
			newMino(target, randShape, Vec2(-MINO_SQ, 0),FramePos);
			newMino(target, randShape, Vec2(MINO_SQ, 0),FramePos);
			newMino(target, randShape, Vec2(0, -MINO_SQ),FramePos);

			/*minoex[0] = { 0,0 };
			minoex[1] = { -1,0 };
			minoex[2] = { 1 ,0 };
			minoex[3] = { 0 ,1 };*/
			positionCheckArray(minoex, randShape, direction);
			break;
		case 3:
			newMino(target, randShape, Vec2(0, 0),FramePos);
			newMino(target, randShape, Vec2(0, -MINO_SQ),FramePos);
			newMino(target, randShape, Vec2(-MINO_SQ, -MINO_SQ),FramePos);
			newMino(target, randShape, Vec2(0, -2 * MINO_SQ),FramePos);

			/*minoex[0] = { 0,0 };
			minoex[1] = { 0,1 };
			minoex[2] = { -1 ,1 };
			minoex[3] = { 0 ,2 };*/
			positionCheckArray(minoex, randShape, direction);
			break;


		}

		break;

	case Mino::kShape_i:
		switch (direction) {
		case 0:
		case 2:
			if (label == "nextMino") {
				FramePos += Vec2(-MINO_SQ/4, MINO_SQ/2+4);
			}

			newMino(target, randShape, Vec2(0, 0),FramePos);
			newMino(target, randShape, Vec2(0, -MINO_SQ),FramePos);
			newMino(target, randShape, Vec2(0, -2 * MINO_SQ),FramePos);
			newMino(target, randShape, Vec2(0, -3 * MINO_SQ),FramePos);
			/*minoex[0] = { 0,0 };
			minoex[1] = { 0,1 };
			minoex[2] = { 0,2 };
			minoex[3] = { 0,3 };*/
			positionCheckArray(minoex, randShape, direction);
			break;
		case 1:
		case 3:
			if (label == "nextMino") {
			FramePos += Vec2(-MINO_SQ/1.5, -MINO_SQ);
	       }

			newMino(target, randShape, Vec2(0, 0),FramePos);
			newMino(target, randShape, Vec2(-MINO_SQ, 0),FramePos);
			newMino(target, randShape, Vec2(1 * MINO_SQ, 0),FramePos);
			newMino(target, randShape, Vec2(2 * MINO_SQ, 0),FramePos);
			/*minoex[0] = { 0,0 };
			minoex[1] = { -1,0 };
			minoex[2] = { 1,0 };
			minoex[3] = { 2,0 };*/
			positionCheckArray(minoex, randShape, direction);

			break;
		}
		break;

	case Mino::kShape_l:
		switch (direction) {
		case 0:
			newMino(target, randShape, Vec2(0, 0),FramePos);
			newMino(target, randShape, Vec2(0, -MINO_SQ),FramePos);
			newMino(target, randShape, Vec2(0, -2 * MINO_SQ),FramePos);
			newMino(target, randShape, Vec2(MINO_SQ, -2 * MINO_SQ),FramePos);
			/*minoex[0] = { 0,0 };
			minoex[1] = { 0,1 };
			minoex[2] = { 0,2 };
			minoex[3] = { 1,2 };*/
			positionCheckArray(minoex, randShape, direction);
			break;
		case 1:
			newMino(target, randShape, Vec2(0, 0),FramePos);
			newMino(target, randShape, Vec2(-MINO_SQ, 0),FramePos);
			newMino(target, randShape, Vec2(-MINO_SQ, -MINO_SQ),FramePos);
			newMino(target, randShape, Vec2(MINO_SQ, 0),FramePos);
			//minoex[0] = { 0,0 };
			//minoex[1] = { -1,0 };
			//minoex[2] = { -1,1 };
			//minoex[3] = { 1,0 };
			positionCheckArray(minoex, randShape, direction);

			break;
		case 2:
			newMino(target, randShape, Vec2(0, 0),FramePos);
			newMino(target, randShape, Vec2(-MINO_SQ, 0),FramePos);
			newMino(target, randShape, Vec2(0, -MINO_SQ),FramePos);
			newMino(target, randShape, Vec2(0, -2 * MINO_SQ),FramePos);
			//minoex[0] = { 0,0 };
			//minoex[1] = { -1,0 };
			//minoex[2] = { 0,1 };
			//minoex[3] = { 0,2 };
			positionCheckArray(minoex, randShape, direction);

			break;
		case 3:
			newMino(target, randShape, Vec2(MINO_SQ, 0),FramePos);
			newMino(target, randShape, Vec2(MINO_SQ, -MINO_SQ),FramePos);
			newMino(target, randShape, Vec2(0, -MINO_SQ),FramePos);
			newMino(target, randShape, Vec2(-MINO_SQ, -MINO_SQ),FramePos);
			//minoex[0] = { 1,0 };
			//minoex[1] = { 1,1 };
			//minoex[2] = { 0,1 };
			//minoex[3] = { -1,1 };
			positionCheckArray(minoex, randShape, direction);

			break;

		}

		break;

	case Mino::kShape_rl:
		switch (direction) {
		case 0:
			newMino(target, randShape, Vec2(0, 0),FramePos);
			newMino(target, randShape, Vec2(0, -MINO_SQ),FramePos);
			newMino(target, randShape, Vec2(0, -2 * MINO_SQ),FramePos);
			newMino(target, randShape, Vec2(-MINO_SQ, -2 * MINO_SQ),FramePos);
			//minoex[0] = { 0,0 };
			//minoex[1] = { 0,1 };
			//minoex[2] = { 0,2 };
			//minoex[3] = { -1,2 };
			positionCheckArray(minoex, randShape, direction);
			break;

		case 1:
			newMino(target, randShape, Vec2(-MINO_SQ, 0),FramePos);
			newMino(target, randShape, Vec2(-MINO_SQ, -MINO_SQ),FramePos);
			newMino(target, randShape, Vec2(0, -MINO_SQ),FramePos);
			newMino(target, randShape, Vec2(MINO_SQ, -MINO_SQ),FramePos);
			//minoex[0] = { -1,0 };
			//minoex[1] = { -1,1 };
			//minoex[2] = { 0,1 };
			//minoex[3] = { 1,1 };
			positionCheckArray(minoex, randShape, direction);

			break;

		case 2:
			newMino(target, randShape, Vec2(0, 0),FramePos);
			newMino(target, randShape, Vec2(MINO_SQ, 0),FramePos);
			newMino(target, randShape, Vec2(0, -MINO_SQ),FramePos);
			newMino(target, randShape, Vec2(0, -2 * MINO_SQ),FramePos);
			//minoex[0] = { 0,0 };
			//minoex[1] = { 1,0 };
			//minoex[2] = { 0,1 };
			//minoex[3] = { 0,2 };
			positionCheckArray(minoex, randShape, direction);

			break;
		case 3:
			newMino(target, randShape, Vec2(0, 0),FramePos);
			newMino(target, randShape, Vec2(-MINO_SQ, 0),FramePos);
			newMino(target, randShape, Vec2(MINO_SQ, -MINO_SQ),FramePos);
			newMino(target, randShape, Vec2(MINO_SQ, 0),FramePos);
			/*minoex[0] = { 0,0 };
			minoex[1] = { -1,0 };
			minoex[2] = { 1,1 };
			minoex[3] = { 1,0 };
*/
			positionCheckArray(minoex, randShape, direction);

			break;

		}

		break;

	case Mino::kShape_o:
		if (label == "nextMino") {
			FramePos += Vec2(-MINO_SQ/2-3, -MINO_SQ/2 );
		}
		newMino(target, randShape, Vec2(0, 0),FramePos);
		newMino(target, randShape, Vec2(MINO_SQ, 0),FramePos);
		newMino(target, randShape, Vec2(0, -MINO_SQ),FramePos);
		newMino(target, randShape, Vec2(MINO_SQ, -MINO_SQ),FramePos);
		/*	minoex[0] = { 0,0 };
			minoex[1] = { 1,0 };
			minoex[2] = { 0,1 };
			minoex[3] = { 1,1 };*/
		positionCheckArray(minoex, randShape, direction);


		break;
	case Mino::kShape_z:

		switch (direction) {
		case 0:
		case 2:
			newMino(target, randShape, Vec2(0, 0),FramePos);
			newMino(target, randShape, Vec2(-MINO_SQ, 0),FramePos);
			newMino(target, randShape, Vec2(0, -MINO_SQ),FramePos);
			newMino(target, randShape, Vec2(MINO_SQ, -MINO_SQ),FramePos);

			/*minoex[0] = { 0,0 };
			minoex[1] = { -1,0 };
			minoex[2] = { 0,1 };
			minoex[3] = { 1,1 };*/
			positionCheckArray(minoex, randShape, direction);

			break;
		case 1:
		case 3:
			newMino(target, randShape, Vec2(MINO_SQ, 0),FramePos);
			newMino(target, randShape, Vec2(MINO_SQ, -MINO_SQ),FramePos);
			newMino(target, randShape, Vec2(0, -MINO_SQ),FramePos);
			newMino(target, randShape, Vec2(0, -2 * MINO_SQ),FramePos);
			//minoex[0] = { 1,0 };
			//minoex[1] = { 1,1 };
			//minoex[2] = { 0,1 };
			//minoex[3] = { 0,2 };
			positionCheckArray(minoex, randShape, direction);

			break;
		}

		break;

	case Mino::kShape_rz:
		switch (direction) {
		case 0:
		case 2:
			newMino(target, randShape, Vec2(0, 0),FramePos);
			newMino(target, randShape, Vec2(MINO_SQ, 0),FramePos);
			newMino(target, randShape, Vec2(0, -MINO_SQ),FramePos);
			newMino(target, randShape, Vec2(-MINO_SQ, -MINO_SQ),FramePos);
			//minoex[0] = { 0,0 };
			//minoex[1] = { 1, 0 };
			//minoex[2] = { 0,1 };
			//minoex[3] = { -1,1 };
			positionCheckArray(minoex, randShape, direction);
			break;
		case 1:
		case 3:
			newMino(target, randShape, Vec2(-MINO_SQ, 0),FramePos);
			newMino(target, randShape, Vec2(-MINO_SQ, -MINO_SQ),FramePos);
			newMino(target, randShape, Vec2(0, -MINO_SQ),FramePos);
			newMino(target, randShape, Vec2(0, -2 * MINO_SQ),FramePos);
			//minoex[0] = { -1,0 };
			//minoex[1] = { -1,1 };
			//minoex[2] = { 0,1 };
			//minoex[3] = { 0,2 };
			positionCheckArray(minoex, randShape, direction);
			break;
		}
		break;

	}
	minos->addChild(target);
	if (!rotate) {
		
		
		if (label == "target") {
			routineindex = (routineindex + 1) % 7;
			if (routineindex == 0) { initRoutine(minoroutine); }
			nextMino(minos);
		}
	}
}
void Tetris::newMino(Node* target, int color, Vec2 posadd, Vec2 posbase) {

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
	targetmino->setPosition(posbase + posadd);
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
			positionCheckArray(tempmino, shape, (direction + 1) % 4);
			for (int i = 0; i < (int)(sizeof(tempmino) / sizeof(conponent)); i++) {
				if (bode[tempmino[i].cposy + targetposy][tempmino[i].cposx + targetposx]>0) {
					return;
				}
			}

		}

	}
	else { return; }

	Vec2 temppos = minos->getChildByName("target")->getPosition();
	minos->removeChildByName("target");
	createNewMino(minos,minoexpand,shape, (direction + 1) % 4, true);
	minos->getChildByName("target")->setPosition(temppos);
}

//void Tetris::nextMino(conponent* nmino, int shape,int direction) {
void Tetris::nextMino(Node* minos) {
	/*conponent* nextmino;
*/
	/*try {}
	catch(Exception){}*/
	conponent nextexpand[4];
	minos->removeChildByName("nextMino");
	createNewMino(minos,nextexpand ,minoroutine[(routineindex ) % 7].cposx, minoroutine[(routineindex ) % 7].cposy, false, "nextMino");
	/*positionCheckArray(nextmino,  shape, direction);*/

	
}

Tetris::conponent* Tetris::positionCheckArray(conponent* minoexist, int shape, int direction)
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