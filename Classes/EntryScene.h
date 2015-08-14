#ifndef entry_scene__h
#define entry_scene__h

#include "cocos2d.h"
#include "spine/spine-cocos2dx.h"

class EntrySceneMainLayer : public cocos2d::Layer
{
public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();

    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();

	virtual bool onTouchBegan(cocos2d::Touch *__touch, cocos2d::Event *__evnt) override;
	virtual void onTouchMoved(cocos2d::Touch *__touch, cocos2d::Event *__evnt) override;
	virtual void onTouchEnded(cocos2d::Touch *__touch, cocos2d::Event *__evnt) override;

	void onKeyPressed(cocos2d::EventKeyboard::KeyCode __code, cocos2d::Event *__evnt) override;
    
    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);
    
    // implement the "static create()" method manually
	CREATE_FUNC(EntrySceneMainLayer);

private:
	void ShutDownApp();

	spine::SkeletonAnimation *_spineNode = NULL;
	int _spineAnimationNow = 0;
	void PlayAnimatioin(const int __index);
};

#endif // entry_scene__h
