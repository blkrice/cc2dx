#include "ParallaxScene.h"

USING_NS_CC;

cocos2d::Scene* ParallaxSceneLayer::createScene()
{
	auto scene = Scene::create();
	auto layer = ParallaxSceneLayer::create();
	scene->addChild(layer);

	return scene;
}

bool ParallaxSceneLayer::init()
{
	return true;
}
