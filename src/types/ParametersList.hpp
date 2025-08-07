#pragma once

#include <Geode/cocos/extensions/GUI/CCControlExtension/CCScale9Sprite.h>


class ParametersList final : public cocos2d::extension::CCScale9Sprite {
public:
	static ParametersList* create();

private:
	bool init() override;

	// Fields
	static constexpr cocos2d::CCSize s_contentSize { 215.f, 170.f };
};