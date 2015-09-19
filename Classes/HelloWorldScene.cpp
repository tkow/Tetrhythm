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

    label = cocos2d::Label::createWithSystemFont("Press the CTRL Key","Arial",32);
    label->setPosition(this->getBoundingBox().getMidX(),this->getBoundingBox().getMidY());
    addChild(label);
    auto eventListener = EventListenerKeyboard::create();

    Director::getInstance()->getOpenGLView()->setIMEKeyboardState(true);
    eventListener->onKeyPressed = [=](EventKeyboard::KeyCode keyCode, Event* event){
        // If a key already exists, do nothing as it will already have a time stamp
        // Otherwise, set's the timestamp to now
        if(keys.find(keyCode) == keys.end()){
            keys[keyCode] = std::chrono::high_resolution_clock::now();
        }
    };
    eventListener->onKeyReleased = [=](EventKeyboard::KeyCode keyCode, Event* event){
        // remove the key.  std::map.erase() doesn't care if the key doesnt exist
        keys.erase(keyCode);
    };

    this->_eventDispatcher->addEventListenerWithSceneGraphPriority(eventListener,this);

    // Let cocos know we have an update function to be called.
    // No worries, ill cover this in more detail later on
    this->scheduleUpdate();
    return true;
}


bool HelloWorld::isKeyPressed(EventKeyboard::KeyCode code) {
    // Check if the key is currently pressed by seeing it it's in the std::map keys
    // In retrospect, keys is a terrible name for a key/value paried datatype isnt it?
    if(keys.find(code) != keys.end())
        return true;
    return false;
}

// double HelloWorld::keyPressedDuration(EventKeyboard::KeyCode code) {
//     if(!isKeyPressed(EventKeyboard::KeyCode::KEY_UP_ARROW))
//         return 0;  // Not pressed, so no duration obviously
//
//     // Return the amount of time that has elapsed between now and when the user
//     // first started holding down the key in milliseconds
//     // Obviously the start time is the value we hold in our std::map keys
//     return std::chrono::duration_cast<std::chrono::milliseconds>
//             (std::chrono::high_resolution_clock::now() - keys[code]).count();
// }

void HelloWorld::update(float delta) {
    // Register an update function that checks to see if the CTRL key is pressed
    // and if it is displays how long, otherwise tell the user to press it
    Node::update(delta);
    if(isKeyPressed(EventKeyboard::KeyCode::KEY_UP_ARROW)) {
        std::stringstream ss;
        ss << "UP key has been pressed";
        label->setString(ss.str().c_str());
    } else
    if(isKeyPressed(EventKeyboard::KeyCode::KEY_DOWN_ARROW)) {
        std::stringstream ss;
        ss << "DOWN key has been pressed";
        label->setString(ss.str().c_str());
    } else
    if(isKeyPressed(EventKeyboard::KeyCode::KEY_LEFT_ARROW)) {
        std::stringstream ss;
        ss << "LEFT key has been pressed";
        label->setString(ss.str().c_str());
    } else
    if(isKeyPressed(EventKeyboard::KeyCode::KEY_RIGHT_ARROW)) {
        std::stringstream ss;
        ss << "RIGHT key has been pressed";
        label->setString(ss.str().c_str());
    } else {
        label->setString("Press the CTRL Key");
    }
}
// Because cocos2d-x requres createScene to be static, we need to make other non-pointer members static
std::map<cocos2d::EventKeyboard::KeyCode,
        std::chrono::high_resolution_clock::time_point> HelloWorld::keys;
