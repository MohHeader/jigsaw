//
//  Piece.h
//  jigsaw
//
//  Created by 9yu on 11/14/12.
//
//

#ifndef jigsaw_Piece_h
#define jigsaw_Piece_h

#include "cocos2d.h"
using namespace cocos2d;

class Piece : public CCSprite, public CCTouchDelegate {
public:
    Piece(void);
    virtual ~Piece(void);
    
    CCRect      rect();
    void        SetPiecePositon(CCPoint pos);
    bool        containsTouchLocation(CCTouch* touch);
    virtual bool ccTouchBegan(CCTouch* touch, CCEvent* event);
    virtual void ccTouchMoved(CCTouch* touch, CCEvent* event);
    virtual void ccTouchEnded(CCTouch* touch, CCEvent* event);
//    virtual void registerWithTouchDispatcher(void);
    
    virtual void onEnter();
    virtual void onExit();

    static Piece*        initwithTexture(CCTexture2D *pTexture, const CCRect& rect);
    
    CCSprite*   PieceSprite()   {   return mpSprite;    }
private:
    CCPoint     mPosition;
    CCSprite*   mpSprite;
};

#endif
