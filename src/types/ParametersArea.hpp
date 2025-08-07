#pragma once

#include <Geode/cocos/base_nodes/CCNode.h>


class ParametersArea final : public cocos2d::CCNode {
public:
	static ParametersArea* create();

private:
	bool init() override;

	void onAdd(cocos2d::CCObject*);

	// Fields
	geode::TextInput* m_keyInput;
	geode::TextInput* m_valueInput;

	static constexpr cocos2d::CCSize s_contentSize { 220.f, 50.f };
};