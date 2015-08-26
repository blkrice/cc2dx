#ifndef spine_scene__h
#define spine_scene__h

#include "cocos2d.h"
#include "spine/spine-cocos2dx.h"

class SpineSceneMainLayer : public cocos2d::Layer
{
public:
	static cocos2d::Scene* createScene();

	virtual bool init();

	void onKeyReleased(cocos2d::EventKeyboard::KeyCode __code, cocos2d::Event *__evnt) override;

	CREATE_FUNC(SpineSceneMainLayer);

private:
	void ShutDownApp();

	spine::SkeletonAnimation *_node = NULL;

	void CallbackBackButton(cocos2d::Ref* pSender);
};

#endif
