#pragma once
#include "cocos2d.h"
USING_NS_CC;


class NodeMap:public Node
{
public:
	virtual bool init() override;
	CREATE_FUNC(NodeMap);

public:
	void initMap();
	void clearMap();
};