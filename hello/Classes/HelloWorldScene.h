#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"

using namespace cocos2d;

class HelloWorld : public CCLayer
{
public:
	// Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
	virtual bool init();  

	// there's no 'id' in cpp, so we recommand to return the exactly class pointer
	static cocos2d::CCScene* scene();
	
	// a selector callback
	virtual void menuCloseCallback(CCObject* pSender);

	// implement the "static node()" method manually
	LAYER_NODE_FUNC(HelloWorld);
    
    void step(ccTime dt);
 	virtual bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
    
 	// optional
 	virtual void ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent) ;
 	virtual void ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent) ;
 	virtual void ccTouchCancelled(CCTouch *pTouch, CCEvent *pEvent);


    virtual void registerWithTouchDispatcher(void);
protected:
    CCMenuItemImage *pCloseItem ;
    CCSprite* pSprite;
};

#endif // __HELLOWORLD_SCENE_H__
