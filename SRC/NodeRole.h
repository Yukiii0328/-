#pragma once
#include "cocos2d.h"
#include "define.h"
using namespace cocos2d;

class NodeRole:public Node
{
public:
	virtual bool init() override;
	CREATE_FUNC(NodeRole);
public:
	void run(); //奔跑
	void jump(); //跳跃
	void slide(); //滑行
	RoleState RoleState; //状态
private:
	Sprite *RoleSprite; //主角精灵
	Sprite *RoleSpriteSlideJump;
	Animate *RoleAnim; //主角动画
	Texture2D *jumpTexture;
	Texture2D *slideTexture;
	
};
