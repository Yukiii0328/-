#pragma once
#include "cocos2d.h"

//该类用来预加载游戏需要的资源
class SceneResLoad : public cocos2d::Scene
{
public:
	virtual bool init() override;
	CREATE_FUNC(SceneResLoad);
private:
	virtual void onEnter() override;//重载

private:
	cocos2d::ProgressTimer *loading; //进度条
};