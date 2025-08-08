#pragma once

#include <string>


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
}