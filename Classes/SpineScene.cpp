#include "SpineScene.h"

USING_NS_CC;

Scene* SpineSceneMainLayer::createScene()
{
	auto scene = Scene::create();
	auto layer = SpineSceneMainLayer::create();
	scene->addChild(layer);

	return scene;
}

bool SpineSceneMainLayer::init()
{
	if (!Layer::init())
	{
		return false;
	}

	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	auto label = Label::createWithTTF("Spine Sample", "fonts/Marker Felt.ttf", 24);

	label->setPosition(Vec2(origin.x + visibleSize.width / 2,
		origin.y + visibleSize.height - label->getContentSize().height));

	this->addChild(label, 1);

	EventListenerKeyboard *keyListener = EventListenerKeyboard::create();
	keyListener->onKeyPressed = CC_CALLBACK_2(SpineSceneMainLayer::onKeyPressed, this);
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(keyListener, this);

	EventListenerTouchOneByOne *touchListener = EventListenerTouchOneByOne::create();
	touchListener->setSwallowTouches(true);
	touchListener->onTouchBegan = CC_CALLBACK_2(SpineSceneMainLayer::onTouchBegan, this);
	touchListener->onTouchMoved = CC_CALLBACK_2(SpineSceneMainLayer::onTouchMoved, this);
	touchListener->onTouchEnded = CC_CALLBACK_2(SpineSceneMainLayer::onTouchEnded, this);
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(touchListener, this);

	{
		_node = spine::SkeletonAnimation::createWithFile("animation/raptor.json", "animation/raptor.atlas", 0.25f);

		_node->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y - 150.f));
		this->addChild(_node, 10);
		PlayAnimatioin(0);
	}

	return true;
}

bool SpineSceneMainLayer::onTouchBegan(Touch *__touch, Event *__evnt)
{
	return true;
}

void SpineSceneMainLayer::onTouchMoved(Touch *__touch, Event *__evnt)
{
}

void SpineSceneMainLayer::onTouchEnded(Touch *__touch, Event *__evnt)
{
	PlayAnimatioin(_nowAnimation + 1);
}

void SpineSceneMainLayer::onKeyPressed(EventKeyboard::KeyCode __code, Event *__evnt)
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

void SpineSceneMainLayer::ShutDownApp()
{
	Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	exit(0);
#endif
}

void SpineSceneMainLayer::PlayAnimatioin(const int __index)
{
	enum { ANIMATION_COUNT = 2 };
	const std::string AnimationName[ANIMATION_COUNT] =
	{
		"walk", "gungrab"
	};
	const bool AnimationLoop[ANIMATION_COUNT] = { true, false };

	_nowAnimation = __index;
	if (ANIMATION_COUNT == _nowAnimation)
	{
		_nowAnimation = 0;
	}

	_node->setAnimation(0, AnimationName[_nowAnimation], AnimationLoop[_nowAnimation]);
}
