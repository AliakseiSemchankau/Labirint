#include "MainMenu.h"

#include "Constants.h"
#include <iostream>
#include <fstream>
USING_NS_CC;

std::ofstream of("cerrLog.txt");

Scene* MainMenu::createScene()
{
	// 'scene' is an autorelease object
	auto scene = Scene::create();

	// 'layer' is an autorelease object
	auto layer = MainMenu::create();

	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;
}

// on "init" you need to initialize your instance
bool MainMenu::init()
{
	//////////////////////////////
	// 1. super init first
	if (!Layer::init())
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
		CC_CALLBACK_1(MainMenu::menuCloseCallback, this));

	closeItem->setPosition(Vec2(origin.x + visibleSize.width - closeItem->getContentSize().width / 2,
		origin.y + closeItem->getContentSize().height / 2));

	auto menuItemPlay = MenuItemFont::create("Play", CC_CALLBACK_1(MainMenu::play, this));
	auto menuItemHighscores= MenuItemFont::create("Highscores", CC_CALLBACK_1(MainMenu::highscores, this));
	auto menuItemExit = MenuItemFont::create("Exit", CC_CALLBACK_1(MainMenu::exit, this));

	menuItemPlay		->setPosition(origin.x + visibleSize.width / 2, origin.y + (visibleSize.height / 4) * 3);
	menuItemHighscores	->setPosition(origin.x + visibleSize.width / 2, origin.y + (visibleSize.height / 4) * 2);
	menuItemExit		->setPosition(origin.x + visibleSize.width / 2, origin.y + (visibleSize.height / 4) * 1);

	auto *menu = Menu::create(menuItemPlay, menuItemHighscores, menuItemExit);

	this->addChild(menu);

	return true;
}

void MainMenu::play(Ref* pSender) {

}

void MainMenu::highscores(Ref* pSender) {

}

void MainMenu::exit(Ref* pSender) {

}



void MainMenu::menuCloseCallback(Ref* pSender)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WP8) || (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
	MessageBox("You pressed the close button. Windows Store Apps do not implement a close button.", "Alert");
	return;
#endif

	Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	exit(0);
#endif
}
