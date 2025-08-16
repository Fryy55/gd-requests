#pragma once

#include <Geode/binding/CCMenuItemSpriteExtra.hpp>


class UtilityWCell final : public CCMenuItemSpriteExtra {
public:
	enum Utility : std::uint8_t {
		GJP2,
		LevelString,
		CompressLS,
		Seed2
	};

	static UtilityWCell* create(Utility utility);

private:
	bool init(Utility);

	void onClick(cocos2d::CCObject*);

	[[nodiscard]] std::string& nameToID(std::string&) const;

	void updateLevelStringBGColor(bool);

	// Fields
	Utility m_utility;
	cocos2d::extension::CCScale9Sprite* m_bg;

	static constexpr cocos2d::CCSize s_contentSize { 80.f, 100.f };
};