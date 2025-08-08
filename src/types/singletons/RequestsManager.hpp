#pragma once

#include <Geode/loader/Mod.hpp>

#include <unordered_map>


class RequestsManager final {
public:
	static RequestsManager* get();

private:
	RequestsManager();

public:
	[[nodiscard]] std::unordered_map<std::string, std::string>* getDB() const { return m_db; }
	[[nodiscard]] bool getDebugLabelSetting() const { return m_debugLabel; }
	void updateDebugLabelSetting() { m_debugLabel = geode::Mod::get()->getSettingValue<bool>("debug-label"); }

	RequestsManager(RequestsManager const&) = delete;
	RequestsManager(RequestsManager&&) = delete;
	RequestsManager& operator=(RequestsManager const&) = delete;
	RequestsManager& operator=(RequestsManager&&) = delete;

private:
	// Fields
	std::unordered_map<std::string, std::string>* m_db;
	bool m_debugLabel;
};