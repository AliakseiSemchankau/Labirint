#pragma once
#include "Player.h"
#include "Constants.h"


bool Player::isInSight(const std::vector<std::vector<Sprite*> >& spriteLabirint, Node* bigSprite, Sprite* object) {

	Vec2 objectCentre = transformCentreToScreenCoordinates(bigSprite, object);

	for (int i = 0; i < spriteLabirint.size(); ++i)
		for (int j = 0; j < spriteLabirint[i].size(); ++j) {
		if (spriteLabirint[i][j]->getTag() != WALL_TAG)
			continue;
		Sprite* curObject = spriteLabirint[i][j];
		Vec2 curObjectCentre = transformCentreToScreenCoordinates(bigSprite, curObject);
		if ((objectCentre - curObjectCentre).length() < SQUARE_SIZE / 2.0)
			continue;
	
		CCRect rectCurObject = rectObjectInRealCoordinates(bigSprite, curObject);
		Vec2 leftLow = Vec2(rectCurObject.getMinX(), rectCurObject.getMinY());
		Vec2 rightHigh = Vec2(rectCurObject.getMaxX(), rectCurObject.getMaxY());
		Vec2 leftHigh = Vec2(rectCurObject.getMinX(), rectCurObject.getMaxY());
		Vec2 rightLow = Vec2(rectCurObject.getMaxX(), rectCurObject.getMinY());
		if (intersect(leftLow, rightHigh, this->getPosition(), objectCentre))
			return false;
		if (intersect(leftLow, rightHigh, this->getPosition(), objectCentre))
			return false;
		}
	return true;

}