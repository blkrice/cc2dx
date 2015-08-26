#ifndef parallax_scene__h
#define parallax_scene__h

#include "cocos2d.h"
#include "spine/spine-cocos2dx.h"

class ParallaxSceneLayer : public cocos2d::Layer
{
public:
	static cocos2d::Scene* createScene();

	virtual bool init();

	CREATE_FUNC(ParallaxSceneLayer);
private:
};

#endif
