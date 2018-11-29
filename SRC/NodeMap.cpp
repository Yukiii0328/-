#include "NodeMap.h"
#include "define.h"

extern Level level;

bool NodeMap::init()
{
	if(!Node::init())
		return false;
	return true;
}



void NodeMap::initMap()
{
	srand((unsigned)time(NULL));
	//添加地板
	std::string blockland;
	std::string thenpc;
	std::string thetool;
	switch (level)
	{
	case SCHOOL:
		blockland = "blocksc.png";
		thenpc = "pangxie.png";
		thetool = "coin.png";
		break;
	case CHINASTYLE:
		blockland = "blockguf.png";
		thenpc = "baozi.png";
		thetool="taohua.png";
		break;
	}

	
	std::string tool_file = "buff.png";

	
	//地图的搭建
	//第一排地图
	for (int i = 0; i<10; i++)//每一个元素宽度是80,然后屏幕的宽度是800,所以一层最多容下10个元素
	{
		
		if (i != 3 && i != 4&& i != 5 && i != 8&&i!=9)//根据i的下标确定要在每层中的10个空位的哪个空位填充元素

		{
			//添加地板
			auto land = Sprite::create(blockland);
			land->setPosition(BLOCK_SIZE / 2 + i*BLOCK_SIZE, BLOCK_SIZE / 2 + 1 * BLOCK_SIZE);
			this->addChild(land);
			land->setTag(LAND); //设置tag
			auto landBody = PhysicsBody::createBox(land->getContentSize());
			landBody->setDynamic(false);
			landBody->setContactTestBitmask(1);//用于碰撞检测
			landBody->getShape(0)->setRestitution(0);
			land->setPhysicsBody(landBody);
		}
	}
	//第二排地图
	for (int i = 0; i<10; i++)
	{
		auto npci = rand() % 8;
		if (npci == 7)
		{
			//添加npc
			auto npc = Sprite::create(thenpc);
			npc->setTag(NPC);
			npc->setPosition(BLOCK_SIZE / 2 + i*BLOCK_SIZE, BLOCK_SIZE / 2 + 2 * BLOCK_SIZE);
			auto npcBody = PhysicsBody::createBox(npc->getContentSize());
			npcBody->setDynamic(false);
			npcBody->setContactTestBitmask(1);
			npcBody->getShape(0)->setRestitution(0);
			npc->setPhysicsBody(npcBody);
			this->addChild(npc);
		}
		auto block = rand() % 5;//出现砖块概率
		//auto blockHigh = rand() % 94;
		if (block == 3)
		//if (i == 3)
		{
			//for (int j = 0; j < blockHigh; j++)
			//{
			
			//添加地板
			auto land = Sprite::create(blockland);
			land->setPosition(BLOCK_SIZE / 2 + i*BLOCK_SIZE, BLOCK_SIZE / 2 + 2 * BLOCK_SIZE);
			this->addChild(land);
			land->setTag(LAND); //设置tag
			auto landBody = PhysicsBody::createBox(land->getContentSize());
			landBody->setDynamic(false);
			landBody->setContactTestBitmask(1);
			landBody->getShape(0)->setRestitution(0);
			land->setPhysicsBody(landBody);
			//}
		}
		
	}
	//第三排地图
	for (int i = 0; i<10; i++)
	{
		
		if (i == 0)
		{
			//添加coin
			auto coin1 = Sprite::create(thetool);
			coin1->setTag(COIN);
			coin1->setPosition(PICKUP_SIZE / 2 + i*BLOCK_SIZE, BLOCK_SIZE / 2 + 3 * BLOCK_SIZE);
			auto coinBody1 = PhysicsBody::createBox(coin1->getContentSize());
			coinBody1->setDynamic(false);
			coinBody1->setContactTestBitmask(1);
			coinBody1->getShape(0)->setRestitution(0.0f);
			coin1->setPhysicsBody(coinBody1);
			this->addChild(coin1);

			auto coin2 = Sprite::create(thetool);
			coin2->setTag(COIN);
			coin2->setPosition(PICKUP_SIZE / 2 * 3 + i*BLOCK_SIZE, BLOCK_SIZE / 2 + 3 * BLOCK_SIZE);
			auto coinBody2 = PhysicsBody::createBox(coin2->getContentSize());
			coinBody2->setDynamic(false);
			coinBody2->setContactTestBitmask(1);
			coinBody2->getShape(0)->setRestitution(0.0f);
			coin2->setPhysicsBody(coinBody2);
			this->addChild(coin2);

		}

	}
	//第四排地图
	for (int i = 0; i<10; i++)
	{
		auto block = rand() % 10;//出现砖块概率
		//auto blockHigh = rand() % 4;
		if (block == 3 || block == 4)
		{
			//for (int j = 0; j < blockHigh; j++)
			//{
				//添加地板
				auto land = Sprite::create(blockland);
				land->setPosition(BLOCK_SIZE / 2 + i*BLOCK_SIZE, BLOCK_SIZE / 2 + 4 * BLOCK_SIZE + 40);
				this->addChild(land);
				land->setTag(LAND); //设置tag
				auto landBody = PhysicsBody::createBox(land->getContentSize());
				landBody->setDynamic(false);
				landBody->setContactTestBitmask(1);
				landBody->getShape(0)->setRestitution(0);
				land->setPhysicsBody(landBody);
			//}

		}
		auto coini = rand() % 5;
		if (coini == 3)
		{
			auto coin1 = Sprite::create(thetool);
			coin1->setTag(COIN);
			coin1->setPosition(PICKUP_SIZE / 2 + i*BLOCK_SIZE, BLOCK_SIZE / 2 + 4 * BLOCK_SIZE);
			auto coinBody1 = PhysicsBody::createBox(coin1->getContentSize());
			coinBody1->setDynamic(false);
			coinBody1->setContactTestBitmask(1);
			coinBody1->getShape(0)->setRestitution(0);
			coin1->setPhysicsBody(coinBody1);
			this->addChild(coin1);

			auto coin2 = Sprite::create(thetool);
			coin2->setTag(COIN);
			coin2->setPosition(PICKUP_SIZE / 2 * 3 + i*BLOCK_SIZE, BLOCK_SIZE / 2 + 4 * BLOCK_SIZE);
			auto coinBody2 = PhysicsBody::createBox(coin2->getContentSize());
			coinBody2->setDynamic(false);
			coinBody2->setContactTestBitmask(1);
			coinBody2->getShape(0)->setRestitution(0.0f);
			coin2->setPhysicsBody(coinBody2);
			this->addChild(coin2);
		}
		if (i == 6)
		{
			//添加道具
			auto tool = Sprite::create(tool_file);
			tool->setTag(TOOL);
			tool->setPosition(PICKUP_SIZE / 2 + i*BLOCK_SIZE, BLOCK_SIZE / 2 + 4 * BLOCK_SIZE);
			auto toolBody = PhysicsBody::createBox(tool->getContentSize());
			toolBody->setDynamic(false);
			toolBody->setContactTestBitmask(1);
			toolBody->getShape(0)->setRestitution(0.0f);
			tool->setPhysicsBody(toolBody);
			this->addChild(tool);
		}
	}
}

void NodeMap::clearMap()
{
	this->removeAllChildrenWithCleanup(true);
}
