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
	[[nodiscard]] std::string const& getEndpoint() const { return m_endpoint; }
	void setEndpoint(std::string_view endpoint) { m_endpoint = endpoint; }

	[[nodiscard]] bool getDebugLabelSetting() const { return m_debugLabel; }
	[[nodiscard]] bool getCopyLevelStringValue() const { return m_copyLevelString; }
	bool toggleCopyLevelString();

	void updateSettings();

	RequestsManager(RequestsManager const&) = delete;
	RequestsManager(RequestsManager&&) = delete;
	RequestsManager& operator=(RequestsManager const&) = delete;
	RequestsManager& operator=(RequestsManager&&) = delete;

private:
	// Fields
	std::unordered_map<std::string, std::string>* m_db;
	std::string m_endpoint;
	bool m_debugLabel;
	bool m_copyLevelString;
};