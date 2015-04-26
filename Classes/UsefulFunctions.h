#pragma once
#ifndef __USEFUL_FUNCTIONS_H__
#define __USEFUL_FUNCTIONS_H__
#include "cocos2d.h"
namespace UsefulFunctions {
	float area(cocos2d::Vec2 a, cocos2d::Vec2 b, cocos2d::Vec2 c);
	float maximum(float a, float b);
	bool intersect_1(float a, float b, float c, float d);
	bool intersect(cocos2d::Vec2 a, cocos2d::Vec2 b, cocos2d::Vec2 c, cocos2d::Vec2 d);
	cocos2d::Vec2 cosmicCoordinates(cocos2d::Node * nod);
	cocos2d::Vec2 cosmicCoordinatesZeroPoint(cocos2d::Node * nod);
	cocos2d::Vec2 transformCentreToScreenCoordinates(const cocos2d::Node* bigSprite, const cocos2d::Sprite* smallSprite);
	cocos2d::Vec2 transformZeroPointToScreenCoordinates(const cocos2d::Node* bigSprite, const cocos2d::Sprite* smallSprite);
	cocos2d::CCRect rectObjectInRealCoordinates(const cocos2d::Node* bigSprite, const cocos2d::Sprite* smallSprite);
	// std::vector<std::vector<bool> > visibleLabirint(std::vector<std::vector<char > >& charLabirint, int indexX, int indexY);
	int sign(int a, int b, int c, int d, int e, int f);
	bool checkLine(int a, int b, int c, int d, int a1, int b1, int c1, int d1);
	bool checks(int x, int y, int indexX, int indexY, int i, int j);
	bool checkIntersect(std::vector<std::vector<char > >& charLabirint, int x, int y, int indexX, int indexY);
	void visibleLabirint(std::vector<std::vector<char > >& charLabirint, int indexX, int indexY, std::vector<std::vector<bool> >& visibleInLabirint);
}
#endif
