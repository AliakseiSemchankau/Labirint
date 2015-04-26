#pragma once
#include "HighScoreScene.h"
#include "Constants.h"
#include <iostream>
#include <fstream>
#include <vector>
USING_NS_CC;

//std::ofstream of("cerrLog.txt");

Scene* HighScore::createScene()
{
	std::ofstream of("output.txt");

	// 'scene' is an autorelease object
	auto scene = Scene::create();

	// 'layer' is an autorelease object
	auto layer = HighScore::create();

	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;
}

// on "init" you need to initialize your instance
bool HighScore::init()
{
	std::ofstream of("HighScoreInitDebugOutput.txt");
	of << "HighScore::init()\n";
	//////////////////////////////
	// 1. super init first
	if (!Layer::init())
	{
		return false;
	}

	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	auto menuItemBack = MenuItemFont::create("Back", CC_CALLBACK_1(HighScore::back, this));

	menuItemBack->setPosition(origin.x + visibleSize.width*0.9, origin.y + visibleSize.height*0.1);

	auto *menu = Menu::create(menuItemBack, NULL);
	menu->setPosition(origin.x, origin.y);
	this->addChild(menu);

	return true;
}

void HighScore::back(cocos2d::Ref* pSender) {

	Director::getInstance()->popScene();

}


