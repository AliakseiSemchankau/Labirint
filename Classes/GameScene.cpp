#pragma once

#include "GameScene.h"
#include "Labyrinth.h"
#include "Constants.h"
#include "Player.h"
#include "UsefulFunctions.h"
//#include "GUI\CCScrollView\CCScrollView.h"
#include <vector>
#include <iostream>
#include <fstream>
USING_NS_CC;

std::ofstream of("GameTouches.txt");

using namespace UsefulFunctions;

Scene* Game::createScene()
{
	// 'scene' is an autorelease object
	auto scene = Scene::create();

	// 'layer' is an autorelease object
	auto layer = Game::create();

	// add layer as a child to scene
	scene->addChild(layer, 0);

	// return the scene
	return scene;
}

// on "init" you need to initialize your instance
bool Game::init()
{
	//////////////////////////////
	// 1. super init first
	if (!Layer::init())
	{
		return false;
	}

	visibleSize = Director::getInstance()->getVisibleSize();
	origin = Director::getInstance()->getVisibleOrigin();

	auto myBigSprite = Player::create("grassBig1.png", CCRect(0, 0, 0, 0));
	myBigSprite->setAnchorPoint(Vec2(0.5, 0.5));

	Vec2 centre = Vec2(
		myBigSprite->getAnchorPoint().x * myBigSprite->getContentSize().width,
		myBigSprite->getAnchorPoint().y * myBigSprite->getContentSize().height);

	Vec2 screenCentre = Vec2(
		myBigSprite->getAnchorPoint().x * myBigSprite->getContentSize().width + visibleSize.width/2,
		myBigSprite->getAnchorPoint().y * myBigSprite->getContentSize().height + visibleSize.height/2);

	this->addChild(myBigSprite, 1, layerTaq);
	
	paintLabirint();

	paintItemsScreen();

	mySprite = reinterpret_cast<Player*> (Player::create("ball.png"));
	
	mySprite->setPosition(visibleSize.width / 2.0, visibleSize.height / 2.0);
	mySprite->setAnchorPoint(Vec2(0.5, 0.5));


	Vec2 startFromCentre = myBigSprite->getChildByTag(START_TAG)->getPosition() - screenCentre;
	myBigSprite->setPosition(myBigSprite->getPosition() - startFromCentre);

	this->addChild(mySprite, 2);
	
	/*auto listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan = CC_CALLBACK_2(Game::onTouchBegan, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);	*/

	auto keyboardListener = EventListenerKeyboard::create();
	
	keyboardListener->onKeyPressed = [=](EventKeyboard::KeyCode keyCode, Event* event){
		// If a key already exists, do nothing as it will already have a time stamp
		// Otherwise, set's the timestamp to now
		
		keys.insert(keyCode);
	};

	keyboardListener->onKeyReleased = [=](EventKeyboard::KeyCode keyCode, Event* event){
		// remove the key.  std::map.erase() doesn't care if the key doesnt exist
		keys.erase(keyCode);
	};

	auto mouseListener = EventListenerTouchOneByOne::create();

	mouseListener->onTouchBegan = [=](cocos2d::Touch* touch, cocos2d::Event* event) {

		Vec2 touchPoint = touch->getLocation();
		return true;

	};

	this->_eventDispatcher->addEventListenerWithSceneGraphPriority(keyboardListener, this);
	//itemsScreen->setPosition("itemsFont.png", CCRect(0, 0, itemsFontWidth, itemsFontHeight);
	//this->_eventDispatcher->addEventListenerWithFixedPriority(mouseListener, 0);
	//this->_eventDispatcher->addEventListenerWithSceneGraphPriority(mouseListener, this);

	this->schedule(schedule_selector(Game::updateGameKeyboard), 0.01);
	this->schedule(schedule_selector(Game::updateGame), 0.01);
	this->schedule(schedule_selector(Game::updateItemScreen), 0.01);

return true;

}

void Game::paintLabirint() {

	charLabirint = charGraph();

	auto node = this->getChildByTag(layerTaq);
	Vec2 screenCentre = Vec2(
		node->getAnchorPoint().x * node->getContentSize().width + visibleSize.width / 2.0,
		node->getAnchorPoint().y * node->getContentSize().height + visibleSize.height / 2.0);

	int N = charLabirint.size();
	int M = charLabirint[0].size();

	spriteLabirint.assign(N, std::vector<Sprite*>(M, nullptr));

	for (int i = 0; i < charLabirint.size(); ++i, of << "\n") 
		for (int j = 0; j < charLabirint[i].size(); ++j) {
			Sprite* sprite;
			of << charLabirint[i][j];
			switch (charLabirint[i][j]) {
				case '.':
					sprite = Sprite::create("grassBig1.png", CCRect(0, 0, SQUARE_SIZE, SQUARE_SIZE));
					sprite->setTag(FLOOR_TAG);
					break;
				case '#':
					sprite = Sprite::create("wall.png", CCRect(0, 0, SQUARE_SIZE, SQUARE_SIZE));
					sprite->setTag(WALL_TAG);
					break;
				case 's':
					sprite = Sprite::create("stone2.png", CCRect(0, 0, SQUARE_SIZE, SQUARE_SIZE));
					sprite->setTag(START_TAG);
					break;
				case'f':
					sprite = Sprite::create("stone2.png", CCRect(0, 0, SQUARE_SIZE, SQUARE_SIZE));
					sprite->setTag(FINISH_TAG);
					break;
				}
			sprite->setAnchorPoint(Vec2(0.5, 0.5));
			sprite->setPosition(screenCentre + SQUARE_SIZE*Vec2(i, j));
			spriteLabirint[i][j] = sprite;
			node->addChild(sprite, 4);
		}

	int items;

				
}

/*bool Game::onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* event) {
	
	Vec2 touchPoint = touch->getLocation();
	Vec2 spritePoint = Vec2(visibleSize.width / 2.0, visibleSize.height / 2.0);
	Vec2 dif = touchPoint - spritePoint;
	float length = dif.length();
	auto moveBy = MoveBy::create(length / VELOCITY, -dif);
	moveBy->setTag(MoveByAction);

	auto node = this->getChildByTag(layerTaq);
	node->stopAllActions();		
	node->runAction(moveBy);
	return true;
}*/

void Game::paintItemsScreen() {

	//itemsScreen = Sprite::create()

}

void Game::mainMenu(Ref* pSender)
{
	Director::getInstance()->popScene();
}

bool Game::isKeyPressed(cocos2d::EventKeyboard::KeyCode code) {

	return keys.count(code);

}

void Game::updateGameKeyboard(float dt) {

	auto node = this->getChildByTag(layerTaq);

	if (this->isKeyPressed(EventKeyboard::KeyCode::KEY_LEFT_ARROW))
		//node->runAction(MoveBy::create(0.1, Vec2(15, 0)));
		node->setPosition(node->getPosition() + Vec2(3, 0));

	if (this->isKeyPressed(EventKeyboard::KeyCode::KEY_RIGHT_ARROW))
		//node->runAction(MoveBy::create(0.1, Vec2(-15, 0)));
		node->setPosition(node->getPosition() + Vec2(-3, 0));

	if (this->isKeyPressed(EventKeyboard::KeyCode::KEY_UP_ARROW))
		//node->runAction(MoveBy::create(0.1, Vec2(0, -15)));
		node->setPosition(node->getPosition() + Vec2(0, -3));

	if (this->isKeyPressed(EventKeyboard::KeyCode::KEY_DOWN_ARROW))
		//node->runAction(MoveBy::create(0.1, Vec2(0, 15)));
		node->setPosition(node->getPosition() + Vec2(0, 3));


}

void Game::updateGame(float dt) {

	/*Vec2 mySpriteCosm = cosmicCoordinates(mySprite);
	of << "mySprite: " << mySpriteCosm.x << " " << mySpriteCosm.y << "\n";

	for (int i = 0; i < spriteLabirint.size(); ++i, of << "\n")
		for (int j = 0; j < spriteLabirint[0].size(); ++j) {
		cocos2d::Vec2 myLabCosm = cosmicCoordinates(spriteLabirint[i][j]);
		of <<"(" << myLabCosm.x << ", " << myLabCosm.y << ") ";
		}*/

	static std::set<std::pair<int, int> > visibleCells;
	static bool flagInitVisibleCells = false;
	static bool flagFinallyInit = false;
	if (!flagInitVisibleCells) {
		flagInitVisibleCells = true;
		for (int i = 0; i < spriteLabirint.size(); ++i)
			for (int j = 0; j < spriteLabirint[i].size(); ++j)
				visibleCells.insert(std::make_pair(i, j));
		for (int i = 0; i < spriteLabirint.size(); ++i)
			for (int j = 0; j < spriteLabirint[0].size(); ++j)
				spriteLabirint[i][j]->setVisible(false);
	}
	
	auto node = this->getChildByTag(layerTaq);

	std::pair<int, int> bestWallBlock;
	float bestLen = 10000.0;
	for (auto it = visibleCells.begin(); it != visibleCells.end(); ++it) {
		int i = (*it).first;
		int j = (*it).second;
		int curTag = spriteLabirint[i][j]->getTag();
		if (curTag != FLOOR_TAG && curTag != START_TAG && curTag != FINISH_TAG)
			continue;

		Vec2 realCoordinates = transformCentreToScreenCoordinates(node, spriteLabirint[i][j]);
		float curLen = (realCoordinates - mySprite->getPosition()).length();
		if (curLen < bestLen)
			bestLen = curLen, bestWallBlock = std::make_pair(i, j);
		}

	if (!flagFinallyInit) {
		flagFinallyInit = true;
		visibleCells.clear();
		visibleCells.insert(bestWallBlock);
		spriteLabirint[bestWallBlock.first][bestWallBlock.second]->setVisible(true);
	}

	int n = spriteLabirint.size();
	int m = spriteLabirint[0].size();

	static std::vector<std::vector<bool> > visibleInLabirint(n, std::vector<bool> (m, false));
	visibleLabirint(charLabirint, bestWallBlock.first, bestWallBlock.second, visibleInLabirint);

	for (int i = std::max(bestWallBlock.first - 17, 0); i < std::min(bestWallBlock.first + 17, n); ++i)
		for (int j = std::max(bestWallBlock.second - 17, 0); j < std::min(bestWallBlock.second + 17, m); ++j){
		bool wasVisible = spriteLabirint[i][j]->isVisible();
		bool nowVisible = visibleInLabirint[i][j];
		if (wasVisible == nowVisible)
			continue;
		if (nowVisible)
			spriteLabirint[i][j]->setVisible(true),
			visibleCells.insert(std::make_pair(i, j));
		//spriteLabirint[i][j]->runAction(FadeIn::create(true));
		else
			spriteLabirint[i][j]->setVisible(false),
			visibleCells.erase(std::make_pair(i, j));
			//spriteLabirint[i][j]->runAction(FadeOut::create(0.1f));
		}
	

	//of << bestWallBlock.first << " " << bestWallBlock.second << "\n";

	//Vec2 wallBlockRealCentre = transformCentreToScreenCoordinates(node, spriteLabirint[bestWallBlock.first][bestWallBlock.second]);
	Vec2 wallBlockRealCentre = cosmicCoordinates(spriteLabirint[bestWallBlock.first][bestWallBlock.second]);
	//Vec2 mySpriteRealCentre = mySprite->getPosition();
	Vec2 mySpriteRealCentre = cosmicCoordinates(mySprite);
	Vec2 direction = mySpriteRealCentre - wallBlockRealCentre;
	if (direction.length() > EPS5)
		direction = direction * float(1 / direction.length());
	else direction = Vec2(1, 0);
	//of << direction.x << " " << direction.y << "\n";
	float angle = direction.getAngle();
	//of << angle << " - angle\n";


	for (auto it = visibleCells.begin(); it != visibleCells.end(); ++it) {
		int i = (*it).first;
		int j = (*it).second;
		CCSprite* currentObject = spriteLabirint[i][j];
		
		//currentObject->setVisible(false);

		Vec2 mySpriteZeroPoint = mySprite->getPosition() - 0.5*mySprite->getContentSize();
		//Vec2 currentObjectZeroPoint = transformZeroPointToScreenCoordinates(node, currentObject);
		//Vec2 currentObjectRealCentre = transformCentreToScreenCoordinates(node, currentObject);
		Vec2 currentObjectZeroPoint = cosmicCoordinatesZeroPoint(currentObject);
		Vec2 currentObjectRealCentre = cosmicCoordinates(currentObject);


		CCRect currentObjectRect = CCRectMake(
			currentObjectZeroPoint.x,
			currentObjectZeroPoint.y,
			currentObject->getContentSize().width,
			currentObject->getContentSize().height);

		CCRect mySpriteRect = CCRectMake(
			mySpriteZeroPoint.x,
			mySpriteZeroPoint.y,
			mySprite->getContentSize().width,
			mySprite->getContentSize().height);

		if (currentObjectRect.intersectsRect(mySpriteRect)) {

			if (currentObject->getTag() == FINISH_TAG) {
				auto menuItemBack = MenuItemFont::create("You Win!", CC_CALLBACK_1(Game::youWin, this));
				menuItemBack->setPosition(origin.x + visibleSize.width*0.2, origin.y + visibleSize.height*0.8);
				auto *menu = Menu::create(menuItemBack, NULL);
				menu->setPosition(origin.x, origin.y);
				this->addChild(menu, 5);
			}

			if (currentObject->getTag() == WALL_TAG) {
				node->stopAllActions();
				Vec2 move;
				float angle = direction.getAngle();
			    //of << direction.x << " " << direction.y << "\n";
				//of << angle << " - angle\n";
				/*if (abs(angle - pi / 4) < EPS3)
					move = Vec2(1, 1);
				if (abs(angle - 3 * pi / 4) < EPS3)
					move = Vec2(-1, 1);
				if (abs(angle + pi / 4) < EPS3)
					move = Vec2(1, -1);
				if (abs(angle + 3 * pi / 4) < EPS3)
					move = Vec2(-1, -1);*/
					if (-pi / 4 < angle && angle < pi / 4)
						move = Vec2(+3, 0);
					if (pi / 4 < angle && angle < 3 * pi / 4)
						move = Vec2(0, 3);
					if (3 * pi / 4 < angle || angle < -3 * pi / 4)
						move = Vec2(-3, 0);
					if (-3 * pi / 4 < angle && angle < -pi / 4)
						move = Vec2(0, -3);
				node->setPosition(node->getPosition() + move);
			}
		}
	}	
}

void Game::updateItemScreen(float dt) {



}

void Game::youWin(cocos2d::Ref* pSender) {
	Director::getInstance()->popScene();
}

/*void Game::paintLabirint() {

	auto node = this->getChildByTag(layerTaq);
	
	Vec2 screenCentre = Vec2(
		node->getAnchorPoint().x * node->getContentSize().width + visibleSize.width / 2.0,
		node->getAnchorPoint().y * node->getContentSize().height + visibleSize.height / 2.0);

	std::vector< std::pair< std::pair<int, int>, std::pair<int, int> > > graph = getEdgeGraph();

	of << graph[0].first.first << " " << graph[0].first.second << " " << graph[0].second.first << " " << graph[0].second.second << "\n";
 
	for (int i = 0; i < graph.size(); ++i) {
		std::pair<std::pair<int, int>, std::pair<int, int> > p = graph[i];
		CCSprite* partSprite;
		if (p.first.first == p.second.first)
			partSprite = Sprite::create("partition.png", CCRect(0, 0, PARTITION_HEIGHT + PARTITION_WIDTH, PARTITION_WIDTH)),
			partSprite->setTag(ROW);
		else
			partSprite = Sprite::create("partition.png", CCRect(0, 0, PARTITION_WIDTH, PARTITION_HEIGHT + PARTITION_WIDTH)),
			partSprite->setTag(COLUMN);
		partSprite->setAnchorPoint(Vec2(0.5, 0.5));
	
		float x = (p.first.first + p.second.first + 1) / 2.0;
		float y = (p.first.second + p.second.second + 1) / 2.0;

		partSprite->setPosition(screenCentre + SQUARE_SIZE*Vec2(x, y));
		node->addChild(partSprite);
		partitions.pushBack(partSprite);
	}

}
*/

/*void Game::updateGame1(float dt) {

	CCObject* it = NULL;

	for (int i = 0; i < partitions.size(); ++i)
	{
		CCSprite* curPart = partitions.at(i);

		CCRect partRect = CCRectMake(
			curPart->getPosition().x,
			curPart->getPosition().y,
			curPart->getContentSize().width,
			curPart->getContentSize().height);

		CCRect mySpriteRect = CCRectMake(
			mySprite->getPosition().x - (mySprite->getContentSize().width / 2),
			mySprite->getPosition().y - (mySprite->getContentSize().height / 2),
			mySprite->getContentSize().width,
			mySprite->getContentSize().height);

		if (partRect.intersectsRect(mySpriteRect)) {
			Vec2 lastPoint = coordinates.back();
			Vec2 newIntersection = mySprite->getPosition();
			coordinates.push_back(newIntersection);
			Vec2 mirrorPoint;

			if (curPart->getTag() == ROW)
				mirrorPoint = Vec2(2 * newIntersection.x - lastPoint.x, lastPoint.y);
			else
				mirrorPoint = Vec2(lastPoint.x, 2 * newIntersection.y - lastPoint.y);

			mySprite->stopAllActions();

			//	of << lastPoint.x << " " << lastPoint.y << "\n";
			///of << newIntersection.x << " " << newIntersection.y << "\n";
			//	of << mirrorPoint.x << " " << mirrorPoint.y << "\n";
			//	of << "\n";
			//	of << "\n";



			Vec2 newVector = mirrorPoint - newIntersection;
			if (newVector.length() < EPS3)
				newVector.x *= 100,
				newVector.y *= 100;
			if (newVector.length() < EPS3)
				newVector = Vec2(1, 1);
			newVector.x *= 100;
			newVector.y *= 100;
			while (newVector.length() < 1000){
				newVector.x *= 10;
				newVector.y *= 10;
			}

			while (newVector.length() > 10000){
				newVector.x /= 10;
				newVector.y /= 10;
			}

			while (abs(newVector.x) > 1000)
				newVector.x /= 1.1;
			while (abs(newVector.y) > 1000)
				newVector.y /= 1.1;

			if (curPart->getTag() == ROW){
				if (mySprite->getPosition().y > curPart->getPosition().y)
					mySprite->setPosition(mySprite->getPosition().x, mySprite->getPosition().y + 8);
				else
					mySprite->setPosition(mySprite->getPosition().x, mySprite->getPosition().y - 8);
			}
			else
			{
				if (mySprite->getPosition().x > curPart->getPosition().x)
					mySprite->setPosition(mySprite->getPosition().x + 8, mySprite->getPosition().y);
				else
					mySprite->setPosition(mySprite->getPosition().x - 8, mySprite->getPosition().y);
			}
			newVector.x += (rand() % 200 - 100);
			newVector.y += (rand() % 200 - 100);

			//			of << newVector.x << " " << newVector.y << " " << newVector.length() << "\n";

			auto moveBy = MoveBy::create(newVector.length() / VELOCITY, newVector);
			//moveTo = MoveTo::create(2, Vec2(5000, 5000));
			mySprite->runAction(moveBy);

			break;
		}

	}



}*/

//of << mySprite->getPosition().x << " " << mySprite->getPosition().y << "\n";
//of << currentObjectRealCentre.x << " " << currentObjectRealCentre.y << "\n";

/*Vec2 direction = mySprite->getPosition() - currentObjectRealCentre;
float len = direction.length();
direction = direction * (1 / len);
of << direction.x << " " << direction.y << "\n";*/

/*if (abs(direction.x / direction.y) > 1 - EPS3) {
if (direction.x > 0 && direction.y > 0)
toMove.push_back(Vec2(-1, -1));
//node->setPosition(node->getPosition() + Vec2(-1, -1));
if (direction.x > 0 && direction.y < 0)
toMove.push_back(Vec2(-1, 1));
//node->setPosition(node->getPosition() + Vec2(-1, +1));
if (direction.x < 0 && direction.y > 0)
toMove.push_back(Vec2(1, -1));
///node->setPosition(node->getPosition() + Vec2(+1, -1));
if (direction.x < 0 && direction.y < 0)
toMove.push_back(Vec2(1, 1));
//node->setPosition(node->getPosition() + Vec2(+1, +1));
}*/

/*if (direction.x > 0 && abs(direction.y) - EPS3 < abs(direction.x)){

of << "first\n";
//node->setPosition(node->getPosition() + Vec2(-2, 0));
toMove.push_back(Vec2(-2, 0));
continue;
}

if (direction.x < 0 && abs(direction.y) - EPS3 < abs(direction.y)){
of << "second\n";
//node->setPosition(node->getPosition() + Vec2(2, 0));
toMove.push_back(Vec2(2, 0));
continue;
}

if (direction.y > 0 && abs(direction.y) + EPS3 > abs(direction.x)){
of << "third\n";
//node->setPosition(node->getPosition() + Vec2(0, -2));
toMove.push_back(Vec2(0, -2));
continue;
}

if (direction.y < 0 && abs(direction.y) + EPS3 > abs(direction.y)){
of << "fourth\n";
//node->setPosition(node->getPosition() + Vec2(0, +2));
toMove.push_back(Vec2(0, 2));
continue;
}
}*/