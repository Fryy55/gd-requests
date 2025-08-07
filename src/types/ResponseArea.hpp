#pragma once

#include <Geode/cocos/base_nodes/CCNode.h>


class ResponseArea final : public cocos2d::CCNode {
public:
	static ResponseArea* create();

private:
	bool init() override;

	void onSend(cocos2d::CCObject*);

	// Fields
	static constexpr cocos2d::CCSize s_contentSize { 290.f, 240.f };
};