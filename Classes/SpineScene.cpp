#include "SpineScene.h"
#include "EntryScene.h"

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
	
	{//spine
		_node = spine::SkeletonAnimation::createWithFile("animation/raptor.json", "animation/raptor.atlas", 0.25f);

		_node->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y - 150.f));
		this->addChild(_node, 10);
		_node->setAnimation(0, "walk", true);
	}

	{//event listener
		this->setKeypadEnabled(true);

		EventListenerTouchOneByOne *listener = EventListenerTouchOneByOne::create();
		listener->onTouchBegan = [this](Touch *__touch, Event *__evt) -> bool
		{
			_node->setAnimation(1, "gungrab", false);
			return true;
		};
		_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
	}

	{//menu
		auto backButton = MenuItemLabel::create(
			Label::createWithTTF("BACK", "fonts/Marker Felt.ttf", 15), CC_CALLBACK_1(SpineSceneMainLayer::CallbackBackButton, this)
			);
		backButton->setPosition(Vec2(50.f, visibleSize.height - 50.f));
		backButton->setColor(Color3B::RED);

		auto menu = Menu::create(backButton, NULL);
		menu->setPosition(Vec2::ZERO);
		this->addChild(menu, 1);
	}

	return true;
}

void SpineSceneMainLayer::onKeyReleased(EventKeyboard::KeyCode __code, Event *__evnt)
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
}

void SpineSceneMainLayer::ShutDownApp()
{
	Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	exit(0);
#endif
}

void SpineSceneMainLayer::CallbackBackButton(Ref* pSender)
{
	Scene * entryScene = EntrySceneMainLayer::createScene();
	Director::getInstance()->replaceScene(entryScene);
}
