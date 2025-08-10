#pragma once

#include <Geode/ui/TextInput.hpp>


namespace req::utils {
	enum class StringType : std::uint8_t {
		Key,
		Value,
		Endpoint
	};

	[[nodiscard]] bool validateString(
		std::string const& string,
		StringType type,
		std::optional<std::string_view> oldKey = std::nullopt
	);

	void pasteClipboard(geode::TextInput* textInput);
	void copyClipboard(std::string const& string, std::string_view content);

	// EditLevelLayer and LevelInfoLayer overload
	void createCopyLSButton(GJGameLevel* level, cocos2d::CCNode* menu);
	// LevelSelectLayer overload
	void createCopyLSButton(BoomScrollLayer* scrollLayer, cocos2d::CCNode* menu);
	// SecretLayer2 overload
	void createCopyLSButton(cocos2d::CCNode* menu);
}