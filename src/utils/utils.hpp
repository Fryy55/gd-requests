#pragma once

#include <Geode/ui/TextInput.hpp>
#include "LimitedTextArea.hpp"


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

	void pasteClipboard(cocos2d::CCLabelBMFont* label);
	void pasteClipboard(geode::TextInput* textInput);
	void pasteClipboard(LimitedTextArea* field);
	void copyClipboard(std::string const& string, std::string_view contentName);
}