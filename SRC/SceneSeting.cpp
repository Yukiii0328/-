#include "SceneSeting.h"
#include "define.h"
#include "LayerMainMenu.h"

//声明外部变量
extern Level level;
extern RoleType roleType;
extern bool isSound;

LabelBMFont *textLevel;
LabelBMFont *textPlayer;
LabelBMFont *textSound;

bool SceneSeting::init()
{
	if(!Scene::init())
		return false;

	auto visibleSize=Director::getInstance()->getVisibleSize();
	auto visibleOrigin=Director::getInstance()->getVisibleOrigin();
	//背景
	auto backGround=Sprite::create("option.png");
	backGround->setPosition(visibleOrigin.x+visibleSize.width/2,visibleOrigin.y+visibleSize.height/2);
	//auto repeatAnim=MoveBy::create(3.0f,Vec2(0,40));
	//backGround->runAction(RepeatForever::create(Sequence::create(repeatAnim,repeatAnim->reverse(),NULL)));
	this->addChild(backGround,0);

	//文本标签
	textLevel=LabelBMFont::create("Map: School","bitmapFontChinese.fnt");
	textLevel->setPosition(visibleOrigin.x+420,visibleOrigin.y+230);
	this->addChild(textLevel);

	textPlayer=LabelBMFont::create("player:Tin","bitmapFontChinese.fnt");
	textPlayer->setPosition(visibleOrigin.x+420,visibleOrigin.y+180);
	this->addChild(textPlayer);

	textSound=LabelBMFont::create("sound: on","bitmapFontChinese.fnt");
	textSound->setPosition(visibleOrigin.x+420,visibleOrigin.y+130);
	this->addChild(textSound);

	//菜单
	auto backItem=MenuItemImage::create("homeon.png","homeoff.png",[](Object *sender)
	{
		auto mainMenu=LayerMainMenu::createScene();
		TransitionScene *transition=TransitionFade::create(1.0f,mainMenu);
		Director::getInstance()->replaceScene(transition);
	});
	backItem->setPosition(visibleOrigin.x+backItem->getContentSize().width/2+5,visibleOrigin.y+visibleSize.height-backItem->getContentSize().height/2-5);
	

	//School
	auto scItem=MenuItemImage::create("School.png","Schoolnight.png",[](Object *sender)
	{
		level=SCHOOL;
		textLevel->setString("Map: School");
	});
	

	scItem->setPosition(visibleOrigin.x+visibleSize.width/4+65,visibleOrigin.y+visibleSize.height/4*3);
	//cnstyle
	auto cnItem=MenuItemImage::create("cn.png","cnnight.png",[](Object *sender)
	{
		level=CHINASTYLE;
		textLevel->setString("Map: China");
	});
	cnItem->setPosition(visibleOrigin.x+visibleSize.width/4*3-5,visibleOrigin.y+visibleSize.height/4*3);
	//tin
	auto tinItem=MenuItemImage::create("tin1.png","tin_jump.png",[](Object *sender)
	{
		roleType=Tin;
		textPlayer->setString("player: Tin");
	});
	tinItem->setPosition(visibleOrigin.x+visibleSize.width/2-160,visibleOrigin.y+visibleSize.height/2-50);
	//cj
	auto cjItem=MenuItemImage::create("cj1.png","cj_jump.png",[](Object *sender)
	{
		roleType=CJuan;
		textPlayer->setString("player: Juan");
	});
	cjItem->setPosition(visibleOrigin.x+visibleSize.width/2+200,visibleOrigin.y+visibleSize.height/2-50);

	//声音开关
	auto soundItem=MenuItemImage::create("soundon.png","soundoff.png",[](Object *sender)
	{
		isSound=!isSound;
		textSound->setString(isSound?"sound: On":"sound: Off");
	});
	soundItem->setPosition(visibleOrigin.x+soundItem->getContentSize().width/2+5,visibleOrigin.y+soundItem->getContentSize().height/2+5);


	auto menu=Menu::create(backItem,scItem,cnItem,tinItem,cjItem,soundItem,NULL);
	menu->setPosition(Point::ZERO);

	this->addChild(menu);
	return true;
}