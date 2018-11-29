#include "LayerMainMenu.h"
#include "SceneGame.h"
#include "SceneSeting.h"
#include "SceneAbout.h"
#include "SceneHelp.h"

extern bool isSound;

Scene *LayerMainMenu::createScene()
{
	auto *scene=Scene::create();
	auto *layer=LayerMainMenu::create();
	scene->addChild(layer);
	return scene;
}

bool LayerMainMenu::init()
{
	if(!Layer::init())
		return false;

	//屏幕属性
	auto vSize=Director::getInstance()->getVisibleSize();
	auto vOrigin=Director::getInstance()->getVisibleOrigin();

	//为场景添加背景图片
	auto menuBackGround=Sprite::create("menu.png");
	menuBackGround->setPosition(Point(vOrigin.x+vSize.width/2,vOrigin.y+vSize.height/2));
	this->addChild(menuBackGround,0);

	//为场景添加主角动画
	auto tinSprite=Sprite::create();
	tinSprite->setPosition(vOrigin.x+vSize.width/2+220,vOrigin.y+vSize.height/2+10);
	this->addChild(tinSprite,0);
	auto tinAnim=Animate::create(AnimationCache::getInstance()->animationByName("tinAnimation"));
	tinSprite->runAction(RepeatForever::create(tinAnim));

	auto cjSprite=Sprite::create();
	cjSprite->setPosition(vOrigin.x+vSize.width/2+330,vOrigin.y+vSize.height/2+20);
	this->addChild(cjSprite,0);
	auto cjAnim=Animate::create(AnimationCache::getInstance()->animationByName("cjAnimation"));
	cjSprite->runAction(RepeatForever::create(cjAnim));


	//添加菜单
	auto newGameItem=MenuItemImage::create("start.png","startpress.png",CC_CALLBACK_1(LayerMainMenu::CallBackStartItem,this));
	newGameItem->setPosition(Point(vOrigin.x+vSize.width/2+280,vOrigin.y+vSize.height/2-60));
	
	auto optionItem=MenuItemImage::create("optionbtn.png","optionbtnpress.png",CC_CALLBACK_1(LayerMainMenu::CallBackOptionItem,this));
	optionItem->setPosition(Point(vOrigin.x+vSize.width/2+280,vOrigin.y+vSize.height/2-110));
	
	auto aboutItem=MenuItemImage::create("about.png","aboutpress.png",CC_CALLBACK_1(LayerMainMenu::CallBackAboutItem,this));
	aboutItem->setPosition(Point(vOrigin.x+vSize.width/2+280,vOrigin.y+vSize.height/2-160));

	auto helpItem = MenuItemImage::create("help.png", "helppress.png", CC_CALLBACK_1(LayerMainMenu::CallBackHelpItem, this));
	helpItem->setPosition(Point(vOrigin.x + vSize.width / 2 + 280, vOrigin.y + vSize.height / 2 - 210));


	auto menu=Menu::create(newGameItem,optionItem,aboutItem,helpItem,NULL);
	menu->setPosition(Point::ZERO);
	this->addChild(menu,1);

}


void LayerMainMenu::onEnter()
{
	Layer::onEnter();
}

void LayerMainMenu::onExit()
{
	Layer::onExit();
}

void LayerMainMenu::CallBackStartItem(Ref *sender)
{
	//game场景
	auto gameScene=SceneGame::createScene();
	TransitionScene *transition=TransitionPageTurn::create(0.5f,gameScene,false);
	Director::getInstance()->replaceScene(transition);
}

void LayerMainMenu::CallBackOptionItem(Ref *sender)
{
	//选项场景
	auto optionScene=SceneSeting::create();
	TransitionScene *transition=TransitionPageTurn::create(0.5f,optionScene,false);
	Director::getInstance()->replaceScene(transition);
}

void LayerMainMenu::CallBackAboutItem(Ref *sender)
{
	//about场景
	auto aboutScene=SceneAbout::create();
	TransitionScene *transition=TransitionPageTurn::create(0.5f,aboutScene,false);
	Director::getInstance()->replaceScene(transition);
}

void LayerMainMenu::CallBackHelpItem(Ref *sender)
{
	//about场景
	auto helpScene = SceneHelp::create();
	TransitionScene *transition = TransitionPageTurn::create(0.5f, helpScene, false);
	Director::getInstance()->replaceScene(transition);
}
