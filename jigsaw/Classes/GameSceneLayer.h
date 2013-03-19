//
//  GameSceneLayer.h
//  jigsaw
//
//  Created by 9yu on 11/13/12.
//
//

#ifndef jigsaw_GameSceneLayer_h
#define jigsaw_GameSceneLayer_h

#include "cocos2d.h"
#include "GameDefine.h"

using namespace cocos2d;

class GameScene : public cocos2d::CCLayer
{
public:
    virtual void onEnter();
    virtual void onExit();

    virtual bool init();
    CREATE_FUNC(GameScene);

    virtual bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
    virtual bool ccTouchEnd(CCTouch *pTouch, CCEvent *pEvent);
    virtual void registerWithTouchDispatcher(void);
    
    void    RandomPiece();
    int     CalcMoveDir();
};

#endif
