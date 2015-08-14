#ifndef spine_scene__h
#define spine_scene__h

#include "cocos2d.h"
#include "spine/spine-cocos2dx.h"

class SpineSceneMainLayer : public cocos2d::Layer
{
public:
	static cocos2d::Scene* createScene();

	virtual bool init();

	virtual bool onTouchBegan(cocos2d::Touch *__touch, cocos2d::Event *__evnt) override;
	virtual void onTouchMoved(cocos2d::Touch *__touch, cocos2d::Event *__evnt) override;
	virtual void onTouchEnded(cocos2d::Touch *__touch, cocos2d::Event *__evnt) override;

	void onKeyPressed(cocos2d::EventKeyboard::KeyCode __code, cocos2d::Event *__evnt) override;

	CREATE_FUNC(SpineSceneMainLayer);

private:
	void ShutDownApp();

	spine::SkeletonAnimation *_node = NULL;
	int _nowAnimation = 0;
	void PlayAnimatioin(const int __index);

	void CallbackBackButton(cocos2d::Ref* pSender);
};

#endif
