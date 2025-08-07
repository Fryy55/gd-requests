#pragma once

#include <Geode/cocos/base_nodes/CCNode.h>


class Padding final : public cocos2d::CCNode {
public:
	static Padding* create(float padding);

private:
	bool init(float);
};