//
//  GameSceneLayer.cpp
//  jigsaw
//
//  Created by 9yu on 11/13/12.
//
//

#include "GameSceneLayer.h"
#include "Piece.h"

using namespace cocos2d;

#define COLS       GAME_MODE
#define NODE_COUNT  (GAME_MODE * GAME_MODE)

int nodes[NODE_COUNT];
int target[NODE_COUNT] = {0,1,2,3,4,5,6,7,8};
enum eMoveDiretion {
    eMoveLeft = 0,
    eMoveRight = 1,
    eMoveUp = 2,
    eMoveDown = 3
    };

static void shuffle(int size, int *a){ //打乱数组顺序
    for (int i=0; i<size; i++) {
        int r = arc4random()%size;
        int t = a[i];
        a[i] = a[r];
        a[r] = t;
    }
}

static bool parityCheck(int length, int *a){
    //返回数组的排列的逆序数加上0元素行号和列号的奇偶性，true为偶，false为奇。
    int v = 0;
    int zeroIndex = -1;
    for(int i=0; i<length; i++){
        for(int j=i+1; j<length; j++){
            if(a[i]>a[j]){
                v++;
            }
        }
        if(a[i] == 0) zeroIndex = i;
    }
    int lineIndex = zeroIndex / COLS+1;
    int colIndex = zeroIndex % COLS+1;
    
    return (lineIndex + colIndex + v) % 2 == 0;
    
}

void GameScene::onEnter()
{
    CCLayer::onEnter();
}

void GameScene::onExit()
{
    CCDirector* pDirector = CCDirector::sharedDirector();
    pDirector->getTouchDispatcher()->removeDelegate(this);
    CCLayer::onExit();
}

void GameScene::RandomPiece()
{
    for (int i=0; i<NODE_COUNT; i++) {
        nodes[i] = i;
    }
    
    shuffle(NODE_COUNT, nodes);
    if (parityCheck(NODE_COUNT, nodes) != parityCheck(NODE_COUNT, target)) {
        //若不满足定理，则交换数组最后两个值，使其奇偶性改变。
        int i = nodes[NODE_COUNT-2];
        nodes[NODE_COUNT-2] = nodes[NODE_COUNT-1];
        nodes[NODE_COUNT-1] = i;
    }
}

bool GameScene::init()
{
    bool bRet = false;
    do {
        if ( !CCLayer::init() )
        {
            return false;
        }
        
        RandomPiece();
        
        CCPoint spritePos[GAME_MODE*GAME_MODE];
        CCSize size = CCDirector::sharedDirector()->getWinSize();
        CCTexture2D* pTex = CCTextureCache::sharedTextureCache()->addImage("1.jpg");
        
        const float frameWidth = texSize/GAME_MODE;
        for (int i = 0; i < GAME_MODE*GAME_MODE; i++) {
            spritePos[i] = CCPoint( 0 + frameWidth * (i%3), 0 + frameWidth * (i/3));
        }
        for (int i = 0; i < GAME_MODE*GAME_MODE; i++) {
            if (nodes[i] == GAME_MODE*GAME_MODE - 1) {
                continue;
            }
            Piece* pSprite = Piece::initwithTexture(pTex, CCRect(spritePos[nodes[i]].x, spritePos[nodes[i]].y, frameWidth, frameWidth));
         //   CCSprite* pSprite = CCSprite::createWithTexture(pTex, CCRect(spritePos[i].x, spritePos[i].y, frameWidth, frameWidth));
            pSprite->PieceSprite()->setAnchorPoint(CCPoint(0, 0));
            pSprite->PieceSprite()->setPosition(CCPoint(spritePos[i].x, (texSize-frameWidth)-spritePos[i].y));
            this->addChild(pSprite->PieceSprite(),0, i);
        }
        
        setTouchEnabled(false);
        bRet = true;
    } while (0);
    return bRet;
}

void GameScene::registerWithTouchDispatcher(void)
{
    CCDirector* pDirector = CCDirector::sharedDirector();
    pDirector->getTouchDispatcher()->addTargetedDelegate(this, kCCMenuHandlerPriority, false);
//    pDirector->getTouchDispatcher()->addStandardDelegate(this, kCCMenuHandlerPriority);
}

bool GameScene::ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent)
{
    CCPoint touchPoint = pTouch->getLocationInView();
    CCPoint pt = this->convertTouchToNodeSpace(pTouch);
//    CCLOG("x:%4f,y:%4f", pt.x, pt.y);
    return true;
}

bool GameScene::ccTouchEnd(CCTouch *pTouch, CCEvent *pEvent)
{
    return true;
}

int GameScene::CalcMoveDir()
{
    return eMoveDown;
}