#pragma once
#ifndef __PLAYER_H__
#define __PLAYER_H__
 
#include "cocos2d.h"
#include "UsefulFunctions.h"
#include "Item.h"
using namespace UsefulFunctions;

USING_NS_CC;
class Player : public cocos2d::Sprite {

public:

	std::vector<Item*> items;



	Player() : Sprite(){}

	bool isInSight(const std::vector<std::vector<Sprite*> >& spriteLabirint, Node* bigSprite, Sprite* object);



};

#endif // __PLAYER_h__