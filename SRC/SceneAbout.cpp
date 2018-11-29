#include "SceneAbout.h"
#include "LayerMainMenu.h"

bool SceneAbout::init()
{
	if(!Scene::init())
		return false;

	auto vSize=Director::getInstance()->getVisibleSize();
	auto vOrigin=Director::getInstance()->getVisibleOrigin();
	//背景
	auto backGround=Sprite::create("option.png");
	backGround->setPosition(vOrigin.x+vSize.width/2,vOrigin.y+vSize.height/2);
	//auto repeatAnim=MoveBy::create(3.0f,Vec2(0,50));
	//backGround->runAction(RepeatForever::create(Sequence::create(repeatAnim,repeatAnim->reverse(),NULL)));
	this->addChild(backGround,0);

	//关于
	/*auto aboutLabel=Sprite::create("helpLable.png");
	aboutLabel->setPosition(vOrigin.x+vSize.width/2,vOrigin.y+vSize.height/2);
	this->addChild(aboutLabel,1);
	auto text=LabelBMFont::create("author:HEY","bitmapFontChinese.fnt");
	text->setPosition(vOrigin.x+vSize.width/2,vOrigin.y+vSize.height/2);
	this->addChild(text,2);*/
	auto HelpLabel = Sprite::create("helpLable.png");
	HelpLabel->setPosition(vOrigin.x + vSize.width / 2, vOrigin.y + vSize.height / 2);
	this->addChild(HelpLabel, 1);
	Dictionary *strings = Dictionary::createWithContentsOfFile("language.xml");
	const char *about = ((String*)strings->objectForKey("about"))->getCString(); //查找xml文件key值
	const char *about1 = ((String*)strings->objectForKey("about1"))->getCString(); //查找xml文件key值
	const char *about2 = ((String*)strings->objectForKey("about2"))->getCString(); //查找xml文件key值
	const char *about3 = ((String*)strings->objectForKey("about3"))->getCString(); //查找xml文件key值
	//创建label标签菜单
	auto label_about = LabelTTF::create(about, "fonts/站酷快乐体2016修订版.ttf", 24);
	auto label_about1 = LabelTTF::create(about1, "fonts/站酷快乐体2016修订版.ttf", 24);
	auto label_about2 = LabelTTF::create(about2, "fonts/站酷快乐体2016修订版.ttf", 24);
	auto label_about3 = LabelTTF::create(about3, "fonts/站酷快乐体2016修订版.ttf", 24);


	//设置坐标位置
	label_about->setPosition(vOrigin.x + vSize.width / 2, vOrigin.y + vSize.height / 2 + 10);
	label_about1->setPosition(vOrigin.x + vSize.width / 2, vOrigin.y + vSize.height / 2 + 30);
	label_about2->setPosition(vOrigin.x + vSize.width / 2, vOrigin.y + vSize.height / 2 - 10);
	label_about3->setPosition(vOrigin.x + vSize.width / 2, vOrigin.y + vSize.height / 2 -  50);
	this->addChild(label_about, 2);
	this->addChild(label_about1, 2);
	this->addChild(label_about2, 2);
	this->addChild(label_about3, 2);
	
	//添加按钮菜单项
	auto backItem=MenuItemImage::create("homeon.png","homeoff.png",[](Object *sender)
	{
		//lambda表达式
		auto mainMenu=LayerMainMenu::createScene();
		TransitionScene *transition=TransitionFade::create(1.0f,mainMenu);
		Director::getInstance()->replaceScene(transition);
	});
	backItem->setPosition(vOrigin.x+backItem->getContentSize().width/2+5,vOrigin.y+vSize.height-backItem->getContentSize().height/2-5);
	auto backMenu=Menu::createWithItem(backItem);
	backMenu->setPosition(Point::ZERO);
	
	this->addChild(backMenu,1);
	

	return true;
}
