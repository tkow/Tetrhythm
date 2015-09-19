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


//¶‚ÉˆÚ“®
void Tetris::move_left(){
	if (posx - 1 >= 0){
		bode[posy][posx] = nothing;
		posx--;
	}
	bode[posy][posx] = mino;
}

//‰E‚ÉˆÚ“®
void Tetris::move_right(){
	if (posx + 1 < 12){
		bode[posy][posx] = nothing;
		posx++;
	}
	bode[posy][posx] = mino;
}

//‰º‚ÉˆÚ“®
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

//Á‹Ž”»’è
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

// on "init" you need to initialize your instance
bool Tetris::init()
{
	//////////////////////////////
	// 1. super init first
	if (!Layer::init())
	{
		return false;
	}

	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	/////////////////////////////
	// 2. add a menu item with "X" image, which is clicked to quit the program
	//    you may modify it.

	// add a "close" icon to exit the progress. it's an autorelease object
	/*auto closeItem = MenuItemImage::create(
		"CloseNormal.png",
		"CloseSelected.png",
		CC_CALLBACK_1(Tetris::menuCloseCallback, this));

	closeItem->setPosition(Vec2(origin.x + visibleSize.width - closeItem->getContentSize().width / 2,
		origin.y + closeItem->getContentSize().height / 2));
*/
	// create menu, it's an autorelease object
	//auto menu = Menu::create(closeItem, NULL);
	//menu->setPosition(Vec2::ZERO);
	//this->addChild(menu, 1);

	/////////////////////////////
	// 3. add your codes below...

	// add a label shows "Hello World"
	// create and initialize a label

	//auto label = Label::createWithTTF("Hello World", "fonts/Marker Felt.ttf", 24);

	//// position the label on the center of the screen
	//label->setPosition(Vec2(origin.x + visibleSize.width / 2,
	//	origin.y + visibleSize.height - label->getContentSize().height));

	//// add the label as a child to this layer
	//this->addChild(label, 1);

	// add "Tetris" splash screen"
	//auto sprite = Sprite::create("pink.png");

	// position the sprite on the center of the screen
	//sprite->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));

	//// add the sprite as a child to this layer
	//this->addChild(sprite, 0);




	return true;
}



bool Tetris::isKeyPressed(EventKeyboard::KeyCode code) {
	// Check if the key is currently pressed by seeing it it's in the std::map keys
	// In retrospect, keys is a terrible name for a key/value paried datatype isnt it?
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
	// Register an update function that checks to see if the CTRL key is pressed
	// and if it is displays how long, otherwise tell the user to press it
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
// Because cocos2d-x requres createScene to be static, we need to make other non-pointer members static




void Tetris::menuCloseCallback(Ref* pSender)
{
	Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	exit(0);
#endif
}

std::map<cocos2d::EventKeyboard::KeyCode,
	std::chrono::high_resolution_clock::time_point> Tetris::keys;