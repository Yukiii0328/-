#include "SimpleAudioEngine.h"
#include "SceneResLoad.h"
#include "LayerMainMenu.h"

using namespace cocos2d;
using namespace CocosDenshion;


bool SceneResLoad::init()
{
	if (!Scene::init())
		return false;
	//屏幕的大小属性
	Size vSize=Director::getInstance()->getVisibleSize();
	Vec2 vOrigin=Director::getInstance()->getVisibleOrigin();
	
	auto TinBackground=Sprite::create("loading.png");
	TinBackground->setPosition(Vec2(vOrigin.x+ vSize.width/2 , vOrigin.y+ vSize.height/2));
	this->addChild(TinBackground);



	//为场景添加进度条
	
			 Sprite *progress=Sprite::create("sliderTrack.png"); //进度条框
	Size progressBackSize=progress->getContentSize();
	progress->setPosition(Point(vOrigin.x+100+progressBackSize.width/2+60, vOrigin.y+120));
	this->addChild(progress,1);


	loading= ProgressTimer::create(Sprite::create("sliderProgress.png"));
	loading->setBarChangeRate(Vec2(1, 0)); //方向的设置
	loading->setType(ProgressTimer::Type::BAR); //形状的设置
	loading->setMidpoint(Vec2(0, 1)); //从左到右
	Size progressSize = loading->getContentSize();
	loading->setPosition(Point(vOrigin.x + 100 + progressSize.width / 2 + 60, vOrigin.y + 120));
	loading->setPercentage(0.0f);
	this->addChild(loading,2);

	return true;
}

void SceneResLoad::onEnter()
{
	//动画资源的预加载
	auto tinAnimation = Animation::create();
	tinAnimation->setDelayPerUnit(0.1f);
	for (int i = 1; i <= 12; i++)
	{
		char str[50] = { 0 };
		sprintf(str, "tin%d.png", i);
		tinAnimation->addSpriteFrameWithFile(str);
	}

	AnimationCache::getInstance()->addAnimation(tinAnimation, "tinAnimation");

	auto cjAnimation = Animation::create();
	cjAnimation->setDelayPerUnit(0.2f);
	for (int i = 1; i <= 8; i++)
	{
		char str[50] = { 0 };
		sprintf(str, "cj%d.png", i);
		cjAnimation->addSpriteFrameWithFile(str);
	}
	AnimationCache::getInstance()->addAnimation(cjAnimation, "cjAnimation");
	loading->setPercentage(50.0f);

	//音乐和音效资源的预加载
	SimpleAudioEngine::getInstance()->preloadBackgroundMusic("spring_music.wav");
	SimpleAudioEngine::getInstance()->preloadBackgroundMusic("winter_music.mp3");

	SimpleAudioEngine::getInstance()->preloadEffect("jump.wav");
	SimpleAudioEngine::getInstance()->preloadEffect("point.mp3");
	SimpleAudioEngine::getInstance()->preloadEffect("gameover.wav");
	loading->setPercentage(100.0f);

	//完毕之后跳转到游戏场景
	auto mainMenu = LayerMainMenu::createScene();
	TransitionScene *transition = TransitionFade::create(3.0f, mainMenu);
	Director::getInstance()->replaceScene(transition);


}
