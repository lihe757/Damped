#include "HelloWorldScene.h"
#include "SimpleAudioEngine.h"
#include <cmath>

using namespace std;
using namespace cocos2d;
using namespace CocosDenshion;

CCScene* HelloWorld::scene()
{
	// 'scene' is an autorelease object
	CCScene *scene = CCScene::node();
	
	// 'layer' is an autorelease object
	HelloWorld *layer = HelloWorld::node();

	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;
}

double      k=0.5;
double      m=10;
double      c=0.5;
double      wn;
double      wd;
double      ss;

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
	//////////////////////////////
	// 1. super init first
	if ( !CCLayer::init() )
	{
		return false;
	}

	/////////////////////////////
	// 2. add a menu item with "X" image, which is clicked to quit the program
	//    you may modify it.

	// add a "close" icon to exit the progress. it's an autorelease object
//	pCloseItem = CCMenuItemImage::itemFromNormalImage(
//										"CloseNormal.png",
//										"CloseSelected.png",
//										this,
//										menu_selector(HelloWorld::menuCloseCallback) );
////	pCloseItem->setPosition( ccp(CCDirector::sharedDirector()->getWinSize().width - 20, 20) );
//    pCloseItem->setPosition(ccp(160,224));
//
//	// create menu, it's an autorelease object
//	CCMenu* pMenu = CCMenu::menuWithItems(pCloseItem, NULL);
//	pMenu->setPosition( CCPointZero );
//	this->addChild(pMenu, 1);

	/////////////////////////////
	// 3. add your codes below...

	// add a label shows "Hello World"
	// create and initialize a label
	CCLabelTTF* pLabel = CCLabelTTF::labelWithString("Hello World", "Thonburi", 34);

	// ask director the window size
	CCSize size = CCDirector::sharedDirector()->getWinSize();

	// position the label on the center of the screen
	pLabel->setPosition( ccp(size.width / 2, size.height - 20) );

	// add the label as a child to this layer
	this->addChild(pLabel, 1);

	// add "HelloWorld" splash screen"
	pSprite = CCSprite::spriteWithFile("HelloWorld.png");

	// position the sprite on the center of the screen
	pSprite->setPosition( ccp(size.width/2, 0) );

	// add the sprite as a child to this layer
	this->addChild(pSprite, 0);
	
//    this->schedule(schedule_selector(HelloWorld::step));
    
    this->setIsTouchEnabled(true);
    
    k=0.5;
    m=10;
    c=0.5;
    
    wn = sqrt(k/m);
    ss = c/(2*sqrt(k*m)); ss=1.0f;
    wd = wn*(sqrt(1-ss*ss));
    
	return true;
}

int16_t            fixY_1 = 160;
double    A_1 = 160;
double    LocalY_1=0;
double    w_1 = 0; //5
double    B_1 = 0.05;//0.4
double    t_1 = 0;
double LocalY_temp = 0;






void HelloWorld::step(ccTime dt){
 

//    LocalY_1 = A_1 * exp( -1 * B_1 * t_1) * cos(sqrt(w_1 * t_1));
    
    LocalY_1 = A_1 * exp(-1 * ss * wn * t_1) * cos(wd * t_1 );

    CCLog("LocalY_1 = %0.2f",LocalY_1);
    
    
//    t_1 = t_1 + 1.0f;
    CCPoint bttn_LIVLocation = ccp(240, fixY_1 - (int16_t)LocalY_1);
    pSprite->setPosition(bttn_LIVLocation);
        
//    CCLog("x=%0.2f,y=%0.2f",bttn_LIVLocation.x,bttn_LIVLocation.y);
    if(abs(LocalY_temp - LocalY_1)<0.001)
        this->unschedule(schedule_selector(HelloWorld::step));
    else
        LocalY_temp = LocalY_1;
    t_1 = t_1 + 0.5;
    
    CCLog("t_1 = %f",t_1);
}



void HelloWorld::registerWithTouchDispatcher()
{
    CCTouchDispatcher::sharedDispatcher()->addTargetedDelegate(this,kCCMenuTouchPriority,true);
}

void HelloWorld::menuCloseCallback(CCObject* pSender)
{   
    t_1 = 0;
    LocalY_1 = 0;
    pSprite->setPosition(ccp(240,0));
    this->unschedule(schedule_selector(HelloWorld::step));
    this->schedule(schedule_selector(HelloWorld::step));
}

bool HelloWorld::ccTouchBegan(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent)
{
    this->unschedule(schedule_selector(HelloWorld::step));
    t_1 = 0;
    LocalY_1 = 0;
    LocalY_temp = 0;
//    pSprite->setPosition(ccp(240,0));
    return true;
}

float offsetY=0;
void HelloWorld::ccTouchMoved(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent)
{
   
    CCPoint location = pTouch->locationInView(pTouch->view());
    CCPoint preTouchPoint = pTouch->previousLocationInView(pTouch->view());
    offsetY = preTouchPoint.y-location.y;
    
    CCPoint bttn_LIVLocation = ccp(240, (pSprite->getPosition().y)+offsetY);
    pSprite->setPosition(bttn_LIVLocation);
    
        
    A_1 = 160;
    
    if(pSprite->getPosition().y < 0){
        A_1 = 160+160;
    }
    float  a =320-(pSprite->getPosition().y+160); //距离顶部的距离
    
    if(pSprite->getPosition().y > 160){
        A_1 = -160;
        if(pSprite->getPosition().y > 320){
            A_1 = -320;
        }
        
        a =-(pSprite->getPosition().y-160); //距离底部的距离
    }

       

    //反推已经滑动的时间 并设置
    t_1 = abs(log(a/A_1))/wn;
    CCLog("m_t_1  = %f",t_1);



}

void HelloWorld::ccTouchEnded(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent)
{
    if(t_1 > 0)
        this->schedule(schedule_selector(HelloWorld::step));
}



void HelloWorld::ccTouchCancelled(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent)
{
    
}