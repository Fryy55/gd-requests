#pragma once


namespace constants {
	inline constexpr char const* urlFilter {
		"ABCDEFGHIJKLMNOPQRSTUVWXYZ"
		"abcdefghijklmnopqrstuvwxyz"
		"0123456789"
		"/:."
	};

	inline constexpr char const* valueFilter {
		"ABCDEFGHIJKLMNOPQRSTUVWXYZ"
		"abcdefghijklmnopqrstuvwxyz"
		"0123456789"
		"-_+="
	};
}