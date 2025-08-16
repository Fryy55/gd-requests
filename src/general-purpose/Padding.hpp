#pragma once

#include <Geode/cocos/base_nodes/CCNode.h>


class Padding final : public cocos2d::CCNode {
public:
	static Padding* create(float side);
	static Padding* create(float width, float height);

private:
	bool init(float, float);
};