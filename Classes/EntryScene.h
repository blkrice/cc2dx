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
    
    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);
    
    // implement the "static create()" method manually
	CREATE_FUNC(EntrySceneMainLayer);

private:
	const std::string CommonTTF = "fonts/Marker Felt.ttf";

	void ChangeSceneMenuCallback(cocos2d::Ref *__sender);
};

#endif // entry_scene__h
