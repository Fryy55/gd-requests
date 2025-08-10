#pragma once

#include <Geode/binding/CCMenuItemSpriteExtra.hpp>


class UtilityWCell final : public CCMenuItemSpriteExtra {
public:
	enum Utility : std::uint8_t {
		GJP2
	};

	static UtilityWCell* create(Utility utility);

private:
	bool init(Utility);

	void onClick(cocos2d::CCObject*);

	// Fields
	Utility m_utility;

	static constexpr cocos2d::CCSize s_contentSize { 80.f, 100.f };
};