#pragma once
#include "cocos2d.h"
USING_NS_CC;

class LayerMainMenu: public Layer
{
public:
	static Scene *createScene();

	CREATE_FUNC(LayerMainMenu);
private:
	void CallBackStartItem(Ref *sender);
	void CallBackOptionItem(Ref *sender);
	void CallBackAboutItem(Ref *sender);
	void CallBackHelpItem(Ref *sender);

	virtual bool init() override;
	virtual void onEnter() override;
	virtual void onExit() override;
};