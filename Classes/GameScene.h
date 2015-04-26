#pragma once
#ifndef __GAME_SCENE_H__
#define __GAME_SCENE_H__

#include "cocos2d.h"
#include "UsefulFunctions.h"
#include "Player.h"
class Game : public cocos2d::Layer
{
protected:
	cocos2d::Vector<cocos2d::Sprite*> spriteObjects;
	std::vector<std::vector<cocos2d::Sprite* > > spriteLabirint;
	std::vector<std::vector<char> > charLabirint;
	Player* mySprite;
	cocos2d::Size visibleSize;
	cocos2d::Vec2 origin;


public:

	// there's no 'id' in cpp, so we recommend returning the class instance pointer
	static cocos2d::Scene* createScene();

	// Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
	virtual bool init();

	// a selector callback
	void mainMenu(cocos2d::Ref* pSender);

	// implement the "static create()" method manually
	CREATE_FUNC(Game);

	//bool onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* event);

	void paintLabirint();

	void paintItemsScreen();

	std::vector<cocos2d::Vec2> coordinates;

	void updateGame(float dt);

	void updateGameKeyboard(float dt);

	void updateItemScreen(float dt);

	void youWin(cocos2d::Ref* pSender);

	bool isKeyPressed(cocos2d::EventKeyboard::KeyCode);

private:
	std::set<cocos2d::EventKeyboard::KeyCode> keys;
	Sprite* itemsScreen;

};

#endif 
//__GAME_SCENE_H__
