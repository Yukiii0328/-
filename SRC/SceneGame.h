#pragma once
#include "cocos2d.h"
#include "NodeRole.h"
#include "NodeMap.h"
USING_NS_CC;

class SceneGame: public Layer
{
public:
	static Scene *createScene();

	CREATE_FUNC(SceneGame);
private:
	virtual bool init() override;
	virtual void onEnter() override;
	virtual void onExit() override;
	virtual bool onTouchBegan(Touch *touch,Event *event) override;
	virtual void onTouchEnded(Touch *touch,Event *event) override;
	//碰撞检测
	bool onContactBegin(const PhysicsContact &contact);
	//定时器
	virtual void update(float dt) override;
private:
	void backGroundUpdate(float dt); //滚动背景
	void addScore(float number); //加分
	void gameOver(); 
	void mapUpdate(float dt);//滚动地图
	//键盘事件
	void onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event);
	void onKeyReleased(EventKeyboard::KeyCode keyCode, Event* event);
	void onKillPlayer(Node * node);
private:
	Size vSize;
	Point vOrigin;

	NodeRole *player; //主角

	Sprite *slideBtn;
	Vector<Texture2D *> slideBtnTextures;
	Sprite *jumpBtn;
	Vector<Texture2D *> jumpBtnTextures;

	Sprite *backGround1,*backGround2; //背景
	NodeMap *gameMap; //地图1
	NodeMap *gameMap2; //地图2与地图1形成地图滚动

	int score; //分数
	int hp;//血量
	LabelBMFont *scoreLabel; //分数精灵
	LabelBMFont *hpLabel; //血量精灵
};