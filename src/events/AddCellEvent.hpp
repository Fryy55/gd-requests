#pragma once

#include <Geode/loader/Event.hpp>


struct AddCellEvent final : geode::Event {
	AddCellEvent(std::string key, std::string value) : key(std::move(key)), value(std::move(value)) {}

	std::string key;
	std::string value;
};