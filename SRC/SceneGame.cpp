#include "SimpleAudioEngine.h"
#include "define.h"
#include "LayerMainMenu.h"
#include "SceneGame.h"
#include "NodeMap.h"

using namespace CocosDenshion;

//全局变量亦作为其他文件的外部变量
extern Level level=SCHOOL;
extern RoleType roleType =Tin;
extern bool isSound=true;

int jumpTimes=0; //当前跳跃次数
int jumpTotal=2; //最多跳跃次数，防止跳跃过高

Scene *SceneGame::createScene()
{
	//为场景添加一个物理世界
	auto *scene=Scene::createWithPhysics();
	scene->getPhysicsWorld()->setGravity(Vec2(0,GRAVITY));
	//scene->getPhysicsWorld()->setContinuousPhysics(true);不能用
	auto *layer=SceneGame::create();
	scene->addChild(layer);
	return scene;
}

bool SceneGame::init()
{
	if(!Layer::init())
		return false;

	//获取屏幕大小及原点位置
	vSize=Director::getInstance()->getVisibleSize();
	vOrigin=Director::getInstance()->getVisibleOrigin();

	//背景
	std::string backGroundFile;
	switch(level)
	{
	case SCHOOL:
		backGroundFile="Schoolbk.png";
		break;
	case CHINASTYLE:
		backGroundFile="cnstyle.png";
		break;
	}
	backGround1=Sprite::create(backGroundFile);
	backGround1->setAnchorPoint(Point::ZERO);
	backGround1->setPosition(Point::ZERO);
	this->addChild(backGround1,0);
	backGround2=Sprite::create(backGroundFile);
	backGround2->setAnchorPoint(Point::ZERO);
	backGround2->setPosition(vOrigin.x + vSize.width-2, vOrigin.y);
	this->addChild(backGround2,0);

	//地图1
	gameMap=NodeMap::create();
	gameMap->setPosition(vOrigin.x,vOrigin.y);
	gameMap->initMap();
	this->addChild(gameMap,1);
	//地图2与地图1形成地图滚动
	gameMap2 = NodeMap::create();
	gameMap2->setPosition(vOrigin.x+800, vOrigin.y);
	gameMap2->initMap();
	this->addChild(gameMap2, 1);


	//添加player主角
	player=NodeRole::create();
	player->setPosition(Point(vOrigin.x+2*BLOCK_SIZE,vOrigin.y+4*BLOCK_SIZE));
	this->addChild(player,1);


	//滑行和跳跃
	score=0; //初始化分数
	hp = 100;//初始化血量
	slideBtn=Sprite::create("slideButton.png");
	auto slideBtnTexture1=Sprite::create("slideButton.png")->getTexture();
	auto slideBtnTexture2=Sprite::create("slideButtonPress.png")->getTexture();
	slideBtnTextures.pushBack(slideBtnTexture1);
	slideBtnTextures.pushBack(slideBtnTexture2);
	slideBtn->setScale(0.5);
	slideBtn->setPosition(Point(vOrigin.x+100,vOrigin.y+50));
	this->addChild(slideBtn,2);

	jumpBtn=Sprite::create("jumpButton.png");
	auto jumpBtnTexture1=Sprite::create("jumpButton.png")->getTexture();
	auto jumpBtnTexture2=Sprite::create("jumpButtonPress.png")->getTexture();
	jumpBtnTextures.pushBack(jumpBtnTexture1);
	jumpBtnTextures.pushBack(jumpBtnTexture2);
	jumpBtn->setScale(0.5);
	jumpBtn->setPosition(Point(vOrigin.x+vSize.width-100,vOrigin.y+50));
	this->addChild(jumpBtn,2);

	//为场景加入UI，分数
	scoreLabel=LabelBMFont::create("score: ","bitmapFontChinese.fnt");
	scoreLabel->setPosition(vOrigin.x+vSize.width-150,vOrigin.y+vSize.height-20);
	this->addChild(scoreLabel,2);
	scoreLabel->setString(String::createWithFormat("score: %d",score)->_string);
	//添加血量标签：
	hpLabel = LabelBMFont::create("hp: ", "bitmapFontChinese.fnt");
	hpLabel->setPosition(vOrigin.x+150, vOrigin.y + vSize.height - 20);
	this->addChild(hpLabel, 2);
	hpLabel->setString(String::createWithFormat("hp: %d", hp)->_string);

	this->scheduleUpdate();//启动默认定时器
	this->schedule(schedule_selector(SceneGame::backGroundUpdate),0.02f); //背景滚屏

	//碰撞监测
	auto contactListener=EventListenerPhysicsContact::create();
	contactListener->onContactBegin=CC_CALLBACK_1(SceneGame::onContactBegin,this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(contactListener,this);

	//触摸监听
	auto touchListener=EventListenerTouchOneByOne::create();
	touchListener->onTouchBegan=CC_CALLBACK_2(SceneGame::onTouchBegan,this);
	touchListener->onTouchEnded=CC_CALLBACK_2(SceneGame::onTouchEnded,this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener,this);

	//键盘监听：
	auto listener = EventListenerKeyboard::create();
	listener->onKeyPressed = CC_CALLBACK_2(SceneGame::onKeyPressed, this);
	listener->onKeyReleased = CC_CALLBACK_2(SceneGame::onKeyReleased, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

	

	//调度器，用于地图滚动
	this->schedule(schedule_selector(SceneGame::mapUpdate), 0.01f);
	return true;
}

void SceneGame::onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event)
{
	if (keyCode == EventKeyboard::KeyCode::KEY_S || keyCode == EventKeyboard::KeyCode::KEY_DOWN_ARROW)
	{
		if (slideBtn != nullptr){slideBtn->setTexture(slideBtnTextures.at(1));}
		if (player != nullptr) { player->slide(); }
	}
	if (jumpTimes < jumpTotal&&keyCode == EventKeyboard::KeyCode::KEY_SPACE)
	{
		if (isSound)
			SimpleAudioEngine::getInstance()->playEffect("jump.wav"); //播放跳跃音效
		if (jumpBtn != nullptr){jumpBtn->setTexture(jumpBtnTextures.at(1));}
		if (player != nullptr) { player->jump(); }
		jumpTimes++;
	}
}

void SceneGame::onKeyReleased(EventKeyboard::KeyCode keyCode, Event* event)
{
	//判断是释放时是否在按钮区域
	if (keyCode == EventKeyboard::KeyCode::KEY_S || keyCode == EventKeyboard::KeyCode::KEY_DOWN_ARROW)
	{
		if (slideBtn != nullptr) { slideBtn->setTexture(slideBtnTextures.at(0)); }
		if (player != nullptr) { player->run(); }
	}

	if (keyCode == EventKeyboard::KeyCode::KEY_SPACE)
	{
		if (jumpBtn != nullptr) { jumpBtn->setTexture(jumpBtnTextures.at(0)); }
	}
}

void SceneGame::mapUpdate(float dt)
{
	gameMap->setPositionX(gameMap->getPositionX() - 3.0f);
	gameMap2->setPositionX(gameMap2->getPositionX() - 3.0f);
	if (gameMap->getPositionX() <= -800)
	{
		gameMap->clearMap();
		gameMap->setPosition(800, 0);
		gameMap->initMap();

	}

	if (gameMap2->getPositionX() <= -800)
	{
		gameMap2->clearMap();
		gameMap2->setPosition(800, 0);
		gameMap2->initMap();

	}

	
}
void SceneGame::backGroundUpdate(float dt)
{
	backGround1->setPositionX(backGround1->getPositionX() - 1.0f);
	backGround2->setPositionX(backGround1->getPositionX() + backGround1->getContentSize().width);
	if (backGround2->getPositionX() <= 0.0f)
	{
		backGround1->setPositionX(0.0f);
		backGround2->setPositionX(backGround1->getPositionX() + backGround1->getContentSize().width);
	}

}
bool SceneGame::onTouchBegan(Touch *touch,Event *event)
{
	auto touchPoint=touch->getLocation();
	//是否在按钮内触摸
	if (slideBtn != nullptr)
	{
		if (slideBtn->getBoundingBox().containsPoint(touchPoint))
		{
			slideBtn->setTexture(slideBtnTextures.at(1));
			player->slide();
		}
	}
	if (jumpBtn != nullptr)
	{
		if (jumpTimes<jumpTotal&&jumpBtn->getBoundingBox().containsPoint(touchPoint))
		{
			if (isSound)
				SimpleAudioEngine::getInstance()->playEffect("jump.wav"); 
			jumpBtn->setTexture(jumpBtnTextures.at(1));
			player->jump();
			jumpTimes++;
		}
	}
	
		
	return true;
}

void SceneGame::onTouchEnded(Touch *touch,Event *event)
{
	auto touchPoint=touch->getLocation();

	if (slideBtn != nullptr)
	{
		if (slideBtn->getBoundingBox().containsPoint(touchPoint))
		{
			slideBtn->setTexture(slideBtnTextures.at(0));
			player->run();
		}
	}
	
	if (jumpBtn != nullptr)
	{
		if (jumpBtn->getBoundingBox().containsPoint(touchPoint))
		{
			jumpBtn->setTexture(jumpBtnTextures.at(0));
		}
	}
	

}

void SceneGame::update(float dt)
{
	
	player->setRotation(0.0f); //保持不旋转 防止角色碰撞而转动
	//当角色在物理世界中被挡道之后，要回到原来的位置
	float step=6.0f;
	if (player->RoleState == JUMP)
	{
		this->schedule(schedule_selector(SceneGame::mapUpdate), 0.01f);
		this->schedule(schedule_selector(SceneGame::backGroundUpdate), 0.02f);
	}
	if (player->getPositionX() < 2 * BLOCK_SIZE)
	player->setPositionX(player->getPositionX()+step);
	
	if(player->getPositionX()>2*BLOCK_SIZE)
		player->setPositionX(player->getPositionX()-step);

	//游戏结束
	if(player->getPositionY()<=0.0f)
		gameOver();
}

bool SceneGame::onContactBegin(const PhysicsContact &contact)
{
	
	jumpTimes=0;
	if (player == nullptr)return true;
	//碰撞的双方  碰撞的双方都要进行检查
	auto target=contact.getShapeA()->getBody()->getNode();
	auto target2 = contact.getShapeB()->getBody()->getNode();
	if (target->getTag() == LAND&&player->RoleState!=JUMP&&target->getPositionY() + target->getContentSize().height / 2 >= player->getPositionY() && target->getPositionY()<= player->getPositionY())
	{
		this->unschedule(schedule_selector(SceneGame::backGroundUpdate));//被地板挡住去路时停止背景的滚动
		this->unschedule(schedule_selector(SceneGame::mapUpdate));//被地板挡住去路时停止地图的滚动
	}
	else if (target2->getTag() == LAND&&player->RoleState!=JUMP &&target2->getPositionY() + target2->getContentSize().height / 2 >= player->getPositionY() && target2->getPositionY() <= player->getPositionY())
	{
		this->unschedule(schedule_selector(SceneGame::backGroundUpdate));
		this->unschedule(schedule_selector(SceneGame::mapUpdate));
	}
	
		if (target->getTag() == COIN)
		{
			//coin消失
			target->removeFromParentAndCleanup(true);
			addScore(100); //加分
		}
		else if (target2->getTag() == COIN)
		{
			target2->removeFromParentAndCleanup(true);
			addScore(100); 
		}

		else if (target->getTag() == NPC&&target->getPositionY() + target->getContentSize().height / 2 > player->getPositionY()- player->getContentSize().height/2) //主角正遇怪物减血
		{
			hp -= 20;
			hpLabel->setString(String::createWithFormat("hp: %d", hp)->_string);
			player->runAction(Blink::create(2, 10));
			//player->setOpacity(player->getOpacity()+hp);无效
			if (hp <= 0)
			{
				player->runAction(Sequence::create(
					Blink::create(1, 10)
					, CCCallFuncN::create(player, callfuncN_selector(SceneGame::onKillPlayer))
					,NULL));
				gameOver();
				//player->setOpacity(128);//完全透明
			}
		}
		else if (target2->getTag() == NPC&&target2->getPositionY() + target2->getContentSize().height / 2 > player->getPositionY() - player->getContentSize().height / 2)
		{
			hp -= 20;
			hpLabel->setString(String::createWithFormat("hp: %d", hp)->_string);
			player->runAction(Blink::create(2, 10));
			//player->setOpacity(player->getOpacity() + hp);
			if (hp <= 0)
			{
				player->runAction(Sequence::create(
					Blink::create(1, 10)
					, CCCallFuncN::create(player, callfuncN_selector(SceneGame::onKillPlayer))
					, NULL));
				gameOver();
				//player->setOpacity(128);//完全透明
			}
		}

	else if(target->getTag()==NPC&&target->getPositionY()+target->getContentSize().height/2<=player->getPositionY() - player->getContentSize().height / 2) //角色在npc头上才能踩扁
	{
		target->removeFromParentAndCleanup(true);
		addScore(150); //加分
	}
	else if (target2->getTag() == NPC&&target2->getPositionY() + target2->getContentSize().height / 2<=player->getPositionY() - player->getContentSize().height / 2) 
	{
		target2->removeFromParentAndCleanup(true);
		addScore(150); 
	}

	else if(target->getTag()==TOOL)
	{
		jumpTotal=3;
		auto toolIcon=Sprite::create("3dt.png");
		toolIcon->setPosition(Point(vOrigin.x+180,vOrigin.y+50));
		this->addChild(toolIcon,2,"tool");
		target->removeFromParentAndCleanup(true);//道具出现一次
		addScore(300); //加分
	}
	else if (target2->getTag() == TOOL)
	{
		jumpTotal = 3;
		auto toolIcon = Sprite::create("3dt.png");
		toolIcon->setPosition(Point(vOrigin.x + 180, vOrigin.y + 50));
		this->addChild(toolIcon, 2,"tool");
		target2->removeFromParentAndCleanup(true); 
		addScore(300);
	}

	//落回地面继续跑
		if (player != nullptr)
		{
			if (player->RoleState == JUMP)
			{
				player->run();
			}
		}
		
	return true;
}

void SceneGame::onKillPlayer(Node * node)
{
	node->removeFromParentAndCleanup(true);
}
void SceneGame::onEnter()
{
	Layer::onEnter();
	//播放音乐
	if(isSound)
		SimpleAudioEngine::getInstance()->playBackgroundMusic(level==SCHOOL?"spring_music.wav":"winter_music.mp3",true);
}

void SceneGame::onExit()
{
	Layer::onExit();
	//关闭音乐
	if(SimpleAudioEngine::getInstance()->isBackgroundMusicPlaying())
		SimpleAudioEngine::getInstance()->stopBackgroundMusic();
}



void SceneGame::addScore(float number)
{
	if(isSound)
		SimpleAudioEngine::getInstance()->playEffect("point.mp3");
	score+=number;
	scoreLabel->setString(String::createWithFormat("score: %d",score)->_string);
}

void SceneGame::gameOver()
{

	//停止所有调度器
	gameMap->unscheduleAllSelectors();
	this->unscheduleAllSelectors();
	slideBtn->removeFromParentAndCleanup(true);
	slideBtn = nullptr;
	jumpBtn->removeFromParentAndCleanup(true);
	jumpBtn = nullptr;
	player = nullptr;
	if (this->getChildByName("tool") != nullptr)
	{
		this->getChildByName("tool")->removeFromParentAndCleanup(true);
	}
	//结束声音
	if(isSound)
		SimpleAudioEngine::getInstance()->playEffect("gameover.wav");

	//弹出菜单
	vSize=Director::getInstance()->getVisibleSize();
	vOrigin=Director::getInstance()->getVisibleOrigin();
	
	auto gameOverPanel=Node::create();
	auto overLabel=Sprite::create("gameover.png");
	overLabel->setPosition(vOrigin.x+vSize.width/2,vOrigin.y+vSize.height/2+80);
	gameOverPanel->addChild(overLabel);

	auto backItem=MenuItemImage::create("backtomenu.png","backtomenu_press.png",[](Object *sender)
	{
		//lambda表达式
		auto mainMenu=LayerMainMenu::createScene();
		TransitionScene *transition=TransitionFade::create(1.0f,mainMenu);
		Director::getInstance()->replaceScene(transition);
	});
	auto backMenu=Menu::createWithItem(backItem);
	backMenu->setPosition(vOrigin.x+vSize.width/2,vOrigin.y+vSize.height/2-100);

	gameOverPanel->addChild(backMenu);

	gameOverPanel->setPositionY(vOrigin.y+vSize.height);
	this->addChild(gameOverPanel,3);
	gameOverPanel->runAction(MoveTo::create(0.5f,Vec2(vOrigin.x,vOrigin.y)));

}