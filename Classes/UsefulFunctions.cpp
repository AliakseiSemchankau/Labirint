#pragma once
#include "UsefulFunctions.h"

float UsefulFunctions::area(cocos2d::Vec2 a, cocos2d::Vec2 b, cocos2d::Vec2 c) {
	return (b.x - a.x) * (c.y - a.y) - (b.y - a.y) * (c.x - a.x);
}


float UsefulFunctions::maximum(float a, float b) {
	if (a < b)
		return b;
	else
		return a;
}

bool UsefulFunctions::intersect_1(float a, float b, float c, float d) {
	if (a > b)  std::swap(a, b);
	if (c > d)  std::swap(c, d);
	return maximum(a, c) <= maximum(b, d);
}

bool UsefulFunctions::intersect(cocos2d::Vec2 a, cocos2d::Vec2 b, cocos2d::Vec2 c, cocos2d::Vec2 d) {
	return intersect_1(a.x, b.x, c.x, d.x)
		&& intersect_1(a.y, b.y, c.y, d.y)
		&& area(a, b, c) * area(a, b, d) <= 0
		&& area(c, d, a) * area(c, d, b) <= 0;
}

cocos2d::Vec2 UsefulFunctions::cosmicCoordinates(cocos2d::Node* nod) {
	if (nod->getParent() == nullptr)
		return nod->getPosition();
	cocos2d::Vec2 moved = nod->getParent()->getPosition();
	return moved + nod->getPosition();
}

cocos2d::Vec2 UsefulFunctions::cosmicCoordinatesZeroPoint(cocos2d::Node* nod) {
	cocos2d::Vec2 cosmicCoordinatesCentre = cosmicCoordinates(nod);
	return (cosmicCoordinatesCentre + cocos2d::Vec2(-nod->getContentSize().width / 2.0, -nod->getContentSize().height / 2.0));

}

cocos2d::Vec2 UsefulFunctions::transformCentreToScreenCoordinates(const cocos2d::Node* bigSprite, const cocos2d::Sprite* smallSprite) {
	cocos2d::Vec2 absMoved = bigSprite->getPosition();
	cocos2d::Vec2 result = smallSprite->getPosition();
	result.x -= bigSprite->getAnchorPoint().x * bigSprite->getContentSize().width;
	result.y -= bigSprite->getAnchorPoint().y * bigSprite->getContentSize().height;
	return (result + absMoved);
}

cocos2d::Vec2 UsefulFunctions::transformZeroPointToScreenCoordinates(const cocos2d::Node* bigSprite, const cocos2d::Sprite* smallSprite) {
	return (transformCentreToScreenCoordinates(bigSprite, smallSprite) - 0.5*smallSprite->getContentSize());
}

cocos2d::CCRect UsefulFunctions::rectObjectInRealCoordinates(const cocos2d::Node* bigSprite, const cocos2d::Sprite* smallSprite) {
	cocos2d::Vec2 smallSpriteZeroPoint = transformZeroPointToScreenCoordinates(bigSprite, smallSprite);
	return cocos2d::CCRectMake(
		smallSpriteZeroPoint.x,
		smallSpriteZeroPoint.y,
		smallSprite->getContentSize().width,
		smallSprite->getContentSize().height);
}

int UsefulFunctions::sign(int a, int b, int c, int d, int e, int f) {
	int ar = (a - e)*(d - f) - (b - f)*(c - e);
	if (ar > 0)
		return 1;
	if (ar < 0)
		return -1;
	return 0;
}

bool UsefulFunctions::checkLine(int a, int b, int c, int d, int a1, int b1, int c1, int d1) {
	int s1 = sign(a1, b1, c, d, a, b);
	int s2 = sign(c1, d1, c, d, a, b);
	return (s1*s2 < 0);
}

bool UsefulFunctions::checks(int x, int y, int indexX, int indexY, int i, int j) {
	x *= 2;
	y *= 2;
	indexX *= 2;
	indexY *= 2;
	i *= 2;
	j *= 2;
	
	if (checkLine(x, y, indexX, indexY, i - 1, j - 1, i + 1, j + 1))
		return true;
	if (checkLine(x, y, indexX, indexY, i + 1, j - 1, i - 1, j + 1))
		return true;
}

bool UsefulFunctions::checkIntersect(std::vector<std::vector<char > >& charLabirint, int x, int y, int indexX, int indexY){

	for (int i = std::min(x, indexX); i <= std::max(x, indexX); ++i)
		for (int j = std::min(y, indexY); j <= std::max(y, indexY); ++j) {
		if (charLabirint[i][j] != '#')
			continue;
		if (checks(x, y, indexX, indexY, i, j))
			return true;
		}
	return false;
}

 void UsefulFunctions::visibleLabirint(std::vector<std::vector<char > >& charLabirint, int indexX, int indexY, std::vector<std::vector<bool> >& visibleInLabirint) {

	int n = charLabirint.size();
	int m = charLabirint[0].size();
	static std::vector<std::vector<int> > coloredLabirint(n, std::vector<int>(m, 0));

	for (int i = std::max(indexX - 15, 0); i < std::min(indexX + 15, n); ++i)
		for (int j = std::max(indexY - 15, 0); j < std::min(indexY + 15, m); ++j)
			coloredLabirint[i][j] = 0;

	for (int i = std::max(indexX - 15, 0); i < std::min(indexX + 15, n); ++i)
		for (int j = std::max(indexY - 15, 0); j < std::min(indexY + 15, m); ++j)
			visibleInLabirint[i][j] = false;


	int leftX = indexX;
	int rightX = indexX;
	int upY = indexY;
	int downY = indexY;

	std::queue<std::pair<int, int> > coloredInFirstColor;

	while (charLabirint[indexX][upY + 1] != '#')
		++upY;
	while (charLabirint[indexX][downY - 1] != '#')
		--downY;
	while (charLabirint[rightX + 1][indexY] != '#')
		++rightX;
	while (charLabirint[leftX - 1][indexY] != '#')
		--leftX;

	for (int i = std::max(indexX - 10, 1); i < std::min(indexX + 10, n); ++i)
		for (int j = std::max(indexY - 10, 1); j < std::min(indexY + 10, m); ++j) {
		if (charLabirint[i][j] == '#')
			continue;
		if (!checkIntersect(charLabirint, i, j, indexX, indexY))
			coloredLabirint[i][j] = 1, coloredInFirstColor.push(std::make_pair(i, j));
		}

	/*for (int i = leftX; i <= rightX; ++i)
		coloredLabirint[i][indexY] = 1, coloredInFirstColor.push(std::make_pair(i, indexY));

	for (int j = downY; j <= upY; ++j)
		coloredLabirint[indexX][j] = 1, coloredInFirstColor.push(std::make_pair(indexX, j));

	for (int i = indexX + 1; i <= rightX; ++i)
		for (int j = indexY + 1; j <= upY; ++j)
			if (charLabirint[i][j] != '#' && coloredLabirint[i - 1][j] == 1 && coloredLabirint[i][j - 1])
				coloredLabirint[i][j] = 1, coloredInFirstColor.push(std::make_pair(i, j));

	for (int i = indexX - 1; i >= leftX; --i)
		for (int j = indexY + 1; j <= upY; ++j)
			if (charLabirint[i][j] != '#' && coloredLabirint[i + 1][j] == 1 && coloredLabirint[i][j - 1])
				coloredLabirint[i][j] = 1, coloredInFirstColor.push(std::make_pair(i, j));

	for (int i = indexX + 1; i <= rightX; ++i)
		for (int j = indexY - 1; j >= downY; --j)
			if (charLabirint[i][j] != '#' && coloredLabirint[i - 1][j] == 1 && coloredLabirint[i][j + 1])
				coloredLabirint[i][j] = 1, coloredInFirstColor.push(std::make_pair(i, j));

	for (int i = indexX - 1; i >= leftX; --i)
		for (int j = indexY - 1; j >= downY; --j)
			if (charLabirint[i][j] != '#' && coloredLabirint[i + 1][j] == 1 && coloredLabirint[i][j + 1])
				coloredLabirint[i][j] = 1, coloredInFirstColor.push(std::make_pair(i, j));
*/
	while (!coloredInFirstColor.empty()) {
		std::pair<int, int> curPair = coloredInFirstColor.front();
		coloredInFirstColor.pop();
		if (charLabirint[curPair.first - 1][curPair.second] == '#')
			coloredLabirint[curPair.first - 1][curPair.second] = 2;
		if (charLabirint[curPair.first + 1][curPair.second] == '#')
			coloredLabirint[curPair.first + 1][curPair.second] = 2;
		if (charLabirint[curPair.first][curPair.second + 1] == '#')
			coloredLabirint[curPair.first][curPair.second + 1] = 2;
		if (charLabirint[curPair.first][curPair.second - 1] == '#')
			coloredLabirint[curPair.first][curPair.second - 1] = 2;
		
		if (charLabirint[curPair.first - 1][curPair.second - 1] == '#')
			coloredLabirint[curPair.first - 1][curPair.second - 1] = 2;
		if (charLabirint[curPair.first + 1][curPair.second - 1] == '#')
			coloredLabirint[curPair.first + 1][curPair.second - 1] = 2;
		if (charLabirint[curPair.first - 1][curPair.second + 1] == '#')
			coloredLabirint[curPair.first - 1][curPair.second + 1] = 2;
		if (charLabirint[curPair.first + 1][curPair.second + 1] == '#')
			coloredLabirint[curPair.first + 1][curPair.second + 1] = 2;
		
	}

	for (int i = std::max(indexX - 10, 0); i < std::min(indexX + 10, n); ++i)
		for (int j = std::max(indexY - 10, 0); j < std::min(indexY + 10, m ); ++j)
			if (coloredLabirint[i][j] > 0)
				visibleInLabirint[i][j] = true;

	//return visibleLabirint;
}