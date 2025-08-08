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
}