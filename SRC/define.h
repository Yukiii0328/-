#pragma once


//游戏背景
enum Level
{
	SCHOOL,
	CHINASTYLE
};


//role类型
enum RoleType
{
	Tin,
	CJuan
};

//role状态
enum RoleState
{
	RUN,
	SLIDE,
	JUMP
};

//地图元素枚举
enum BlockType
{
	LAND,  //地板
	NPC,   //npc
	COIN,  //星星
	TOOL,  //道具
	NONE   
};

const float BLOCK_SIZE=80.0f; 
const float PICKUP_SIZE=40.0f;
const float ROLE_RADIUS=50.0f;
const float GRAVITY=-1500.0f;
const float ROLE_SPEED=700.0f;

