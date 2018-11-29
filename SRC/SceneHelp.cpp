#include "SceneHelp.h"
#include "LayerMainMenu.h"


bool SceneHelp::init()
{
	if(!Scene::init())
		return false;

	auto vSize=Director::getInstance()->getVisibleSize();
	auto vOrigin=Director::getInstance()->getVisibleOrigin();
	//背景
	auto helpbk=Sprite::create("option.png");
	helpbk->setPosition(vOrigin.x + vSize.width / 2, vOrigin.y + vSize.height / 2);
	//auto repeatAnim=MoveBy::create(3.0f,Vec2(0,50));
	//helpbk->runAction(RepeatForever::create(Sequence::create(repeatAnim, repeatAnim->reverse(), NULL)));
	this->addChild(helpbk, 0);

	//帮助
	/*Dictionary* strings = Dictionary::createWithContentsOfFile("images/language.xml");
	const char * str;
	str = ((String *)strings->objectForKey("help"))->getCString();
	auto label = Label::createWithSystemFont(str,"宋体", 30);
	label->setPosition(Vec2(vOrigin.x + vSize.width / 2, vOrigin.y + vSize.height / 2));
	this->addChild(label, 3); */
	/*CCLabelTTF *text2 = CCLabelTTF::create("空格","站酷快乐体2016修订版.ttf",20);
	text2->setPosition(vOrigin.x + vSize.width / 2, vOrigin.y + vSize.height / 2);
	this->addChild(text2,3);*/
	auto HelpLabel=Sprite::create("helpLable.png");
	HelpLabel->setPosition(vOrigin.x+vSize.width/2,vOrigin.y+vSize.height/2);
	this->addChild(HelpLabel,1);
	Dictionary *strings = Dictionary::createWithContentsOfFile("language.xml");
	//label_jump->setColor(Color3B::GREEN);
	//label_slide->setColor(Color3B::GREEN);
	const char *help = ((String*)strings->objectForKey("help"))->getCString(); //查找xml文件key值
	const char *jump = ((String*)strings->objectForKey("jump"))->getCString(); //查找xml文件key值
	const char *slide = ((String*)strings->objectForKey("slide"))->getCString(); //查找xml文件key值

	//创建label标签菜单
	    auto label_help = LabelTTF::create(help, "fonts/站酷快乐体2016修订版.ttf", 24);
		auto label_jump = LabelTTF::create(jump, "fonts/站酷快乐体2016修订版.ttf", 24);
		auto label_slide = LabelTTF::create(slide, "fonts/站酷快乐体2016修订版.ttf", 24);

		//设置菜单坐标位置
		label_help->setPosition(vOrigin.x + vSize.width / 2, vOrigin.y + vSize.height / 2 + 10);
		label_jump->setPosition(vOrigin.x + vSize.width / 2, vOrigin.y + vSize.height / 2 + 30);

		label_slide->setPosition(vOrigin.x + vSize.width / 2, vOrigin.y + vSize.height / 2 + 60);


		//添加进图层
		this->addChild(label_help, 2);
		this->addChild(label_jump,2);

		this->addChild(label_slide,2);

	
	/*CCLabelBMFont *text = CCLabelBMFont::create("help", "bitmapFontChinese.fnt");
	text->setPosition(vOrigin.x + vSize.width / 2, vOrigin.y + vSize.height / 2 );
	this->addChild(text, 2);
	auto text1 = LabelBMFont::create("跳跃", "help.fnt");
	text1->setPosition(vOrigin.x + vSize.width / 2, vOrigin.y + vSize.height / 2 + 15);
	this->addChild(text1, 2);*/
	

	
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