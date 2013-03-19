//
//  Piece.cpp
//  jigsaw
//
//  Created by 9yu on 11/14/12.
//
//

#include "Piece.h"

Piece::Piece()
{

}

Piece::~Piece()
{
    
}

Piece* Piece::initwithTexture(CCTexture2D *pTexture, const CCRect& rect)
{
    Piece* pPiece = new Piece();
    pPiece->mpSprite = CCSprite::createWithTexture(pTexture, rect);
    
   // pPiece->autorelease();
    
    return pPiece;
}

/*void Piece::registerWithTouchDispatcher(void)
{
    CCDirector* pDirector = CCDirector::sharedDirector();
    pDirector->getTouchDispatcher()->addTargetedDelegate(this, kCCMenuHandlerPriority, false);
}*/

void Piece::SetPiecePositon(CCPoint pos)
{
    mPosition = pos;
}

CCRect Piece::rect()
{
    CCSize s = getTexture()->getContentSize();
    return CCRectMake(-s.width / 2, -s.height / 2, s.width, s.height);
}

bool Piece::containsTouchLocation(CCTouch* touch)
{
    return rect().containsPoint(convertTouchToNodeSpaceAR(touch));
}

bool Piece::ccTouchBegan(CCTouch* touch, CCEvent* event)
{
    CCPoint touchPoint = touch->getLocationInView();
    CCPoint pt = this->convertTouchToNodeSpace(touch);
    CCLOG("x:%4f,y:%4f", pt.x, pt.y);
    return true;
}
void Piece::ccTouchMoved(CCTouch* touch, CCEvent* event)
{
    
}
void Piece::ccTouchEnded(CCTouch* touch, CCEvent* event)
{
    
}

void Piece::onEnter(){
    
    CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, kCCMenuHandlerPriority, true);
    
    CCSprite::onEnter();
        
}

void Piece::onExit(){
    
    CCDirector::sharedDirector()->getTouchDispatcher()->removeDelegate(this);
    
    CCSprite::onExit();

}
