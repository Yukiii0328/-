#include "NodeRole.h"


extern RoleType roleType; 

bool NodeRole::init()
{
	if(!Node::init())
		return false;
	//定义动画
	Animation *cjAnimation=Animation::create();
	for(int i=1;i<=8;i++)
		cjAnimation->addSpriteFrameWithFile("cj"+std::to_string(i)+".png");
	cjAnimation->setDelayPerUnit(0.15f);

	Animation *tinAnimation=Animation::create();
	for(int i=1;i<=12;i++)
		tinAnimation->addSpriteFrameWithFile("tin"+std::to_string(i)+".png");
	tinAnimation->setDelayPerUnit(0.1f);

	std::string RoleTextureName;
	std::string RoleJumpTexureName;
	std::string RoleSlideTextureName;
	Animation *RoleAnimation;

	//游戏角色
	switch(roleType)
	{
	case Tin:
		RoleTextureName="tin1.png";
		RoleJumpTexureName="tin_jump.png";
		RoleSlideTextureName="tin_slide.png";
		RoleAnimation=tinAnimation;
		break;
	case CJuan:
		RoleTextureName="cj1.png";
		RoleJumpTexureName="cj_jump.png";
		RoleSlideTextureName="cj_slide.png";
		RoleAnimation=cjAnimation;
		break;
	}

	

	RoleSprite=Sprite::create(RoleTextureName); //此处一张角色纹理来确定精灵的大小
	
	jumpTexture=Sprite::create(RoleJumpTexureName)->getTexture(); //跳跃
	slideTexture=Sprite::create(RoleSlideTextureName)->getTexture(); //滑行

	RoleAnim=Animate::create(RoleAnimation);
	this->addChild(RoleSprite);

	auto RoleBody=PhysicsBody::createBox(RoleSprite->getContentSize()); 
	RoleBody->setDynamic(true);
	RoleBody->setContactTestBitmask(1);
	RoleBody->setGravityEnable(true);
	RoleBody->getShape(0)->setRestitution(0.0f); //设置弹力
	this->setPhysicsBody(RoleBody);

	RoleSprite->runAction(RepeatForever::create(RoleAnim)); 
	RoleState=RUN;



	return true;
}

void NodeRole::run()
{
	RoleState=RUN;
	RoleSprite->resume();
}

void NodeRole::jump()
{
	RoleState=JUMP;
	
	RoleSprite->pause();
	RoleSprite->setTexture(jumpTexture); //跳跃
	this->getPhysicsBody()->setVelocity(Vec2(0,ROLE_SPEED));

}

void NodeRole::slide()
{
	RoleState=SLIDE;
	RoleSprite->pause();
	RoleSprite->setTexture(slideTexture); //滑行
}