#pragma once
#include "HelloWorldScene.h"
#include "Labyrinth.h"
#include "Constants.h"
#include <vector>
#include <fstream>
USING_NS_CC;

Scene* HelloWorld::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = HelloWorld::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    /////////////////////////////
    // 2. add a menu item with "X" image, which is clicked to quit the program
    //    you may modify it.

    // add a "close" icon to exit the progress. it's an autorelease object
    auto closeItem = MenuItemImage::create(
                                           "CloseNormal.png",
                                           "CloseSelected.png",
                                           CC_CALLBACK_1(HelloWorld::menuCloseCallback, this));
    
	closeItem->setPosition(Vec2(origin.x + visibleSize.width - closeItem->getContentSize().width/2 ,
                                origin.y + closeItem->getContentSize().height/2));

     //create menu, it's an autorelease object
    auto menu = Menu::create(closeItem, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);

	mySprite = Sprite::create("ball.png");
	Vec2 startPosition = Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2);
	mySprite->setPosition(startPosition);
	coordinates.push_back(startPosition);
	this->addChild(mySprite, 2);

	//auto moveTo = MoveTo::create(50 / 1.0, Vec2(200, 2000));
	//mySprite->runAction(moveTo);

	paintLabirint();

	auto listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan = CC_CALLBACK_2(HelloWorld::onTouchBegan, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

	this->schedule(schedule_selector(HelloWorld::updateGame), 0.003);

    return true;
}

void HelloWorld::paintLabirint() {

	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	std::vector< std::pair< std::pair<int, int>, std::pair<int, int> > > graph = getEdgeGraph();

	for (int i = 0; i < graph.size(); ++i) {
		std::pair<std::pair<int, int>, std::pair<int, int> > p = graph[i];
		CCSprite* partSprite;
		if (p.first.first == p.second.first)
			partSprite = Sprite::create("partition.png", CCRect(0, 0, PARTITION_HEIGHT*1.05, PARTITION_WIDTH));
		else
			partSprite = Sprite::create("partition.png", CCRect(0, 0, PARTITION_WIDTH, PARTITION_HEIGHT*1.05));
		partSprite->setAnchorPoint(Vec2(0, 0));
		int setX;
		int setY;
		if (p.first.first == p.second.first)
			setX = origin.x + SQUARE_SIZE*p.first.first,
			setY = origin.y + SQUARE_SIZE*p.first.second,
			partSprite->setTag(ROW);
		else
			setX = origin.x + SQUARE_SIZE*(p.first.first + 1),
			setY = origin.y + SQUARE_SIZE*p.first.second,
			partSprite->setTag(COLUMN);

		partSprite->setPosition(setX - SQUARE_SIZE / 2, setY - SQUARE_SIZE / 2);
		this->addChild(partSprite);
		
		partitions.pushBack(partSprite);
	}

}

bool HelloWorld::onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* event) {



	float toX = touch->getLocation().x;
	float toY = touch->getLocation().y;

	CCLOG("x = %f, y = %f", toX, toY);

	float curX = mySprite->getPosition().x;
	float curY = mySprite->getPosition().y;

	float difX = toX - curX;
	float difY = toY - curY;

	float length = sqrt(difX*difX + difY*difY);
	float velocity = 900.0 / 1.0;

	auto moveTo = MoveTo::create(length / VELOCITY, Vec2(toX, toY));
	
	mySprite->stopAllActions();
	coordinates.push_back(mySprite->getPosition());
	mySprite->runAction(moveTo);

	return true;

}

void HelloWorld::menuCloseCallback(Ref* pSender)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WP8) || (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
	MessageBox("You pressed the close button. Windows Store Apps do not implement a close button.","Alert");
    return;
#endif

    Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}

void HelloWorld::updateGame(float dt) {

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

			while(abs(newVector.x) > 1000)
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
	


}