#pragma once
#ifndef __ITEM_H__
#define __ITEM_H__

#include "cocos2d.h"
#include "UsefulFunctions.h"
using namespace UsefulFunctions;

USING_NS_CC;
class Item : public cocos2d::Sprite {

	std::string usualPicture;

public:

	Item() : Sprite(){}

	std::string getUsualPicture();

};

#endif // __PLAYER_h__