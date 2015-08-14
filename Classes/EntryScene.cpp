#include "EntryScene.h"

USING_NS_CC;

Scene* EntrySceneMainLayer::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
	auto layer = EntrySceneMainLayer::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool EntrySceneMainLayer::init()
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
										   CC_CALLBACK_1(EntrySceneMainLayer::menuCloseCallback, this));
    
	closeItem->setPosition(Vec2(origin.x + visibleSize.width - closeItem->getContentSize().width/2 ,
                                origin.y + closeItem->getContentSize().height/2));

    // create menu, it's an autorelease object
    auto menu = Menu::create(closeItem, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);

    /////////////////////////////
    // 3. add your codes below...

    // add a label shows "Hello World"
    // create and initialize a label
    
    auto label = Label::createWithTTF("Cocos2d-X", "fonts/Marker Felt.ttf", 24);
    
    // position the label on the center of the screen
    label->setPosition(Vec2(origin.x + visibleSize.width/2,
                            origin.y + visibleSize.height - label->getContentSize().height));

    // add the label as a child to this layer
    this->addChild(label, 1);

    // add "HelloWorld" splash screen"
    auto sprite = Sprite::create("HelloWorld.png");

    // position the sprite on the center of the screen
    sprite->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));

    // add the sprite as a child to this layer
	this->addChild(sprite, 0);

	EventListenerKeyboard *keyListener = EventListenerKeyboard::create();
	keyListener->onKeyPressed = CC_CALLBACK_2(EntrySceneMainLayer::onKeyPressed, this);
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(keyListener, this);

	EventListenerTouchOneByOne *touchListener = EventListenerTouchOneByOne::create();
	touchListener->setSwallowTouches(true);
	touchListener->onTouchBegan = CC_CALLBACK_2(EntrySceneMainLayer::onTouchBegan, this);
	touchListener->onTouchMoved = CC_CALLBACK_2(EntrySceneMainLayer::onTouchMoved, this);
	touchListener->onTouchEnded = CC_CALLBACK_2(EntrySceneMainLayer::onTouchEnded, this);
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(touchListener, this);

	{
		_spineNode = spine::SkeletonAnimation::createWithFile("animation/raptor.json", "animation/raptor.atlas", 0.25f);

		_spineNode->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y - 150.f));
		this->addChild(_spineNode, 10);
		PlayAnimatioin(0);
	}
    
    return true;
}

bool EntrySceneMainLayer::onTouchBegan(Touch *__touch, Event *__evnt)
{
	return true;
}

void EntrySceneMainLayer::onTouchMoved(Touch *__touch, Event *__evnt)
{
}

void EntrySceneMainLayer::onTouchEnded(Touch *__touch, Event *__evnt)
{
	PlayAnimatioin(_spineAnimationNow + 1);
}

void EntrySceneMainLayer::onKeyPressed(EventKeyboard::KeyCode __code, Event *__evnt)
{
	if (
		EventKeyboard::KeyCode::KEY_ESCAPE == __code
#if ( CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID )
		|| EventKeyboard::KeyCode::KEY_BACK == __code
#endif
		)
	{
		ShutDownApp();
	}
	else
	{
		if (EventKeyboard::KeyCode::KEY_1 <= __code && EventKeyboard::KeyCode::KEY_7 >= __code)
		{
			int listIndex = (int)__code - (int)EventKeyboard::KeyCode::KEY_1;
			PlayAnimatioin(listIndex);
		}
	}
}

void EntrySceneMainLayer::menuCloseCallback(Ref* pSender)
{
	ShutDownApp();
}

void EntrySceneMainLayer::ShutDownApp()
{
	Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	exit(0);
#endif
}

void EntrySceneMainLayer::PlayAnimatioin(const int __index)
{
	enum { ANIMATION_COUNT = 2 };
	const std::string AnimationName[ANIMATION_COUNT] =
	{
		"walk", "gungrab"
	};
	const bool AnimationLoop[ANIMATION_COUNT] = { true, false };

	_spineAnimationNow = __index;
	if (ANIMATION_COUNT == _spineAnimationNow)
	{
		_spineAnimationNow = 0;
	}

	_spineNode->setAnimation(0, AnimationName[_spineAnimationNow], AnimationLoop[_spineAnimationNow]);
}
